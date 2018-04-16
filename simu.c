#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <kernel_list.h>

#define API_RTN_OK 0
#define API_RTN_ERROR -1

#define LIMIT_OF_CORES 8 /* 0 ~ 7 */
#define LIMIT_OF_PROCESS 128 /* pid 0 ~ 127 */

#define VRUNTIME_WINDOW 10 /* every 10 tick one window */

#ifndef INT8
typedef char INT8;
#endif

#ifndef UINT8
typedef unsigned char UINT8;
#endif

#ifndef INT16
typedef unsigned short INT16;
#endif

#ifndef UINT16
typedef unsigned short UINT16;
#endif

#ifndef INT32
typedef int INT32;
#endif

#ifndef UINT32
typedef unsigned int UINT32;
#endif

#ifndef INT64
typedef long long INT64;
#endif

#ifndef UINT64
typedef unsigned long long UINT64;
#endif

typedef INT8 PROC_ID;

typedef enum {
	SCHED_NORMAL,
	SCHED_FIFO,
	SCHED_BUTT
} SCHED_TYPE;

typedef enum {
	WEIGHT_LOW = 1,
	WEIGHT_MID = 2,
	WEIGHT_HIGH = 4,
	WEIGHT_NONE
} WEIGHT_VAL;

typedef struct ProcInfo_Tag {
	SCHED_TYPE type;
	UINT32 exec_start;
	UINT32 exec_length;
	WEIGHT_VAL weight;
	UINT32 priority;
} ProcInfo;

static int core[8] = {0};

struct task {
	struct ProcInfo_Tag proc_info;
	int running_cpu; /* running on cpu */
	int cpu_mask; /* cpu mask */
	int valid; /* 1 valid task */
	int end; /* 1 out task */
	int running; /* is running */
	int runned_win; /* runned ticks in on window */
	int vtime;
	int runned_time;
};

struct mnode {
	int pid;
	int time;
	struct list_head entry;
};

struct task norm_arr[128] = {0};
struct task fifo_arr[128] = {0};

struct list_head cpu_list[8];
static int inited = 0;

INT32 EnableCore(UINT32 core_id)
{
	int i;
	if (!inited) {
		inited = 1;
		for (i = 0; i < 8; i++) {
			INIT_LIST_HEAD(&cpu_list[i]);
		}
	}
	if (core_id > 7) {
		printf("core_id error\n");
		return -1;
	}
	if (core[core_id]) {
		printf("already enable core %d\n", core_id);
		return -1;
	}
	core[core_id] = 1;
	return 0;
}

INT32 AddProc(PROC_ID pid, ProcInfo proc_info)
{

	/*SCHED_TYPE type;*/
	/*UINT32 exec_start;*/
	/*UINT32 exec_length;*/
	/*WEIGHT_VAL weight;*/
	/*UINT32 priority;*/
	if (pid > 127 || pid < 0) {
		printf("pid error\n");
		return -1;
	}
	if (proc_info.type == SCHED_NORMAL) {
		if(norm_arr[pid].valid) {
			printf("already add pid %d\n", pid);
			return -1;
		}
		printf("add normal %d\n", pid);
		norm_arr[pid].proc_info.weight = WEIGHT_NONE;
		memcpy(&(norm_arr[pid].proc_info), &proc_info, sizeof(proc_info));
		norm_arr[pid].valid = 1;
		norm_arr[pid].running_cpu = 0xff;
		norm_arr[pid].cpu_mask = 0xff;
		norm_arr[pid].end = 0;
	} else if (proc_info.type == SCHED_FIFO) {
		if(fifo_arr[pid].valid) {
			printf("already add pid %d\n", pid);
			return -1;
		}
		printf("add fifo %d\n", pid);
		fifo_arr[pid].proc_info.priority = 15;
		memcpy(&(fifo_arr[pid].proc_info), &proc_info, sizeof(proc_info));
		fifo_arr[pid].valid = 1;
		fifo_arr[pid].running_cpu = 0xff;
		fifo_arr[pid].cpu_mask = 0xff;
		fifo_arr[pid].end = 0;
	} else {
		printf("proc type error\n");
		return -1;
	}
	return 0;
}

INT32 SetAffinity(PROC_ID pid, UINT32 cpusetmask)
{
	if (norm_arr[pid].valid) {
		norm_arr[pid].cpu_mask = cpusetmask;
	} else if (fifo_arr[pid].valid){
		fifo_arr[pid].cpu_mask = cpusetmask;
	} else {
		printf("error pid");
		return -1;
	}
	return 0;
}

int not_end()
{
	int i = 0;
	ProcInfo info;
	for (i = 0; i < 128; i++) {
		if (norm_arr[i].valid) {
			if (!norm_arr[i].end) {
				info = norm_arr[i].proc_info;
				/*printf("not end normal pid %d start %d length %d\n", i, info.exec_start, info.exec_length);*/
				return 1;
			}
		}
		if (fifo_arr[i].valid) {
			if (!fifo_arr[i].end) {
				info = fifo_arr[i].proc_info;
				/*printf("not end fifo pid %d start %d length %d\n", i, info.exec_start, info.exec_length);*/
				return 1;
			}
		}
	}
	return 0;
}

int schedule_one_fifo(int cpu, int time, int schedule)
{
	int task_loop;
	int little = 16;
	int to_run = -1;
	struct mnode *node;
	struct ProcInfo_Tag *info;

	/* find alreay running in this cpu */
	for (task_loop = 0; task_loop < 127; task_loop++) {
		if (!schedule) {
			if (fifo_arr[task_loop].valid && !fifo_arr[task_loop].end) {
				if (fifo_arr[task_loop].running &&
				    fifo_arr[task_loop].running_cpu == cpu &&
				    fifo_arr[task_loop].cpu_mask & (1 << cpu)) {
					printf("schedule fifo pid %d on cpu %d\n", task_loop, cpu);
					to_run = task_loop;
				}
			}
		}
	}

	if (to_run != -1) {
		goto run;
	}

	for (task_loop = 0; task_loop < 127; task_loop++) {
		/* find a valid not end */
		if (fifo_arr[task_loop].valid) {
			/*printf("fifo %d\n", fifo_arr[task_loop].valid);*/
		}
		if (fifo_arr[task_loop].valid && !fifo_arr[task_loop].end) {
			info = &(fifo_arr[task_loop].proc_info);
			/*printf("fifo pid %d start %d cur %d mask %d\n",*/
				/*task_loop, info.exec_start, time, fifo_arr[task_loop].cpu_mask & (1 << cpu));*/
			if (info->exec_start <= time && (fifo_arr[task_loop].cpu_mask & (1 << cpu))) {
				/*printf("info priority %d little %d\n", info->priority, little);*/
				if (info->priority < little) {
					to_run = task_loop;
				}
			}
		}
	}

	if (to_run == -1) {
		printf("no fifo task to run curr\n");
		return 0;
	}

run:
	node = (struct mnode *)malloc(sizeof(*node));
	node->pid = to_run;
	node->time = time;
	fifo_arr[to_run].running = 1;
	fifo_arr[to_run].running_cpu = cpu;
	info = &(fifo_arr[to_run].proc_info);
	info->exec_length--;
	printf("schedule fifo pid %d on cpu %d exec_length %d \n", to_run, cpu, info->exec_length);
	list_insert(&node->entry, &cpu_list[cpu]);
	if (info->exec_length == 0) {
		fifo_arr[to_run].end = 1;
		fifo_arr[to_run].running = 0;
	}
	return 1;
}

int schedule_one_norm(int cpu, int time, int schedule)
{
	int task_loop;
	int little = 0xfffffff - 1;
	int vtime;
	int to_run = -1;
	struct mnode *node;
	struct ProcInfo_Tag *info;

	/* find alreay running in this cpu */
	for (task_loop = 0; task_loop < 127; task_loop++) {
		if (!schedule) {
			if (norm_arr[task_loop].valid && !norm_arr[task_loop].end) {
				if (norm_arr[task_loop].running && norm_arr[task_loop].running_cpu == cpu) {
					/*printf("schedule normal pid %d on cpu %d\n", task_loop, cpu);*/
					norm_arr[task_loop].runned_win++;
					to_run = task_loop;
				}
			}
		} else {
			norm_arr[task_loop].runned_win = 0;
		}
	}

	for (task_loop = 0; task_loop < 127; task_loop++) {
		/* find a valid not end */
		if (norm_arr[task_loop].valid && !norm_arr[task_loop].end) {
			info = &(norm_arr[task_loop].proc_info);
			/*printf("normal pid %d start %d cur %d mask %d\n",*/
				/*task_loop, info.exec_start, time, norm_arr[task_loop].cpu_mask & (1 << cpu));*/
			if (info->exec_start <= time && (norm_arr[task_loop].cpu_mask & (1 << cpu))) {
				norm_arr[task_loop].runned_win++;
				vtime = (400 * norm_arr[task_loop].runned_win) / info->weight;
				/*printf("vtime %d little %d\n", vtime, little);*/
				if (vtime < little) {
					to_run = task_loop;
				}
			}
		}
	}
	if (to_run == -1) {
		printf("no normal task to run curr\n");
		return 0;
	}
run:
	node = (struct mnode *)malloc(sizeof(*node));
	node->pid = to_run;
	node->time = time;
	norm_arr[to_run].running = 1;
	norm_arr[to_run].running_cpu = cpu;
	info = &(norm_arr[to_run].proc_info);
	info->exec_length--;
	norm_arr[to_run].vtime = (400 * norm_arr[task_loop].runned_win) / info->weight;
	printf("schedule normal pid %d on cpu %d exec_length %d \n", to_run, cpu, info->exec_length);
	list_insert(&node->entry, &cpu_list[cpu]);
	if (info->exec_length == 0) {
		norm_arr[to_run].end = 1;
		norm_arr[to_run].running = 0;
	}
	return 1;
}

void SimuSchedule(void)
{
	int time_loop = 0;
	int cpu_loop = 0;
	while (not_end()) {
		for (cpu_loop = 0; cpu_loop < 8; cpu_loop++) {
			if (!core[cpu_loop])
				continue;
			if (time_loop % 10) {
				if(schedule_one_fifo(cpu_loop, time_loop, 1)) {
					printf("time [%d] fifo\n", time_loop);
				} else if (schedule_one_norm(cpu_loop, time_loop, 1)){
					printf("time [%d] normal\n", time_loop);
				} else {
					printf("time [%d] no task\n", time_loop);
				}
			} else {
				if(schedule_one_fifo(cpu_loop, time_loop, 0)) {
					printf("time [%d] fifo\n", time_loop);
				} else if (schedule_one_norm(cpu_loop, time_loop, 0)) {
					printf("time [%d] normal\n", time_loop);
				} else {
					printf("time [%d] no task\n", time_loop);
				}
			}
		}
		time_loop++;
	}
}

INT32 QueryCpuStat(UINT32 core_id, UINT32 begin_tick, UINT32 length, PROC_ID arrary[])
{
	int index = 0;
	int tick;
	int have = 0;
	int cur_pid ;
	struct list_head *curr;
	struct list_head *next;
	struct mnode *cur_node;
	for (tick = begin_tick; tick < begin_tick + length; tick++) {
		list_for_each_safe(curr, next, &cpu_list[core_id]) {
			cur_node = list_entry(curr, struct mnode, entry);
			if (cur_node->time == tick) {
				/*printf("tick %d cur time %d hava pid %d\n", tick, cur_node->time, cur_node->pid);*/
				cur_pid = cur_node->pid;
				have = 1;
			}
		}
		if (have) {
			/*printf("index %d pid %d\n", index, cur_pid);*/
			arrary[index] = cur_pid;
		} else {
			/*printf("index %d pid %d\n", index, -1);*/
			arrary[index] = -1;
		}
		index++;
		have = 0;
	}
	return 0;
}

void Clear(void)
{
	int i = 0;
	struct list_head *curr;
	struct list_head *next;
	struct mnode *cur_node;
	for (i = 0; i < 8; i++) {
		list_for_each_safe(curr, next, &cpu_list[i]) {
			cur_node = list_entry(curr, struct mnode, entry);
			list_remove(&cpu_list[i]);
			free(cur_node);
		}
	}
}

void test_demo()
{
	UINT32 cid = 0; /* core number */
	PROC_ID pid;
	INT32 ret, loop;
	ProcInfo aPIF[] = {
		/* type, exec_start, exec_length, weight, priority */
		{SCHED_FIFO, 2, 1, WEIGHT_NONE, 0}, /* pid 0 */
		{SCHED_NORMAL, 0, 4, WEIGHT_MID, 0}, /* pid 1 */
		{SCHED_NORMAL, 2, 2, WEIGHT_HIGH, 0}, /*pid 2*/
		{SCHED_NORMAL, 8, 2, WEIGHT_LOW, 0}, /*pid 3*/
	};

	PROC_ID result[100];
	PROC_ID expect[10] = {0, 2, 2, 1, 1, -1, 3, 3, -1, -1};

	ret = EnableCore(cid);
	if (API_RTN_OK != ret) {
		printf("enalbe core faile\n");
		goto Case_End;
	}

	for (pid = 0; pid < sizeof(aPIF) / sizeof(aPIF[0]); pid++) {
		ret = AddProc(pid, aPIF[pid]);
		if (ret != API_RTN_OK) {
			printf("Add proc fail\n");
			goto Case_End;
		}
	}

	ret = AddProc(0, aPIF[0]);
	if (ret == API_RTN_OK) {
		printf("add proc test faile\n");
		goto Case_End;
	}

	SimuSchedule();
	memset(result, -2, sizeof(result));
	ret = QueryCpuStat(cid, 2, 10, result);
	if (ret != API_RTN_OK) {
		printf("query fail\n");
		goto Case_End;
	}
	int i;
	for (i = 0; i < 10; i++) {
		printf("expect %d got %d\n", expect[i], result[i]);
	}
	if (memcmp(expect, result, 10)) {
		printf("query test failed\n");
		goto Case_End;
	}
	if (result[10] != -2) {
		printf("memory overflow\n");
		goto Case_End;
	}
	memset(result, -2, sizeof(result));
	ret = QueryCpuStat(cid, 0, 100, result);
	if (ret != API_RTN_OK) {
		printf("query fail\n");
		goto Case_End;
	}
	for (loop = 10; loop < 100; loop++) {
		if (result[loop] != -1) {
			printf("query test 100 failed");
		}
	}
	printf("test pass\n");
Case_End:
	Clear();
}

int main()
{
	test_demo();
}

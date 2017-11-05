#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kernel_list.c"

struct node {
	struct list_head entry;
	struct node *parent;
	char name[10];
	int type; /* 1-dir 2-file*/
}

static LIST_HEAD total_list;

static struct node *root = NULL;

struct node *get_type(int type, char *name)
{
	struct node *entry, tmp;
	struct node *local_node;
	list_for_each_safe(entry, temp, entry) {
		local_node = list_entry(entry, struct node, entry);
		printf("node type %d name %d\n", local_node->type, local_node->name);
		if (local_node->type == type && !strcmp(local_node->name, name))
			return local_node;
	}

	return NULL;
}

/*
 * 在指定的parent下创建目录
 * return 0 success
 * return -1 父目录不存在,待创建目录名已存在
 */
int create_dir(const char *parent_dir_name, const char *dir_name)
{
	struct node *parent;
	struct node *dir;
	if (root == NULL) {
		root = malloc(sizeof(*root));
		memset(root, 0, sizeof(*root));
		strcpy(root->name, "root", strlen("root"));
		list_add(&root->entry, &total_list)
	}
	
	parent = get_type(1, parent_dir_name);
	if (parent == NULL)
		return -1;

	dir = malloc(sizeof(*dir));
	memset(dir, 0, sizeof(*dir));
	strcpy(dir->name, dir_name, strlen(dir_name));
	dir->type = 1;
	dir->parent = parent;
	list_add(&dir->entry, &total_list);
}

void delete_dir(const char *dir_name)
{
	struct node *dir;	

	dir = get_type(1, dir_name);
	if (dir) {
		list_del(dir->entry);
		free(dir);
	}
}

/*
 * -1 目录名不存在,或者子目录父目录
 */
int move_dir(const char *src_dir_name, const char *dst_dir_name)
{
	struct node *src_dir;
	struct node *dst_dir;

	src_dir = get_type(1, src_dir_name);
	if (src_dir == NULL)
		return -1;

	dst_dir = get_type(1, dst_dir_name);
	if (dst_dir == NULL)
		return -1;

	src_dir->parent = dst_dir;
}

/*
 * -1 已有同文件名存在，目录名不存在
 */
int create_file(const char *dir_name, const char *file_name)
{
	struct node *dir;	
	struct node *file;	

	dir = get_type(1, dir_name);
	if (!dir)
		return -1;

	file = get_type(0, file_name);
	if (file)
		return -1;

	file = malloc(sizeof(*file));
	strcpy(file->name, file_name, strlen(file_name));
	file->type = 0;
	file->parent = dir;
	list_add(&file->entry, &total_list);
}

void deletefile(const char *file_name)
{
	struct node *file;	

	file = get_type(0, file_name);
	if (file) {
		list_del(file->entry);
		free(file);
	}
}

/*
 * 目录下文件个数
 */
unsigned int get_file_num(const char *dir_name)
{
	int i = 0;
	struct node *dir;	
	struct node *entry, tmp;
	struct node *local_node;

	dir = get_type(1, dir_name);
	if (dir == NULL)
		return 0;

	list_for_each_safe(entry, temp, entry) {
		local_node = list_entry(entry, struct node, entry);
		if (local_node->type == 0 && local_node->parent == dir) {
			i++;
		}
	}
	return i;
}

/* 释放全部内存 */
void clear(void)
{
	struct node *entry, tmp;
	struct node *local_node;
	list_for_each_safe(entry, temp, entry) {
		local_node = list_entry(entry, struct node, entry);
		printf("node type %d name %d\n", local_node->type, local_node->name);
		if (local_node->type == type && !strcmp(local_node->name, name))
			return local_node;
	}
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * 在指定的parent下创建目录
 * return 0 success
 * return -1 父目录不存在,待创建目录名已存在
 */
int create_dir(const char *parent_dir_name, const char * dir_name)
{

}

void delete_dir(const char *dir_name)
{

}

/*
 * -1 目录名不存在,或者子目录父目录
 */
int move_dir(const char *src_dir_name, const char *dst_dir_name)
{

}

/*
 * -1 已有同文件名存在，目录名不存在
 */
int create_file(const char *dir_name, const char *file_name)
{

}

void deletefile(const char *file_name)
{

}

/*
 * 目录下文件个数
 */
unsigned int get_file_num(const char *dir_name)
{

}

/* 释放全部内存 */
void clear(void)
{

}

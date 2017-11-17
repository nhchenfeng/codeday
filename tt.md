/******************************************************************************

Copyright (C), 2001-2011, Huawei Tech. Co., Ltd.

******************************************************************************
File Name     :
Version       :
Author        :
Created       : 2010/3
Last Modified :
Description   :
Function List :

History       :
1.Date        : 2010/3
Author      :
Modification: Created file

******************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct node{
	char *data;
	struct node *next;
}linklist_node;

typedef linklist_node* linkstring;

int book_num = 0;

//char *name_list[200] = {0};//The array of char pointer to store the book name

//linklist_node* head = NULL;

linklist_node head = {NULL,NULL};

/******************************************************************************************************
函数说明 ： 增加书名
原型     ： int AddBook (char* BookName);
输入参数 ： BookName 书名字符串。该字符串可能在函数外被释放，请自行分配书名的存储空间
输出参数 ： 无
返回值   ：
0  成功（如果书名在库中已存在，也返回成功，但书名不重复加入）；
-1 失败
********************************************************************************************************/
int AddBook(char *BookName)//error
{
	if ((NULL == BookName) || (strlen(BookName) > 500))
		return -1;
	char *name_ptr = BookName;
	if (*name_ptr == '\0')
		return -1;
	int word_cnt = 1;
	while (*name_ptr != '\0'){
		if (*name_ptr == ' '){
			word_cnt++;
		}
		name_ptr++;
	}
	if (word_cnt > 10)
		return -1;

	char *word_ptr = BookName;
	int word_size = 0;
	while (*word_ptr != '\0'){
		if (*word_ptr == ' '){
			word_size = 0;
		}
		word_size++;
		word_ptr++;
		if (word_size > 50)
			return -1;
	}

	if (head.next == NULL){//the book list is empty, to construct it

		linklist_node* stringnode = (linklist_node *)malloc(sizeof(linklist_node));
		stringnode->data = (char *)malloc(strlen(BookName) + 1);
		strncpy(stringnode->data, BookName, strlen(BookName) + 1);
		stringnode->next = NULL;

		head.next = stringnode;
		book_num++;

		return 0;
	}
	linklist_node* ptr = head.next;

	while ((NULL != ptr->next)){

		if ((0 == strncmp(ptr->data, BookName, strlen(BookName) + 1)))//the bookname is already exist
			return 0;
		
		if (!(0 < strcmp(ptr->next->data, BookName)) 
			&& (0 > strcmp(ptr->data, BookName)))//search the place to insert the name
			ptr = ptr->next;
		else 
			break;
	}
	if ((0 == strncmp(ptr->data, BookName, strlen(BookName) + 1)))//the bookname is already exist
		return 0;

	if (ptr == head.next){
		if (0 > strcmp(ptr->data, BookName)){
			linklist_node* insertnode = (linklist_node *)malloc(sizeof(linklist_node));
			insertnode->data = (char *)malloc(strlen(BookName) + 1);
			strncpy(insertnode->data, BookName, strlen(BookName) + 1);

			insertnode->next = ptr->next;//error
			ptr->next = insertnode;
			book_num++;
		}else{
			linklist_node* insertnode = (linklist_node *)malloc(sizeof(linklist_node));
			insertnode->data = (char *)malloc(strlen(BookName) + 1);
			strncpy(insertnode->data, BookName, strlen(BookName) + 1);
			insertnode->next = ptr;
			head.next = insertnode;
			book_num++;
		}
	}else{
		linklist_node* insertnode = (linklist_node *)malloc(sizeof(linklist_node));
		insertnode->data = (char *)malloc(strlen(BookName) + 1);
		strncpy(insertnode->data, BookName, strlen(BookName) + 1);
		insertnode->next = ptr->next;
		ptr->next = insertnode;//error
		book_num++;
	}
	if (200 < book_num)
		return -1;
	return 0;
}


/*********************************************************************************************************************
函数说明：查询库中所有书名，按照字典顺序输出
原型    ：int ListAllBooks(int* pNumber, char* result[200] );
输入参数：无
输出参数：
pNumber 返回库中书名个数（未找到则为0）
result  返回库中所有书名。按照字典顺序输出。输出到的内存空间由调用者分配，内存中存储格式请参见PPT说明。
每个字符串必须以’\0’结束。
返回值  ：0 成功；-1 失败

**********************************************************************************************************************/
int ListAllBooks(int *pNumber, char *result[200])
{

	/* 在这里实现功能 */
	if (NULL == head.next){
		*pNumber = 0;
		return -1;
	}

	linklist_node *ptr = head.next;
	int i = 0;
	while (NULL != ptr){
		int book_len = strlen(ptr->data);
		memcpy(result[i], ptr->data, book_len + 1);
		i++;
		(*pNumber)++;
		ptr = ptr->next;
	}
	return 0;

};

/*************************************************************************************************
函数说明：根据搜索条件，返回满足搜索条件的书名
原型    ：int SearchBooks(char* condition, int* pNumber, char* result[200] );
输入参数：condition 搜索条件字符串
输出参数：
pNumber 返回满足条件的书名个数（未找到则为0）
result  返回符合条件的书名。输出到的内存空间由调用者分配，内存中存储格式请参见PPT说明。
每个字符串必须以’\0’结束。
返回值  ：0 成功；-1 失败
**************************************************************************************************/
int SearchBooks(char *condition, int *pNumber, char *result[200])
{
	/* 在这里实现功能 */
	if (NULL == head.next){
		*pNumber = 0;
		return -1;
	}

	linklist_node *ptr = head.next;
	*pNumber = 0;

	char *name_ptr = condition;
	int word_cnt = 1;
	char *condition_delim[60];

	for (int i = 0; i < 10; i++)
	{
		condition_delim[i] = (char *)malloc(60);
		memset(condition_delim[i],'\0', 60);
	}

	while (*name_ptr != '\0'){
		if (*name_ptr == ' '){
			word_cnt++;
		}
		name_ptr++;
	}

	char *word_ptr = condition;

	for (int j = 0; j < word_cnt; j++){
		int chr_cnt = 0;
		while (*word_ptr != '\0'){
			if (*word_ptr == ' '){
				//word_cnt++;
				break;
			}
			word_ptr++;
			chr_cnt++;	
		}
		memcpy(condition_delim[j], word_ptr - chr_cnt, chr_cnt);
		word_ptr++;

	}
	if (word_cnt > 3)
		return -1;

	int book_cnt = 0;

	while (NULL != ptr){
		char *str = ptr->data;
		int flag = 0;
		for (int cnt = 0; cnt < word_cnt; ){//cnt == 1?
			char *ptr_first = strstr(str, condition_delim[cnt]);
			if (NULL == ptr_first){//To search the next bookname
				ptr = ptr->next;
				if (NULL == ptr)
					break;
				str = ptr->data;
				cnt = 0;
			}else {
				int condition_len =  strlen(condition_delim[cnt]);
				if ((0 == strncmp(str, ptr_first, condition_len)) && //begin word 
					((*(str + strlen(condition_delim[cnt])) == ' ') || 
					*(str + strlen(condition_delim[cnt])) == '\0')){
						cnt++;
						flag++;
				}else{

					int index = ptr_first - str - 1;
					if ((0 != strncmp(str, ptr_first, condition_len)) && //not begin word
						(*(str + index) == ' ') && ((*(str + index  + condition_len + 1) == ' ')  || 
						(*(str + index + condition_len + 1) == '\0'))){

							cnt++;
							flag++;
					}else{
						ptr = ptr->next;//next bookname
						if (NULL == ptr)
							break;
						str = ptr->data;
						cnt = 0;
					}	
				}
			}
		}

		if (flag == word_cnt){
			int book_len = strlen(ptr->data);
			memcpy(result[book_cnt], ptr->data, book_len + 1);
			(*pNumber)++;
			ptr = ptr->next;
			book_cnt++;
		}
	}
	//if (0 == *pNumber)
	//	return -1;
	return 0;
}


/*************************************************************************************************
函数说明：清空库中所有书名
原型    ：int ClearAllBooks();
输入参数：无
返回值  ：0 成功；-1 失败
**************************************************************************************************/
int ClearAllBooks()
{
	/* 在这里实现功能 */
	/* 在这里实现功能 */
	if (NULL == head.next){
		return 0;
	}

	linklist_node *ptr = head.next;
	head.next = NULL;
	while (NULL != ptr){
		linklist_node *temp = ptr->next;	
		free(ptr);
		ptr = temp;
	}
	book_num = 0;
	return 0;
}

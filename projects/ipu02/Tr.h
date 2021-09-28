/**************************************************
*
*	该模块能够再编译器确定翻译表的内容
*
*	此文件应该发布给外部使用，
*	使用时，修改 TR_TABLE_FILE_NAME 位仪表文件
*	LANGUAGE_COUNT应该定义为>=语言数量，不能小于。
*	允许为了方便直接定义为10这样的大数，但可能会牺牲少量内存
*
***************************************************/
#pragma once
#include <cassert>
#include <stdio.h>

#define TR_TABLE_FILE_NAME	"TrTable.h"
#define TR_LANGUAGE_COUNT	4

//定义Id
#define TR_ITEM(id, ...) id,
enum
{
#include TR_TABLE_FILE_NAME
	TR_ID_MAX,
};

//定义文本表
#undef TR_ITEM
#define TR_ITEM(id, ...) { __VA_ARGS__ },
static const char * const g_trStrMap[TR_ID_MAX][TR_LANGUAGE_COUNT] =
{
#include TR_TABLE_FILE_NAME
};

inline const char *get(int lan, int id) 
{
	assert(lan < TR_LANGUAGE_COUNT);
	assert(id < TR_ID_MAX); 
	return g_trStrMap[id][lan];
}
#define	TR(lan, id)						(get(lan, id))


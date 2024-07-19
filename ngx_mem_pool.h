#pragma once
#include"config.h"
/*
	移植nginx内存池源码，用我的cpp实现
*/

//清理函数的类型
using ngx_pool_cleanup_pt = void(*)(void* data);
struct ngx_pool_cleanup_s {
	ngx_pool_cleanup_pt handler;			//保存了执行清理操作的回调函数
	void*				data;				//传递给回调函数的操作
	ngx_pool_cleanup_s* next;				//所有的cleanup操作都被串在一条链表上
};

/*
	大块内存的头部信息
*/
struct ngx_pool_large_s {
	ngx_pool_large_s* next;			//所有的大块内存分配也是被串在一条链表上
	void*			  alloc;		//保存分配出去的大块内存的起始地址
};

/*
	分配小块内存的内存池的头部数据信息
*/
struct ngx_pool_s;
struct ngx_pool_data_t {
	u_char*     last;			//小块内存池的起始地址
	u_char*     end;			//小块内存池的结尾地址
	ngx_pool_s* next;			//链表形式
	ngx_uint_t  failed;			//小块内存池分配内存失败的次数
};

/*
	ngx内存池的头部信息和管理成员信息
*/
struct ngx_pool_s {
	ngx_pool_data_t			  d;		//存储的是当前小块内存池的使用情况
	size_t				    max;		//存储的是小块内存和大块内存的分界线
	ngx_pool_s*			current;		//指向第一个提供小块内存分配的小块内存池
	ngx_pool_large_s*	  large;		//指向大块内存（链表）的人口地址
	ngx_pool_cleanup_s* cleanup;		//指向所有预制的cleanup函数的链表
};

class ngx_mem_pool {
public:
	bool ngx_create_pool(size_t size);
	void* ngx_palloc(size_t size);
	void* ngx_pnalloc(size_t size);
	void* ngx_pcalloc(size_t size);
	void ngx_pfree(void* p);
	void ngx_reset_pool();
	void ngx_destroy_pool();
	ngx_pool_cleanup_s* ngx_pool_cleanup_add(size_t size);
private:
	void* ngx_palloc_small(size_t size, ngx_uint_t align);
	void* ngx_palloc_large(size_t size);
	void* ngx_palloc_block(size_t size);

	ngx_pool_s* pool_;						//指向ngx内存池的人口指针
};
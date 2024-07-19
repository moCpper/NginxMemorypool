#pragma once
#include"config.h"
/*
	��ֲnginx�ڴ��Դ�룬���ҵ�cppʵ��
*/

//������������
using ngx_pool_cleanup_pt = void(*)(void* data);
struct ngx_pool_cleanup_s {
	ngx_pool_cleanup_pt handler;			//������ִ����������Ļص�����
	void*				data;				//���ݸ��ص������Ĳ���
	ngx_pool_cleanup_s* next;				//���е�cleanup������������һ��������
};

/*
	����ڴ��ͷ����Ϣ
*/
struct ngx_pool_large_s {
	ngx_pool_large_s* next;			//���еĴ���ڴ����Ҳ�Ǳ�����һ��������
	void*			  alloc;		//��������ȥ�Ĵ���ڴ����ʼ��ַ
};

/*
	����С���ڴ���ڴ�ص�ͷ��������Ϣ
*/
struct ngx_pool_s;
struct ngx_pool_data_t {
	u_char*     last;			//С���ڴ�ص���ʼ��ַ
	u_char*     end;			//С���ڴ�صĽ�β��ַ
	ngx_pool_s* next;			//������ʽ
	ngx_uint_t  failed;			//С���ڴ�ط����ڴ�ʧ�ܵĴ���
};

/*
	ngx�ڴ�ص�ͷ����Ϣ�͹����Ա��Ϣ
*/
struct ngx_pool_s {
	ngx_pool_data_t			  d;		//�洢���ǵ�ǰС���ڴ�ص�ʹ�����
	size_t				    max;		//�洢����С���ڴ�ʹ���ڴ�ķֽ���
	ngx_pool_s*			current;		//ָ���һ���ṩС���ڴ�����С���ڴ��
	ngx_pool_large_s*	  large;		//ָ�����ڴ棨�������˿ڵ�ַ
	ngx_pool_cleanup_s* cleanup;		//ָ������Ԥ�Ƶ�cleanup����������
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

	ngx_pool_s* pool_;						//ָ��ngx�ڴ�ص��˿�ָ��
};
    各种成员函数的作用：
```c++
    //创建指定size大小的内存池但不超过1个页面大小
    bool ngx_mem_pool::ngx_create_pool(size_t size);
    //考虑内存字节对齐，从内存池申请size大小的内存
    void* ngx_mem_pool::ngx_palloc(size_t size);
    //不考虑内存对齐的情况
    void* ngx_mem_pool::ngx_pnalloc(size_t size);
    //初始化为0
    void* ngx_mem_pool::ngx_pcalloc(size_t size);
    //释放大块内存
    void ngx_mem_pool::ngx_pfree(void* p);
    //内存重置函数
    void ngx_mem_pool::ngx_reset_pool();
    //内存池的销毁函数
    void ngx_mem_pool::ngx_destroy_pool();
    //添加回调清理操作函数
    ngx_pool_cleanup_s* ngx_mem_pool::ngx_pool_cleanup_add(size_t size);
    //小块内存分配
    void* ngx_mem_pool::ngx_palloc_small(size_t size, ngx_uint_t align);

    //大块内存分配
    void* ngx_mem_pool::ngx_palloc_large(size_t size);

    //分配新的小块内存池
    void* ngx_mem_pool::ngx_palloc_block(size_t size);
```

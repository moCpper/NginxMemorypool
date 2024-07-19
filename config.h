#pragma once

#include<cstdlib>
#include<memory.h>

using u_char = unsigned char;
using ngx_uint_t = unsigned int;

//Ĭ��һ������ҳ���С4k
const int ngx_pagesize = 4096;

#define NGX_ALIGNMENT sizeof(unsigned long)

//�ֽڶ���
#define ngx_align(d, a)     (((d) + (a - 1)) & ~(a - 1))
#define ngx_align_ptr(p, a)                                                   \
    (u_char *) (((uintptr_t) (p) + ((uintptr_t) a - 1)) & ~((uintptr_t) a - 1))

#define ngx_memzero(buf, n)       (void) ::memset(buf, 0, n)

//ngxС���ڴ�ؿɷ�������ռ�
#define NGX_MAX_ALLOC_FROM_POOL  (ngx_pagesize - 1)

#define NGX_DEFAULT_POOL_SIZE    (16 * 1024)    //16k ��ʾһ��Ĭ��ngx�ڴ�ؿ��ٵĴ�С

#define NGX_POOL_ALIGNMENT       16
#define NGX_MIN_POOL_SIZE                                                     \
    ngx_align((sizeof(ngx_pool_t) + 2 * sizeof(ngx_pool_large_t)),            \
              NGX_POOL_ALIGNMENT)


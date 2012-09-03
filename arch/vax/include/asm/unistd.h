#if !defined(_VAX_UNISTD_H) || defined(__SYSCALL)
#define _VAX_UNISTD_H

#define sys_mmap2 sys_mmap_pgoff

#include <asm-generic/unistd.h>

#endif

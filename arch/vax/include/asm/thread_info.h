#ifndef _VAX_THREAD_INFO_H
#define _VAX_THREAD_INFO_H

#ifndef __ASSEMBLY__
#include <asm/types.h>
#include <asm/processor.h>
#endif

#define THREAD_SIZE_ORDER	0
#define THREAD_SIZE		(PAGE_SIZE << THREAD_SIZE_ORDER)

#ifndef __ASSEMBLY__

typedef unsigned long mm_segment_t;

struct thread_info {
	struct task_struct	*task;		/* main task structure */
	struct exec_domain	*exec_domain;	/* execution domain */
	unsigned long		flags;		/* low level flags */
	__u32			cpu;		/* current CPU */
	__s32			preempt_count;	/* 0 => preemptable, <0 => BUG */
	mm_segment_t		addr_limit;	/* thread address space:
						 *  0-0x7FFFFFFF for user-thread
						 *  0-0xFFFFFFFF for kernel-thread
						 */
	struct restart_block	restart_block;
	__u8			supervisor_stack[0];
};

/*
 * macros/functions for gaining access to the thread information structure
 *
 * preempt_count needs to be 1 initially, until the scheduler is functional.
 */
#ifndef __ASSEMBLY__
#define INIT_THREAD_INFO(tsk)				\
{							\
	.task		= &tsk,				\
	.exec_domain	= &default_exec_domain,		\
	.flags		= 0,				\
	.cpu		= 0,				\
	.preempt_count	= 1,				\
	.addr_limit	= KERNEL_DS,			\
	.restart_block  = {				\
			  .fn = do_no_restart_syscall,	\
	},						\
}

#define init_thread_info	(init_thread_union.thread_info)

static inline struct thread_info *current_thread_info(void)
{
	/* XXX: Use kernel stack pointer ("KSP") */
	return NULL;
}

#define get_thread_info(ti) get_task_struct((ti)->task)
#define put_thread_info(ti) put_task_struct((ti)->task)

#endif /* !__ASSEMBLY__ */

/*
 * Thread information flags:
 */
#define TIF_SYSCALL_TRACE	0	/* syscall trace active */
#define TIF_NOTIFY_RESUME	1	/* resumption notification requested */
#define TIF_SIGPENDING		2	/* signal pending */
#define TIF_NEED_RESCHED	3	/* rescheduling necessary */
#define TIF_MEMDIE		4
#define TIF_RESTORE_SIGMASK	5
#define TIF_POLLING_NRFLAG	17	/* true if poll_idle() is polling TIF_NEED_RESCHED */

#define _TIF_SYSCALL_TRACE	(1 << TIF_SYSCALL_TRACE)
#define _TIF_NOTIFY_RESUME	(1 << TIF_NOTIFY_RESUME)
#define _TIF_SIGPENDING		(1 << TIF_SIGPENDING)
#define _TIF_NEED_RESCHED	(1 << TIF_NEED_RESCHED)
#define _TIF_MEMDIE		(1 << TIF_MEMDIE)
#define _TIF_RESTORE_SIGMASK	(1 << TIF_RESTORE_SIGMASK)
#define _TIF_POLLING_NRFLAG	(1 << TIF_POLLING_NRFLAG)

#endif

#endif

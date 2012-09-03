#ifndef _VAX_MMU_CONTEXT_H
#define _VAX_MMU_CONTEXT_H

#include <asm-generic/mm_hooks.h>

extern int init_new_context(struct task_struct *tsk, struct mm_struct *mm);

extern void destroy_context(struct mm_struct *mm);

extern void switch_mm(struct mm_struct *prev, struct mm_struct *next,
		      struct task_struct *tsk);

#define deactivate_mm(tsk, mm) do { } while (0)

#define activate_mm(prev, next) switch_mm((prev), (next), NULL)

static inline void enter_lazy_tlb(struct mm_struct *mm, struct task_struct *tsk)
{
}

#endif

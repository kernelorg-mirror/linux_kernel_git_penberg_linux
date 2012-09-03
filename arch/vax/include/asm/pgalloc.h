#ifndef __VAX_PGALLOC_H
#define __VAX_PGALLOC_H

#include <linux/memblock.h>
#include <linux/bootmem.h>
#include <linux/threads.h>
#include <linux/mm.h>

#include <asm/page.h>

extern int mem_init_done;

#define pmd_populate_kernel(mm, pmd, pte) \
	set_pmd(pmd, __pmd(_KERNPG_TABLE + __pa(pte)))

static inline void
pmd_populate(struct mm_struct *mm, pmd_t * pmd, struct page *pte)
{
	set_pmd(pmd,
		__pmd(_KERNPG_TABLE +
		      ((unsigned long)page_to_pfn(pte) << (unsigned long)
		       PAGE_SHIFT)));
}

/*
 * Allocate and free page tables.
 */
static inline pgd_t *pgd_alloc(struct mm_struct *mm)
{
	pgd_t *ret;

	ret = (pgd_t *) __get_free_page(GFP_KERNEL);
	if (!ret)
		return NULL;

	memset(ret, 0, USER_PTRS_PER_PGD * sizeof(pgd_t));

	memcpy(ret + USER_PTRS_PER_PGD, swapper_pg_dir + USER_PTRS_PER_PGD,
	       (PTRS_PER_PGD - USER_PTRS_PER_PGD) * sizeof(pgd_t));

	return ret;
}

static inline void pgd_free(struct mm_struct *mm, pgd_t * pgd)
{
	free_page((unsigned long)pgd);
}

extern pte_t *pte_alloc_one_kernel(struct mm_struct *mm, unsigned long address);

static inline struct page *pte_alloc_one(struct mm_struct *mm,
					 unsigned long address)
{
	struct page *pte;

	pte = alloc_pages(GFP_KERNEL | __GFP_REPEAT, 0);
	if (pte)
		clear_page(page_address(pte));

	return pte;
}

static inline void pte_free_kernel(struct mm_struct *mm, pte_t * pte)
{
	free_page((unsigned long)pte);
}

static inline void pte_free(struct mm_struct *mm, struct page *pte)
{
	__free_page(pte);
}

#define __pte_free_tlb(tlb, pte, addr) tlb_remove_page((tlb), (pte))
#define pmd_pgtable(pmd) pmd_page(pmd)

#define check_pgt_cache()          do { } while (0)

#endif

#ifndef _VAX_PGTABLE_H
#define _VAX_PGTABLE_H

#include <asm-generic/pgtable-nopmd.h>

#define VMALLOC_START	(PAGE_OFFSET)
#define VMALLOC_END	(PAGE_OFFSET)

#include <asm-generic/pgtable.h>

#define _PAGE_VALID	(1<<31)		/* Mapping valid */
#define _PAGE_MODIFY	(1<<26)		/* Hardware modify bit */

/*
 * Hardware page protection bits (27:30):
 */

#define _PAGE_KW	(0x02 << 27)	/* 0010 */
#define _PAGE_KR	(0x03 << 27)	/* 0011 */
#define _PAGE_UW	(0x04 << 27)	/* 0100 */
#define _PAGE_URKW	(0x0e << 27)	/* 1110 */
#define _PAGE_UR	(0x0f << 27)	/* 1111 */
#define _PAGE_SR	(0x0b << 27)	/* 1011 */

/*
 * Linux specific bits:
 */

#define _PAGE_ACCESSED	(1<<23)
#define _PAGE_DIRTY	_PAGE_MODIFY

#define _PFN_MASK	0x001FFFFF
#define _PAGE_TABLE	(_PAGE_VALID | _PAGE_DIRTY | _PAGE_ACCESSED | _PAGE_UW )
#define _KERNPG_TABLE	(_PAGE_VALID | _PAGE_DIRTY | _PAGE_ACCESSED | _PAGE_KW )

#define _PAGE_CHG_MASK	(_PFN_MASK | _PAGE_ACCESSED | _PAGE_DIRTY)

#define PAGE_PROT_MASK	0x78000000

#define PAGE_NONE	__pgprot(_PAGE_VALID | _PAGE_ACCESSED)
#define PAGE_SHARED	__pgprot(_PAGE_VALID | _PAGE_ACCESSED | _PAGE_UW)
#define PAGE_COPY	__pgprot(_PAGE_VALID | _PAGE_ACCESSED | _PAGE_UR)

#define PAGE_READONLY	__pgprot(_PAGE_VALID | _PAGE_ACCESSED | _PAGE_UR)
#define PAGE_KERNEL	__pgprot(_PAGE_VALID | _PAGE_KW | _PAGE_DIRTY | _PAGE_ACCESSED)
#define PAGE_KRO	__pgprot(_PAGE_VALID | _PAGE_KR | _PAGE_DIRTY | _PAGE_ACCESSED)

#endif

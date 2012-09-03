#ifndef _VAX_IO_H
#define _VAX_IO_H

#include <asm-generic/io.h>

extern void __iomem *__ioremap(phys_addr_t offset, unsigned long size,
			       pgprot_t prot);

static inline void __iomem *ioremap(phys_addr_t offset, unsigned long size)
{
	return __ioremap(offset, size, PAGE_KERNEL);
}

static inline void __iomem *ioremap_nocache(phys_addr_t offset,
					    unsigned long size)
{
	return __ioremap(offset, size, __pgprot(pgprot_val(PAGE_KERNEL)));
}

extern void iounmap(void *addr);

#endif

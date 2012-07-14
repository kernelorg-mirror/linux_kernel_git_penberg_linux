/*
 * VAX kernel startup code
 */

#include <linux/linkage.h>
#include <linux/init.h>

	__INIT
ENTRY(stext)
	/* Generic kernel entry */
	calls	$0, start_kernel

	/* Not reached */
	halt

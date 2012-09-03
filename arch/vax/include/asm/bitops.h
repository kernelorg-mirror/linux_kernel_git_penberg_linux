#ifndef _VAX_BITOPS_H
#define _VAX_BITOPS_H

#include <linux/compiler.h>
#include <asm/byteorder.h>
#include <asm/atomic.h>

#ifdef __KERNEL__

#define smp_mb__before_clear_bit()	barrier()
#define smp_mb__after_clear_bit()	barrier()

/**
 * test_and_set_bit - Set a bit and return its old value
 * @nr: Bit to set
 * @addr: Address to count from
 *
 * This operation is atomic and cannot be reordered.
 * It also implies a memory barrier.
 */
static inline int test_and_set_bit(int nr, volatile void *addr)
{
	int oldbit;

	/* There are interlocked versions of bbss and bbcs we could use... */
	__asm__ __volatile__(
	"	clrl	%0			\n"
	"	bbcs	%2, %1, 1f		\n"
	"	incl	%0			\n"
	"1:					\n"
	: "=&r" (oldbit),
	  "=m" (addr)
	: "r" (nr)
	: "memory");

	return oldbit;
}

/**
 * test_and_clear_bit - Clear a bit and return its old value
 * @nr: Bit to set
 * @addr: Address to count from
 *
 * This operation is atomic and cannot be reordered.
 * It also implies a memory barrier.
 */
static inline int test_and_clear_bit(int nr, volatile void *addr)
{
	int oldbit;

	__asm__ __volatile__(
	"	clrl	%0			\n"
	"	bbcc	%2, %1, 1f		\n"
	"	incl	%0			\n"
	"1:					\n"
	: "=&r" (oldbit),
	  "=m" (addr)
	: "ir" (nr)
	: "memory");

	return oldbit;
}

/**
 * test_and_change_bit - Change a bit and return its new value
 * @nr: Bit to set
 * @addr: Address to count from
 *
 * This operation is atomic and cannot be reordered.
 * It also implies a memory barrier.
 */
static inline int test_and_change_bit(int nr, volatile void *addr)
{
	int oldbit;

	__asm__ __volatile__(
	"	clrl	%0			\n"
	"	bbsc	%2. %1, 4f		\n"
	"	incl	%0			\n"
	"	bbcs	%2, %1,4f		\n"
	"4:					\n"
	: "=&r" (oldbit),
	  "=m" (addr)
	: "ir" (nr)
	: "memory");

	return oldbit;
}

/*
 * Atomic, but doesn't care about the return value.
 * Rewrite later to save a cycle or two.
 */

static inline void clear_bit(int nr, volatile void *addr)
{
	test_and_clear_bit(nr, addr);
}

static inline void set_bit(int nr, volatile void *addr)
{
	test_and_set_bit(nr, addr);
}

static inline void change_bit(int nr, volatile void *addr)
{
	test_and_change_bit(nr, addr);
}

/*
 * These are allowed to be non-atomic.  In fact the generic flavors are
 * in non-atomic.h.  Would it be better to use intrinsics for this?
 *
 * OK, writes in our architecture do not invalidate LL/SC, so this has to
 * be atomic, particularly for things like slab_lock and slab_unlock.
 *
 */
static inline void __clear_bit(int nr, volatile unsigned long *addr)
{
	test_and_clear_bit(nr, addr);
}

static inline void __set_bit(int nr, volatile unsigned long *addr)
{
	test_and_set_bit(nr, addr);
}

static inline void __change_bit(int nr, volatile unsigned long *addr)
{
	test_and_change_bit(nr, addr);
}

/*  Apparently, at least some of these are allowed to be non-atomic  */
static inline int __test_and_clear_bit(int nr, volatile unsigned long *addr)
{
	return test_and_clear_bit(nr, addr);
}

static inline int __test_and_set_bit(int nr, volatile unsigned long *addr)
{
	return test_and_set_bit(nr, addr);
}

static inline int __test_and_change_bit(int nr, volatile unsigned long *addr)
{
	return test_and_change_bit(nr, addr);
}

static inline int __test_bit(int nr, const volatile void *addr)
{
	int oldbit;

	__asm__ __volatile__(
	"	clrl	%0			\n"
	"	bbc	%2, %1, 1f		\n"
	"	incl	%0			\n"
	"1:					\n"
	: "=&r" (oldbit)
	: "m" (addr),
	  "ir" (nr));

	return oldbit;
}

#define test_bit(nr, addr) __test_bit(nr, addr)

/**
 * ffz - find first zero in word.
 * @word: The word to search
 *
 * Undefined if no zero exists, so code should check against ~0UL first.
 * (VAX)
 * We could check the Z condition code bit if we wanted to check against
 * the ~OUL case, but this interface is designed for intel. Nuff sed.
 */
static inline unsigned long ffz(unsigned long word)
{
	__asm__(
	"	ffc	$0, $32, %1, %0		\n"
	: "=rm" (word)
	: "rm" (word));

	return word;
}

/**
 * ffs - find first bit set
 * @x: the word to search
 *
 * This is defined the same way as
 * the libc and compiler builtin ffs routines, therefore
 * differs in spirit from the above ffz (man ffs).
 */
static inline int ffs(int x)
{
	int r;

	__asm__(
	"	ffs	$0, $32, %1, %0		\n"
	"	bnequ	1f			\n"
	"	movl	$-1, %0			\n"
	"1:					\n"
	: "=ir" (r)
	: "mr" (x));

	return r + 1;
}

/**
 * __ffs - find first bit in word.
 * @word: The word to search
 *
 * Undefined if no bit exists, so code should check against 0 first.
 */
static inline unsigned long __ffs(unsigned long word)
{
	__asm__(
	"	ffs	$0, $32, %1, %0		\n"
	: "=rm" (word)
	: "rm" (word));

	return word;
}

#include <asm-generic/bitops/fls.h>
#include <asm-generic/bitops/__fls.h>

#include <asm-generic/bitops/lock.h>
#include <asm-generic/bitops/find.h>

#include <asm-generic/bitops/fls64.h>
#include <asm-generic/bitops/sched.h>
#include <asm-generic/bitops/hweight.h>

#include <asm-generic/bitops/le.h>
#include <asm-generic/bitops/ext2-atomic.h>

#endif /* __KERNEL__ */
#endif

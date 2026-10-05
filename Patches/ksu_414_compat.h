#ifndef __KSU_414_COMPAT_H
#define __KSU_414_COMPAT_H

#include <linux/version.h>

/* syscall_fn_t: upstream only typedefs for x86_64 (sys_call_ptr_t is 5.9+) */
#if defined(__aarch64__) && !defined(__KSU_SYSCALL_FN_T)
#define __KSU_SYSCALL_FN_T
typedef long (*syscall_fn_t)(const struct pt_regs *);
#endif

/* MODULE_IMPORT_NS: introduced in 5.4-ish era */
#include <linux/module.h>
#ifndef MODULE_IMPORT_NS
#define MODULE_IMPORT_NS(x)
#endif

/* strncpy_from_user_nofault: named strncpy_from_unsafe_user before 5.8 */
#if LINUX_VERSION_CODE < KERNEL_VERSION(5, 8, 0)
#include <linux/uaccess.h>
#define strncpy_from_user_nofault(dst, src, len) strncpy_from_unsafe_user(dst, src, len)
#endif

/* ksys_close: removed in 5.9; 4.14 has sys_close via ksys_ namespace */
#if LINUX_VERSION_CODE < KERNEL_VERSION(5, 9, 0)
#include <linux/syscalls.h>
#define ksys_close(fd) sys_close(fd)
#endif

/* linux/pgtable.h only exists 5.8+ */
#if LINUX_VERSION_CODE < KERNEL_VERSION(5, 8, 0)
#include <asm/pgtable.h>
#else
#include <linux/pgtable.h>
#endif

#endif /* __KSU_414_COMPAT_H */

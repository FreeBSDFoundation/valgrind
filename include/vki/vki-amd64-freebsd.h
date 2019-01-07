/*
   This file is part of Valgrind, a dynamic binary instrumentation
   framework.

   Copyright (C) 2000-2005 Julian Seward 
      jseward@acm.org

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public License as
   published by the Free Software Foundation; either version 2 of the
   License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
   02111-1307, USA.

   The GNU General Public License is contained in the file COPYING.
*/

#ifndef __VKI_AMD64_FREEBSD_H
#define __VKI_AMD64_FREEBSD_H

/* PAGE_SHIFT determines the page size. */
#define VKI_PAGE_SHIFT	12
#define VKI_PAGE_SIZE	(1UL << VKI_PAGE_SHIFT)
#define VKI_MAX_PAGE_SHIFT      VKI_PAGE_SHIFT
#define VKI_MAX_PAGE_SIZE       VKI_PAGE_SIZE

#define	VKI_MINSIGSTKSZ	2048

//----------------------------------------------------------------------
// sys/_sigset.h
//----------------------------------------------------------------------
#define	_VKI_NSIG		128
#define	_VKI_NSIG_WORDS		4
#define	_VKI_NSIG_BPW		((_VKI_NSIG) / (_VKI_NSIG_WORDS))

typedef struct {
	vki_uint32_t	sig[_VKI_NSIG_WORDS];
} vki_sigset_t;

struct _vki_fpstate {
	unsigned short 	cwd;
	unsigned short	swd;
	unsigned short	twd;
	unsigned short	fop;
	unsigned long	rip;
	unsigned long	rdp;
	unsigned int	mxcsr;
	unsigned int	mxcsr_mask;
	unsigned int	st_space[32];	/* 8*16 bytes for each FP-reg */
	unsigned int	xmm_space[64];	/* 16*16 bytes for each XMM-reg */
	unsigned int	reserved2[24];
};

struct vki_sigcontext {
	vki_sigset_t mask;
	long    onstack;
	long    rdi;
	long    rsi;
	long    rdx;
	long    rcx;
	long    r8;
	long    r9;
	long    rax;
	long    rbx;
	long    rbp;
	long    r10;
	long    r11;
	long    r12;
	long    r13;
	long    r14;
	long    r15;
	long    trapno;
	long    addr;
	long    flags;
	long    err;
	long    rip;
	long    cs;
	long    rflags;
	long    rsp;
	long    ss;
	long    len;                 /* sizeof(mcontext_t) */
	long	fpformat;
	long	ownedfp;
	struct _vki_fpstate fpstate;
	long	spare2[8];
};

/*
 * Retrieved from src/sys/amd64/include/reg.h
 * Note that on 8.x trapno and err are no-more meaningful, but we
 * don't set them anyway.
 */
struct vki_user_regs_struct {
	vki_register_t r15;
	vki_register_t r14;
	vki_register_t r13;
	vki_register_t r12;
	vki_register_t r11;
	vki_register_t r10;
	vki_register_t r9;
	vki_register_t r8;
	vki_register_t rdi;
	vki_register_t rsi;
	vki_register_t rbp;
	vki_register_t rbx;
	vki_register_t rdx;
	vki_register_t rcx;
	vki_register_t rax;
	vki_register_t trapno;
	vki_register_t err;
	vki_register_t rip;
	vki_register_t cs;
	vki_register_t rflags;
	vki_register_t rsp;
	vki_register_t ss;
};

struct vki_reg_struct {
	vki_register_t	r_r15;
	vki_register_t	r_r14;
	vki_register_t	r_r13;
	vki_register_t	r_r12;
	vki_register_t	r_r11;
	vki_register_t	r_r10;
	vki_register_t	r_r9;
	vki_register_t	r_r8;
	vki_register_t	r_rdi;
	vki_register_t	r_rsi;
	vki_register_t	r_rbp;
	vki_register_t	r_rbx;
	vki_register_t	r_rdx;
	vki_register_t	r_rcx;
	vki_register_t	r_rax;
	vki_uint32_t	r_trapno;
	vki_uint16_t	r_fs;
	vki_uint16_t	r_gs;
	vki_uint32_t	r_err;
	vki_uint16_t	r_es;
	vki_uint16_t	r_ds;
	vki_register_t	r_rip;
	vki_register_t	r_cs;
	vki_register_t	r_rflags;
	vki_register_t	r_rsp;
	vki_register_t	r_ss;
};

struct vki_fpreg {
	unsigned long	fpr_env[4];
	unsigned char	fpr_acc[8][16];
	unsigned char	fpr_xacc[16][16];
	unsigned long	fpr_spare[12];
};

struct vki_dbreg {
	unsigned long  dr[16];
};

typedef vki_register_t vki_elf_greg_t;
typedef struct _vki_fpstate vki_elf_fpregset_t;

#define VKI_AT_SYSINFO		32
#define	VKI_ELF_NGREG							\
	(sizeof (struct vki_user_regs_struct) / sizeof(vki_elf_greg_t))

typedef vki_elf_greg_t vki_elf_gregset_t[VKI_ELF_NGREG];

struct vki_mcontext {
	vki_register_t	onstack;	/* XXX - sigcontext compat. */
	vki_register_t	rdi;		/* machine state (struct trapframe) */
	vki_register_t	rsi;
	vki_register_t	rdx;
	vki_register_t	rcx;
	vki_register_t	r8;
	vki_register_t	r9;
	vki_register_t	rax;
	vki_register_t	rbx;
	vki_register_t	rbp;
	vki_register_t	r10;
	vki_register_t	r11;
	vki_register_t	r12;
	vki_register_t	r13;
	vki_register_t	r14;
	vki_register_t	r15;
	vki_register_t	trapno;
	vki_register_t	addr;
	vki_register_t	flags;
	vki_register_t	err;
	vki_register_t	rip;
	vki_register_t	cs;
	vki_register_t	rflags;
	vki_register_t	rsp;
	vki_register_t	ss;

	long		len;
	long		fpformat;
	long		ownedfp;
	struct _vki_fpstate	fpstate;
	long		spare2[8];
};

#define VKI_FPFMT_NODEV		0x10000
#define VKI_FPFMT_XMM		0x10002

#define VKI_FPOWNED_NONE	0x20000
#define VKI_FPOWNED_FPU		0x20001
#define VKI_FPOWNED_PCB		0x20002

struct vki_sigaction_base {
        void    (*ksa_handler)(int);
        int          sa_flags;
        vki_sigset_t sa_mask;           /* mask last for extensibility */
};
typedef  struct vki_sigaction_base  vki_sigaction_toK_t;
typedef  struct vki_sigaction_base  vki_sigaction_fromK_t;

#endif // __VKI_AMD64_FREEBSD_H

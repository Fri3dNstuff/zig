/*	$NetBSD: proc.h,v 1.15 2021/03/07 14:31:53 rin Exp $	*/

/*-
 * Copyright (C) 1995, 1996 Wolfgang Solfrank.
 * Copyright (C) 1995, 1996 TooLs GmbH.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by TooLs GmbH.
 * 4. The name of TooLs GmbH may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY TOOLS GMBH ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL TOOLS GMBH BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef _POWERPC_PROC_H_
#define _POWERPC_PROC_H_

#ifdef _KERNEL_OPT
#include "opt_modular.h"
#include "opt_ppcarch.h"
#endif

/*
 * Machine-dependent part of the lwp structure
 */
struct mdlwp {
	volatile int md_flags;
	volatile int md_astpending;
	struct trapframe *md_utf;		/* user trampframe */
};

struct trapframe;

struct mdproc {
	void (*md_syscall)(struct trapframe *);
#if defined(PPC_BOOKE) || defined(PPC_IBM4XX) || \
    ((defined(MODULAR) || defined(_MODULE)) && !defined(_LP64))
	vaddr_t md_ss_addr[2];
	uint32_t md_ss_insn[2];
#endif
};

#ifdef _KERNEL
#define	LWP0_CPU_INFO	&cpu_info[0]
#define	LWP0_MD_INITIALIZER {	\
		.md_flags = 0, \
		.md_utf = (void *)0xdeadbeef, \
	}
#endif /* _KERNEL */

#endif /* _POWERPC_PROC_H_ */
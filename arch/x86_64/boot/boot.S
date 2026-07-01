/* SPDX-License-Identifier: AGPL-3.0-or-later */
/* Copyright 2026 KasuganoMeow */
/*
This file is part of Meow.

Meow is free software: you can redistribute it and/or modify it under the terms of
the GNU Affero General Public License as published by the Free Software Foundation, 
either version 3 of the License, or (at your option) any later version.

Meow is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
PURPOSE. See the GNU Affero General Public License for more details.

You should have received a copy of the GNU Affero General Public License along with 
Meow. If not, see <https://www.gnu.org/licenses/>.
*/

.code32

#define ASM_FILE   1
#include <meow/multiboot2.h>

/* Although the GNU AS automatically resolves symbols at link time, 
   it is good practice to list external symbols. */
.extern pml4
.extern boot_gdt_pointer
.extern kernel_main

.section .bss
.align 16
.globl stack_bottom
stack_bottom:
    .space 16384
.globl stack_top
stack_top:

.section .text

.globl start, _start
start:
_start:
	jmp multiboot_entry

multiboot_header:
	.align 8
	.long MULTIBOOT2_HEADER_MAGIC
	.long MULTIBOOT_ARCHITECTURE_I386
	.long multiboot_header_end - multiboot_header
	.long -(MULTIBOOT2_HEADER_MAGIC + MULTIBOOT_ARCHITECTURE_I386 + \
        (multiboot_header_end - multiboot_header))
multiboot_header_end:
	.short MULTIBOOT_HEADER_TAG_END
    .short 0
    .long 8

multiboot_entry:
	cli

    movl %eax, %edi
    movl %ebx, %esi

    leal stack_top, %esp

    leal pml4, %eax
    movl %eax, %cr3

    movl %cr4, %eax
    orl $(1 << 5), %eax
    movl %eax, %cr4

    movl $0xC0000080, %ecx
    rdmsr
    orl $(1 << 8), %eax
    wrmsr

    movl %cr0, %eax
    orl $(1 << 31), %eax
    movl %eax, %cr0

    lgdt boot_gdt_pointer

    pushl $0x08
    pushl $long_mode_entry
    lret

.code64

long_mode_entry:
    movw $0x10, %ax
    movw %ax, %ds
    movw %ax, %es
    movw %ax, %fs
    movw %ax, %gs
    movw %ax, %ss

    leaq stack_top(%rip), %rsp

    call kernel_main

/* If the code reaches this point, it means I need to launch an ICBM at the
   person responsible for all this. */
    cli
unreachable:
    hlt
    jmp unreachable

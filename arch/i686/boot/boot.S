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

#define ASM_FILE   1
#include <meow/multiboot2.h>

.section .bss
.align 16
.globl stack_bottom
stack_bottom:
    .space 16384
.globl stack_top
stack_top:

.section .text

.global start, _start
start:
_start:
	jmp multiboot_entry

multiboot_header:
	.align 8
	.long MULTIBOOT2_HEADER_MAGIC
	.long MULTIBOOT_ARCHITECTURE_I386
	.long multiboot_header_end - multiboot_header
	.long -(MULTIBOOT2_HEADER_MAGIC + MULTIBOOT_ARCHITECTURE_I386 + (multiboot_header_end - multiboot_header))
multiboot_header_end:
	.short MULTIBOOT_HEADER_TAG_END
    .short 0
    .long 8

multiboot_entry:
	cli

	lgdt boot_gdt_pointer

    movl $reload_segments, %ecx
    pushl $0x08
    pushl %ecx
    lret
reload_segments:
    movw $0x10, %cx
    movw %cx, %ds
    movw %cx, %es
    movw %cx, %fs
    movw %cx, %gs
    movw %cx, %ss

    leal stack_top, %esp

    movl %cr4, %ecx
    orl $(1 << 5), %ecx
    movl %ecx, %cr4

    movl $pdpt, %ecx
    movl %ecx, %cr3

    movl %cr0, %ecx
    orl $(1 << 31), %ecx
    movl %ecx, %cr0

    pushl %ebx
    pushl %eax

    call kernel_main

/* If the code reaches this point, it means I need to launch an ICBM at the
   person responsible for all this. */
    cli
unreachable:
    hlt
    jmp unreachable

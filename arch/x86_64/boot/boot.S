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

.intel_syntax noprefix
.code32

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
.globl start, _start
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

	mov edi, eax
    mov esi, ebx

	lea esp, [stack_top]

    lea eax, [pml4]
    mov cr3, eax

    mov eax, cr4
    or eax, 1 << 5
    mov cr4, eax

    mov ecx, 0xC0000080
    rdmsr
    or eax, 1 << 8
    wrmsr

    mov eax, cr0
    or eax, 1 << 31
    mov cr0, eax

    lgdt [boot_gdt_pointer]

    push 0x08
    push offset long_mode_entry
    retf

.code64
long_mode_entry:
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    lea rsp, [stack_top]

    call initKernel
loop:
    hlt
    jmp loop

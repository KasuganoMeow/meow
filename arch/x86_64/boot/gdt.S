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

.section .rodata

.align 8
boot_gdt_start:
	.quad 0x0000000000000000

    .word 0x0000
    .word 0x0000
    .byte 0x00
    .byte 0x9A
    .byte 0xAF
    .byte 0x00

    .word 0x0000
    .word 0x0000
    .byte 0x00
    .byte 0x92
    .byte 0xCF
    .byte 0x00
boot_gdt_end:

.global boot_gdt_pointer
boot_gdt_pointer:
    .word (boot_gdt_end - boot_gdt_start - 1)
    .long boot_gdt_start

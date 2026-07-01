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

.section .page_table, "aw", @progbits

.align 0x1000
.global pml4
pml4:
    .long 0, 0

.align 0x1000
.global pdpt
pdpt:
    .long pd + 0x3
    .long 0
    .long 0, 0
    .long 0, 0
    .long 0, 0
    .long 0, 0

.align 0x1000
.global pd
pd:
    .set i, 0
    .rept 8
    .long (i << 21) + 0x83
    .long 0
    .set i, i+1
    .endr

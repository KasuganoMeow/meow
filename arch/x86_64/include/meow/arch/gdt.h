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

#ifndef MEOW_ARCH_GDT_H
#define MEOW_ARCH_GDT_H 1

#include <stdint.h>

typedef struct [[gnu::packed]] {
	uint16_t limit_1;
	uint16_t base_1;
	uint8_t  base_2;
	uint8_t  access;
	uint8_t  granularity;
	uint8_t  base_3;
} gdt_entry_t;

typedef struct [[gnu::packed]] {
	uint16_t limit;
	uint64_t base;
} gdtr_t;

void gdt_set_descriptor(uint32_t index, uint8_t access, uint8_t flags);
void gdt_init(void);

#endif

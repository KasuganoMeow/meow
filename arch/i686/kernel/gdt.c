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

#include <stdint.h>

#include <meow/arch/gdt.h>

gdt_entry_t gdt[3];
gdtr_t      gdtr;

extern void gdt_load(void);

void gdt_set_descriptor(uint32_t index, uint32_t base, uint32_t limit, uint8_t access, uint8_t flags) {	
	gdt[index].base_1 = base & 0xFFFF;
	gdt[index].base_2 = (base >> 16) & 0xFF;
	gdt[index].base_3 = (base >> 24) & 0xFF;
	gdt[index].limit_1 = limit & 0xFFFF;
	gdt[index].granularity = ((limit >> 16) & 0x0F) | (flags & 0xF0);
	gdt[index].access = access;
}

void gdt_init(void) {
	gdt_set_descriptor(0, 0, 0, 0, 0);
	gdt_set_descriptor(1, 0, 0xFFFFF, 0x9A, 0xCF);
	gdt_set_descriptor(2, 0, 0xFFFFF, 0x92, 0xCF);

	gdtr.limit = sizeof(gdt) - 1;
	gdtr.base = (uint32_t)(uintptr_t)&gdt[0];

	gdt_load();
}

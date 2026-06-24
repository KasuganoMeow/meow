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

extern void load_gdt(void);

segment_descriptor         gdt_entries[3];
segment_descriptor_pointer gdt_pointer;

void set_gdt_entry(uint32_t index, uint32_t base, uint32_t limit, uint8_t access, uint8_t flags) {
	gdt_entries[index].base_1 = base & 0xFFFF;
	gdt_entries[index].base_2 = (base >> 16) & 0xFF;
	gdt_entries[index].base_3 = (base >> 24) & 0xFF;
	gdt_entries[index].limit_1 = limit & 0xFFFF;
	gdt_entries[index].granularity = ((limit >> 16) & 0x0F) | (flags & 0xF0);
	gdt_entries[index].access = access;
}

void init_gdt(void) {
	set_gdt_entry(0, 0, 0, 0, 0);
	set_gdt_entry(1, 0, 0xFFFFF, 0x9A, 0xCF);
	set_gdt_entry(2, 0, 0xFFFFF, 0x92, 0xCF);

	gdt_pointer.limit = sizeof(gdt_entries) - 1;
	gdt_pointer.base = (uint32_t)(uintptr_t)&gdt_entries[0];

	load_gdt();
}

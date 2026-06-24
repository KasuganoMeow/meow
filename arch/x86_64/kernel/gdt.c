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

#include <meow/arch/gdt.h>

extern void load_gdt(void);

segment_descriptor         gdt_entries[3];
segment_descriptor_pointer gdt_pointer;

void set_gdt_entry(uint32_t index, uint8_t access, uint8_t flags) {
	gdt_entries[index].base_1 = 0;
	gdt_entries[index].base_2 = 0;
	gdt_entries[index].base_3 = 0;
	gdt_entries[index].limit_1 = 0;
	gdt_entries[index].access = access;
	gdt_entries[index].granularity = (flags & 0xF0);
}

void init_gdt(void) {
	set_gdt_entry(0, 0, 0);
	set_gdt_entry(1, 0x9A, 0x20);
	set_gdt_entry(2, 0x92, 0x00);

	gdt_pointer.limit = sizeof(gdt_entries) - 1;
	gdt_pointer.base = (uint64_t)&gdt_entries[0];

	load_gdt();
}

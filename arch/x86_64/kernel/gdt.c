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

static gdt_entry_t gdt[3];
gdtr_t             gdtr;

extern void gdt_load(void);

void gdt_set_descriptor(uint32_t index, uint8_t access, uint8_t flags) {
	gdt[index].base_1 = 0;
	gdt[index].base_2 = 0;
	gdt[index].base_3 = 0;
	gdt[index].limit_1 = 0;
	gdt[index].access = access;
	gdt[index].granularity = (flags & 0xF0);
}

void gdt_init(void) {
	gdt_set_descriptor(0, 0, 0);
	gdt_set_descriptor(1, 0x9A, 0x20);
	gdt_set_descriptor(2, 0x92, 0x00);

	gdtr.limit = sizeof(gdt) - 1;
	gdtr.base = (uint64_t)&gdt[0];

	gdt_load();
}

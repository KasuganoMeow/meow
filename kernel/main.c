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
#include <meow/arch/idt.h>
#include <meow/panic.h>
#include <meow/tty.h>

#include <stdint.h>
#include <stddef.h>

void initKernel(uint32_t magic, uintptr_t info_addr) {
	if (magic != 0x36d76289 || !info_addr) {
		panic();
	}
	gdt_init();
	idt_init();
	terminal_initialize();
	asm volatile (".byte 0x0F, 0x0B");
}

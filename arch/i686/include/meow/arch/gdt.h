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

#ifndef GDT_H
#define GDT_H 1

typedef struct [[gnu::packed]] {
	unsigned short limit_1;
	unsigned short base_1;
	unsigned char  base_2;
	unsigned char  access;
	unsigned char  granularity;
	unsigned char  base_3;
} segment_descriptor;

typedef struct [[gnu::packed]] {
	unsigned short limit;
	unsigned long  base;
} segment_descriptor_pointer;

void init_gdt(void);

#endif

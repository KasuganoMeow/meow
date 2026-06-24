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

#ifndef MEOW_ARCH_IDT_H
#define MEOW_ARCH_IDT_H 1

#include <stdint.h>

typedef struct [[gnu::packed]] {
    uint16_t isr_low;
    uint16_t kernel_cs;
    uint8_t  ist;
    uint8_t  attributes;
    uint16_t isr_mid;
    uint32_t isr_high;
    uint32_t reserved;
} idt_entry_t;

typedef struct [[gnu::packed]] {
    uint16_t limit;
    uint64_t base;
} idtr_t;

typedef struct {
    uint64_t rax, rbx, rcx, rdx, rsi, rdi, rbp;
    uint64_t r8, r9, r10, r11, r12, r13, r14, r15;
    uint64_t int_no, err_code;
    uint64_t rip, cs, rflags, rsp, ss;
} registers_t;

void idt_set_descriptor(uint8_t vector, void* isr, uint8_t flags);
void idt_init(void);

#endif

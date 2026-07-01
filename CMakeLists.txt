# SPDX-License-Identifier: AGPL-3.0-or-later
# Copyright 2026 KasuganoMeow
# This file is part of Meow.
# 
# Meow is free software: you can redistribute it and/or modify it under the terms of
# the GNU Affero General Public License as published by the Free Software Foundation, 
# either version 3 of the License, or (at your option) any later version.
# 
# Meow is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
# without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
# PURPOSE. See the GNU Affero General Public License for more details.
# 
# You should have received a copy of the GNU Affero General Public License along with 
# Meow. If not, see <https://www.gnu.org/licenses/>.

cmake_minimum_required(VERSION 3.10)
project(Meow C ASM)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_C_COMPILER clang)
set(CMAKE_ASM_COMPILER clang)

set(INTERNAL_COMPILE_FLAGS
    -Wall
    -Wextra
    -std=gnu23
    -ffreestanding
)

if(ARCH STREQUAL "x86_64")
    set(CMAKE_C_COMPILER_TARGET x86_64-elf)
	set(ARCH_COMPILE_FLAGS
		-fno-stack-protector
		-fno-stack-check
		-fno-lto
		-fno-PIC
		-fno-pie
		-ffunction-sections
		-fdata-sections
		-m64
		-march=x86-64
		-mabi=sysv
		-mno-80387
		-mno-mmx
		-mno-sse
		-mno-sse2
		-mno-red-zone
		-mcmodel=kernel
	)
    set(ARCH_LINK_FLAGS
        -m64
    )
elseif(ARCH STREQUAL "i686")
    set(CMAKE_C_COMPILER_TARGET i686-elf)
	set(ARCH_COMPILE_FLAGS
		-m32
        -march=i686
        -fno-stack-protector
        -fno-stack-check
        -fno-lto
        -fno-PIC
        -fno-pie
        -ffunction-sections
        -fdata-sections
        -mno-80387
        -mno-mmx
        -mno-sse
        -mno-sse2
        -mgeneral-regs-only
	)
    set(ARCH_LINK_FLAGS
        -m32
        -Wl,-melf_i386
    )
endif()

set(COMPILE_FLAGS
    -g
    -O0
    -pipe
    ${INTERNAL_COMPILE_FLAGS}
    ${ARCH_COMPILE_FLAGS}
)

set(LINK_FLAGS
    -nostdlib
    -static
    -Wl,--gc-sections
    -Wl,-T,${CMAKE_CURRENT_SOURCE_DIR}/arch/${ARCH}/linker/linker.lds
    ${ARCH_LINK_FLAGS}
)

file(GLOB_RECURSE SOURCES
    "kernel/*.c"
    "lib/*.c"
    "arch/${ARCH}/kernel/*.*"
    "arch/${ARCH}/boot/*.*"
    "arch/${ARCH}/lib/*.*"
)

add_executable(meow ${SOURCES})

target_compile_options(meow PRIVATE ${COMPILE_FLAGS})

target_link_options(meow PRIVATE ${LINK_FLAGS})

target_include_directories(meow PRIVATE
    "include"
    "arch/${ARCH}/include"
)

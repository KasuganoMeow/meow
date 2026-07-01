# Porject Meow
`meow` is a toy kernel written in `C` (and some `ASM`) that can run on `x86_64` and `i686` architectures.

The speed at which I update this project depends on how well I slept last night and what I ate for breakfast today.

# Note
I refactored all assembly code that previously used `Intel GAS syntax`; it now uses `AT&T GAS syntax`.

# Language
Currently, only `C` and `ASM` are accepted; languages ​​such as `Rust` and `C++` are not being considered.

(I once considered a C++ version of the `meow`; if anyone is interested, I could clean it up and upload it, though it won't be merged into the main branch)

# Build
`meow` is compiled using `cmake` and `clang`.

(Previously used `cmake` + `GCC`)

`i686` Version:
```
mkdir build && cd build
cmake .. -DARCH=i686 && make -j$(nproc)
```
`x86_64` Version:
```
mkdir build && cd build
cmake .. -DARCH=x86_64 && make -j$(nproc)
```

# TODO
The following are the goals of Project Meow.
## Short-term goals
- [x] `Multiboot 2` compatibility
- [x] Load temporary `GDT`
- [x] Enable memory paging (identical mapping)
- [x] Enter long mode (applicable to `x86_64`)
- [x] The basic `stopcpu()` and `panic()` functions
- [x] `IDT` and Interrupt Handling
- [ ] Memory repaging and mapping the kernel to the high half of memory
- [ ] Physical Memory Manager
- [ ] Virtual Memory Manager
- [ ] Memory Allocator
  
## Long-term goals
- [ ] `SMP` support
- [ ] Keyboard interrupt (`APIC`) and `PS/2` driver
- [ ] Virtual File System
- [ ] `PATA` and `SATA` drivers
- [ ] File system
- [ ] Enter user space
- [ ] Implement some system calls

## Almost impossible goal
- [ ] `DRM`/`KMS` driver
- [ ] X Window System porting
- [ ] `xHCI` driver
- [ ] Network driver
- [ ] Have basic toolchain

# License
[GNU AGPLv3](https://www.gnu.org/licenses/) or later

<img src="https://upload.wikimedia.org/wikipedia/commons/0/06/AGPLv3_Logo.svg" alt="GNU AGPLv3 Logo" style="width: 200px; height: auto;">

# Porject Meow
`meow` is a toy kernel written in `C` (and some `ASM`) that can run on `x86_64` and `i686` architectures.

The speed at which I update this project depends on how well I slept last night and what I ate for breakfast today.

# TODO
The following are the goals of Project Meow.
## Short-term goals
- [x] `Multiboot 2` compatibility
- [x] Load temporary `GDT`
- [x] Enable memory paging (identical mapping)
- [x] Enter long mode (applicable to `x86_64`)
- [x] The basic `stopcpu()` and `panic()` functions
- [ ] `IDT` and Interrupt Handling
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

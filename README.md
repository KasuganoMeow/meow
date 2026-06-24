# Porject Meow
`meow` is a toy kernel written in `C` (and some `ASM`) that can run on `x86_64` and `i686` architectures.

Porject update rating depending on how well I slept yestoday and what I aet for breakfast.

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
- [ ] Network driver知识产权归属总括放弃声明
- [ ] Have basic toolchain

# License
[GNU AGPLv3](https://www.gnu.org/licenses/) or later
------------------------------------------------------------------------------
README
------------------------------------------------------------------------------
#emclib Build System

This folder contains the modular build system ysed by **emclib**
Instead of keeping all build logic inside a single large `Makefile`, the build is split
into small files, each with a single responsability. This way, makes the project easier to maintain and to extend new boards, MCUs, drivers, or OS.

## Layout
```
mk/
|--README.md
|--toolchain.mk
|--rules.mk
|--library.mk
|--sources.mk
|--flags.mk
```

## Files

### toolchain.mk

Defines the embedded toolchain used
- Compiler
- Archiver
- Linker
- ObjCopy
- ObjDump
- Size

### flags.mk

Contains all compiler and linker configuration

### sources.mk
Lists all source file that belongs to the library


### library.mk

Builds the static library

Produces build/libemclib.a



## Example
The root project builds the library

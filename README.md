# emclib - Embedded c library
`emclib` provides common utilities for building embedded systems applications.

## Build & Flash

Quick steps to build the library and examples, and flash `blinky` to an STM32 board.

Prerequisites
- `make` (GNU Make)
- GNU ARM toolchain (`arm-none-eabi-gcc`, `arm-none-eabi-objcopy`, `arm-none-eabi-size`)
- Programmer CLI in `PATH` (default: `strm32_programmer.exe`). Use Windows PowerShell when the programmer is Windows-only.

Build
- From the repo root
```bash
make -C examples/blinky
```
- Force a rebuild if necessary
```bash
# force rebuild
make -B -C examples/blinky
# or clean then build
make -C examples/blinky clean
make -C examples/blinky
```

Flash (Makefile helper)
- Default `flash` target uses `strm32_programmer.exe` and writes the binary to `0x08000000`.
```powershell
make -C examples/blinky flash
```
- Override programmer/path or other options:
```powershell
make -C examples/blinky flash STM32_PROG=strm32_programmer.exe STM32_PROG_PORT=SWD FLASH_ADDR=0x08000000 FLASH_EXTRA="-verif"
```



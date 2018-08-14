# pynquino bsp library (work in progress)
## What is this
This is an Arduino API porting to PYNQ by Xilinx. You'll be able to compile Arduino sketches on the PYNQ.

## Install 
Here is how to build PYNQ BSP with pynquino-bsp-library. All the Arduino functions will be merged into libxil.a.
```sh
git clone https://github.com/xilinx/pynq
cd pynq/boards/sw_repo
git clone https://github.com/shohei/pynquino-bsp-library
make
```
Now you've got a bsp_iop_arduino_mb. Copy this folder to pynq/pynq/lib/arduino.

** Attention: pynqmb has a bug in PYNQ v2.1(the version I'm using). You have to fix it by downloading uart.c/uart.h from here.
https://github.com/shohei/PYNQ/commit/b8928631b1b8b118b046d204b2c2dbeeeb063648

## Fix linker script
I extended a BRAM size of the Arduino IOP from the default 64K to 256K. In this case, you have to update the linker script as well.
```
cd pynq/boards/sw_repo/bsp_iop_arduino_mb
vim lscript.ld
```
```diff
MEMORY
{
-   microblaze_bram : ORIGIN = 0x50, LENGTH = 0xEFB0
+  microblaze_bram : ORIGIN = 0x50, LENGTH = 0xEFB0
}
```

## Reference
The original code was taken from the project folowing:
http://igg.me/at/zynq

https://github.com/Trenz-Electronic/Arduino-Vivado-SDK

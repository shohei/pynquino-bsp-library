# pynquino bsp library (work in progress)
## What is this
This is an Arduino API porting to PYNQ by Xilinx. You'll be able to compile Arduino sketches on the PYNQ.

## Install 


### Prerequisites1. Fix pynqmb library
pynqmb library has a bug in PYNQ v2.1(the version I'm using). You have to fix it by downloading uart.c/uart.h from here.
https://github.com/shohei/PYNQ/commit/b8928631b1b8b118b046d204b2c2dbeeeb063648
That is,
```sh
git clone https://github.com/xilinx/pynq
cd pynq/boards/sw_repo
cd pynqmb/src
wget https://raw.githubusercontent.com/shohei/PYNQ/b8928631b1b8b118b046d204b2c2dbeeeb063648/boards/sw_repo/pynqmb/src/uart.c uart.c
wget https://raw.githubusercontent.com/shohei/PYNQ/b8928631b1b8b118b046d204b2c2dbeeeb063648/boards/sw_repo/pynqmb/src/uart.h uart.h
```

### Prerequisites2. Fix mailbox_bram library
I extended a BRAM size of the Arduino IOP from the default 64K to 256K. You must update mailbox_bram library accordingly.
```sh
cd pynq/boards/sw_repo
cd mailbox_bram/src
wget https://raw.githubusercontent.com/shohei/PYNQ/ef48cbed829094b6bce712e859e3d857db5741fc/boards/sw_repo/mailbox_bram/src/mailbox_io.c mailbox_io.c
```
### Prerequisites2. Fix linker script
You also have to update the linker script.
```
cd pynq/boards/sw_repo/bsp_iop_arduino_mb
vim lscript.ld
```
```diff
MEMORY
{
-  microblaze_bram : ORIGIN = 0x50, LENGTH = 0xEFB0
+  microblaze_bram : ORIGIN = 0x50, LENGTH = 0x3EFB0
}
```
and make
```
make
```
### Finally 
Here we build a PYNQ-MicroBlaze BSP with pynquino-bsp-library. All the Arduino functions will be merged into libxil.a.
```sh
cd pynq/boards/sw_repo
git clone https://github.com/shohei/pynquino-bsp-library
make
```
Now you've got a bsp_iop_arduino_mb. Copy this folder to pynq/pynq/lib/arduino.



## Reference
The original code was taken from the project folowing:
http://igg.me/at/zynq

https://github.com/Trenz-Electronic/Arduino-Vivado-SDK

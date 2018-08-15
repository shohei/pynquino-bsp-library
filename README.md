# pynquino bsp library (work in progress)
## What is this
This is an Arduino API porting to PYNQ by Xilinx. You'll be able to compile Arduino sketches on the PYNQ.

## Install 


### Prerequisites1. Fix pynqmb library
pynqmb library has a bug in PYNQ v2.1(the version I'm using). You have to fix it by downloading uart.c/uart.h from here.
https://github.com/shohei/PYNQ/commit/b8928631b1b8b118b046d204b2c2dbeeeb063648
In addition, you need to update the memoery allocation in circular_buffer.h. This is required because I extended a BRAM size of the Arduino IOP from the default 64K to 256K. 
Here is how we do it.
```sh
git clone https://github.com/xilinx/pynq
cd pynq/boards/sw_repo
cd pynqmb/src
wget https://raw.githubusercontent.com/shohei/PYNQ/b8928631b1b8b118b046d204b2c2dbeeeb063648/boards/sw_repo/pynqmb/src/uart.c 
mv uart.c.1 uart.c
wget https://raw.githubusercontent.com/shohei/PYNQ/b8928631b1b8b118b046d204b2c2dbeeeb063648/boards/sw_repo/pynqmb/src/uart.h 
mv uart.h.1 uart.h
wget https://raw.githubusercontent.com/shohei/PYNQ/master/boards/sw_repo/pynqmb/src/circular_buffer.h
mv circular_buffer.h.1 circular_buffer.h
```

### Prerequisites2. Fix mailbox_bram library
You must update mailbox_bram library accordingly. This is caused by the BRAM size increase mentioned above.
```sh
cd pynq/boards/sw_repo
cd mailbox_bram/src
wget https://raw.githubusercontent.com/shohei/PYNQ/ef48cbed829094b6bce712e859e3d857db5741fc/boards/sw_repo/mailbox_bram/src/mailbox_io.c 
mv mailbox_io.c.1 mailbox_io.c
```
### Prerequisites3. Fix linker script
You also have to update the linker script if you increase the BRAM size to 256K. 
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
### Prerequiresites4. Fix makefile
Create BSP based on hardware definition file top.hdf, rather than default base.hdf.

PYNQ/boards/sw_repo/makefile
```diff
- HDF := ../Pynq-Z1/base/base/base.sdk/base.hdf
+ HDF := ../Pynq-Z1/base/base/base.sdk/top.hdf
```

### Finally 
Here we build a PYNQ-MicroBlaze BSP with pynquino-bsp-library. All the Arduino functions will be merged into libxil.a.
```sh
cd pynq/boards/sw_repo
git clone https://github.com/shohei/pynquino-bsp-library
make
```
Now you've got a bsp_iop_arduino_mb. Copy this folder to pynq/pynq/lib/arduino and rename it as bsp_iop_arduino.



## Reference
The original code was taken from the project folowing:
http://igg.me/at/zynq

https://github.com/Trenz-Electronic/Arduino-Vivado-SDK

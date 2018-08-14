# pynquino bsp library
## What is this
This is an Arduino API porting to PYNQ by Xilinx. You'll be able to compile Arduino sketch on the PYNQ.

## Install 
Here is how to build PYNQ BSP with pynquino-bsp-library. All the Arduino functions will be merged into libxil.a.
```sh
git clone https://github.com/xilinx/pynq
cd pynq/boards/sw_repo
git clone https://github.com/shohei/pynquino-bsp-library
(fix linker script: see below)
make
```
Now you've got a bsp_iop_arduino_mb. Copy this folder to pynq/pynq/lib/arduino.

** Attention: pynqmb has a bug in PYNQ v2.1(the version I'm using). You have to fix it by downloading uart.c/uart.h from here.
https://github.com/shohei/PYNQ/commit/b8928631b1b8b118b046d204b2c2dbeeeb063648

## Reference
The original code was taken from the project folowing:
http://igg.me/at/zynq

https://github.com/Trenz-Electronic/Arduino-Vivado-SDK

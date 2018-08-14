# pynquino bsp library

## How to build PYNQ BSP with pynquino-bsp-library
```sh
git clone https://github.com/xilinx/pynq
cd pynq/boards/sw_repo
git clone https://github.com/shohei/pynquino-bsp-library
(fix linker script: see below)
make
```
Now you've got a bsp_iop_arduino_mb. Copy this folder to pynq/pynq/lib/arduino.

## Reference
The original code was taken from the project folowing:
http://igg.me/at/zynq

https://github.com/Trenz-Electronic/Arduino-Vivado-SDK

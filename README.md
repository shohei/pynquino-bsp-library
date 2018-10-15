# pynquino bsp library (work in progress)
## What is this
This is an Arduino API porting to PYNQ by Xilinx. You'll be able to compile Arduino sketches on the PYNQ.

## Install 

### Prerequisites1. Fix mailbox_bram library
You must update mailbox_bram library accordingly. This is caused by the BRAM size increase mentioned above.
```sh
cd pynq/boards/sw_repo
cd mailbox_bram/src
wget https://raw.githubusercontent.com/shohei/PYNQ/ef48cbed829094b6bce712e859e3d857db5741fc/boards/sw_repo/mailbox_bram/src/mailbox_io.c 
mv mailbox_io.c.1 mailbox_io.c
```
### Prerequisites2. Fix linker script
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
### Prerequisites3. Fix makefile
Create BSP based on hardware definition file top.hdf, rather than default base.hdf.

PYNQ/boards/sw_repo/makefile
```diff
- HDF := ../Pynq-Z1/base/base/base.sdk/base.hdf
+ HDF := ../Pynq-Z1/base/base/base.sdk/base_wrapper.hdf
```

### Prerequisites4. Update Uartlite library
Add readline() function to Uartlite library

boards/sw_repo/pynqmb/src/uart.c
```c
void uart_readline(uart dev_id, char* read_data){
    unsigned int ReceivedCount = 0;
    while (1) {
            ReceivedCount += XUartLite_Recv(&xuart[dev_id],
                           read_data + ReceivedCount,
                           1);
            if (read_data[ReceivedCount - 1] == '\n') {
                break;
            }
        }
}
```
boards/sw_repo/pynqmb/src/uart.h
```c
void uart_readline(uart dev_id, char* read_data);
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

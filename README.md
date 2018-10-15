# pynquino bsp library (work in progress)
## What is this
This is an Arduino API porting to PYNQ by Xilinx. You'll be able to compile Arduino sketches on the PYNQ.

## Install 

### Prerequisites 1. Fix mailbox_bram library
You must update mailbox_bram library accordingly. This is caused by the BRAM size increase mentioned above.
https://github.com/shohei/PYNQ/commit/ef48cbed829094b6bce712e859e3d857db5741fc
#### mailbox_bram
```sh
cd pynq/boards/sw_repo/mailbox_bram/src
```
```diff
- #define STDIN_OFFSET 0xF000
- #define STDOUT_OFFSET 0xF400
- #define RPCIN_OFFSET 0xF800
- #define RPCOUT_OFFSET 0xFC00
+ #define STDIN_OFFSET 0x3F000
+ #define STDOUT_OFFSET 0x3F400
+ #define RPCIN_OFFSET 0x3F800
+ #define RPCOUT_OFFSET 0x3FC00
```
```diff
- int last_available = 0xFFFF;
+ int last_available = 0x3FFFF;
```
#### circular_buffer
boards/sw_repo/pynqmb/src/circular_buffer.h
```diff
- #define MAILBOX_CMD_ADDR       (*(volatile u32 *)(0x0000FFFC))
- #define MAILBOX_DATA(x)        (*(volatile u32 *)(0x0000F000 +((x)*4)))
- #define MAILBOX_DATA_PTR(x)    ( (volatile u32 *)(0x0000F000 +((x)*4)))
- #define MAILBOX_DATA_FLOAT(x)     (*(volatile float *)(0x0000F000 +((x)*4)))
- #define MAILBOX_DATA_FLOAT_PTR(x) ( (volatile float *)(0x0000F000 +((x)*4)))

+ #define MAILBOX_CMD_ADDR       (*(volatile u32 *)(0x00003FFFC))
+ #define MAILBOX_DATA(x)        (*(volatile u32 *)(0x00003F000 +((x)*4)))
+ #define MAILBOX_DATA_PTR(x)    ( (volatile u32 *)(0x00003F000 +((x)*4)))
+ #define MAILBOX_DATA_FLOAT(x)     (*(volatile float *)(0x00003F000 +((x)*4)))
+ #define MAILBOX_DATA_FLOAT_PTR(x) ( (volatile float *)(0x00003F000 +((x)*4)))```

### Prerequisites 2. Fix makefile
Create BSP based on hardware definition file top.hdf, rather than default base.hdf.

PYNQ/boards/sw_repo/makefile
```diff
- HDF := ../Pynq-Z1/base/base/base.sdk/base.hdf
+ HDF := ../Pynq-Z1/base/base/base.sdk/base_wrapper.hdf
```

### Prerequisites 3. Update Uartlite library
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
### Prerequisites 4. Edit build .tcl script
Add pynquino as a build dependency
PYNQ/boards/sw_repo/build_xsdk.tcl
```c
foreach mb $processors {
    set bsp "bsp_${mb}"
    if {![file exists $bsp]} {
        puts "Creating new BSP ${bsp} ..."
        createbsp -name $bsp -proc $mb -hwproject $hw_def -os standalone
        setlib -bsp $bsp -lib pynqmb
add --> setlib -bsp $bsp -lib pynquino
```

### Build 
Here we build a PYNQ-MicroBlaze BSP with pynquino-bsp-library. All the Arduino functions will be merged into libxil.a.
```sh
cd pynq/boards/sw_repo
git clone https://github.com/shohei/pynquino-bsp-library
make
```
Now you've got a bsp_iop_arduino_mb. 

### Postprocess. Fix linker script and project name
You also have to update the linker script if you increase the BRAM size to 256K. 

pynq/boards/sw_repo/bsp_iop_arduino_mb/lscript.ld
```diff
MEMORY
{
-  microblaze_bram : ORIGIN = 0x50, LENGTH = 0xEFB0
+  microblaze_bram : ORIGIN = 0x50, LENGTH = 0x3EFB0
}
```
pynq/boards/sw_repo/bsp_iop_arduino_mb/.project
```diff
-  <name>bsp_iop_arduino_mb</name>
+  <name>bsp_iop_arduino</name>
```

### Install
Copy bsp_iop_arduino_mb folder to pynq/pynq/lib/arduino and rename it as bsp_iop_arduino.
```sh
cp -r bsp_iop_arduino_mb pynq/lib/arduino/bsp_iop_arduino
```

### Post install
pynq/lib/arduino/bsp_iop_arduino/.sdkproject
```
THIRPARTY=false
- HW_PROJECT_REFERENCE=hw_base
+ HW_PROJECT_REFERENCE=base_wrapper_hw_platform_0 # or suitable name
PROCESSOR=iop_arduino_mb
MSS_FILE=system.mss
```
pynq/lib/arduino/bsp_iop_arduino/.project
```diff
-        <name>bsp_iop_arduino_mb</name>
+       <name>bsp_iop_arduino</name>
```
## Reference
The original code was taken from the project folowing:
http://igg.me/at/zynq

https://github.com/Trenz-Electronic/Arduino-Vivado-SDK

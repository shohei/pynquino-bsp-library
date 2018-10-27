//#include "xil_cache.h"

#include "Arduino.h"
#include "wiring_int.h"

#include "xparameters.h"

#include "xtmrctr.h"
XTmrCtr TimerCounterInst;

//#include "xiomodule_l.h"

// PIT1 uses FIT1 prescaler
//#define TMR_MICROS     (*(volatile uint32_t *)( XPAR_IOMODULE_0_BASEADDR + XTC_TCR_OFFSET  + (XTC_TIMER_COUNTER_OFFSET*0) ))
//#define TMR_MICROS_TLR (*(volatile uint32_t *)( XPAR_IOMODULE_0_BASEADDR + XTC_TLR_OFFSET  + (XTC_TIMER_COUNTER_OFFSET*0) ))
//#define TMR_MICROS_CTR (*(volatile uint32_t *)( XPAR_IOMODULE_0_BASEADDR + XTC_TCSR_OFFSET + (XTC_TIMER_COUNTER_OFFSET*0) ))

// PIT2 uses FIT2 prescaler
//#define TMR_MILLIS     (*(volatile uint32_t *)( XPAR_IOMODULE_0_BASEADDR + XTC_TCR_OFFSET  + (XTC_TIMER_COUNTER_OFFSET*1) ))
//#define TMR_MILLIS_TLR (*(volatile uint32_t *)( XPAR_IOMODULE_0_BASEADDR + XTC_TLR_OFFSET  + (XTC_TIMER_COUNTER_OFFSET*1) ))
//#define TMR_MILLIS_CTR (*(volatile uint32_t *)( XPAR_IOMODULE_0_BASEADDR + XTC_TCSR_OFFSET + (XTC_TIMER_COUNTER_OFFSET*1) ))

// PIT3 no prescaler, system clock direct
//#define TMR_DELAY     (*(volatile uint32_t *)( XPAR_IOMODULE_0_BASEADDR + XTC_TCR_OFFSET  + (XTC_TIMER_COUNTER_OFFSET*2) ))
//#define TMR_DELAY_TLR (*(volatile uint32_t *)( XPAR_IOMODULE_0_BASEADDR + XTC_TLR_OFFSET  + (XTC_TIMER_COUNTER_OFFSET*2) ))
//#define TMR_DELAY_CTR (*(volatile uint32_t *)( XPAR_IOMODULE_0_BASEADDR + XTC_TCSR_OFFSET + (XTC_TIMER_COUNTER_OFFSET*2) ))

#include "xil_printf.h"


#ifdef XPAR_XGPIOPS_NUM_INSTANCES

#include "xgpiops.h"
//#include "xscugic.h"
//#include "xtime_l.h"

//XScuGic IntcInstance;
XGpioPs Gpio;
//XTime tCurrent;

#endif

//#define ledpin 7

void init()
{
	int Status;
	//int i, j;
	//unsigned long * addr;

//	xil_printf("wiring.c init() - enter\n\r");

#ifdef XPAR_XGPIOPS_NUM_INSTANCES
	//XScuGic_Config *IntcConfig;
	XGpioPs_Config *GPIOConfigPtr;


	// Start millis and micros timers
//	TMR_MICROS_CTR = (XTC_CSR_ENABLE_TMR_MASK | XTC_CSR_AUTO_RELOAD_MASK);
//	TMR_MILLIS_CTR = (XTC_CSR_ENABLE_TMR_MASK | XTC_CSR_AUTO_RELOAD_MASK);

//	TMR_MICROS_TLR = 0xFFFFFFFF;
//	TMR_MILLIS_TLR = 0xFFFFFFFF;

	// Enable the timer used for delay timing,no auto reload
//	TMR_DELAY_CTR = (XTC_CSR_ENABLE_TMR_MASK | XTC_CSR_AUTO_RELOAD_MASK);


	GPIOConfigPtr = XGpioPs_LookupConfig(XPAR_PS7_GPIO_0_DEVICE_ID);
	Status = XGpioPs_CfgInitialize(&Gpio, GPIOConfigPtr, GPIOConfigPtr ->BaseAddr);

//	XGpioPs_SetDirectionPin(&Gpio, ledpin, 1);
//	XGpioPs_SetOutputEnablePin(&Gpio, ledpin, 1);
//	XGpioPs_WritePin(&Gpio, ledpin, 1);

#endif

//	xil_printf("wiring.c init() - exit\n\r");
  Status;
  Status = XTmrCtr_Initialize(&TimerCounterInst, XPAR_IOP_ARDUINO_TIMERS_SUBSYSTEM_TIMER_5_DEVICE_ID);
  if (Status != XST_SUCCESS) {
    printf("Timer Initialize Error\n\r");
        return XST_FAILURE;
  }
  XTmrCtr_SetOptions(&TimerCounterInst, 0, XTC_AUTO_RELOAD_OPTION);
  XTmrCtr_Start(&TimerCounterInst, 0);
}

uint32_t millis(void)
{
	//unsigned int millis = ~TMR_MILLIS;
  //XTime_GetTime(&tCurrent);
  //u32 micros =  1.0 * (tCurrent) / (COUNTS_PER_SECOND/1000000L);
  //u32 millis = micros/1000;
  //printf("Output took %d ms.\n",millis);
  uint32_t millis = (uint32_t) micros() / 1000.0;
	return millis;
}

uint32_t micros(void)
{
	//unsigned int micros = ~TMR_MICROS;
  //XTime_GetTime(&tCurrent);
  //u32 micros =  1.0 * (tCurrent) / (COUNTS_PER_SECOND/1000000L);

  uint32_t micros = (uint32_t) XTmrCtr_GetValue(&TimerCounterInst, 0) / 100.0;
  //uint32_t micros = 0;
	return micros;
}

volatile int xx;

void delay(uint32_t value)
{
	//TMR_DELAY = value * 1000;
	//while ((TMR_DCR & 0x200) == 0);
#ifdef XPAR_XGPIOPS_NUM_INSTANCES
	int x = value*50000;
	while(x--) xx++;
#endif

#ifdef PROC_MICROBLAZE
	int x = value*1000;
	while(x--) xx++;

#endif


//  	delayMicroseconds(value * 1000);

}

void delayMicroseconds(uint32_t value)
{
//        TMR_DELAY_CTR = (XTC_CSR_ENABLE_TMR_MASK | XTC_CSR_AUTO_RELOAD_MASK);
//        TMR_DELAY_TLR = value * 100;

//	while(TMR_DELAY)
		;

//	int x = value;
//	while(x--) xx++;

}


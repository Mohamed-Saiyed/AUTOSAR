#include <stdbool.h>
#include <stdint.h>
#include "hw_memmap.h"
#include "debug.h"
#include "sysctl.h"
#include "gpio.h"
#include "interrupt.h"
#include "hw_ints.h"
#include "i2c.h"
#include "pin_map.h"
#include "Dio.h"
Std_ReturnType X ,Y , Z;
	
volatile uint8 A = 0b10010100;
volatile uint8 B = 0b01001010;
volatile uint8 C = 0b00001000;
volatile uint8 F ;
Std_VersionInfoType Version;

extern Dio_ChannelGroupType ChannelGroup[];
int main(void)
{
		uint32_t ui32Index = 0;
		uint32_t pui32DataTx[8] = {0};
		uint32_t pui32DataRx[8] = {0};
		SysCtlClockSet(SYSCTL_SYSDIV_2_5 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ |SYSCTL_OSC_MAIN);
		volatile uint32 i;
		
		SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
		SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
		
		GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE , GPIO_PIN_0);
		GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE , GPIO_PIN_1);
		GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE , GPIO_PIN_2);
		GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE , GPIO_PIN_3);
		
	  GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE , GPIO_PIN_0);
		GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE , GPIO_PIN_1);
		GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE , GPIO_PIN_2);
		GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE , GPIO_PIN_3);
		GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE , GPIO_PIN_4);
		GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE , GPIO_PIN_5);
		GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE , GPIO_PIN_6);
	//	GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE , GPIO_PIN_7);
		
		//GPIOPinTypeGPIOInput(GPIO_PORTF_BASE , GPIO_PIN_6);
	
		
		//GPIOPadConfigSet(GPIO_PORTF_BASE , GPIO_PIN_6 , GPIO_STRENGTH_4MA , GPIO_PIN_TYPE_STD_WPD);
		
		//GPIOPinWrite(GPIO_PORTF_BASE , GPIO_PIN_6,GPIO_PIN_6);

		Dio_GetVersionInfo(&Version);
		
		F = (((~A)&B) | (C&A));
		while(1)
		{
			 //Dio_WritePort(LED1_PORT , 0b11110000);
			Dio_WriteChannel(LED1 , STD_HIGH);
			Dio_WriteChannel(LED2 , STD_HIGH);
			Dio_WriteChannel(LED3 , STD_HIGH);
//			
			Dio_WriteChannelGroup(&ChannelGroup[1] , 0b01000111);
//			
//			X = Dio_ReadPort(LED1_PORT);
			
			//X = Dio_ReadChannelGroup(&ChannelGroup[0]);
			
		}
		
		
}
		





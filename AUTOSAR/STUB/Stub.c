/**********************************************************************************
***********************************************************************************
**														  						 **		
**	FILENAME	:	Stub.c                              					   	 **
**	                                                      						 **
**	VERSION		: 	1.0.0                                 						 **
**                                                        						 **
**	DATE		:	2021-3-23                             						 **
**                                                        						 **
**	PLATFORM	:	TIVA C      		                  						 **
**																				 **
**  VARIANT  	: 	NA                                                           **
**                                                        						 **
**	AUTHOR		:  	MohamedSayed                          						 **
**                                                        						 **
**	VENDOR		: 	NA				                     						 **
**                                                        						 **
**	                                                      						 **
**	DESCRIPTION : 	   NA    													 **
**                                                                               **
**	SPECIFICATION(S) : NA														 **
**                                                       						 **
**	MAY BE CHANGED BY USER : Yes                          						 **
**                                                       					     **
***********************************************************************************/

#include "Det.h"

#include "gpio.h"
#include "hw_memmap.h"

Std_ReturnType Det_ReportError(uint16 ModuleId, uint8 InstanceId, uint8 ApiId, uint8 ErrorId)
{	
  	GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE , GPIO_PIN_3);

		GPIOPinWrite(GPIO_PORTF_BASE , GPIO_PIN_3 , GPIO_PIN_3);
}





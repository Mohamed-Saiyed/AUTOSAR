/**********************************************************************************
***********************************************************************************
**														  						 **		
**	FILENAME	:	Dio_Lcfg.h                              					 **
**	                                                      						 **
**	VERSION		: 	1.0.0                                 						 **
**                                                        						 **
**	DATE		:	2021-3-22                             						 **
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
**	DESCRIPTION : Digital I/O Driver link time configuration file       		 **
**                                                                               **
**	SPECIFICATION(S) : AUTOSAR_SWS_DIODriver, AUTOSAR Release 4.3.1              **
**                                                       						 **
**	MAY BE CHANGED BY USER : No                          						 **
**                                                       					     **
***********************************************************************************/

/*****************************************************************/
/*				    	Include Headers					         */
/*****************************************************************/

#include "Dio.h"
#include "Dio_MemMap.h"

const Dio_PortChannelConfig ChannelConfig[NUM_OF_USED_PINS] = 
{
	{
		LED1,
		LED1_PORT,
		
	},
	{
		LED2,
		LED2_PORT,
	},
	{
		LED3,
		LED3_PORT,
	}
};

const Dio_ChannelGroupType ChannelGroup[NUM_OF_USED_GROUPS] =
{
	{
		0xCE,
		1,
		LED1_PORT
	},
	{
		0x8E,
		1,
		LED1_PORT
	}
};

Dio_ConfigType Dio_Config = 
{
	ChannelConfig,
	ChannelGroup
};







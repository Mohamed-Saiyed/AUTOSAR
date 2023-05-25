/**********************************************************************************
***********************************************************************************
**														  						 **		
**	FILENAME	:	Dio_Cfg.h                              					     **
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
**	DESCRIPTION : Digital I/O Driver coniguration file       					 **
**                                                                               **
**	SPECIFICATION(S) : AUTOSAR_SWS_DIODriver, AUTOSAR Release 4.3.1              **
**                                                       						 **
**	MAY BE CHANGED BY USER : Yes                          						 **
**                                                       					     **
***********************************************************************************/
#ifndef DIO_CFG_H
#define DIO_CFG_H

#include "gpio.h"

//Dio_LevelType Dio_Config1;

/* Dio configutration file Vendor */
#define DIO_CFG_VENDOR_ID	(0x40u)

/*	Moudle Version	1.0.0 */
#define DIO_CFG_SW_MAJOR_VERSION			(0X01u)
#define DIO_CFG_SW_MINOR_VERSION			(0X00u)
#define DIO_CFG_SW_PATCH_VERSION			(0X00u)

/* Autosar version 4.3.1 */
#define DIO_CFG_AR_RELEASE_MAJOR_VERSION	(0X04u)
#define DIO_CFG_AR_RELEASE_MINOR_VERSION	(0X03u)
#define DIO_CFG_AR_RELEASE_PATCH_VERSION	(0X01u)

/* development error detection and Notification */
#define DioDevErrorDetect					STD_ON

/* Adds / removes the service Dio_FlipChannel() from the code */
#define DioFlipChannelApi					STD_ON

/* Adds / removes the service Dio_ GetVersionInfo() from the code */
#define DioVersionInfoApi					STD_ON

/* this configuration shall be done with a configration tool */

#define NUM_OF_USED_PINS		3
#define NUM_OF_USED_PORTS		3
#define NUM_OF_USED_GROUPS	2


#define LED1		DIO_CHANNEL_B_4
#define LED2		DIO_CHANNEL_B_5
#define LED3		DIO_CHANNEL_B_6

#define LED1_PORT	DIO_PORT_B
#define LED2_PORT	DIO_PORT_B
#define LED3_PORT	DIO_PORT_B


#endif /*DIO_CFG_H*/



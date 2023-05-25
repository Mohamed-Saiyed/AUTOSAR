/**********************************************************************************
***********************************************************************************
**														  						 **		
**	FILENAME	:	Std_Types.h                            						 **
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
**	VENDOR		: 	NA                                  						 **
**                                                        						 **
**	                                                      						 **
**	DESCRIPTION : AUTOSAR Standard Types            							 **
**                                                                               **
**	SPECIFICATION(S) : AUTOSAR_SWS_StandardTypes, AUTOSAR Release 4.3.1          **
**                                                       						 **
**	MAY BE CHANGED BY USER : No                          						 **
**                                                       					     **
***********************************************************************************/
#ifndef	STD_TYPES_H        
#define STD_TYPES_H

/*****************************************************************/
/*				    	Include Headers					         */
/*****************************************************************/

#include "Compiler.h"
#include "Platform_Types.h"

/*****************************************************************/
/*				        Macros Definition       		         */
/*****************************************************************/

/* Standard Types Vendor ID */
#define STD_TYPES_VENDOR_ID				(0x40u)

/* Standard Types module ID */
#define STD_MODULE_ID					(197u)


/*	Moudle Version	1.0.0 */
#define STD_SW_MAJOR_VERSION			(0x01u)
#define STD_SW_MINOR_VERSION			(0x00u)
#define STD_SW_PATCH_VERSION			(0x00u)

/* Autosar version 4.3.1 */
#define STD_AR_RELEASE_MAJOR_VERSION	(0x04u)
#define STD_AR_RELEASE_MINOR_VERSION	(0x03u)
#define STD_AR_RELEASE_PATCH_VERSION	(0x01u)



#ifndef STATUSTYPEDEFINED
	#define STATUSTYPEDEFINED 
	
	#define E_OK 0x00u 
	
	/* OSEK compliance*/
	typedef unsigned char StatusType; 

#endif /* STATUSTYPEDEFINED */

#define E_NOT_OK				 	0x01u

/* Physical state 5V or 3.3V */
#define STD_HIGH 					0x01u 

/* Physical state 0V */
#define STD_LOW 					0x00u 

/* Logical state active */
#define STD_ACTIVE 					0x01u 

/* Logical state idle */
#define STD_IDLE 					0x00u 

/* Logical state ON (Enalbe) */
#define STD_ON			 			0x01u 

/* Logical state OFF (Disable) */
#define STD_OFF 					0x00u

/*****************************************************************/
/*				        Types Definition        		         */
/*****************************************************************/

/* Standard API return type */
typedef uint8 Std_ReturnType;

/*
   structre to request the version of a BSW module using
   the <Module name>_GetVersionInfo() function
*/
typedef struct 
{
	uint16	vendorID;
	uint16	moduleID;
	uint8	sw_major_version;
	uint8	sw_minor_version;
	uint8	sw_patch_version;
	
}Std_VersionInfoType;



/*****************************************************************/
/*				        Functions Prototype        		         */
/*****************************************************************/


#endif /* STD_TYPES_H */

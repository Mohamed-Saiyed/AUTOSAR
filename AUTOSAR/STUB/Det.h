/**********************************************************************************
***********************************************************************************
**														  						 **		
**	FILENAME	:	Det.h                              					     	 **
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
**	DESCRIPTION : 	NA       													 **
**                                                                               **
**	SPECIFICATION(S) : AUTOSAR_SWS_DevelopmentErrorTracer, AUTOSAR Release 4.3.1 **
**                                                       						 **
**	MAY BE CHANGED BY USER : Yes                          						 **
**                                                       					     **
***********************************************************************************/
#ifndef DET_H
#define DET_H

/*****************************************************************/
/*				    	Include Headers					         */
/*****************************************************************/

#include "Std_Types.h "

/*****************************************************************/
/*				        Macros Definition       		         */
/*****************************************************************/

/* Module Version 1.0.0 */
#define DET_MAJOR_VERSION           (1U)
#define DET_MINOR_VERSION           (0U)
#define DET_PATCH_VERSION           (0U)

/* AUTOSAR Version 4.3.1 */
#define DET_AR_RELEASE_MAJOR_VERSION   (4U)
#define DET_AR_RELEASE_MINOR_VERSION   (3U)
#define DET_AR_RELEASE_PATCH_VERSION   (1U)

/*****************************************************************/
/*				        Functions Prototype        		         */
/*****************************************************************/

extern Std_ReturnType Det_ReportError(uint16 ModuleId, uint8 InstanceId, uint8 ApiId, uint8 ErrorId);

#endif /*DET_H*/

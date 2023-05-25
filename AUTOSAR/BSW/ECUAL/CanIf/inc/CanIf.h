/**********************************************************************************
***********************************************************************************
**														  						 **		
**	FILENAME	:	CanIf.h                              					     **
**	                                                      						 **
**	VERSION		: 	1.0.0                                 						 **
**                                                        						 **
**	DATE		:	2021-4-8                            						 **
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
**	DESCRIPTION : Can Interface Module header file. 							 **
**                                                                               **
**	SPECIFICATION(S) : AUTOSAR_SWS_CANInterface, AUTOSAR Release 4.3.1           **
**                                                       						 **
**	MAY BE CHANGED BY USER : No                          						 **
**                                                       					     **
***********************************************************************************/
#ifndef CANIF_H
#define CANIF_H

/*****************************************************************/
/*				    	Include Headers					         */
/*****************************************************************/

#include "CanIf_Types.h"
#include "CanIf_Cfg.h"


/*****************************************************************/
/*				        Macros Definition       		         */
/*****************************************************************/

/* CanIf Module Vendor ID */
#define CANIF_VENDOR_ID		(0x40u)

/* CanIf Driver Module ID */
#define CANIF_MODULE_ID		(60u)

/* CanIf Driver Instance ID */
#define CANIF_INSTANCE_ID	(0x00u)


/*	Moudle Version	1.0.0 */
#define CANIF_SW_MAJOR_VERSION			(0x01u)
#define CANIF_SW_MINOR_VERSION			(0x00u)
#define CANIF_SW_PATCH_VERSION			(0x00u)

/* Autosar version 4.3.1 */
#define CANIF_AR_RELEASE_MAJOR_VERSION	(0x04u)
#define CANIF_AR_RELEASE_MINOR_VERSION	(0x03u)
#define CANIF_AR_RELEASE_PATCH_VERSION	(0x01u)

/**************** Version Check ******************/

#if ((CANIF_TYPES_AR_RELEASE_MAJOR_VERSION != CANIF_AR_RELEASE_MAJOR_VERSION)\
 ||  (CANIF_TYPES_AR_RELEASE_MINOR_VERSION != CANIF_AR_RELEASE_MINOR_VERSION)\
 ||  (CANIF_TYPES_AR_RELEASE_PATCH_VERSION != CANIF_AR_RELEASE_PATCH_VERSION))
  #error "Autosar version of CanIf_Types.h Doesn't Match"
#endif /* */


/**************** API Service IDs ****************/

#if (CANIF_DEV_ERROR_DETECT == STD_ON)

#if (CANIF_PUBLIC_READTXPDU_NOTIFY_STATUS_API == STD_ON)
 /* CanIf_ReadTxNotifStatus Services ID */
 #define CANIF_READTXNOTIFSTATUS_SID						(0x07u)
#endif /* CANIF_PUBLIC_READTXPDU_NOTIFY_STATUS_API */

#if (CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API == STD_ON)
 /* CanIf_ReadRxNotifStatus Services ID */
 #define CANIF_READRXNOTIFSTATUS_SID						(0x08u)
#endif /* CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API */

#if (CANIF_PUBLIC_SETDYNAMICTXID_API == STD_ON)
 /* CanIf_SetDynamicTxId Services ID */
 #define CANIF_SETDYNAMICTXID_SID							(0x0Cu)
#endif /* CANIF_PUBLIC_SETDYNAMICTXID_API */

/* CanIf_ControllerModeIndication Services ID */
#define CANIF_CONTROLLERMODEINDICATION_SID					(0x17u)


/******* Devlopment Errors Macros definition *****/

/* API service called with invalid parameter */
/* if the “CanId” parameter to be Invalid within the current configuration */
#define CANIF_E_PARAM_CANID 						(10u)
 
/* API service called with invalid pointer */
#define CANIF_E_PARAM_POINTER 						(20u)

/* API service used without module initialization */
#define CANIF_E_UNINIT 								(30u)

/* Transmit PDU ID invalid */
#define CANIF_E_INVALID_TXPDUID 					(50u)

/* Receive PDU ID invalid */ 
#define CANIF_E_INVALID_RXPDUID 					(60u)

#endif /* CANIF_DEV_ERROR_DETECT */

/* CanIf init status */
#define CANIF_UNINITIALIZED							(0u)
#define CANIF_INITIALIZED							(1u)

#if (CANIF_PUBLIC_SETDYNAMICTXID_API == STD_ON)
/**********************************************************************************
**	Service name: CanIf_SetDynamicTxId                         					 **
**	                                                      						 **
**	Syntax:	      FUNC( void, CANIF_CODE ) CanIf_SetDynamicTxId		    		 **
**				  (																 **
**					PduIdType CanIfTxSduId,                                      **
**				    Can_IdType CanId                                             **
**				  )                                                              **
**																				 **
**  Description : This API 													     **
**				 -reconfigures the corresponding CAN identifier					 **
**				  of the requested CAN L-PDU.                                    **
**                                                        						 **
**	Service ID:   0x0C                            						    	 **
**                                                        						 **
**	Sync/Async:	  Synchronous           						 				 **
**																				 **
**  Reentrancy:   Non Reentrant                                            		 **
**                                                        						 **
**	Parameters (in): CanIfTxSduId - L-SDU handle to be transmitted.       		 **
**				     CanId        - CAN ID of CAN L-SDU.                		 **
**                                                        						 **
**	Parameters (inout): NA               						 				 **
**                                                   						 	 **                                  
**	Parameters (out):   NA    													 **
**                                                                               **
**	Return value:    	NA											        	 **									
**                                                       						 **                                  
***********************************************************************************/
FUNC( void, CANIF_CODE ) CanIf_SetDynamicTxId
(
	PduIdType CanIfTxSduId,
	Can_IdType CanId
);

#endif /* CANIF_PUBLIC_SETDYNAMICTXID_API */

#if(CANIF_PUBLIC_READTXPDU_NOTIFY_STATUS_API == STD_ON)
/**********************************************************************************
**	Service name: CanIf_ReadTxNotifStatus                     					 **
**	                                                      						 **
**	Syntax:	   FUNC( CanIf_NotifStatusType, CANIF_CODE ) CanIf_ReadTxNotifStatus **		    		 
**			   (																 **
** 				  PduIdType CanIfTxSduId,                                        **
**			   )                                                                 **
**																				 **
**  Description : This API 													     **
**				 -Reads the confirmation status of a specific static or 		 **
**				 dynamic CAN Tx L-PDU, requested by the CanIfTxSduId.            **
**                                                        						 **
**	Service ID:   0x07                            						    	 **
**                                                        						 **
**	Sync/Async:	  Synchronous           						 				 **
**																				 **
**  Reentrancy:   Non Reentrant                                            		 **
**                                                        						 **
**	Parameters (in): CanIfTxSduId - L-SDU handle to be transmitted.       		 **
**                                                        						 **
**	Parameters (inout): NA               						 				 **
**                                                   						 	 **                                           		
**	Parameters (out):   NA    													 **
**                                                                               **
**	Return value:    RetVal- the confirmation status Of Tx L-PDU 				 **
**					 CANIF_NO_NOTIFICATION				 					     **
**                   CANIF_TX_RX_NOTIFICATION                				     **											 
**                                                       						 **                                  				
***********************************************************************************/
FUNC( CanIf_NotifStatusType, CANIF_CODE) CanIf_ReadTxNotifStatus
(
	PduIdType CanIfTxSduId
);

#endif /* CANIF_PUBLIC_READTXPDU_NOTIFY_STATUS_API */

#endif /* CANIF_H */

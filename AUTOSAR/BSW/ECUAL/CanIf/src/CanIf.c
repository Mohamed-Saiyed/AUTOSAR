/**********************************************************************************
***********************************************************************************
**														  						 **		
**	FILENAME	:	CanIf.c                              					     **
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
**	DESCRIPTION : CanIf Interface Module source file.							 **
**                                                                               **
**	SPECIFICATION(S) : AUTOSAR_SWS_CANInterface, AUTOSAR Release 4.3.1           **
**                                                       						 **
**	MAY BE CHANGED BY USER : No                          						 **
**                                                       					     **
***********************************************************************************/

/***********************************************************************************/
/*				    			Include Headers			         				   */
/***********************************************************************************/

#include "CanIf.h"
#include "irq.h"

#if (CANIF_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"
#endif /* CANIF_DEV_ERROR_DETECT */

/**************** Version Check ******************/

#ifndef CANIF_SW_MAJOR_VERSION
#error "CANIF_SW_MAJOR_VERSION is not defined."
#endif /* CANIF_SW_MAJOR_VERSION */

#ifndef CANIF_SW_MINOR_VERSION
#error "CANIF_SW_MINOR_VERSION is not defined."
#endif /* CANIF_SW_MINOR_VERSION */

#ifndef CANIF_SW_PATCH_VERSION
#error "CANIF_SW_PATCH_VERSION is not defined."
#endif /* CANIF_SW_PATCH_VERSION */

#if (CANIF_DEV_ERROR_DETECT == STD_ON)

#if ( DET_AR_RELEASE_MAJOR_VERSION != CANIF_AR_RELEASE_MAJOR_VERSION )
#error "DET_AR_RELEASE_MAJOR_VERSION Doesn't Match."
#endif /* DET_AR_RELEASE_MAJOR_VERSION */

#if ( DET_AR_RELEASE_MINOR_VERSION != CANIF_AR_RELEASE_MINOR_VERSION )
#error "DET_AR_RELEASE_MINOR_VERSION Doesn't Match."
#endif /* DET_AR_RELEASE_MINOR_VERSION */

#if ( DET_AR_RELEASE_PATCH_VERSION != CANIF_AR_RELEASE_PATCH_VERSION )
#error "DET_AR_RELEASE_PATCH_VERSION Doesn't Match."
#endif /* DET_AR_RELEASE_PATCH_VERSION */

#endif /* CANIF_DEV_ERROR_DETECT */

/*******************************************************************************/
/*                      Private Macro Definitions 			                   */
/*******************************************************************************/

#if (CANIF_DEV_ERROR_DETECT == STD_ON)

/* Mask for the CanId Type (Standard , Extended) */
#define CANIF_CANID_TYPE_MASK		(0x80000000UL)

/* CanIf Error status definition */
#define CANIF_OK	(1u)
#define CANIF_ERROR (0u)

#endif /* CANIF_DEV_ERROR_DETECT */

/*******************************************************************************/
/*                      Local Types Definition		 	  	                   */
/*******************************************************************************/

/* Struct to Hold various Flags and data for Tx PDUs */
typedef struct 
{
	/* Variable to hold the confirmation status for Tx L-PDUs */
	/* Shall be set by CanIf_TxConfirmation() Api */
#if(CANIF_PUBLIC_READTXPDU_NOTIFY_STATUS_API == STD_ON)
	uint8 TxConfirmationStatus;
#endif /* CANIF_PUBLIC_READTXPDU_NOTIFY_STATUS_API */
	
}TxLPduType;



/*******************************************************************************/
/*                      Local Variables Definition  		                   */
/*******************************************************************************/

/* Static variable to Save CanIf State */
static uint8 CanInitState = CANIF_UNINITIALIZED;

/* Pointer to Save CanIf configuration parameters to be used in various Functions */
static const CanIf_ConfigType* CanIf_ConfigPtr;

/* TxLPduType object for each Tx L-PUD */
static TxLPduType TxLPdu[TX_CAN_L_PDU_NUM];


/*******************************************************************************/
/*                      Local Function ProtoType  			                   */
/*******************************************************************************/

#if (CANIF_DEV_ERROR_DETECT == STD_ON)

/* Inline function to chek the TX PUD ID */
LOCAL_INLINE uint8 CanIfCheckTxId( PduIdType CanIfTxSduId);

/* Inline Function to Check the validation of The Pdu CanId */
LOCAL_INLINE uint8 CanIfCheckCanId(Can_IdType CanId);

/* Inline Function to Get a Pointer to corresponding TxPduId configuration Structure */
LOCAL_INLINE CanIfTxPduCfgType* CanIfGetTxPduCfg(PduIdType CanIfTxSduId);

#endif /* CANIF_DEV_ERROR_DETECT */

/*
	[SWS_CANIF_00335] This API can be enabled or disabled at pre-compile time 
	configuration globally by the parameter	CANIF_PUBLIC_READTXPDU_NOTIFY_STATUS_API
*/	
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
FUNC( CanIf_NotifStatusType, CANIF_CODE) CanIf_ReadTxNotifStatus(PduIdType CanIfTxSduId)
{
	/* Variable to hold the Api return value */
	CanIf_NotifStatusType RetVal  = CANIF_NO_NOTIFICATION;
		
#if (CANIF_DEV_ERROR_DETECT == STD_ON)

/* Variable to Save the API's Error State */
	Std_ReturnType ErrorState = E_OK;

	if( CanInitState == CANIF_UNINITIALIZED )
	{
	/*	
		[SWS_CANIF_00901] all CanIf API services other than CanIf_Init() and
		CanIf_GetVersionInfo() shall report to the DET (using CANIF_E_UNINIT)
		unless the CanIf has been initialized with a preceding call of CanIf_Init().
	*/	
		Det_ReportError(CANIF_MODULE_ID  ,
						CANIF_INSTANCE_ID,
						CANIF_READTXNOTIFSTATUS_SID,
						CANIF_E_UNINIT);
						
		/* Set the API Errorstate to E_NOT_OK */
		ErrorState = E_NOT_OK;				
	}
	else if( CanIfCheckTxId(CanIfTxSduId) != CANIF_OK)
	{
	/*	
		[SWS_CANIF_00331] If parameter CanIfTxSduId of The Api is out of range
		CanIf shall report development error code CANIF_E_INVALID_TXPDUID to
		the Det_ReportError service of the DET when The Api is called
	*/	
		Det_ReportError(CANIF_MODULE_ID  ,
						CANIF_INSTANCE_ID,
						CANIF_READTXNOTIFSTATUS_SID,
						CANIF_E_INVALID_TXPDUID);
						
		/* Set the API Errorstate to E_NOT_OK */
		ErrorState = E_NOT_OK;		
	}
	else if((CanIf_ConfigPtr->CanIfInitCfgObj->CanIfTxPduCfgObj[CanIfTxSduId].CanIfTxPduReadNotifyStatus) != TRUE)
	{
		
	/*	
		[SWS_CANIF_00331] If parameter CanIfTxSduId of The Api has no status 
		information was configured for this CAN Tx L-SDU, CanIf shall report
		development error code CANIF_E_INVALID_TXPDUID to the Det_ReportError
		service of the DET when The Api is called
	*/	
		Det_ReportError(CANIF_MODULE_ID  ,
						CANIF_INSTANCE_ID,
						CANIF_READTXNOTIFSTATUS_SID,
						CANIF_E_INVALID_TXPDUID);
						
		/* Set the API Errorstate to E_NOT_OK */
		ErrorState = E_NOT_OK;	
	}
	/* (MISRA-C:2004 Rule 14.10 (required)) 
	All if … else if constructs shall be terminated with an else clause. */
	else
	{
		
	}
#endif /* CANIF_DEV_ERROR_DETECT */

#if (CANIF_DEV_ERROR_DETECT == STD_ON)
	/* Api Passes all checks */
	if(E_OK == ErrorState)	
#endif /* CANIF_DEV_ERROR_DETECT */
	{
		/* Enter Critical section */
		irq_Disable();
		
		/* Check for Tx L-SDU Notification Status */
		if(TxLPdu[CanIfTxSduId].TxConfirmationStatus != CANIF_NO_NOTIFICATION)
		{
			RetVal = CANIF_TX_RX_NOTIFICATION;
		}
		/*
			[SWS_CANIF_00393] If configuration parameters CANIF_PUBLIC_READTXPDU_NOTIFY_STATUS_API
			and CANIF_TXPDU_READ_NOTIFYSTATUS for the transmitted L-SDU are set to TRUE, 
			and if CanIf_ReadTxNotifStatus() is called, the CanIf shall reset the notification status
			for the transmitted L-SDU.
		*/
		TxLPdu[CanIfTxSduId].TxConfirmationStatus = CANIF_NO_NOTIFICATION;
		
		/* Exit Critical section */
		 irq_Enable(); 
	}
	
	/* return the Tx L-SDU NotifyStatus Value */
	return RetVal;
}

#endif /* CANIF_PUBLIC_READTXPDU_NOTIFY_STATUS_API */


/*
	[SWS_CANIF_00357] The function CanIf_SetDynamicTxId() shall be pre compile time configurable
	On/Off by the configuration parameter CANIF_PUBLIC_SETDYNAMICTXID_API
*/	
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
)
{
	/* Pointer to point to the TxPduData */
	CanIfTxPduCfgType* CanIfTxPduCfg;
	
#if (CANIF_DEV_ERROR_DETECT == STD_ON)
	
	/* Variable to Hold the API's Error State */
	Std_ReturnType ErrorState = E_OK;
	
	if( CanInitState == CANIF_UNINITIALIZED )
	{
	/*	
		[SWS_CANIF_00901] all CanIf API services other than CanIf_Init() and
		CanIf_GetVersionInfo() shall report to the DET (using CANIF_E_UNINIT)
		unless the CanIf has been initialized with a preceding call of CanIf_Init().
	*/	
		Det_ReportError(CANIF_MODULE_ID  ,
						CANIF_INSTANCE_ID,
						CANIF_SETDYNAMICTXID_SID,
						CANIF_E_UNINIT);
						
	/*
		[SWS_CANIF_00355] If CanIf was not initialized before calling
		The Api, then the Api shall not execute a reconfiguration of Tx CanId.
	*/					
		/* Set the API Errorstate to E_NOT_OK */
		ErrorState = E_NOT_OK;				
	}
	else if( CanIfCheckTxId(CanIfTxSduId) != CANIF_OK)
	{
		
	/*	
		[SWS_CANIF_00352] If parameter CanIfTxSduId of The Api has an invalid value,
		CanIf shall report development	error code CANIF_E_INVALID_TXPDUID to 
		the Det_ReportError service of the DET module, when Api is called.
	*/		
		Det_ReportError(CANIF_MODULE_ID  ,
						CANIF_INSTANCE_ID,
						CANIF_SETDYNAMICTXID_SID,
						CANIF_E_INVALID_TXPDUID);
						
						
		/* Set the API Errorstate to E_NOT_OK */
		ErrorState = E_NOT_OK;		
	}
	else if (CanIfCheckCanId(CanId) != CANIF_OK )
	{
		
	/*	
		[SWS_CANIF_00353] d If parameter CanId of API has an invalid value,
		CanIf shall report development error code CANIF_E_PARAM_CANID to the
		Det_ReportError service of the DET module, when The Api is called.
	*/		
		Det_ReportError(CANIF_MODULE_ID  ,
						CANIF_INSTANCE_ID,
						CANIF_SETDYNAMICTXID_SID,
						CANIF_E_PARAM_CANID);
						
		/* Set the API Errorstate to E_NOT_OK */
		ErrorState = E_NOT_OK;		
	}
	/* (MISRA-C:2004 Rule 14.10 (required)) 
	All if … else if constructs shall be terminated with an else clause. */
	else
	{
		
	}
#endif /* CANIF_DEV_ERROR_DETECT */

#if (CANIF_DEV_ERROR_DETECT == STD_ON)
	/* Api Passes all checks */
	if(E_OK == ErrorState)	
#endif /* CANIF_DEV_ERROR_DETECT */
	{		
		/* Enter Critical section */
		irq_Disable();
		
		/* Get the corresponding TxPduId Configuration Structure */ 
		CanIfTxPduCfg = CanIfGetTxPduCfg(CanIfTxSduId);
		
		/* Change the current TxPdu CanId to the new one */
		CanIfTxPduCfg->CanIfTxPduCanId = CanId ;
		
		/* Exit Critical section */
		 irq_Enable(); 
		
	}
}

#endif /* CANIF_PUBLIC_SETDYNAMICTXID_API */

#if (CANIF_DEV_ERROR_DETECT == STD_ON)
/**********************************************************************************
**	Service name: CanIfCheckTxId                             		             **
**	                                                      						 **
**	Syntax:	      uint8 CanIfCheckTxId	  						 		         **
**				  ( 															 **
**					PduIdType CanIfTxSduId								     	 **
** 				  )																 **
**																				 **
**  Description : This LOCAL_INLINE API 									     **
**				  -Checks the TX PUD-ID if valid or Not.					   	 **
**																				 **
**                                                        						 **
**	Service ID:   NA                           						    	     **
**                                                        						 **
**	Sync/Async:	  Synchronous           						 				 **
**																				 **
**  Reentrancy:   Reentrant                                              		 **
**                                                        						 **
**	Parameters (in): CanIfTxSduId - L-SDU handle to be transmitted.       		 **
**                                                        						 **
**	Parameters (inout): NA               						 				 **
**                                                   						 	 **                                           					
**	Parameters (out):   NA    													 **
**                                                                               **
**	Return value:    ErrorState of CanIfTxSduId									 **
**					 CANIF_OK    - CanIfTxSduId Valid							 **
**                   CANIF_ERROR - CanIfTxSduId Not Valid          				 **
**																 				 **
***********************************************************************************/
LOCAL_INLINE uint8 CanIfCheckTxId( PduIdType CanIfTxSduId)
{
	uint8 ErrorState  = (uint8)CANIF_OK;
	
	if(CanIfTxSduId >= TX_CAN_L_PDU_NUM)
	{
		ErrorState = (uint8)CANIF_ERROR;
	}
	
	return (ErrorState);
}

/**********************************************************************************
**	Service name: CanIfCheckCanId                             		             **
**	                                                      						 **
**	Syntax:	      uint8 CanIfCheckCanId	  						 		         **
**				  ( 															 **
**					Can_IdType CanId									     	 **
** 				  )																 **
**																				 **
**  Description : This LOCAL_INLINE API 									     **
**				  -Checks the validation of The Pdu CanId.					   	 **
**																				 **
**                                                        						 **
**	Service ID:   NA                           						    	     **
**                                                        						 **
**	Sync/Async:	  Synchronous           						 				 **
**																				 **
**  Reentrancy:   Reentrant                                              		 **
**                                                        						 **
**	Parameters (in): CanId - CAN ID of CAN L-SDU.			               		 **
**                                                        						 **
**	Parameters (inout): NA               						 				 **
**                                                   						 	 **                                           					
**	Parameters (out):   NA    													 **
**                                                                               **
**	Return value:    ErrorState of CanId										 **
**					 CANIF_OK    - CanId Valid									 **
**                   CANIF_ERROR - CanId Not Valid          					 **
**																 				 **
***********************************************************************************/
LOCAL_INLINE uint8 CanIfCheckCanId(Can_IdType CanId)
{
	uint8 ErrorState  = (uint8)CANIF_OK;
	
	if (((( (uint32)CanId & CANIF_CANID_TYPE_MASK) == 0) && (( (uint32)CanId & 0x3FFFF800UL) != 0)) || 
	    ((( (uint32)CanId & CANIF_CANID_TYPE_MASK) != 0) && (( (uint32)CanId & 0x20000000UL) != 0)))
	{
		ErrorState = (uint8)CANIF_ERROR;
	}
	
	return (ErrorState);
}

#endif /* CANIF_DEV_ERROR_DETECT */

/**********************************************************************************
**	Service name: CanIfGetTxPduCfg                             		             **
**	                                                      						 **
**	Syntax:	      CanIfTxPduCfgType* CanIfGetTxPduCfg	  		 		         **
**				  ( 															 **
**					PduIdType CanIfTxSduId								     	 **
** 				  )																 **
**																				 **
**  Description : This LOCAL_INLINE API 									     **
**				  -Gets a Pointer to corresponding TxPduId						 **
**				   configuration Structure.										 **
**																				 **
**                                                        						 **
**	Service ID:   NA                           						    	     **
**                                                        						 **
**	Sync/Async:	  Synchronous           						 				 **
**																				 **
**  Reentrancy:   Reentrant                                              		 **
**                                                        						 **
**	Parameters (in): CanIfTxSduId - L-SDU handle to be transmitted.       		 **
**                                                        						 **
**	Parameters (inout): NA               						 				 **
**                                                   						 	 **                                           					
**	Parameters (out):   NA    													 **
**                                                                               **
**	Return value:  A pointer to corresponding Tx L-SDU configuration Strcture.   **
**																				 **
***********************************************************************************/
LOCAL_INLINE CanIfTxPduCfgType* CanIfGetTxPduCfg(PduIdType CanIfTxSduId)
{
	CanIfTxPduCfgType* CanIfTxPduCfg;
	
	CanIfTxPduCfg = (CanIfTxPduCfgType* )&(CanIf_ConfigPtr->CanIfInitCfgObj->CanIfTxPduCfgObj[CanIfTxSduId]);
	
	return (CanIfTxPduCfg);
}

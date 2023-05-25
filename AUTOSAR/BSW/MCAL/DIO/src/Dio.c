/**********************************************************************************
***********************************************************************************
**														  						 **		
**	FILENAME	:	Dio.c                              						     **
**	                                                      						 **
**	VERSION		: 	1.0.0                                 						 **
**                                                        						 **
**	DATE		:	2021-3-24                             						 **
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
**	DESCRIPTION : Digital I/O Driver source file      							 **
**                                                                               **
**	SPECIFICATION(S) : AUTOSAR_SWS_DIODriver, AUTOSAR Release 4.3.1              **
**                                                       						 **
**	MAY BE CHANGED BY USER : No                          						 **
**                                                       					     **
***********************************************************************************/

/***********************************************************************************/
/*				    			Include Headers			         				   */
/***********************************************************************************/

#include "Dio.h"
#include "Dio_MemMap.h"
#include "SchM_Dio.h"
#include "Common_Macros.h"
#include "hw_gpio.h"
#include "hw_memmap.h"

#if (DioDevErrorDetect == STD_ON)
#include "Det.h"
#endif /* DioDevErrorDetect */

/**************** Version Check ******************/

#ifndef DIO_SW_MAJOR_VERSION
#error "DIO_SW_MAJOR_VERSION is not defined."
#endif /* DIO_SW_MAJOR_VERSION */

#ifndef DIO_SW_MINOR_VERSION
#error "DIO_SW_MINOR_VERSION is not defined."
#endif /* DIO_SW_MINOR_VERSION */

#ifndef DIO_SW_PATCH_VERSION
#error "DIO_SW_PATCH_VERSION is not defined."
#endif /* DIO_SW_PATCH_VERSION */

#if (DioDevErrorDetect == STD_ON)

#if ( DET_AR_RELEASE_MAJOR_VERSION != DIO_AR_RELEASE_MAJOR_VERSION )
#error "DET_AR_RELEASE_MAJOR_VERSION Doesn't Match."
#endif /* DET_AR_RELEASE_MAJOR_VERSION */

#if ( DET_AR_RELEASE_MINOR_VERSION != DIO_AR_RELEASE_MINOR_VERSION )
#error "DET_AR_RELEASE_MINOR_VERSION Doesn't Match."
#endif /* DET_AR_RELEASE_MINOR_VERSION */

#if ( DET_AR_RELEASE_PATCH_VERSION != DIO_AR_RELEASE_PATCH_VERSION )
#error "DET_AR_RELEASE_PATCH_VERSION Doesn't Match."
#endif /* DET_AR_RELEASE_PATCH_VERSION */

#endif /* DioDevErrorDetect */

/*******************************************************************************/
/*                      Private Macro Definitions 			                   */
/*******************************************************************************/

#if (DioDevErrorDetect == STD_ON)

/* Error status definition */
#define DIO_ERROR	(0u)
#define DIO_OK		(1u)
#endif /* DioDevErrorDetect */

/* 0th bit definition */
#define DIO_NUM_0 	(0u)

/* Dio directions definitions */
#define DIO_PIN_INPUT	(0u)
#define DIO_PIN_OUTPUT	(1u)

/* Dio Maximum pins in one port */
#define DIO_PORT_WIDTH  (0x08u)

/* Dio Data regeister definition */
#define DIO_DATA_REG	(GPIO_O_DATA + 0x3FC)

/* Dio port addresses for Tiva C */
static const uint32 DioPortAddress[] = 
{
	GPIO_PORTA_BASE,
	GPIO_PORTB_BASE,
	GPIO_PORTC_BASE,
	GPIO_PORTD_BASE,
	GPIO_PORTE_BASE,
	GPIO_PORTF_BASE
	
};

/* extern the main Dio container that includes all configuration  */
extern Dio_ConfigType Dio_Config;

/* Save the main container in a private one */	
static const Dio_ConfigType* DioConfig = &Dio_Config ;

#if (DioDevErrorDetect == STD_ON)

/* INLINE Function to Check ChannelId if it is valid or Not */
LOCAL_INLINE uint8 DioCheckChannelID(Dio_ChannelType ChannelId);

/* INLINE Function to Check GroupIdPtr if it is valid or Not */
LOCAL_INLINE uint8 DioCheckGroupID(const Dio_ChannelGroupType* GroupIdPtr);

/* INLINE Function to Check PortId if it is valid or Not */
LOCAL_INLINE uint8 DioCheckPortID(Dio_PortType PortId);

#endif /* DioDevErrorDetect */

/* INLINE Function to Get the port address from the port symbolic ID */
LOCAL_INLINE uint32 DioGetPortAddress(Dio_PortType PortNumber);

/* INLINE Function to Get the PortNumber from the Channel symbolic ID */
LOCAL_INLINE Dio_PortType DioGetChannelPortNumber(Dio_ChannelType ChannelId);

/* INLINE Function to Get the Pin position from the Channel symbolic ID */
LOCAL_INLINE uint8 DioGetChannelPinNumber(Dio_ChannelType ChannelId);

/* INLINE Function to Set a value of the Pin of the specifies level */
LOCAL_INLINE void DioWritePin(uint32 PortAddress, uint8 PinNumber, Dio_LevelType Level);

/* INLINE Function to Get a value of the Pin Level */
LOCAL_INLINE Dio_LevelType DioReadPin(uint32 PortAddress, uint8 PinNumber);

/* INLINE Function to Get the value of a Pin Direction */
LOCAL_INLINE uint8 DioGetPinDirection(uint32 PortAddress, uint8 PinNumber);


/***********************************************************************************/
/*				    		Global Function Definitions	         				   */
/***********************************************************************************/

/**********************************************************************************
**	Service name: Dio_ReadChannel                             					 **
**	                                                      						 **
**	Syntax:	      Dio_LevelType Dio_ReadChannel									 **
**				  ( 															 **
**					const Dio_ChannelType ChannelId								 **
** 				  )																 **
**																				 **
**  Description : This API 													     **
**				  -retrun the physical level of the specified DIO channel   	 **
**				  -shall work on input and output channels						 **
**                                                        						 **
**	Service ID:   0x00                            						    	 **
**                                                        						 **
**	Sync/Async:	  Synchronous           						 				 **
**																				 **
**  Reentrancy:   Reentrant                                              		 **
**                                                        						 **
**	Parameters (in): ChannelId - ID of DIO channel                         		 **
**                                                        						 **
**	Parameters (inout): NA               						 				 **
**                                                   						 	 **                                           						 **
**	Parameters (out):   NA    													 **
**                                                                               **
**	Return value:     The physical level of the corresponding CannelId        	 **												 
**                                                       						 **                                  					     **
***********************************************************************************/
Dio_LevelType Dio_ReadChannel( const Dio_ChannelType ChannelId )
{
	/* Variable to save the channel's port number  */
	Dio_PortType  ChannelPortNumber ;
	/* Varialbe to save the channel's Pin Position */
	uint8  	      ChannelPinNumber  ;
	/* Variable to hold the channel's port address */
	uint32 		  ChannelPortAddress;
	/* varilabe to hold the return value(physical level of the channel) */
	Dio_LevelType ChannelLevel	    ;
	
#if (DioDevErrorDetect == STD_ON)
	/* 
	   [SWS_Dio_00074] The Api shall check the channel ID if 
	    development error detection is enabled
	*/
	uint8 Check      = DioCheckChannelID(ChannelId);
	/* Variable to Save the API's Error State */
	uint8 ErrorState = E_OK;
	
	/* if Haven't the check passesd */
	if(DIO_ERROR == Check)
	{
		/* 
		   [SWS_Dio_00074] if the ChannelId is not valid within the current configuration
		   the API shall raise the error DIO_E_PARAM_INVALID_CHANNEL_ID to the DET.  
		*/
		Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID, DIO_READCHANNEL_SID, DIO_E_PARAM_INVALID_CHANNEL_ID);
		
		/* Set the API Errorstate to E_NOT_OK*/
		ErrorState = E_NOT_OK;
		
		/* 
		   [SWS_Dio_00118] if development errors are enabled and an error ocurred 
	       the Dio module’s read functions shall return with the value '0'.
		*/	
		ChannelLevel = STD_LOW ;
	}
	
#endif
	
#if (DioDevErrorDetect == STD_ON)
	/* Have all checks passed */
	if(E_OK == ErrorState)
#endif
	{
		/* Get the channel port number from its ID */
		ChannelPortNumber  = DioGetChannelPortNumber(ChannelId);
		
		/* Get the channel's Pin Position */
		ChannelPinNumber   = DioGetChannelPinNumber(ChannelId);
		
		/* Get the channel's port address */
		ChannelPortAddress = DioGetPortAddress(ChannelPortNumber);
		
		/* Read the channel level to decide the return value */
		/* if it is not low */
		if(DioReadPin(ChannelPortAddress, ChannelPinNumber) != STD_LOW)
		{
			ChannelLevel = STD_HIGH;
		}
	}
	
	/* return the Channel level value */
	return (ChannelLevel);
}

/**********************************************************************************
**	Service name: Dio_WriteChannel                             					 **
**	                                                      						 **
**	Syntax:	      void Dio_WriteChannel									 		 **
**				  ( 															 **
**					const Dio_ChannelType ChannelId,						     **
**					const Dio_LevelType Level 									 **
** 				  )																 **
**																				 **
**  Description : This API 													     **
**				  -set the level of a single DIO channel to STD_HIGH or STD_LOW  **
**				  -shall work on input and output channels						 **
**				  -have no effect on the physical output level On Input Channels **
**                                                        						 **
**	Service ID:   0x01                            						    	 **
**                                                        						 **
**	Sync/Async:	  Synchronous           						 				 **
**																				 **
**  Reentrancy:   Reentrant                                              		 **
**                                                        						 **
**	Parameters (in): ChannelId - ID of DIO channel							     **
**					 Level     - Value to be written							 **
**                                                        						 **
**	Parameters (inout): NA               						 				 **
**                                                   						 	 **                                           		
**	Parameters (out):   NA    													 **
**                                                                               **
**	Return value: NA				       	 									 **
**                                                       						 **                                  				
***********************************************************************************/
void Dio_WriteChannel( const Dio_ChannelType ChannelId, const Dio_LevelType Level )
{
 	/* Variable to save the channel's port number   */	
	Dio_PortType  ChannelPortNumber ;
	/* Varialbe to save the channel's Pin Position  */
	uint8  	      ChannelPinNumber  ;
	/* Variable to hold the channel's port address  */
	uint32 		  ChannelPortAddress;
	/* Variable to hold the channel's Pin Direction */
	uint8		  ChannelDirection = DIO_PIN_OUTPUT;
	
#if (DioDevErrorDetect == STD_ON)
	/* 
	   [SWS_Dio_00074] The Api shall check the channel ID if 
	    development error detection is enabled
	*/
	uint8 Check      = DioCheckChannelID(ChannelId);
	/* Variable to Save the API's Error State */
	uint8 ErrorState = E_OK;
	
	/* if Haven't the check passesd */
	if(DIO_ERROR == Check)
	{
		/* 
		   [SWS_Dio_00074] if the ChannelId is not valid within the current configuration
		   the API shall raise the error DIO_E_PARAM_INVALID_CHANNEL_ID to the DET.  
		*/
		Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID, DIO_WRITECHANNEL_SID, DIO_E_PARAM_INVALID_CHANNEL_ID);
		
		/* Set the API Errorstate to E_NOT_OK*/
		ErrorState = E_NOT_OK;
	}
	
#endif /* DioDevErrorDetect */
	/*
		[SWS_Dio_00119] if development errors are enabled and an error ocurred,
		the Dio module’s write functions shall NOT process the write command.
	*/		
#if (DioDevErrorDetect == STD_ON)
	/* Have all checks passed */
	if(E_OK == ErrorState)
#endif /* DioDevErrorDetect */
	{
		/* Get the channel port number from its ID */
		ChannelPortNumber  = DioGetChannelPortNumber(ChannelId);
		
		/* Get the channel's Pin Position */
		ChannelPinNumber   = DioGetChannelPinNumber(ChannelId);
		
		/* Get the channel's port address */
		ChannelPortAddress = DioGetPortAddress(ChannelPortNumber);
		
		/* Get the channel's PIN Direction */
		ChannelDirection   = DioGetPinDirection(ChannelPortAddress, ChannelPinNumber);
		
		/*
			[SWS_Dio_00070] if a Dio write function is used on an input channel,
			it shall have no effect on the physical output level
		*/
		if(DIO_PIN_INPUT != ChannelDirection)
		{
			/* Decide the value to be written */
			/*if it is high*/
			if(STD_HIGH == Level)
			{
				/* Set the corresponding channel to STD_HIGH */
				DioWritePin(ChannelPortAddress, ChannelPinNumber, STD_HIGH);
			}
			else
			{
				/* if low, Set the corresponding channel to STD_LOW */
				DioWritePin(ChannelPortAddress, ChannelPinNumber, STD_LOW);
			}
		}
	}

}

/**********************************************************************************
**	Service name: Dio_ReadPort                             						 **
**	                                                      						 **
**	Syntax:	      Dio_PortLevelType Dio_ReadPort								 **
**				  ( 															 **
**					const Dio_PortType PortId							         **
** 				  )																 **
**																				 **
**  Description : This API 													     **
**				  -return the level of all channels of that port  				 **
**                                                        						 **
**	Service ID:   0x02                            						    	 **
**                                                        						 **
**	Sync/Async:	  Synchronous           						 				 **
**																				 **
**  Reentrancy:   Reentrant                                              		 **
**                                                        						 **
**	Parameters (in): PortId - ID of DIO Port                         		     **
**                                                        						 **
**	Parameters (inout): NA               						 				 **                                              
**                                                   						 	 **                                           	
**	Parameters (out):   NA    													 **                                              
**                                                                               **                                              
**	Return value      :the level of all channels of that port       		 	 **												 
**                                                       						 **                                  			
***********************************************************************************/                                             
Dio_PortLevelType Dio_ReadPort( const Dio_PortType PortId )
{
	/* Variable to save the port address  */
	uint32 			  PortAddress;
	/* Variable to save the port level    */
	Dio_PortLevelType PortLevel;
	
#if (DioDevErrorDetect == STD_ON)

	/* 
	   [SWS_Dio_00075] The Api shall check the Port ID if 
	    development error detection is enabled
	*/
	uint8 Check      = DioCheckPortID(PortId);
	
	/* Variable to Save the API's Error State */
	uint8 ErrorState = E_OK;
	
	/* if Haven't the check passesd */
	if(DIO_ERROR == Check)
	{
		/* 
		   [SWS_Dio_00075] if the PortId is not valid within the current configuration
		   the API shall raise the error DIO_E_PARAM_INVALID_PORT_ID to the DET.  
		*/
		Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID, DIO_READPORT_SID, DIO_E_PARAM_INVALID_PORT_ID);
		
		/* Set the API Errorstate to E_NOT_OK */
		ErrorState = E_NOT_OK;
		
		/* 
		   [SWS_Dio_00118] if development errors are enabled and an error ocurred 
		   the Dio module’s read functions shall return with the value '0'.
		*/	
		PortLevel = (Dio_PortLevelType)STD_LOW ;
	}
	
#endif /* DioDevErrorDetect */
	
#if (DioDevErrorDetect == STD_ON)	
	/* Have all checks passed */
	if(E_OK == ErrorState)
#endif	/* DioDevErrorDetect */
	{
		/* Get the Corresponding port address */
		PortAddress = DioGetPortAddress(PortId);
		
		/* Get the Corresponding port level*/
		PortLevel = (GET_PORT((uint32)(PortAddress + DIO_DATA_REG)));
	}
	
	/* Return the port level */
	return (PortLevel);
}

/**********************************************************************************
**	Service name: Dio_WritePort                             					 **
**	                                                      						 **
**	Syntax:	      void Dio_WritePort									 		 **
**				  ( 															 **
**					const Dio_PortType PortId,							         **
**					const Dio_PortLevelType Level 								 **
** 				  )																 **
**																				 **
**  Description : This API 													     **
**				  -set a value of the port										 **
**				  -shall ensure that the functionality of the input 			 **
**                 channels of that port is not affected 						 **
**                                                        						 **
**	Service ID:   0x03                            						    	 **
**                                                        						 **
**	Sync/Async:	  Synchronous           						 				 **
**																				 **
**  Reentrancy:   Reentrant                                              		 **
**                                                        						 **
**	Parameters (in): PortId - ID of DIO Port                         		     **
**					 Level  - Value to be written							     **
**                                                        						 **
**	Parameters (inout): NA               						 				 **
**                                                   						 	 **                                           			
**	Parameters (out):   NA    													 **
**                                                                               **
**	Return value: NA				       	 									 **
**                                                       						 **                                  					
***********************************************************************************/	
void Dio_WritePort( const Dio_PortType PortId, const Dio_PortLevelType Level )
{
	/* Variable to save the port address  */
	uint32 	 PortAddress;
	/* Varialbe to save the Pin Position  */
	uint8  	 PinNumber;
	/* Variable to hold Port Direction */
	uint8	 ChannelsDirection;
	/* Variable to hold the old data reg value */
	uint8 	 OldDataReg;
	/* Variable to hold the new Port data reg value */
	Dio_PortLevelType PortNewVal;
	
#if (DioDevErrorDetect == STD_ON)
	
	/* 
	   [SWS_Dio_00075] The Api shall check the Port ID if 
	    development error detection is enabled
	*/
	uint8 Check      = DioCheckPortID(PortId);
	
	/* Variable to Save the API's Error State */
	uint8 ErrorState = E_OK;
	
	/* if Haven't the check passesd */
	if(DIO_ERROR == Check)
	{
		/* 
		   [SWS_Dio_00075] if the PortId is not valid within the current configuration
		   the API shall raise the error DIO_E_PARAM_INVALID_PORT_ID to the DET.  
		*/ 	
		Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID, DIO_WRITEPORT_SID, DIO_E_PARAM_INVALID_PORT_ID);
		
		/* Set the API Errorstate to E_NOT_OK */
		ErrorState = E_NOT_OK;
	}
	
#endif

	/*
		[SWS_Dio_00119] if development errors are enabled and an error ocurred,
		the Dio module’s write functions shall NOT process the write command
	*/
#if (DioDevErrorDetect == STD_ON)
	/* Have all checks passed */
	if(E_OK == ErrorState)
#endif	
	{
		/* Get the Corresponding port address */
		PortAddress = DioGetPortAddress(PortId);
		
		/* Get the all Port's Pin direction */
		ChannelsDirection = (GET_PORT((uint32)(PortAddress + GPIO_O_DIR)));
		
		/* Get the old Dio Port Data register value */
		OldDataReg 		  = (GET_PORT((uint32)(PortAddress + DIO_DATA_REG)));
		
		/*
			[SWS_Dio_00004]The API shall ensure that the functionality of 
			the input channels of that port is not affected.
		*/
		/* Masking to the pin direction if it is input noting will be changed */
		PortNewVal = ((~ChannelsDirection) & OldDataReg) | (Level & ChannelsDirection);
		
		/*
			[SWS_Dio_00007] The API function shall simultaneously set the levels 
			 of all output channels (at one shot ).
		*/
		SET_PORT((uint32)(PortAddress + DIO_DATA_REG) , PortNewVal);

	}		
} 

/**********************************************************************************
**	Service name: Dio_ReadChannelGroup                             				 **
**	                                                      						 **
**	Syntax:	      Dio_PortLevelType Dio_ReadChannelGroup					     **
**				  ( 															 **
**					const Dio_ChannelGroupType * const ChannelGroupIdPtr	     **
** 				  )																 **
**																				 **
**  Description : This API 													     **
**				  -shall read the levels of a DIO channel group  				 **
**                                                        						 **
**	Service ID:   0x04                            						    	 **
**                                                        						 **
**	Sync/Async:	  Synchronous           						 				 **
**																				 **
**  Reentrancy:   Reentrant                                              		 **
**                                                        						 **
**	Parameters (in): ChannelGroupIdPtr - Pointer to ChannelGroup                 **
**                                                        						 **
**	Parameters (inout): NA               						 				 **
**                                                   						 	 **                                     
**	Parameters (out):   NA    													 **
**                                                                               **
**	Return value      :Level of a subset of the adjoining bits of a port	 	 **										
**                                                       						 **                                  	
***********************************************************************************/
Dio_PortLevelType Dio_ReadChannelGroup( const Dio_ChannelGroupType* const ChannelGroupIdPtr )
{
	/* Variable to hole the port address  */
	uint32 		  	  ChannelPortAddress;
	/* Variable to save the port level    */
	Dio_PortLevelType RetVal;
	
#if (DioDevErrorDetect == STD_ON)

	/* 
	   [SWS_Dio_00114]] The Api shall check the ChannelGroupIdPtr if 
	    development error detection is enabled.
	*/
	uint8 Check      = DioCheckGroupID(ChannelGroupIdPtr);
	
	/* Variable to Save the API's Error State */
	uint8 ErrorState = E_OK;
	
	/* if Haven't the check passesd */
	if(DIO_ERROR == Check)
	{
		/* 
		   [[SWS_Dio_00114]] if the ChannelGroupIdPtr is not valid within the current configuration
		   the API shall raise the error DIO_E_PARAM_INVALID_GROUP to the DET.  
		*/ 	
		Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID, DIO_READCHANNELGROUP_SID, DIO_E_PARAM_INVALID_GROUP);
		
		/* Set the API Errorstate to E_NOT_OK */
		ErrorState = E_NOT_OK;
		
		/* 
		   [SWS_Dio_00118] if development errors are enabled and an error ocurred 
		   the Dio module’s read functions shall return with the value '0'.
		*/	
		RetVal = (Dio_PortLevelType)STD_LOW;
	}
	
#endif /* DioDevErrorDetect */
		
#if (DioDevErrorDetect == STD_ON)
	/* Have all checks passed */
	if(E_OK == ErrorState)
#endif /* DioDevErrorDetect */
	{
		/* Get the Corresponding channel group port address */
		ChannelPortAddress = DioGetPortAddress(ChannelGroupIdPtr->port);	
	
		/*
		  [SWS_Dio_00092] The API shall do the masking of the channel group.
		*/	
		RetVal = (Dio_PortLevelType)((GET_PORT((uint32)(ChannelPortAddress + DIO_DATA_REG))) & \
									 ChannelGroupIdPtr->mask);		  
		
		/*[SWS_Dio_00093] The API function shall do the shifting 
		   so that the values read by the function are aligned to the LSB
		*/
	    RetVal = (Dio_PortLevelType)(RetVal >> ChannelGroupIdPtr->offset);
	}
	
	/* Retrun the level of the channel group */
	return (RetVal);
}

/**********************************************************************************
**	Service name: Dio_WriteChannelGroup                             			 **
**	                                                      						 **
**	Syntax:	      void Dio_WriteChannelGroup									 **
**				  ( 															 **
**					const Dio_ChannelGroupType * const ChannelGroupIdPtr	     **
**					const Dio_PortLevelType Level 								 **
** 				  )																 **
**																				 **
**  Description : This API 													     **
**				  -shall simultaneously set an adjoining subset					 **
**				   of DIO channels							                     **
**				  -shall ensure that the functionality of the input 			 **
**                 channels of that port is not affected 						 **					
**                                                        						 **
**	Service ID:   0x05                            						    	 **
**                                                        						 **
**	Sync/Async:	  Synchronous           						 				 **
**																				 **
**  Reentrancy:   Reentrant                                              		 **
**                                                        						 **
**	Parameters (in): ChannelGroupIdPtr - Pointer to ChannelGroup                 **
**					 Level  - Value to be written							     **
**                                                        						 **
**	Parameters (inout): NA               						 				 **
**                                                   						 	 **                                           			
**	Parameters (out):   NA    													 **
**                                                                               **
**	Return value: NA				       	 									 **
**                                                       						 **                                  					
***********************************************************************************/
void Dio_WriteChannelGroup( const Dio_ChannelGroupType* const ChannelGroupIdPtr, const Dio_PortLevelType Level )
{
	/* Variable to save the port address  */
	uint32 	  		ChannelPortAddress  ;
	/* Variable to save the Next port level value */
	uint32    		NewPortValue		;
	/* Variable to hold Channel group's pins Direction */
	uint8	  		ChannelsDirection    ;
	/* Variable to hold the old data reg value */
	uint8 	 OldDataRegVal;
	
#if (DioDevErrorDetect == STD_ON)

	/* 
	   [SWS_Dio_00114]] The Api shall check the ChannelGroupIdPtr if 
	    development error detection is enabled.
	*/
	uint8 Check      = DioCheckGroupID(ChannelGroupIdPtr);
	
	/* Variable to Save the API's Error State */
	uint8 ErrorState = E_OK;
	
	/* if Haven't the check passesd */
	if(DIO_ERROR == Check)
	{
		/* 
		   [[SWS_Dio_00114]] if the ChannelGroupIdPtr is not valid within the current configuration
		   the API shall raise the error DIO_E_PARAM_INVALID_GROUP to the DET.  
		*/ 
		Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID, DIO_WRITECHANNELGROUP_SID, DIO_E_PARAM_INVALID_GROUP);
		
		/* Set the API Errorstate to E_NOT_OK */
		ErrorState = E_NOT_OK;
	}
	
#endif /* DioDevErrorDetect */
		
	/*
		[SWS_Dio_00119] if development errors are enabled and an error ocurred,
		the Dio module’s write functions shall NOT process the write command.
	*/
#if (DioDevErrorDetect == STD_ON)
	if(E_OK == ErrorState)
#endif /* DioDevErrorDetect */ 
	{
		/* Get the Corresponding channel group port address */
		ChannelPortAddress = DioGetPortAddress(ChannelGroupIdPtr->port);
		
		/* Get the old Dio Port Data register value */
		OldDataRegVal 		   = (GET_PORT((uint32)(ChannelPortAddress + DIO_DATA_REG)));
		
		/* Get the all Port's Pin direction */
		ChannelsDirection = (GET_PORT((uint32)(ChannelPortAddress + GPIO_O_DIR)));
		
		/*	
		  [SWS_Dio_00040] The API shall not change the remaining channels of the port
		  and channels which are configured as input
		*/
		/*
		  [SWS_Dio_00090] The API function shall 
		  do the masking of the channel group.
	    */
		/*
		  [SWS_Dio_00091] The API shall do the shifting so that 
		  the values written by the function are aligned to the LSB
		*/
		NewPortValue = (((~ChannelsDirection) & OldDataRegVal) 		   | \
					   ((~(ChannelGroupIdPtr->mask)) & OldDataRegVal)  | \
					   (ChannelsDirection & (ChannelGroupIdPtr->mask) &  \
					   (Level << ChannelGroupIdPtr->offset))); 
		
		/*
		   [SWS_Dio_00008]The API shall simultaneously set an adjoining 
		   subset of DIO channels (channel group).
		*/   
		SET_PORT((uint32)(ChannelPortAddress + DIO_DATA_REG) , NewPortValue);		
	
	}
}

#if (DioVersionInfoApi == STD_ON)
/**********************************************************************************
**	Service name: Dio_GetVersionInfo                             			     **
**	                                                      						 **
**	Syntax:	      void Dio_GetVersionInfo									     **
**				  ( 															 **
**					 Std_VersionInfoType * const VersionInfo	      		     **
** 				  )																 **
**																				 **
**  Description : This API 														 **
**				  -get the version information of this module			         **
**				  -only available if DioVersionInfoApi is STD_ON				 **	
**                                                        						 **
**	Service ID:   0x12                            						    	 **
**                                                        						 **
**	Sync/Async:	  Synchronous           						 				 **
**																				 **
**  Reentrancy:   Reentrant                                              		 **
**                                                        						 **
**	Parameters (in): 	NA														 **
**					 															 **
**	Parameters (inout): NA               						 				 **
**                                                   						 	 **                                           		
**	Parameters (out):   VersionInfo - Pointer to where to store					 **
** 				 		the version information of this module.    				 **
**                                                                               **
**	Return value: NA				       	 									 **
**                                                       						 **                                  				
***********************************************************************************/
void Dio_GetVersionInfo(Std_VersionInfoType* const VersionInfo )
{
	
#if (DioDevErrorDetect == STD_ON)	

	/* Variable to Save the API's Error State */
	uint8 ErrorState = E_OK;
	
	if(NULL_PTR == VersionInfo)
	{
		/*
		  [SWS_Dio_00189] if DET is enabled for the DIO Driver module, the function API 
		  shall raise DIO_E_PARAM_POINTER, if the argument is NULL pointer and return without any action
		*/  
		Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID, DIO_GETVERSIONINFO_SID, DIO_E_PARAM_POINTER);
		
		/* Set the API Errorstate to E_NOT_OK */
		ErrorState = E_NOT_OK;
	}
	
#endif /* DioDevErrorDetect */

#if (DioDevErrorDetect == STD_ON)	
	/* Have all checks passed */
	if(E_OK == ErrorState)
#endif /* DioDevErrorDetect */	
	{
		/* Copy Dio module Vendor ID */
		VersionInfo->vendorID 		  = (uint16)DIO_VENDOR_ID;
		/* Copy Dio module ID */
		VersionInfo->moduleID 		  = (uint8) DIO_MODULE_ID;
		/* Copy Dio Software major version information */
		VersionInfo->sw_major_version = (uint8)	DIO_SW_MAJOR_VERSION;
		/* Copy Dio Software minor version information */
		VersionInfo->sw_minor_version = (uint8)	DIO_SW_MINOR_VERSION;
		/* Copy Dio Software patch version information */
		VersionInfo->sw_patch_version = (uint8)	DIO_SW_PATCH_VERSION;
	}
}

#endif /* DioVersionInfoApi */

#if (DioFlipChannelApi == STD_ON)
/**********************************************************************************
**	Service name: Dio_FlipChannel                             					 **
**	                                                      						 **
**	Syntax:	      Dio_LevelType Dio_FlipChannel									 **
**				  ( 															 **
**					Dio_ChannelType ChannelId									 **
** 				  )																 **
**																				 **
**  Description : This API 													     **
**				  -retrun inverted level of the specified DIO channel		   	 **
**				  -only available if DioFlipChannelApi is STD_ON				 **
**				  -shall ensure that the functionality of the input 			 **
**                 channels of that port is not affected 						 **
**				  -in case of input channels shall have no influence    	     **
**        		   on the result of next Read service    						 **
**                                                        						 **
**	Service ID:   0x11                            						    	 **
**                                                        						 **
**	Sync/Async:	  Synchronous           						 				 **
**																				 **
**  Reentrancy:   Reentrant                                              		 **
**                                                        						 **
**	Parameters (in): ChannelId - ID of DIO channel                         		 **
**                                                        						 **
**	Parameters (inout): NA               						 				 **
**                                                   						 	 **                                       
**	Parameters (out):   NA    													 **
**                                                                               **
**	Return value:     The inverted level of the corresponding CannelId        	 **											
**                                                       						 **                                  		
***********************************************************************************/
Dio_LevelType Dio_FlipChannel( Dio_ChannelType ChannelId )
{
	/* Variable to save the channel's port number  */
	Dio_PortType  ChannelPortNumber ;
	/* Varialbe to save the channel's Pin Position */
	uint8  	      ChannelPinNumber  ;
	/* Variable to save the port address  */
	uint32 		  ChannelPortAddress;
	/* Varialbe to save the current Pin Level */
	Dio_LevelType ChannelLevel		;
	/* Varialbe to save the Next Pin Level value */
	Dio_LevelType RetVal			;
	/* Variable to hold the channel's Pin Direction */
	uint8		  ChannelDirection = DIO_PIN_OUTPUT;
	
#if (DioDevErrorDetect == STD_ON)

	/* 
	   [SWS_Dio_00074] The Api shall check the channel ID if 
	    development error detection is enabled
	*/
	uint8 Check      = DioCheckChannelID(ChannelId);
	/* Variable to Save the API's Error State */
	uint8 ErrorState = E_OK;
	
	if(DIO_ERROR == Check)
	{
		/* 
		   [SWS_Dio_00074] if the ChannelId is not valid within the current configuration
		   the API shall raise the error DIO_E_PARAM_INVALID_CHANNEL_ID to the DET.  
		*/
		Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID, DIO_FLIPCHANNEL_SID, DIO_E_PARAM_INVALID_CHANNEL_ID);
		/* Set the API Errorstate to E_NOT_OK*/
		ErrorState = E_NOT_OK;
	}
	
#endif /* DioDevErrorDetect */
	
#if (DioDevErrorDetect == STD_ON)
	/* Have all checks passed */
	if(E_OK == ErrorState)
#endif /* DioDevErrorDetect */
	{
		/* Get the channel port number from its ID */
		ChannelPortNumber  = DioGetChannelPortNumber(ChannelId);
	
		/* Get the channel's Pin Position */
		ChannelPinNumber   = DioGetChannelPinNumber(ChannelId);
		
		/* Get the channel's port address */
		ChannelPortAddress = DioGetPortAddress(ChannelPortNumber);
	
		/* Get the channel's PIN Direction */
		ChannelDirection   = DioGetPinDirection(ChannelPortAddress, ChannelPinNumber);
		
		/* Get the current channel level */
	    ChannelLevel	   = DioReadPin(ChannelPortAddress, ChannelPinNumber);	
		
		/*
		  [SWS_Dio_00192] If the specified channel is configured as an input channel, the API 
		  shall have no influence on the physical output.
		*/
		if(DIO_PIN_INPUT != ChannelDirection)
		{
			TOGGLE_BIT(((uint32)ChannelPortAddress + DIO_DATA_REG),ChannelPinNumber);
				
			RetVal = DioReadPin(ChannelPortAddress, ChannelPinNumber);	
		}
		else
		{
			/*
			   [SWS_Dio_00192]the return value shall be the level of the specified channel.
			*/
			RetVal = ChannelLevel;
		}
	}
	
	/* Return The value */
	return (RetVal);
}

#endif /* DioFlipChannelApi */

/***********************************************************************************/
/*				    		Local Function Definitions	         				   */
/***********************************************************************************/

/**********************************************************************************
**	Service name: DioGetChannelPortNumber                             		     **
**	                                                      						 **
**	Syntax:	      Dio_PortType DioGetChannelPortNumber	  						 **
**				  ( 															 **
**					const Dio_ChannelType ChannelId								 **
** 				  )																 **
**																				 **
**  Description : This LOCAL_INLINE API 									     **
**				  -Gets the port Number of the specified channel.			   	 **
**																				 **
**                                                        						 **
**	Service ID:   NA                           						    	     **
**                                                        						 **
**	Sync/Async:	  Synchronous           						 				 **
**																				 **
**  Reentrancy:   Reentrant                                              		 **
**                                                        						 **
**	Parameters (in): ChannelId - ID of DIO channel                         		 **
**                                                        						 **
**	Parameters (inout): NA               						 				 **
**                                                   						 	 **                                           					
**	Parameters (out):   NA    													 **
**                                                                               **
**	Return value:    RetVal- the port Number of the specified channel. 			 **
**																 				 **
***********************************************************************************/
LOCAL_INLINE Dio_PortType DioGetChannelPortNumber(const Dio_ChannelType ChannelId)
{
	Dio_PortType RetVal;
	uint8 LocalIndex   ;
	
	for(LocalIndex = DIO_NUM_0 ; LocalIndex < NUM_OF_USED_PINS; LocalIndex++)
	{
		if(DioConfig->Dio_PortChannel[LocalIndex].Channel_Id == ChannelId)
		{
			RetVal = DioConfig->Dio_PortChannel[LocalIndex].PortId;
		}
	}
	
	return (RetVal);
}

/**********************************************************************************
**	Service name: DioGetChannelPinNumber                             		     **
**	                                                      						 **
**	Syntax:	      uint8 DioGetChannelPinNumber	  						 		 **
**				  ( 															 **
**					const Dio_ChannelType ChannelId								 **
** 				  )																 **
**																				 **
**  Description : This LOCAL_INLINE API 									     **
**				  -Gets Pin number from its symbolic ID.					   	 **
**																				 **
**                                                        						 **
**	Service ID:   NA                           						    	     **
**                                                        						 **
**	Sync/Async:	  Synchronous           						 				 **
**																				 **
**  Reentrancy:   Reentrant                                              		 **
**                                                        						 **
**	Parameters (in): ChannelId - ID of DIO channel                         		 **
**                                                        						 **
**	Parameters (inout): NA               						 				 **
**                                                   						 	 **                                           					
**	Parameters (out):   NA    													 **
**                                                                               **
**	Return value:    RetVal- Pin number from its symbolic ID.		 			 **
**																 				 **
***********************************************************************************/
LOCAL_INLINE uint8 DioGetChannelPinNumber( const Dio_ChannelType ChannelId)
{
	uint8 LocalTemp = 0x0F  ;
	Dio_PortType RetVal;
	
	RetVal = (ChannelId & LocalTemp);
		
	return (RetVal);
}

/**********************************************************************************
**	Service name: DioGetPortAddress                             		         **
**	                                                      						 **
**	Syntax:	      uint32 DioGetPortAddress	  						 		     **
**				  ( 															 **
**					const Dio_PortType PortNumber							     **
** 				  )																 **
**																				 **
**  Description : This LOCAL_INLINE API 									     **
**				  -Gets The port address from port number.					   	 **
**																				 **
**                                                        						 **
**	Service ID:   NA                           						    	     **
**                                                        						 **
**	Sync/Async:	  Synchronous           						 				 **
**																				 **
**  Reentrancy:   Reentrant                                              		 **
**                                                        						 **
**	Parameters (in): PortNumber - Number of DIO PORT.                      		 **
**                                                        						 **
**	Parameters (inout): NA               						 				 **
**                                                   						 	 **                                           					
**	Parameters (out):   NA    													 **
**                                                                               **
**	Return value:    RetVal- Specified Port address.				 			 **
**																 				 **
***********************************************************************************/
LOCAL_INLINE uint32 DioGetPortAddress(const Dio_PortType PortNumber)
{
	uint32 RetVal;
	
	RetVal =  DioPortAddress[PortNumber];
	
	return (RetVal);
}

#if (DioDevErrorDetect == STD_ON)

/**********************************************************************************
**	Service name: DioCheckChannelID                             		    	 **
**	                                                      						 **
**	Syntax:	      uint8 DioCheckChannelID	  							 	     **
**				  ( 															 **
**					const Dio_ChannelType ChannelId								 **
** 				  )																 **
**																				 **
**  Description : This LOCAL_INLINE API 									     **
**				  -Checks the ChannelId if valid or Not.					   	 **
**																				 **
**                                                        						 **
**	Service ID:   NA                           						    	     **
**                                                        						 **
**	Sync/Async:	  Synchronous           						 				 **
**																				 **
**  Reentrancy:   Reentrant                                              		 **
**                                                        						 **
**	Parameters (in): ChannelId - ID of DIO channel                         		 **
**                                                        						 **
**	Parameters (inout): NA               						 				 **
**                                                   						 	 **                                           					
**	Parameters (out):   NA    													 **
**                                                                               **
**	Return value:    ErrorState of ChannelId, 									 **
**					 DIO_OK    - ChannelId Valid				 				 **
**                   DIO_ERROR - ChannelId Not Valid               				 **
**                                  					     					 **
***********************************************************************************/
LOCAL_INLINE uint8 DioCheckChannelID(const Dio_ChannelType ChannelId)
{
	uint8 ErrorState  = DIO_OK ;
    uint8 CannelIndex = 0      ;
	uint8 Config  	  = 0  	   ;
	
	if(ChannelId > DIO_MAX_CHANNEL_ID)
	{
		ErrorState = DIO_ERROR ;
	}	
	else
	{
		for(CannelIndex = DIO_NUM_0 ; CannelIndex < NUM_OF_USED_PINS ; CannelIndex++)
		{
			if(DioConfig->Dio_PortChannel[CannelIndex].Channel_Id == ChannelId)
			{
				Config++;

				break;
			}
		}
	}
	
	if(Config == 0)
	{
		ErrorState = DIO_ERROR ;
	}
	
	return (ErrorState);
}


/**********************************************************************************
**	Service name: DioCheckPortID                             		             **
**	                                                      						 **
**	Syntax:	      uint8 DioCheckPortID	  						 		         **
**				  ( 															 **
**					const Dio_PortType PortId							     	 **
** 				  )																 **
**																				 **
**  Description : This LOCAL_INLINE API 									     **
**				  -Checks the PortId if valid or Not.						   	 **
**																				 **
**                                                        						 **
**	Service ID:   NA                           						    	     **
**                                                        						 **
**	Sync/Async:	  Synchronous           						 				 **
**																				 **
**  Reentrancy:   Reentrant                                              		 **
**                                                        						 **
**	Parameters (in): PortId - ID of DIO Port                         		     **
**                                                        						 **
**	Parameters (inout): NA               						 				 **
**                                                   						 	 **                                           					
**	Parameters (out):   NA    													 **
**                                                                               **
**	Return value:    ErrorState of PortId, 										 **
**					 DIO_OK    - PortId Valid				 					 **
**                   DIO_ERROR - PortId Not Valid               				 **
**																 				 **
***********************************************************************************/
LOCAL_INLINE uint8 DioCheckPortID(const Dio_PortType PortId)
{
	uint8 ErrorState  = DIO_OK ;
    uint8 PortIndex   = 0      ;
	uint8 Config  	  = 0  	   ;
	
	if(PortId > DIO_MAX_PORT_ID)
	{
		ErrorState = DIO_ERROR ;
	}	
	else
	{
		for(PortIndex = DIO_NUM_0 ; PortIndex < NUM_OF_USED_PORTS ; PortIndex++)
		{
			if(DioConfig->Dio_PortChannel[PortIndex].PortId == PortId)
			{
				Config++;

				break;
			}
		}
	}
	
	if(Config == 0)
	{
		ErrorState = DIO_ERROR ;
	}
	
	return (ErrorState);
}

/**********************************************************************************
**	Service name: DioCheckGroupID                             		             **
**	                                                      						 **
**	Syntax:	      uint8 DioCheckGroupID	  						 		         **
**				  ( 															 **
**					const Dio_ChannelGroupType * const GroupIdPtr		     	 **
** 				  )																 **
**																				 **
**  Description : This LOCAL_INLINE API 									     **
**				  -Checks the GroupIdPtr if valid or Not.					   	 **
**																				 **
**                                                        						 **
**	Service ID:   NA                           						    	     **
**                                                        						 **
**	Sync/Async:	  Synchronous           						 				 **
**																				 **
**  Reentrancy:   Reentrant                                              		 **
**                                                        						 **
**	Parameters (in): ChannelGroupIdPtr - Pointer to ChannelGroup                 **
**                                                        						 **
**	Parameters (inout): NA               						 				 **
**                                                   						 	 **                                           					
**	Parameters (out):   NA    													 **
**                                                                               **
**	Return value:    ErrorState of GroupIdPtr, 									 **
**					 DIO_OK    - GroupIdPtr Valid			 					 **
**                   DIO_ERROR - GroupIdPtr Not Valid              				 **
**																 				 **
***********************************************************************************/
LOCAL_INLINE uint8 DioCheckGroupID(const Dio_ChannelGroupType* const GroupIdPtr)
{
	uint32 LocalGroupIndex;
	uint8 ErrorState = (uint8)DIO_ERROR;
		
	if(NULL_PTR != GroupIdPtr)
	{
		for(LocalGroupIndex = 0 ; LocalGroupIndex < NUM_OF_USED_GROUPS; LocalGroupIndex++)
		{
			if(GroupIdPtr == &(DioConfig->Dio_ChannelGroup[LocalGroupIndex]))
			{
				ErrorState = (uint8)DIO_OK;
			}
		}
	}	

	return (ErrorState);
}

#endif /* DioDevErrorDetect */

/**********************************************************************************
**	Service name: DioWritePin                             					     **
**	                                                      						 **
**	Syntax:	      void DioWritePin									 		     **
**				  ( 															 **
**					const uint32 PortAddress,						         	 **
**					const uint8 PinNumber, 										 **
**					const Dio_LevelType Level									 **
** 				  )																 **
**																				 **
**  Description : This LOCAL_INLINE API 									     **
**				  -set a value of the Pin of the specifies level.				 **
**                                                        						 **
**	Service ID:   NA                            						    	 **
**                                                        						 **
**	Sync/Async:	  Synchronous           						 				 **
**																				 **
**  Reentrancy:   Reentrant                                              		 **
**                                                        						 **
**	Parameters (in): PortAddress  - Addresss of DIO Port    					 **			
**					 PinNumber	  - Pin number from its symbolic ID				 **
**					 Level        - Value to be written					         **
**                                                        						 **
**	Parameters (inout): NA               						 				 **
**                                                   						 	 **                                           				
**	Parameters (out):   NA    													 **
**                                                                               **
**	Return value: NA				       	 									 **
**                                                       						 **                                  					    
***********************************************************************************/	
LOCAL_INLINE void DioWritePin
(
	const uint32 PortAddress,
	const uint8 PinNumber, 
	const Dio_LevelType Level
)
{
	if(Level != STD_LOW)
	{
		SET_BIT((uint32)(PortAddress + DIO_DATA_REG), PinNumber);
	}
	else
	{
		CLEAR_BIT((uint32)(PortAddress + DIO_DATA_REG), PinNumber);
	}
}

/**********************************************************************************
**	Service name: DioReadPin                             					     **
**	                                                      						 **
**	Syntax:	      Dio_LevelType DioReadPin							    	     **
**				  ( 															 **
**					const uint32 PortAddress,						         	 **
**					const uint8 PinNumber 										 **
** 				  )																 **
**																				 **
**  Description : This LOCAL_INLINE API 									     **
**				  -Get a value of the Pin Level.								 **
**                                                        						 **
**	Service ID:   NA                            						    	 **
**                                                        						 **
**	Sync/Async:	  Synchronous           						 				 **
**																				 **
**  Reentrancy:   Reentrant                                              		 **
**                                                        						 **
**	Parameters (in): PortAddress  - Addresss of DIO Port    					 **			
**					 PinNumber	  - Pin number from its symbolic ID				 **
**                                                        						 **
**	Parameters (inout): NA               						 				 **
**                                                   						 	 **                                           			
**	Parameters (out):   NA    													 **                                                     
**                                                                               **                                                     
**	Return value: RetVal  The level of the corresponding Pin.		        	 **	                                                    
**                                                       						 **                                  					
***********************************************************************************/
LOCAL_INLINE Dio_LevelType DioReadPin
(
	const uint32 PortAddress,
	const uint8 PinNumber
)
{
	Dio_LevelType RetVal;
	
	RetVal = GET_BIT((uint32)(PortAddress + DIO_DATA_REG) , PinNumber);
	
	return (RetVal);
}

/**********************************************************************************
**	Service name: DioGetPinDirection                             				 **
**	                                                      						 **
**	Syntax:	      uint8 DioGetPinDirection									 	 **
**				  ( 															 **
**					const uint32 PortAddress,						         	 **
**					const uint8 PinNumber 										 **
** 				  )																 **
**																				 **
**  Description : This LOCAL_INLINE API 									     **
**				  -Get the value of a Pin Direction.							 **
**                                                        						 **
**	Service ID:   NA                            						    	 **
**                                                        						 **
**	Sync/Async:	  Synchronous           						 				 **
**																				 **
**  Reentrancy:   Reentrant                                              		 **
**                                                        						 **
**	Parameters (in): PortAddress  - Addresss of DIO Port    					 **			
**					 PinNumber	  - Pin number from its symbolic ID				 **
**                                                        						 **
**	Parameters (inout): NA               						 				 **
**                                                   						 	 **                                           	
**	Parameters (out):   NA    													 **
**                                                                               **
**	Return value:    RetVal   		 - Pin Direction, 							 **
**					 DIO_PIN_OUTPUT  - Pin Direction is output          		 **
**                   DIO_PIN_INPUT   - Pin Direction is input	               	 **
**																 				 **
**                                                       						 **                                  			
***********************************************************************************/
LOCAL_INLINE uint8 DioGetPinDirection
(
	const uint32 PortAddress, 
	const uint8 PinNumber
)
{
	Dio_LevelType RetVal;
	
	RetVal = GET_BIT((uint32)(PortAddress + GPIO_O_DIR) , PinNumber);
	
	return (RetVal);
}


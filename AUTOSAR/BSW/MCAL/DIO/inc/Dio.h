/**********************************************************************************
***********************************************************************************
**														  						 **		
**	FILENAME	:	Dio.h                              						     **
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
**	DESCRIPTION : Digital I/O Driver header file      							 **
**                                                                               **
**	SPECIFICATION(S) : AUTOSAR_SWS_DIODriver, AUTOSAR Release 4.3.1              **
**                                                       						 **
**	MAY BE CHANGED BY USER : No                          						 **
**                                                       					     **
***********************************************************************************/
#ifndef DIO_H
#define DIO_H

/*****************************************************************/
/*				    	Include Headers					         */
/*****************************************************************/

#include "Std_Types.h "
#include "Dio_Cfg.h"

/*****************************************************************/
/*				        Macros Definition       		         */
/*****************************************************************/

/* DIO Driver Vendor ID */
#define DIO_VENDOR_ID	(0x40u)

/* DIO Driver Module ID */
#define DIO_MODULE_ID	(120u)

/* DIO Driver Instance ID */
#define DIO_INSTANCE_ID	(0x00u)

/*	Moudle Version	1.0.0 */
#define DIO_SW_MAJOR_VERSION			(0x01u)
#define DIO_SW_MINOR_VERSION			(0x00u)
#define DIO_SW_PATCH_VERSION			(0x00u)

/* Autosar version 4.3.1 */
#define DIO_AR_RELEASE_MAJOR_VERSION	(0x04u)
#define DIO_AR_RELEASE_MINOR_VERSION	(0x03u)
#define DIO_AR_RELEASE_PATCH_VERSION	(0x01u)

/**************** Version Check ******************/

/* Check for Std_Types.h */

#if ( STD_AR_RELEASE_MAJOR_VERSION != DIO_AR_RELEASE_MAJOR_VERSION )
#error "STD_AR_RELEASE_MAJOR_VERSION Doesn't Match."
#endif /* STD_AR_RELEASE_MAJOR_VERSION */

#if ( STD_AR_RELEASE_MINOR_VERSION != DIO_AR_RELEASE_MINOR_VERSION )
#error "STD_AR_RELEASE_MINOR_VERSION Doesn't Match."
#endif /* STD_AR_RELEASE_MINOR_VERSION */

#if ( STD_AR_RELEASE_PATCH_VERSION != DIO_AR_RELEASE_PATCH_VERSION )
#error "STD_AR_RELEASE_PATCH_VERSION Doesn't Match."
#endif /* STD_AR_RELEASE_PATCH_VERSION */

/* Check for Dio_Cfg.h */
/* check for Autosar version */
#if ( DIO_CFG_AR_RELEASE_MAJOR_VERSION != DIO_AR_RELEASE_MAJOR_VERSION )
#error "DIO_CFG_AR_RELEASE_MAJOR_VERSION Doesn't Match."
#endif /* DIO_CFG_AR_RELEASE_MAJOR_VERSION */

#if ( DIO_CFG_AR_RELEASE_MINOR_VERSION != DIO_AR_RELEASE_MINOR_VERSION )
#error "DIO_CFG_AR_RELEASE_MINOR_VERSION Doesn't Match."
#endif /* DIO_CFG_AR_RELEASE_MINOR_VERSION */

#if ( DIO_CFG_AR_RELEASE_PATCH_VERSION != DIO_AR_RELEASE_PATCH_VERSION )
#error "DIO_CFG_AR_RELEASE_PATCH_VERSION Doesn't Match."
#endif /* DIO_CFG_AR_RELEASE_PATCH_VERSION */

/* Check for Software version */
#if ( DIO_CFG_SW_MAJOR_VERSION != DIO_SW_MAJOR_VERSION )
#error "DIO_CFG_SW_MAJOR_VERSION Doesn't Match."
#endif /* DIO_CFG_SW_MAJOR_VERSION */

#if ( DIO_CFG_SW_MINOR_VERSION != DIO_SW_MINOR_VERSION )
#error "DIO_CFG_SW_MINOR_VERSION Doesn't Match."
#endif /* DIO_CFG_SW_MINOR_VERSION */

#if ( DIO_CFG_SW_PATCH_VERSION != DIO_SW_PATCH_VERSION )
#error "DIO_CFG_SW_PATCH_VERSION Doesn't Match."
#endif /* DIO_CFG_SW_PATCH_VERSION */

/**************** API Services ID ****************/

#if (DioDevErrorDetect == STD_ON)

/* Dio_ReadChannel Services ID */
#define DIO_READCHANNEL_SID				(0x00u)
/* Dio_WriteChannel Services ID */
#define DIO_WRITECHANNEL_SID			(0x01u)
/* Dio_ReadPort Services ID */
#define DIO_READPORT_SID				(0x02u)
/* Dio_WritePort Services ID */
#define DIO_WRITEPORT_SID				(0x03u)
/* Dio_ReadChannelGroup Services ID */
#define DIO_READCHANNELGROUP_SID		(0x04u)
/* Dio_WriteChannelGroup Services ID */
#define DIO_WRITECHANNELGROUP_SID		(0x05u)

/*************************************************/
#if (DioVersionInfoApi == STD_ON)
/* Dio_GetVersionInfo Services ID */
 #define DIO_GETVERSIONINFO_SID			(0x12u)

#endif /* DioVersionInfoApi */

#if (DioFlipChannelApi == STD_ON)
/* Dio_FlipChannel Services ID */
 #define DIO_FLIPCHANNEL_SID			(0x11u)

#endif /* DioFlipChannelApi */
 
/******* Devlopment Errors Macron definition *****/

/* if the “ChannelId” parameter to be Invalid within the current configuration */
#define DIO_E_PARAM_INVALID_CHANNEL_ID (0x0Au)

/* if the “PortlId” parameter to be Invalid within the current configuration */
#define DIO_E_PARAM_INVALID_PORT_ID	   (0x14u)

/* if the “GrouplId” parameter to be Invalid within the current configuration */
#define DIO_E_PARAM_INVALID_GROUP	   (0x1Fu)

/* This Error is called whenever a Null pointer exists */
#define DIO_E_PARAM_POINTER			   (0x20u)

#endif /* DioDevErrorDetect */ 

/*****************************************************************/
/*				       Dev Macros Definition       		         */
/*****************************************************************/

/* define the maximum DIO pins channels ID in TIVA C MCU */
#define DIO_MAX_CHANNEL_ID	(0x53u)

/* The maximum port IDs for Tiva C controller */
#define DIO_MAX_PORT_ID	    (5u)

/*****************************************************************/
/*				        Types Definition        		         */
/*****************************************************************/

/* Type Definition contain the numeric ID of a DIO channel */
typedef uint8 Dio_ChannelType;

/* Type Definition contain the numeric ID of a DIO port */
typedef uint8 Dio_PortType;

/* Type Definition the possible levels that a DIO channel can have */
typedef uint8 Dio_LevelType;

/* Type Definition for the value of a DIO port */
typedef uint8 Dio_PortLevelType;



/* is the type for the definition of a channel group, which consists of several adjoining channels within a port */
typedef struct 
{
	/* Defines the positions of the channel group */
	uint32 			mask;
	
	/* Position of the Channel Group on the port, counted from the LSB */
	uint8  			offset;
	
	/* Port on which the Channel group is defined */
	Dio_PortType    port;	
}Dio_ChannelGroupType;


/* Type defenition to hold channel and port configuration */
typedef struct 
{
	/* Variable to hold the channel ID */
	Dio_ChannelType Channel_Id;
	
	/* Variable to hold the Port ID */
	Dio_PortType	PortId;
}Dio_PortChannelConfig;

/* Type defenition to hold all configuration parameters of the AUTOSAR DIO module */
typedef struct 
{
	/* Pointer to Port and channel configuration */
	const Dio_PortChannelConfig* 	   Dio_PortChannel;
		
	/* Pointer to channel group configuration */	
	const Dio_ChannelGroupType*        Dio_ChannelGroup;
}Dio_ConfigType;


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
extern Dio_LevelType Dio_ReadChannel
(
	const Dio_ChannelType ChannelId 
);

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
extern void Dio_WriteChannel
(
	const Dio_ChannelType ChannelId, 
	const Dio_LevelType Level 
);

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
Dio_PortLevelType Dio_ReadPort
(
	const Dio_PortType PortId
);

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
void Dio_WritePort
(
	const Dio_PortType PortId, 
	const Dio_PortLevelType Level
);

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
Dio_PortLevelType Dio_ReadChannelGroup
(
	const Dio_ChannelGroupType* const ChannelGroupIdPtr
);

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
void Dio_WriteChannelGroup
(
	const Dio_ChannelGroupType* const ChannelGroupIdPtr,
	const Dio_PortLevelType Level
);

#if (DioVersionInfoApi == STD_ON)
/**********************************************************************************
**	Service name: Dio_GetVersionInfo                             			     **
**	                                                      						 **
**	Syntax:	      void Dio_GetVersionInfo									     **
**				  ( 															 **
**					 Std_VersionInfoType * const VersionInfo		  		     **
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
void Dio_GetVersionInfo
(
	Std_VersionInfoType* const VersionInfo
);

#endif /* DioVersionInfoApi */

#if (DioFlipChannelApi == STD_ON)
/**********************************************************************************
**	Service name: Dio_FlipChannel                             					 **
**	                                                      						 **
**	Syntax:	      Dio_LevelType Dio_FlipChannel									 **
**				  ( 															 **
**					const Dio_ChannelType ChannelId								 **
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
Dio_LevelType Dio_FlipChannel
(
	const Dio_ChannelType ChannelId
);

#endif /* DioFlipChannelApi */

#endif /*DIO_H*/


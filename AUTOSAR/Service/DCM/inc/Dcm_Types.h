/**********************************************************************************
***********************************************************************************
**														  						 **		
**	FILENAME	:	Dcm_Types.h                          					     **
**	                                                      						 **
**	VERSION		: 	1.0.0                                 						 **
**                                                        						 **
**	DATE		:	2021-5-16                            						 **
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
**	DESCRIPTION : Dcm Types.													 **
**                                                                               **
**	SPECIFICATION(S) : AUTOSAR_SWS_DiagnosticCommunicationManager, AUTR 4.3.1    **
**                                                       						 **
**	MAY BE CHANGED BY USER : No                          						 **
**                                                       					     **
***********************************************************************************/

typedef uint8 Dcm_StatusType;
#define DCM_E_OK							((Dcm_StatusType) 0x00)
#define DCM_E_ROE_NOT_ACCEPTED				((Dcm_StatusType) 0x06)
#define DCM_E_PERIODICID_NOT_ACCEPTED		((Dcm_StatusType) 0x07)

typedef uint8 Dcm_CommunicationModeType;
#define DCM_ENABLE_RX_TX_NORM 				((Dcm_CommunicationModeType) 0x00)
#define DCM_ENABLE_RX_DISABLE_TX_NORM		((Dcm_CommunicationModeType) 0x01)
#define DCM_DISABLE_RX_ENABLE_TX_NORM   	((Dcm_CommunicationModeType) 0x02)
#define DCM_DISABLE_RX_TX_NORMAL			((Dcm_CommunicationModeType) 0x03)
#define DCM_ENABLE_RX_TX_NM  				((Dcm_CommunicationModeType) 0x04)
#define DCM_ENABLE_RX_DISABLE_TX_NM			((Dcm_CommunicationModeType) 0x05)
#define DCM_DISABLE_RX_ENABLE_TX_NM			((Dcm_CommunicationModeType) 0x06)
#define DCM_DISABLE_RX_TX_NM				((Dcm_CommunicationModeType) 0x07)
#define DCM_ENABLE_RX_TX_NORM_NM			((Dcm_CommunicationModeType) 0x08)
#define DCM_ENABLE_RX_DISABLE_TX_NORM_NM	((Dcm_CommunicationModeType) 0x09)
#define DCM_DISABLE_RX_ENABLE_TX_NORM_NM	((Dcm_CommunicationModeType) 0x0A)
#define DCM_DISABLE_RX_TX_NORM_NM			((Dcm_CommunicationModeType) 0x0B)

typedef uint8 Dcm_ReturnReadMemoryType;
#define DCM_READ_OK							((Dcm_ReturnReadMemoryType) 0x00)
#define DCM_READ_PENDING					((Dcm_ReturnReadMemoryType) 0x01)
#define DCM_READ_FAILED						((Dcm_ReturnReadMemoryType) 0x02)
#define DCM_READ_FORCE_RCRRP				((Dcm_ReturnReadMemoryType) 0x03)

typedef uint8 Dcm_ReturnWriteMemoryType;
#define DCM_WRITE_OK						((Dcm_ReturnWriteMemoryType) 0x00)
#define DCM_WRITE_PENDING					((Dcm_ReturnWriteMemoryType) 0x01)
#define DCM_WRITE_FAILED					((Dcm_ReturnWriteMemoryType) 0x02)
#define DCM_WRITE_FORCE_RCRRP				((Dcm_ReturnWriteMemoryType) 0x03)

typedef uint8 Dcm_EcuStartModeType;
#define DCM_COLD_START						((Dcm_EcuStartModeType) 0x00)
#define DCM_WARM_START						((Dcm_EcuStartModeType) 0x01)

typedef uint8 Dcm_MsgItemType;

typedef Dcm_MsgItemType* Dcm_MsgType;

typedef uint32 Dcm_MsgLenType;

typedef uint8 Dcm_IdContextType;

typedef uint8 Dcm_ExtendedOpStatusType;
#define DCM_INITIAL 						((Dcm_ExtendedOpStatusType) 0x00)
#define DCM_PENDING 						((Dcm_ExtendedOpStatusType) 0x01)
#define DCM_CANCEL  						((Dcm_ExtendedOpStatusType) 0x02)
#define DCM_FORCE_RCRRP_OK					((Dcm_ExtendedOpStatusType) 0x03)
#define DCM_POS_RESPONSE_SENT 				((Dcm_ExtendedOpStatusType) 0x04)
#define DCM_POS_RESPONSE_FAILED 			((Dcm_ExtendedOpStatusType) 0x05)
#define DCM_NEG_RESPONSE_SENT 				((Dcm_ExtendedOpStatusType) 0x06)
#define DCM_NEG_RESPONSE_FAILED				((Dcm_ExtendedOpStatusType) 0x07)

typedef struct 
{
	uint32 reqType:1;
	
	uint32 suppressPosResponse:1;
	
}Dcm_MsgAddInfoType;


typedef struct 
{
	uint16	ConnectionId;
	
	uint16	TesterAddress;
	
	uint8	Sid;
	
	uint8	SubFncId;
	
	boolean	ReprogramingRequest;
	
	boolean	ApplUpdated;
	
	boolean ResponseRequired;
	
}Dcm_ProgConditionsType;


typedef struct 
{
	
}Dcm_ConfigType;


typedef struct 
{
	Dcm_MsgType 		reqData;
	
	Dcm_MsgLenType		reqDataLen;
	
	Dcm_MsgType 		resData;
	
	Dcm_MsgLenType		resDataLen;
	
	Dcm_MsgAddInfoType	msgAddInfo;
	
	Dcm_MsgLenType 		resMaxDataLen;
	
	Dcm_IdContextType	idContext;
	
	PduIdType    		dcmRxPduId:;
}Dcm_MsgContextType;















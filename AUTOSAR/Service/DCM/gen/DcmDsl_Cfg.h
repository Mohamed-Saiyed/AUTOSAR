
typedef uint32	DcmDslBufferSizeType;

typedef uint8	DcmDslBufferIdType;

typedef uint8 	DcmDslBufferStateType;
#define DCM_DSL_BUFFER_LOCKED		((DcmDslBufferStateType)0x00)
#define DCM_DSL_BUFFER_NOT_LOCKED	((DcmDslBufferStateType)0x01)

typedef uint8 DcmDslDiagRespMaxNumRespPendType;

typedef uint8 DcmDslProtocolIDType;
#define DCM_OBD_ON_CAN					((DcmDslProtocolIDType)0x00)
#define DCM_OBD_ON_FLEXRAY				((DcmDslProtocolIDType)0x01)
#define DCM_OBD_ON_IP					((DcmDslProtocolIDType)0x02)
#define DCM_PERIODICTRANS_ON_CAN		((DcmDslProtocolIDType)0x03)
#define DCM_PERIODICTRANS_ON_FLEXRAY	((DcmDslProtocolIDType)0x04)
#define DCM_PERIODICTRANS_ON_IP			((DcmDslProtocolIDType)0x05)
#define DCM_ROE_ON_CAN					((DcmDslProtocolIDType)0x06)
#define DCM_ROE_ON_FLEXRAY				((DcmDslProtocolIDType)0x07)
#define DCM_ROE_ON_IP					((DcmDslProtocolIDType)0x08)
#define DCM_UDS_ON_CAN					((DcmDslProtocolIDType)0x18)
#define DCM_UDS_ON_FLEXRAY				((DcmDslProtocolIDType)0x19)
#define DCM_UDS_ON_IP					((DcmDslProtocolIDType)0x1A)
#define DCM_UDS_ON_LIN					((DcmDslProtocolIDType)0x1B)

typedef uint16 DcmDslProtocolMaximumResponseSizeType;

typedef uint8 DcmDslProtocolPriorityType;

typedef uint8 DcmDslProtocolRxAddrType;
#define DCM_FUNCTIONAL_TYPE				((DcmDslProtocolRxAddrType)0x00)
#define DCM_PHYSICAL_TYPE				((DcmDslProtocolRxAddrType)0x01)


typedef struct 
{
	DcmDslBufferSizeType	    DcmDslMaxBufferSize;
	
	uint32 						DcmDslBufferFilledLength;
	
	uint32						DcmDslTpSduLength;
	
	DcmDslBufferIdType			DcmDslBufferId;
	
	DcmDslBufferStateType	    DcmDslBufferState;
	
	uint32						Buffer[];
	
}Dcm_DslBufferType;

typedef struct
{
	
}Dcm_DslCallbackDCMRequestServiceType;


typedef struct
{
	DcmDslDiagRespMaxNumRespPendType DcmDslDiagRespMaxNumRespPend;
	
	boolean						 	 DcmDslDiagRespOnSecondDeclinedRequest;
	
}Dcm_DslDiagRespType;

typedef struct 
{
	DcmDslProtocolRxAddrType	DcmDslProtocolRxAddr;
	
	PduIdType					DcmDslProtocolRxPduId;
	
	PduInfoType*				DcmDslProtocolRxPduRef;
	
}Dcm_DslProtocolRxType;

typedef struct 
{
	PduIdType					DcmDslTxConfirmationPduId;
	
	PduInfoType*				DcmDslProtocolTxPduRef;//
	
}Dcm_DslProtocolTxType;


typedef struct 
{
	uint16 									DcmDslProtocolRxConnectionId;
	
	uint16 									DcmDslProtocolRxTesterSourceAddr;
	
	Dcm_DslPeriodicTransmissionType* 		DcmDslPeriodicTransmission;
			
	uint16*									DcmDslProtocolComMChannelRef;		
			
	Dcm_DslResponseOnEventType*				DcmDslROEConnectionRef;
	
	Dcm_DslProtocolRxType*					DcmDslProtocolRx[];
		
	Dcm_DslProtocolTxType*					DcmDslProtocolTx;
	
}Dcm_DslMainConnectionType;

typedef struct 
{
	PduIdType 			DcmDslPeriodicTxConfirmationPduId;
	
	PduInfoType*  		DcmDslPeriodicTxPduRef;
	
}Dcm_DslPeriodicConnectionType;

typedef struct 
{
	Dcm_DslPeriodicConnectionType* DcmDslPeriodicConnection;
	
}Dcm_DslPeriodicTransmissionType;

typedef struct 
{
	PduIdType			DcmDslRoeTxConfirmationPduId;
	
	PduInfoType* 		DcmDslRoeTxPduRef;
	
}Dcm_DslResponseOnEventType;

typedef struct 
{
	Dcm_DslMainConnectionType*		DcmDslMainConnection;
	
	Dcm_DslPeriodicTransmissionType*	DcmDslPeriodicTransmission;
	
	Dcm_DslResponseOnEventType*		DcmDslResponseOnEventType;
	
}Dcm_DslConnectionType;

typedef struct 
{
	DcmDslProtocolIDType					DcmDslProtocolID;
	
	DcmDslProtocolMaximumResponseSizeType	DcmDslProtocolMaximumResponseSize;
	
	float32									DcmDslProtocolPreemptTimeout;

	DcmDslProtocolPriorityType				DcmDslProtocolPriority;
	
	boolean									DcmDslProtocolRowUsed;
	
	uint8									DcmDslProtocolTransType;
	
	DcmDslProtocolIDType					DcmDslProtocolType;
	
	uint16									DcmDspProtocolEcuAddr;
	
	boolean									DcmSendRespPendOnRestart;
	
	boolean									DcmSendRespPendOnTransToBoot;

	float32									DcmTimStrP2StarServerAdjust;

	uint32									DcmDemClientRef;
	
	Dcm_DslBufferType*						DcmDslProtocolRxBufferRef;
	
	uint32*									DcmDslProtocolSIDTable;
	
	Dcm_DslBufferType*						DcmDslProtocolTxBufferRef;
	
	Dcm_DslConnectionType*					DcmDslConnection;
	
}Dcm_DslProtocolRowType;



typedef struct 
{
	Dcm_DslProtocolRowType*	DcmDslProtocolRow;
								
	Dcm_DslConnectionType*	DcmDslConnection;	
	
}Dcm_DslProtocolType;

typedef struct 
{
	Dcm_DslBufferType*						 DcmDslBuffer;
	
	Dcm_DslCallbackDCMRequestServiceType* 	 DcmDslCallbackDCMRequestService;
	
	Dcm_DslDiagRespType*					 DcmDslDiagResp;
	
	Dcm_DslProtocolType*					 DcmDslProtocol;
	
}Dcm_DslType;

typedef struct 
{
	Dcm_DslType* Dsl;
	
}Dcm_ConfigType;


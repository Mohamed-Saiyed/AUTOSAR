/**********************************************************************************
***********************************************************************************
**														  						 **		
**	FILENAME	:	Dcm_Dsl.c                           					     **
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
**	DESCRIPTION : Dcm Dsl Source File.											 **
**                                                                               **
**	SPECIFICATION(S) : AUTOSAR_SWS_DiagnosticCommunicationManager, AUTR 4.3.1    **
**                                                       						 **
**	MAY BE CHANGED BY USER : No                          						 **
**                                                       					     **
***********************************************************************************/

/***********************************************************************************/
/*				    			Include Headers			         				   */
/***********************************************************************************/


DcmDslBufferType DslBuffer[DCM_DSL_MAX_BUFFER_SIZE];

void Dcm_Dsl_Init (const Dcm_ConfigType* ConfigPtr)
{
	Dcm_DslBufferInit();
}

BufReq_ReturnType DcmDslStartOfReception
(
	PduIdType id,
	PduLengthType TpSduLength,
	PduLengthType* bufferSizePtr
)
{
	BufReq_ReturnType BufferState;
	Dcm_DslProtocolRowType* DslProtocoRow;
	Dcm_DslBufferType*		DslBuffer;
	
	DslProtocoRow = &(ConfigPtr->Dsl->DcmDslProtocol->DcmDslProtocolRow);
	
	DslBuffer = &(DslProtocoRow->DcmDslProtocolRxBufferRef);
	
	if(TpSduLength != 0)
	{
		if(DslBuffer->DcmDslBufferSize < TpSduLength)
		{
			BufferState = BUFREQ_E_OVFL;
		}
		else if(DCM_BUFFER_IDLE != DslBuffer->DcmDslBufferState)
		{
			BufferState = BUFREQ_E_BUSY;
		}
		else
		{
			BufferState = BUFREQ_OK;
			DslBuffer->DcmDslBufferState = DCM_BUFFER_RX_BUSY;
			DslBuffer->DcmDslTpSduLength = TpSduLength;
			*bufferSizePtr = (PduLengthType)DslBuffer->DcmDslBufferSize;
		}
	}
	else
	{
		BufferState = BUFREQ_E_NOT_OK;
		
	}
	
	return BufferState;

}

BufReq_ReturnType DcmDslCopyRxData
(
	PduIdType id,
	const PduInfoType* info,
	PduLengthType* bufferSizePtr
)
{	
	BufReq_ReturnType RetVal;
	uint32 LocalIndex;
	PduLengthType DataLength;
	Dcm_DslProtocolRowType* DslProtocoRow;
	Dcm_DslBufferType*		DslBuffer;
			
	DataLength = info->SduLength;
	
	DslProtocoRow = &(ConfigPtr->Dsl->DcmDslProtocol->DcmDslProtocolRow);
		
	DslBuffer = &(DslProtocoRow->DcmDslProtocolRxBufferRef);
				
	if((DataLength != 0) || (info->SduDataPtr != NULL_PTR))
	{		
		if(((DslBuffer->DcmDslBufferFilledLength) + DataLength) <= (DslBuffer->DcmDslTpSduLength))
		{			
			for(LocalIndex = 0; LocalIndex < DataLength; LocalIndex++)
			{
				DslBuffer.Buffer[LocalIndex] = info->SduDataPtr[LocalIndex];
			}
			
			DslBuffer->DcmDslBufferFilledLength += DataLength;
			
			*bufferSizePtr = (PduLengthType)((DslBuffer->DcmDslMaxBufferSize) -
											 (DslBuffer->DcmDslBufferFilledLength));
			
			RetVal = BUFREQ_OK;
		}
		else
		{
			RetVal = BUFREQ_E_NOT_OK;
		}
	}
	else
	{
		*bufferSizePtr = (PduLengthType)((DslBuffer->DcmDslMaxBufferSize) -
										(DslBuffer->DcmDslBufferFilledLength));
		RetVal = BUFREQ_OK;
	}
	
	return RetVal;
}

BufReq_ReturnType DcmDslCopyTxData
(
	PduIdType id,
	const PduInfoType* info,
	const RetryInfoType* retry,
	PduLengthType* availableDataPtr
)
{
	BufReq_ReturnType RetVal;
	uint32 LocalIndex;
	PduLengthType DataLength;
	Dcm_DslProtocolRowType* DslProtocoRow;
	Dcm_DslBufferType*		DslBuffer;
	
	DataLength = info->SduLength;
	
	DslProtocoRow = &(ConfigPtr->Dsl->DcmDslProtocol->DcmDslProtocolRow);
		
	DslBuffer = &(DslProtocoRow->DcmDslProtocolTxBufferRef);
	
	if(DataLength <= (DslBuffer->DcmDslTpSduLength - DslBuffer->DcmDslBufferFilledLength))
	{
		for(LocalIndex = 0; LocalIndex < DataLength; LocalIndex++)
		{
			info->SduDataPtr[LocalIndex] = DslBuffer.Buffer[LocalIndex];
		}
		
		DslBuffer->DcmDslBufferFilledLength += DataLength;
			
		*availableDataPtr = (PduLengthType)((DslBuffer->DcmDslTpSduLength) -
											(DslBuffer->DcmDslBufferFilledLength));
		RetVal = BUFREQ_OK;
	}
	else
	{
		RetVal = BUFREQ_E_NOT_OK;
	}
	
	return RetVal;
		
}

FUNC(void , DCM_CODE) Dcm_TpTxConfirmation
(
	PduIdType id,
	Std_ReturnType result
)
{
	DslProtocoRow = &(ConfigPtr->Dsl->DcmDslProtocol->DcmDslProtocolRow);
		
	DslBuffer = &(DslProtocoRow->DcmDslProtocolTxBufferRef);
	
	DslBuffer->DcmDslBufferState		= DCM_BUFFER_IDLE;
	DslBuffer->DcmDslBufferFilledLength = 0;
	DslBuffer->DcmDslBufferId 			= 0;
	DslBuffer->DcmDslTpSduLength 		= 0;
	
	
	DcmDslStopStopErrorHandling();
	
	
}

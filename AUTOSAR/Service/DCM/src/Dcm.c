/**********************************************************************************
***********************************************************************************
**														  						 **		
**	FILENAME	:	Dcm.c         	                     					     **
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
**	DESCRIPTION : Dcm Main Source File.											 **
**                                                                               **
**	SPECIFICATION(S) : AUTOSAR_SWS_DiagnosticCommunicationManager, AUTR 4.3.1    **
**                                                       						 **
**	MAY BE CHANGED BY USER : No                          						 **
**                                                       					     **
***********************************************************************************/

/***********************************************************************************/
/*				    			Include Headers			         				   */
/***********************************************************************************/






VAR(uint8 , DCM_VAR) DcmInitState = DCM_UNINITIALIZED;



FUNC(void , DCM_CODE) Dcm_Init(const Dcm_ConfigType* ConfigPtr)
{

#if ( DCM_DEV_ERROR_DETECT == STD_ON )
	
	if(ConfigPtr == NULL_PTR)
	{
		Det_ReportError(DCM_MODULE_ID  ,
						DCM_INSTANCE_ID,
						DCM_INIT_SID,
						DCM_E_PARAM_POINTER);
	}
	else
#endif /* DCM_DEV_ERROR_DETECT */
	{
		Dcm_Dsl_Init();
		Dcm_DsD_Init();
		Dcm_Dsp_Init();
		
		DcmInitState = DCM_INITIALIZED;
	}
	
}

FUNC(BufReq_ReturnType , DCM_CODE) Dcm_StartOfReception
(
	PduIdType id,
	const PduInfoType* info,
	PduLengthType TpSduLength,
	PduLengthType* bufferSizePtr
)
{
	BufReq_ReturnType BufferState;
	
	BufferState = DcmDslStartOfReception(id,TpSduLength,bufferSizePtr);
	
	return BufferState;
}

FUNC(BufReq_ReturnType , DCM_CODE) Dcm_CopyRxData
(
	PduIdType id,
	const PduInfoType* info,
	PduLengthType* bufferSizePtr
)
{
	BufReq_ReturnType RetVal;
		
	RetVal = DcmDslCopyRxData(id,info,bufferSizePtr);

	return RetVal;
}

FUNC(void , DCM_CODE) Dcm_TpRxIndication
(
	PduIdType id,
	Std_ReturnType result
)
{
	if(E_OK == result)
	{
		
	}
	else
	{
		
	}
	
}

FUNC(BufReq_ReturnType , DCM_CODE) Dcm_CopyTxData
(
	PduIdType id,
	const PduInfoType* info,
	const RetryInfoType* retry,
	PduLengthType* availableDataPtr
)
{
	BufReq_ReturnType RerVal;
	
	RerVal = DcmDslCopyTxData(id,info,retry,availableDataPtr);
	
	return RerVal;
}

FUNC(void , DCM_CODE) Dcm_TpTxConfirmation
(
	PduIdType id,
	Std_ReturnType result
)
{
	DcmDslTpTxConfirmation(id,result);
	
	
	
}



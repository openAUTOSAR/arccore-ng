/* -------------------------------- Arctic Core ------------------------------
 * Arctic Core - the open source AUTOSAR platform http://arccore.com
 *
 * Copyright (C) 2009  ArcCore AB <contact@arccore.com>
 *
 * This source code is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 as published by the
 * Free Software Foundation; See <http://www.gnu.org/licenses/old-licenses/gpl-2.0.txt>.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 * -------------------------------- Arctic Core ------------------------------*/





#ifndef DCM_INTERNAL_H_
#define DCM_INTERNAL_H_

// SID table
#define SID_DIAGNOSTIC_SESSION_CONTROL			0x10
#define SID_ECU_RESET							0x11
#define SID_CLEAR_DIAGNOSTIC_INFORMATION		0x14
#define SID_READ_DTC_INFORMATION				0x19
#define SID_READ_DATA_BY_IDENTIFIER				0x22
#define SID_READ_SCALING_DATA_BY_IDENTIFIER		0x24
#define SID_SECURITY_ACCESS						0x27
#define SID_READ_DATA_BY_PERIODIC_IDENTIFIER	0x2A
#define SID_DYNAMICALLY_DEFINE_DATA_IDENTIFIER	0x2C
#define SID_WRITE_DATA_BY_IDENTIFIER			0x2E
#define SID_INPUT_OUTPUT_CONTROL_BY_IDENTIFIER	0x2F
#define SID_ROUTINE_CONTROL						0x31
#define SID_TESTER_PRESENT						0x3E
#define SID_NEGATIVE_RESPONSE					0x7F
#define SID_CONTROL_DTC_SETTING					0x85

// Misc definitions
#define SUPPRESS_POS_RESP_BIT		0x80
#define SID_RESPONSE_BIT			0x40
#define VALUE_IS_NOT_USED			0x00

typedef enum {
	DSD_TX_RESPONSE_READY,
	DSD_TX_RESPONSE_SUPPRESSED
} DsdProcessingDoneResultType;

/*
 * DSP
 */
boolean DspCheckSessionLevel(const Dcm_DspSessionRowType **sessionLevelRefTable);
boolean DspCheckSecurityLevel(const Dcm_DspSecurityRowType	**securityLevelRefTable);

void DspInit(void);
void DspMain(void);
void DspUdsDiagnosticSessionControl(const PduInfoType *pduRxData, PduInfoType *pduTxData);
void DspUdsEcuReset(const PduInfoType *pduRxData, PduIdType txPduId, PduInfoType *pduTxData);
void DspUdsClearDiagnosticInformation(const PduInfoType *pduRxData, PduInfoType *pduTxData);
void DspUdsSecurityAccess(const PduInfoType *pduRxData, PduInfoType *pduTxData);
void DspUdsTesterPresent(const PduInfoType *pduRxData, PduInfoType *pduTxData);
void DspUdsReadDtcInformation(const PduInfoType *pduRxData, PduInfoType *pduTxData);
void DspUdsReadDataByIdentifier(const PduInfoType *pduRxData, PduInfoType *pduTxData);
void DspUdsReadScalingDataByIdentifier(const PduInfoType *pduRxData, PduInfoType *pduTxData);
void DspUdsWriteDataByIdentifier(const PduInfoType *pduRxData, PduInfoType *pduTxData);
void DspUdsControlDtcSetting(const PduInfoType *pduRxData, PduInfoType *pduTxData);
void DspDcmConfirmation(PduIdType confirmPduId);


/*
 * DSD
 */
void DsdInit(void);
void DsdMain(void);
void DsdHandleRequest(void);
void DsdDspProcessingDone(Dcm_NegativeResponseCodeType responseCode);
void DsdDataConfirmation(PduIdType confirmPduId, NotifResultType result);
void DsdDslDataIndication(const PduInfoType *pduRxData, const Dcm_DsdServiceTableType *protocolSIDTable, Dcm_ProtocolAddrTypeType addrType, PduIdType txPduId, PduInfoType *pduTxData, PduIdType rxContextPduId);


/*
 * DSL
 */
void DslInit(void);
void DslMain(void);
void DslHandleResponseTransmission(void);
void DslDsdProcessingDone(PduIdType txPduId, DsdProcessingDoneResultType result);
void DslGetCurrentServiceTable(const Dcm_DsdServiceTableType **currentServiceTable);

BufReq_ReturnType DslProvideRxBufferToPdur(PduIdType dcmRxPduId, PduLengthType tpSduLength, const PduInfoType **pduInfoPtr);
void DslRxIndicationFromPduR(PduIdType dcmRxPduId, NotifResultType result);
Std_ReturnType DslGetActiveProtocol(Dcm_ProtocolType *protocolId);
void DslSetSecurityLevel(Dcm_SecLevelType secLevel);
Std_ReturnType DslGetSecurityLevel(Dcm_SecLevelType *secLevel);
void DslSetSesCtrlType(Dcm_SesCtrlType sesCtrlType);
Std_ReturnType DslGetSesCtrlType(Dcm_SesCtrlType *sesCtrlType);
BufReq_ReturnType DslProvideTxBuffer(PduIdType dcmTxPduId, const PduInfoType **pduInfoPtr, PduLengthType length);
void DslTxConfirmation(PduIdType dcmTxPduId, NotifResultType result);
void DslResetSessionTimeoutTimer(void);


#endif /* DCM_INTERNAL_H_ */
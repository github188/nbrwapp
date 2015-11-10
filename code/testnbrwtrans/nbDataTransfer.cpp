/********************************************************************
 File: nbDataTransfer.cpp
 Function: Provide class to ger data from device and transfer it to
           set address.     
 Author: Luobihe
 Date: 2015-6-29
*********************************************************************/

#include <stdio.h>
#include "nbDataTransfer.h"

#pragma comment(lib, "Winmm.lib")

CNbDataTransfer::CNbDataTransfer(void)
{
    iTimerID     = -1;
    iTimeDelay   = TRANSFER_DELAY;
    iState       = TRANSFER_NOT_START;
    iTransOption = TRANSFER_ALL_DATA;
}

CNbDataTransfer::~CNbDataTransfer(void)
{
    if (iTimerID != -1) {
        timeKillEvent(iTimerID);
        iTimerID = -1;
    }

    Free();
}

void CNbDataTransfer::Free(void)
{
    rwDataParse.Free();
    iState = TRANSFER_NOT_START;
}

/*-------------------------------------------------------------------
 Function: SetParameter(...)
 Purpose: ����ת������״̬
 Parameters: szSrcIp -- [IN], redwood �豸 IP ��ַ
             iInterval -- [IN], ����Դ �˿�
             szUser -- [IN], user name
             szPw -- [IN], password
             szUdpIp -- [IN], �������ݵ�udp��������ַ
             iUdpPort -- [IN], �������ݵ�udp�����������˿�
             iInterval -- [IN], ת�����ݵļ������λΪ�� 
             iTransferOption -- [IN], ת���������������ݻ�ֻ
                       ת�仯�����ݣ� 
                       0�� ת�������ݣ� 1�� תֻ�仯������
 return: -1 --  ����������
         0  -- �ɹ�
-------------------------------------------------------------------*/
int CNbDataTransfer::SetParameter(const char* szSrcIp, int iSrcPort, 
        const char* szUser, const char* szPw, const char* szUdpIp,
        int iUdpPort, int iInterval, int iTransferOption)
{
    if (szSrcIp == NULL || szUdpIp == NULL || iInterval <= 0)
        return -1;

    //����Դ����
    rwhandler.setNetAddr((char*)szSrcIp, iSrcPort);  
    rwhandler.setUserAndPw(szUser, szPw);

    //udp ��������
    nbDataSender.setPeerAddr(szUdpIp, iUdpPort); 

    //����ת������
    iTimeDelay = iInterval * 1000;
    iTransOption = iTransferOption;

    return 0;
}

int CNbDataTransfer::StartTransferFlow(void)
{
    if (iTimerID != -1)
        return 0;

    iTimerID = timeSetEvent(iTimeDelay, TRANSFER_TIMER_RESOLUTION, 
        (LPTIMECALLBACK)CallBackFunc, (DWORD_PTR)this, TIME_PERIODIC);

    if (iTimerID <= 0) {
        iTimerID = -1;
        return -1;
    }

    iState = TRANSFER_START;

    return 0;
}

int CNbDataTransfer::StopTransferFlow(void)
{
    if (iTimerID == -1)
        return 0;

    if (TIMERR_NOERROR == timeKillEvent(iTimerID)) {
        Free();
        iTimerID = -1;

        return 0;
    }

    return -1;
}

void CALLBACK CNbDataTransfer::CallBackFunc(UINT wTimerID, UINT msg,DWORD dwUser,DWORD dwl,DWORD dw2) 
{
    CNbDataTransfer* pTemp = (CNbDataTransfer*)dwUser;
    pTemp->oneOp();
}

int CNbDataTransfer::oneOp()
{
    //read from redwood
    if (rwhandler.readRedWoodData()) {
        iState = TRANSFER_ERROR_READRWDATA;
        return -1;
    }

    FILE* p_file = NULL;
    p_file = fopen("testjson.dat", "rw");
    if (p_file) {
        fwrite(rwhandler.getRedWoodData(), 1, strlen(rwhandler.getRedWoodData()), p_file);
        fclose(p_file);
        p_file = NULL;
    }

    //parse data
    if (rwDataParse.ParseRedWoodDataFromStr(rwhandler.getRedWoodData())) {
        iState = TRANSFER_ERROR_PARSEDATA;
        return -1;
    }
    
    //transfer data with UDP
    const char* pTransData = NULL;
    pTransData = iTransOption ? rwDataParse.GetParseData() :
        rwDataParse.GetAllParseData();
    if (nbDataSender.sendData(pTransData)) {
        iState = TRANSFER_ERROR_SENDDATA;
        return -1;
    }

    iState = TRANSFER_START;

    return 0;
}

int CNbDataTransfer::GetTransferStates(void)
{
    return iState;
}
/********************************************************************
 File: nbDataTransfer.h
 Function: Provide class to ger data from device and transfer it to
           set address.     
 Author: Luobihe
 Date: 2015-6-29
*********************************************************************/

#ifndef __NBDATATRANSFER_H__
#define __NBDATATRANSFER_H__

#include "redWoodHandle.h"
#include "nbDataSender.h" 
#include "redWoodDataParse.h"

#include <Windows.h>

#ifdef __cplusplus
extern "C"
{
#endif

//��ʱ������
#define TRANSFER_TIMER_RESOLUTION       1          //ת�����ݵĶ�ʱ���ֱ���
#define TRANSFER_DELAY                  2000       //����ת����ʱ����

//ת�������ݹ�ģ
#define TRANSFER_ALL_DATA               0          //ת����������
#define TRANSFER_CHANGED_DATA           1          //ת�����ϴη������ݲ�ͬ������


//ת����״̬�궨��
#define TRANSFER_NOT_START              0
#define TRANSFER_START                  1
   
#define TRANSFER_ERROR_READRWDATA       2    //�� redwood ���ݲ��ɹ�
#define TRANSFER_ERROR_PARSEDATA        3    //���� redwood ���ݲ��ɹ�
#define TRANSFER_ERROR_SENDDATA         4    //���� redwood ���ݲ��ɹ�


class CNbDataTransfer {
private:
    CRedWoodHandle rwhandler;
    CNbDataSender  nbDataSender;
    CRedWoodDataParse rwDataParse;

    int iTimerID;      //��ʱ�����
    int iTimeDelay;    //��ʱ���
    int iState;        //ת����״̬
    int iTransOption;  //ת�������ݹ�ģ

private:
public:
    //����һ�β��Լ�����ת��
    int oneOp(void);

    //�ͷ���Դ
    void Free(void);

    //��ʱ���ص�����
    static void CALLBACK CallBackFunc(UINT wTimerID, UINT msg,DWORD dwUser,DWORD dwl,DWORD dw2);

public:
    CNbDataTransfer(void);
    ~CNbDataTransfer(void);

    //���ò���
    int SetParameter(const char* szSrcIp, int iSrcPort, 
        const char* szUser, const char* szPw, 
        const char* szUdpIp, int iUdpPort, 
        int iInterval, int iTransferOption);

    //����ת������
    int StartTransferFlow(void);

    //ֹͣת������
    int StopTransferFlow(void);

    //��ȡ״̬,���ص�״̬Ϊ���涨���ֵ֮һ
    int GetTransferStates(void);
};

#ifdef __cplusplus
}
#endif

#endif  //__NBDATATRANSFER_H__
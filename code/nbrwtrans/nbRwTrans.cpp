/********************************************************************
 File: nbRwTrans.cpp
 Function: newbest ת�� redwood �豸���ݵĽӿ�     
 Author: Luobihe
 Date: 2015-7-1
*********************************************************************/

#define DLL_NBRWTRANS_API __declspec(dllexport)

#include "nbRwTrans.h"
#include "nbDataTransfer.h"

static CNbDataTransfer s_DataTranser;   //��������

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
extern int DLL_NBRWTRANS_API SetTransferParameter(const char* szSrcIp,
                                                  int iSrcPort,
                                                  const char* szUser,
                                                  const char* szPw,
                                                  const char* szUdpIp,
                                                  int iUdpPort,
                                                  int iInterval,
                                                  int iTransferOption)
{
    return s_DataTranser.SetParameter(szSrcIp, iSrcPort, 
        szUser, szPw, szUdpIp, iUdpPort,
        iInterval, iTransferOption);
}

/*-------------------------------------------------------------------
 Function: StartTransferFlow()
 Purpose: ��������ת������
 Parameters:
 return: 0 --  �ɹ�
         -1 -- ʧ��
-------------------------------------------------------------------*/
int StartTransferFlow(void)
{
    return s_DataTranser.StartTransferFlow();
}

/*-------------------------------------------------------------------
 Function: StopTransferFlow()
 Purpose: ֹͣ����ת������
 Parameters: 
 return: 0 --  �ɹ�
         -1 -- ʧ��
-------------------------------------------------------------------*/
int StopTransferFlow(void)
{
    return s_DataTranser.StopTransferFlow();
}

/*-------------------------------------------------------------------
 Function: GetTransferStates()
 Purpose: ��ȡ Transfer ��״̬
 Parameters: 
 return: 0 --  δ����
         1 -- ����������
         2 -- ��ȡ redwood ���ݲ��ɹ�
         3 -- ���� redwood ���ݲ��ɹ�
         4 -- ���� redwood ���ݲ��ɹ�
-------------------------------------------------------------------*/
int DLL_NBRWTRANS_API GetTransferStates(void)
{
    return s_DataTranser.GetTransferStates();
}
/********************************************************************
 File: nbRwTrans.h
 Function: newbest ת�� redwood �豸���ݵĽӿ�     
 Author: Luobihe
 Date: 2015-7-1
*********************************************************************/

#ifndef __NBRWTRANS_H__
#define __NBRWTRANS_H__


#ifndef DLL_NBRWTRANS_API
#define DLL_NBRWTRANS_API 
#endif

#ifdef __cplusplus
extern "C"
{
#endif

    
//ת����״̬�궨��
#define TRANSFER_NOT_START              0    //����δ����
#define TRANSFER_START                  1    //����������
   
#define TRANSFER_ERROR_READRWDATA       2    //�� redwood ���ݲ��ɹ�
#define TRANSFER_ERROR_PARSEDATA        3    //���� redwood ���ݲ��ɹ�
#define TRANSFER_ERROR_SENDDATA         4    //���� redwood ���ݲ��ɹ�


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
                                                  int iTransferOption);

/*-------------------------------------------------------------------
 Function: StartTransferFlow()
 Purpose: ��������ת������
 Parameters:
 return: 0 --  �ɹ�
         -1 -- ʧ��
-------------------------------------------------------------------*/
extern int DLL_NBRWTRANS_API StartTransferFlow(void);

/*-------------------------------------------------------------------
 Function: StopTransferFlow()
 Purpose: ֹͣ����ת������
 Parameters: 
 return: 0 --  �ɹ�
         -1 -- ʧ��
-------------------------------------------------------------------*/
extern int DLL_NBRWTRANS_API StopTransferFlow(void);

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
extern int DLL_NBRWTRANS_API GetTransferStates(void);

#ifdef __cplusplus
}
#endif

#endif  //__NBRWTRANS_H__

/********************************************************************
 File: httpResHandle.h
 Function: ���� http ��Ӧ����
 Author: Luobihe
 Date: 2015-6-26
********************************************************************/

#ifndef __HTTPRESHANDLE_H__
#define __HTTPRESHANDLE_H__

#define HTTPREADBUFF (1024*4)

class CHttpResHandler {         
public:
    //��ȡhttp��Ӧ��ͷ��
    static int readHttpResHead(int sockfd, char* pBuffer);

    //��Tcp����ͷ���õ��������ȡ�ĳ���
    static int readTcpDataLen(int sockfd);

    //��http��Ӧ������
    static int readHttpResBody(int sockfd, char* pBuffer);

};

#endif  //  __HTTPRESHANDLE_H__
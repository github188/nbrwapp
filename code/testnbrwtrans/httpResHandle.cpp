/********************************************************************
 File: httpResHandle.cpp
 Function: ���� http ��Ӧ����
 Author: Luobihe
 Date: 2015-6-26
********************************************************************/

#include <string.h>
#include <stdio.h>
#include "httpResHandle.h"


#ifdef _WIN32

#include <winsock.h>
#pragma comment(lib, "ws2_32.lib")
#include <Windows.h>

#else

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/in.h>

#endif

/*-------------------------------------------------------------------
 Function: readHttpResHead(int, char*);
           ��ȡhttp��Ӧ��ͷ��,���� \r\n\r\n�򷵻�
 Parameters:
     sockfd -- [IN], ����� socket
     pBuffer -- [OUT], ������ http ��Ӧͷ
 Return�� -1 -- ��httpЭ������
          >= 0 -- ͷ����С
-------------------------------------------------------------------*/
int CHttpResHandler::readHttpResHead(int sockfd, char* pBuffer)
{
    if (pBuffer == NULL)
        return -1;

    bool bIsDone = false;
    bool bIsCF = false;
    int  iRet = 0;
    int  iLen = 0;

    while (!bIsDone) {
        iRet = recv(sockfd, pBuffer, 1, 0);
        if (iRet < 0)
            return -1;

        iLen ++;

        switch (*pBuffer) {
            case '\r':
                break;

            case '\n':
                if (bIsCF)
                    bIsDone = true;

                bIsCF = true;
                break;

            case '\0':
                return -1;

            default:
                bIsCF = false;            
        }

        pBuffer++;
    }

    *pBuffer = 0;

    return iLen;
}

/*-------------------------------------------------------------------
 Function: readTcpDataLen(int);
           ��ȡTcp����ͷ
 Parameters:
     sockfd -- [IN], ����� socket
 Return�� ���ݳ���
-------------------------------------------------------------------*/
int CHttpResHandler::readTcpDataLen(int sockfd)
{
    char szBuffer[8] = {0};
    int  iLen = 0;
    int  iRet = 0;

    iRet = recv(sockfd, szBuffer, 5, 0);
    if (iRet < 0)                   
        return -1;                       

    sscanf(szBuffer, "%x", &iLen);

    return iLen;
}

/*-------------------------------------------------------------------
 Function: readHttpResBody(int, char*);
           ��ȡhttp��Ӧ��������
 Parameters:
     sockfd -- [IN], ����� socket
     pBuffer -- [OUT], ������ http ��Ӧͷ
 Return�� -1 -- ��httpЭ������
          >= 0 -- ���ݴ�С
-------------------------------------------------------------------*/
int CHttpResHandler::readHttpResBody(int sockfd, char* pBuffer)
{
    char szBuffer[256] = {0};
    int iLen = 0;
    int iRet = 0;
    int iBodyLen = 0;

    iRet = CHttpResHandler::readHttpResHead(sockfd, szBuffer);
    if (iRet <= 0)
        return -1;

    //read http body
    do { 
        iLen = CHttpResHandler::readTcpDataLen(sockfd);
        if (iLen <= 0)
            break;                             

        iRet = recv(sockfd, pBuffer + iBodyLen, iLen, 0);
        if (iRet <= 0)
            break;
        iBodyLen += iRet;

        pBuffer[iBodyLen] = 0; 
     
        iRet = recv(sockfd, szBuffer, 2, 0);
        if (iRet <= 0)
            break;       
    } while (1); 

    return iBodyLen;
}
// ͷ�ļ� base64.h

#ifndef __BASE64_H__
#define __BASE64_H__

/* Base64 ���� */ 
char* base64_encode(const char* data, char* pDest, int data_len); 

/* Base64 ���� */ 
char *base64_decode(const char* data, char* pDest, int data_len); 

#endif
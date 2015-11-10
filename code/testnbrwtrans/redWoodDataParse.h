/********************************************************************
 File: redWoodDataParse.h
 Function: Parse the get redwood data to a special format.     
 Author: Luobihe
 Date: 2015-6-29
*********************************************************************/

#ifndef __REDWOODDATAPARSE_H__
#define __REDWOODDATAPARSE_H__

#include "cJSON.h"

#define TRANSER_JSON_VERSION  "1.1"

/*
Parse the data from redwood device.
General some point in the data and packet them in a
special format to transfer
*/
class CRedWoodDataParse {
private:
    cJSON *rawJson;
    cJSON *oldDataJson;
    cJSON *updatedDataJson;
    char* pParseData;
    char* pAllParseData;

private:
    //�������ַ�������������json����
    int ParseFromStr(const char *value);

    //�������ݲ����浽 updateDataJson �У�ԭ�е�����ת�Ƶ� oldDataJson
    int UpdateData(void);

    //�������󣬲���Ҫ������ı��ַ���
    int GenerateOutData(void);

    //add sensor data
    int AddSensorDataToJson(cJSON* sensorJson, cJSON* descJson);

    //�� json ��������ı��� pParseData
    int GenerateOutDataFromJson(cJSON* json);

    //�� json ��������ı��� pAllParseData
    int GenerateFullOutDataFromJson(cJSON* json);

    void testAddSensorData();
    void testUpdateData();
    void testGenerateOutData();

public:
    CRedWoodDataParse(void);
    ~ CRedWoodDataParse(void);

    //������Դ
    void Free();

    //�������ַ�������Ҫ������ַ���
    int ParseRedWoodDataFromStr(const char* pRWStr);  

    const char* GetParseData(void) {return pParseData;}

    const char* GetAllParseData(void) { return pAllParseData;}

    void Test();

};

#endif  //__REDWOODDATAPARSE_H__
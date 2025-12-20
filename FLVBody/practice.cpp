//
//  practice.cpp
//  FLVBody
//
//  Created by scarlett on 2023/9/18.
//

#include "practice.hpp"
#include "scriptData.h"


parseScriptData::parseScriptData()
{
}
parseScriptData::~parseScriptData()
{
    fclose(file);
}
//----------------------------------------------
bool parseScriptData::openFile(char* path)
{

    file = fopen(path, "rb");
    if(file == nullptr)
        return false;
    return true;
}
//----------------------------------------------
void parseScriptData::jumptocur()
{
    fread(&header,sizeof(header),1,file);
    uint32_t ptag;
    fread(&ptag, sizeof(uint32_t), 1, file);
    fread(&tag, sizeof(FlvTag), 1, file);
//    int pos = ftell(file);
}
//----------------------------------------------
void parseScriptData::parseMetaData()
{
    char data[300];
    fread(data, 1, 1, file);
    array.type = data[0];
    meta.name = getString(array.length);
    printf("===%s===\n",meta.name.c_str()); //要有換行符號才會印出
    fread(data,1, 1, file);
    meta.type = data[0];
    printf("類型：%d\n",meta.type);
    if(meta.type == 8)
    {
        fread(data, 4, 1, file);
        char* p = (char*)&meta.total;
        for(int i=0; i<4; i++)
        {
            p[i] = data[3-i];
        }
//        meta.total = data[0]+data[1]+data[2]+data[3];
    }
    printf("數量：%d\n",meta.total);
}
//----------------------------------------------
void parseScriptData::parseECMA()
{
    char data[300];
    while(1)
    {
        array.name = getString(array.length);
        printf("key: %s ",array.name.c_str());

        fread(data, 1, 1, file);
        array.type = data[0];
        if(array.type == 0)
        {
            fread(data, 8, 1, file);
            char *p = (char *)&(Number.value);
            for(int i=0; i<8; i++)
            {
                p[i] = data[7-i];
            }
//            memcpy(&(Number.value), data, 8);
            printf("\tvalue: %f\n",Number.value);
        }
        if(array.type == 1)
        {
            fread(data, 1, 1, file);
            memcpy(&Bool.value, data, 1);
            printf("\tvalue: %d\n", Bool.value);
        }
        if(array.type == 2)
        {
            String.value = getString(String.length);
            printf("\tvalue: %s\n", String.value.c_str());
        }
    }
   
    
    
}
//----------------------------------------------
uint16_t parseScriptData::getUint16(char* a)
{
    uint16_t b = (a[0] << 8)| a[1];
    return b;
}
//----------------------------------------------
string parseScriptData::getString(uint16_t &stringLen)
{
  //  char* data = (char*)malloc(100 * sizeof(uint8_t)); //轉成char＊不會自動讓數據轉換為字元陣列
    char data[100];
    fread(data, 2, 1, file);
    stringLen = getUint16(data); //0008 -> 8
    if(stringLen == 0) //如果stringLen這兩個byte都是0
    {
        return "";
    }
    fread(data, stringLen, 1, file);
    data[stringLen] = 0;
    string name(data); //回傳2byte的data
    return name;
}

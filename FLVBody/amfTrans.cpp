//
//  amfTrans.cpp
//  FLVBody
//
//  Created by scarlett on 2023/9/12.
//

#include "amfTrans.hpp"
#include "scriptData.h"

//--------------------------------------------------
amfAnalyse::amfAnalyse()
    :FlvResolver()
{
    file = nullptr;
    
}
//--------------------------------------------------
amfAnalyse::~amfAnalyse()
{
    if(file != nullptr)
    {
        fclose(file);
    }
}
//--------------------------------------------------
bool amfAnalyse::openFile(const char* path)
{
    if(path == nullptr)
        return false;
    file = fopen(path, "rb");
    
    return true;
}
//--------------------------------------------------
bool amfAnalyse::jump2cur()
{
    if(file == nullptr)
        return  false;
    FlvHeader header;
    fread((void*)&header, sizeof(FlvHeader), 1, file);
    uint32_t previoustag;
    fread((void*)&previoustag, sizeof(uint32_t), 1, file);
    FlvTag tag;
    fread((void*)&tag, sizeof(FlvTag), 1, file);
    //24
    
    return true;
}
//--------------------------------------------------
bool amfAnalyse::analyseMetaData()
{
    uint8_t data[300]; //temp
    fread(data, 3, 1, file);
    array.type=data[0]; //02
    array.length=getUint16(data+1);//000A -> 10
    fread(data, array.length, 1, file); //text content
    data[array.length]=0; //讀進onMetaData把字串後面放一個0 讓程式讀到0時結束
    meta.name=string((char *)data); //把onMetaData轉成string存進meta.name
    printf("=====%s=====\n",meta.name.c_str());
    uint8_t dataType;
    uint32_t dataCount=0;
    fread(&dataType, 1, 1, file);
    
    if(dataType==8)
    {
        fread(&data, 4, 1, file);
        dataCount= data[0]<<24 | data[1] << 16 | data[2] << 8| data[3];
        analyseECMA();
    }
    return true;
}

//--------------------------------------------------
bool amfAnalyse::analyseECMA()
{
    uint8_t data[300];
//infinite loop means that the function will continue to parse data and will not exit until a certain termination condition is reached
    while(1)
    {
        array.name=getString(file, array.length); //0008 stringLen=8
        printf("key: %s", array.name.c_str());
        if(array.length==0 )//&& isEndFlag())
        {
            break;
        }
        fread(data, 1, 1, file);//fread的值是1 資料是放在data裡
        array.type=data[0];
        switch(array.type)
        {
            case 0:
            {
                fread(&data, 8, 1, file);// value type
                double value;
                char *p=(char *)&value; //指到最前面
                for(int i=0;i<8;i++)
                {
                    p[i]=data[7-i]; //把double位元轉換
                }
                printf("\t value: double %f\n", value);
                break; //跳出case，回到switch
            }
            case 1:
                Bool.value = fread(data, 1, 1, file);
                printf("\t value: %d \n", Bool.value);
                break;
            case 2:
                String.value=getString(file, String.length);
                printf("\t value: %s \n", String.value.c_str());
                break;
            
        }
    }
    return true;
}
//--------------------------------------------------
bool amfAnalyse::isEndFlag()
{
    bool isEnd=false;
    uint8_t data[300];
//    if(stringLen==0) //檢查stringLen是否等於0，如果等於0，則表示接下來的字串為空字串。
//    {
        //使用fread從檔案中讀取1個字節的數據，並檢查這個字節是否等於9。如果等於9，則印出"finish"並返回一個空字串。
        fread(data, 1, 1, file);
        if(data[0]==9)
        {
            printf("finish \n");
           // return string("");
            isEnd=true;
        }
//    }
    
    return isEnd;
}
//--------------------------------------------------
string amfAnalyse::getString(FILE *file, uint16_t &stringLen)
{
    uint8_t data[300];
    fread(data, 2, 1, file); //讀進2b
    stringLen=getUint16(data); //0008 -> 8
    if(stringLen==0) //檢查stringLen是否等於0，如果等於0，則表示接下來的字串為空字串。
    {
        //使用fread從檔案中讀取1個字節的數據，並檢查這個字節是否等於9。如果等於9，則印出"finish"並返回一個空字串。
        fread(data, 1, 1, file);
        if(data[0]==9)
        {
            printf("finish \n");
            return string("");
        }
//        return string("");
    }
    fread(data, stringLen, 1, file);//再讀進字串內容
    data[stringLen]=0; //後面放0結束
    string name=string((char*)data);
    return name;
}
//--------------------------------------------------
uint16_t amfAnalyse::getUint16(unsigned char * data)
{
    //把000D轉成big endian
    uint16_t value=0;
    value=data[0]<<8 | data[1];
    return value;
}

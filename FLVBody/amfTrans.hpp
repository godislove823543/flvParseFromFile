//
//  amfTrans.hpp
//  FLVBody
//
//  Created by scarlett on 2023/9/12.
//
#pragma once
#ifndef amfTrans_hpp
#define amfTrans_hpp
#include "FlvResolver.hpp"
#include "scriptData.h"
#include <stdint.h>
using namespace std;

class amfAnalyse:FlvResolver
{
private:
    FILE* file;
    MetaDataTag meta;
    ECMA_ELEMENT_NUMBER Number;
    ECMA_ELEMENT_BOOL Bool;
    ECMA_ELEMENT_STRING String;
    ECMA_ARRAY array;

public:
    amfAnalyse();
    ~amfAnalyse();
    
    bool openFile(const char* path);
    bool jump2cur();
    bool analyseMetaData();
    bool analyseECMA();
    bool isEndFlag();
    uint16_t getUint16(unsigned char * data);
    string getString(FILE *file,uint16_t &stringLen);
};
#endif /* amfTrans_hpp */

//
//  practice.hpp
//  FLVBody
//
//  Created by scarlett on 2023/9/18.
//

#ifndef practice_hpp
#define practice_hpp
#include "scriptData.h"
#include "FlvResolver.hpp"
#include <stdio.h>
#include <stdint.h>
using namespace std;
class parseScriptData
{
private:
    FILE* file;
    FlvHeader header;
    FlvTag tag;
    MetaDataTag meta;
    ECMA_ARRAY array;
    ECMA_ELEMENT_NUMBER Number;
    ECMA_ELEMENT_BOOL Bool;
    ECMA_ELEMENT_STRING String;
public:
    parseScriptData();
    ~parseScriptData();
    
    bool openFile(char* path);
    void jumptocur();
    void parseMetaData();
    void parseECMA();
    uint16_t getUint16(char* a);
    string getString(uint16_t &stringLen);
    
};
#endif /* practice_hpp */

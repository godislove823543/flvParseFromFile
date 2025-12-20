//
//  scriptData.h
//  FLVBody
//
//  Created by scarlett on 2023/9/13.
//

#ifndef scriptData_h
#define scriptData_h
#include <stdint.h>
#include <string>
#include <vector>
using namespace std;

//metadata
struct MetaDataTag
{
    string name;
    uint8_t type;
    uint32_t total;
};

//ECMA array
struct ECMA_ARRAY
{   
    uint8_t type;
    string name;
    uint16_t length;
};
//duration ~ audiosamplesize,audiocodecid,filesize
struct ECMA_ELEMENT_NUMBER
{
    double value; //jump over 8
};
struct ECMA_ELEMENT_BOOL
{
    uint8_t value; //01
};
struct ECMA_ELEMENT_STRING
{
    uint16_t length;
    string value;
};

#endif /* scriptData_h */

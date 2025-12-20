//
//  FLVBody.hpp
//  FLVBody
//
//  Created by scarlett on 2023/9/6.
//
#pragma once

#include <stdio.h>
#include <stdint.h>
#include <vector>

#pragma pack(push, 1)
struct FlvHeader
{
    uint8_t Signature[3];
    uint8_t Version;
    uint8_t TypeFlags;
    uint32_t DataOffset;
};

struct uint24_t
{
    uint8_t low_byte;
    uint8_t mid_byte;
    uint8_t high_byte;
};

struct FlvTag
{
    uint8_t TagType; //18
    uint8_t DataSize[3]; //174
    uint24_t Timestamp; //0
    uint8_t TimestampExtended;//0
    uint24_t StreamID; //0
};
#pragma pack(pop)

class FlvResolver
{
private:
    FILE* file;
    FlvHeader header;
    std::vector<uint32_t> tagsize; //放previous tag size
    std::vector<FlvTag> tagGroup;
    FlvTag tag;
    
public:
    FlvResolver();
    ~FlvResolver();

    bool openFile(const char* path);
    
    bool resolveFlvHeader();
    void printHeader(char* buf, size_t buf_size);
    bool resolveFlvBody();
    void printBody(FlvTag tag,int i);
    bool resolvePreviousTagSize();
    bool resolveFlvTag(int i);
    
    uint32_t BE2LE_32(uint32_t be);
    uint32_t BE2LE_24(uint24_t be);
};



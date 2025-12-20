//
//  FlvResolver.cpp
//  FlvResolver
//
//  Created by scarlett on 2023/9/6.
//

#include <stdlib.h>
#include <string.h>
#include "FlvResolver.hpp"

using namespace std;
//--------------------------------------------------
FlvResolver::FlvResolver()
{
    file = nullptr;
}
//--------------------------------------------------
FlvResolver::~FlvResolver()
{
    if (file != nullptr)
    {
        fclose(file);
    }
}
//--------------------------------------------------
bool FlvResolver::openFile(const char* path)
{
    if(path == nullptr)
        return false;

    file = fopen(path, "rb");
    
    return true;
}
//--------------------------------------------------
bool FlvResolver::resolveFlvHeader()
{
    if(file == nullptr)
        return false;
    
    size_t result = fread((void *)&header, sizeof(FlvHeader), 1, file);
    if(result == 0)
        return false;
    
    header.DataOffset = BE2LE_32(header.DataOffset);
 
    return true;
}
//--------------------------------------------------
void FlvResolver::printHeader(char* buf, size_t buf_size)
{
    int pos = 0;
        pos = snprintf(buf, buf_size, "===FLV Header===\n");
        pos += snprintf(buf + pos, buf_size - pos, "Signature : %c%c%c\n",
                        header.Signature[0],header.Signature[1],header.Signature[2]);
        pos += snprintf(buf + pos, buf_size - pos, "Version : %d\n",
                        header.Version);
        pos += snprintf(buf + pos, buf_size - pos, "TypeFlags : %d\n",
                        header.TypeFlags);
        pos += snprintf(buf + pos, buf_size - pos, "DataOffset : %d\n",
                        header.DataOffset);
    printf("%s",buf);
}
//--------------------------------------------------
bool FlvResolver::resolveFlvBody()
{
    int i = 0;
    resolvePreviousTagSize(); //skip 0
    
    while(!feof(file))
    {
        if (resolveFlvTag(i) == false)
            break;
        i++;
        
        if (resolvePreviousTagSize() == false)
            break;
    }
    
    return true;
}

//--------------------------------------------------
bool FlvResolver::resolvePreviousTagSize()
{
    if(file == nullptr)
        return false;
    
    uint32_t t;
    size_t result = fread((void*)&t, sizeof(uint32_t), 1, file); //4
    if(result != 1)
        return false;
    
    // add to vector
    tagsize.push_back(BE2LE_32(t));
    return true;
}
//--------------------------------------------------
bool FlvResolver::resolveFlvTag(int i)
{
    if(file == nullptr)
        return false;
    
    FlvTag tag = {0};
    size_t tag_result = fread((void*)&tag, sizeof(FlvTag), 1, file); //11
    if(tag_result != 1)
        return false;
    tagGroup.push_back(tag);
    

    int a = (tag.DataSize[0] << 16) | (tag.DataSize[1] << 8) | tag.DataSize[2];  //檢查目前位置 int pos=ftell(file);
    fseek(file, a, SEEK_CUR); //往後跳datasize格
    printBody(tag,i);
    return true;
}
//--------------------------------------------------
void FlvResolver::printBody(FlvTag tag,int i)
{
    int pos = 0;
    int buf_size = 4096;
    char buf[4096];
        pos += snprintf(buf + pos, buf_size - pos, "===FLV Body===\n");
        pos += snprintf(buf + pos, buf_size - pos,"PreviousTagSize%d: %d\n",i,tagsize.back());
        pos += snprintf(buf + pos, buf_size - pos, "Tag%d\n",i+1);
        pos += snprintf(buf + pos, buf_size - pos, "TagType: %d\n",tag.TagType);
        pos += snprintf(buf + pos, buf_size - pos, "DataSize: %d%d%d\n",tag.DataSize[0],tag.DataSize[1],tag.DataSize[2]);
        pos += snprintf(buf + pos, buf_size - pos, "Timestamp: %d\n",BE2LE_24(tag.Timestamp));
        pos += snprintf(buf + pos, buf_size - pos, "TimestampExtended: %d\n",tag.TimestampExtended);
        pos += snprintf(buf + pos, buf_size - pos, "StreamID: %d\n",BE2LE_24(tag.StreamID));
        printf("%s",buf);
}
//--------------------------------------------------
uint32_t FlvResolver::BE2LE_32(uint32_t be)
{
    uint32_t le = 0;
    le |= (be & 0xFF) << 24;
    le |= ((be >> 8) & 0xFF) << 16;
    le |= ((be >> 16) & 0xFF) << 8;
    le |= (be >> 24) & 0xFF;
    return le;
}
//--------------------------------------------------
uint32_t FlvResolver::BE2LE_24(uint24_t be)
{
    uint32_t le = 0;
    le |= be.low_byte << 16;
    le |= be.mid_byte << 8;
    le |= be.high_byte;
    
    return le;
}

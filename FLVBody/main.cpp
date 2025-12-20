//
//  main.cpp
//  FLVBody
//
//  Created by scarlett on 2023/9/6.
//
#include <iostream>

//
//#include "FlvResolver.hpp"
#include "amfTrans.hpp"
#include "practice.hpp"
int main(int argc, const char * argv[])
{
    //test mine ist big or little
//    int num = 0x1234ABCD;
//    char *ptrNum = (char *) &num;
//    for(int i = 0; i < 4; i++)
//        printf("%p: %02x \n",(void*)ptrNum,(unsigned char)*ptrNum++);

    
//    FlvResolver* resover = new FlvResolver();
//
//    // 1. open flv file
//    resover->openFile("/Users/scarlett/Documents/bipbop.flv");
//    // 2. resolve flv header
//    char headInfo[4096];
//    char tagInfo[4096];
//    resover->resolveFlvHeader();
//    resover->printHeader(headInfo, 4096);
//    // 3. resolve flv body
//    resover->resolveFlvBody();
//
//    delete resover;
    

    parseScriptData* p = new parseScriptData();
    p->openFile("/Users/Scarlett/flv_parser2/bipbop.flv");
    p->jumptocur();
    p->parseMetaData();
    p->parseECMA();
    delete p;
    
    return 0;
}

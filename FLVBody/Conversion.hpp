//
//  Conversion.hpp
//  FLVBody
//
//  Created by scarlett on 2023/9/7.
//

#ifndef Conversion_hpp
#define Conversion_hpp

#include <stdio.h>
#include <math.h>
#include <string.h>

class HexToDec
{
public:
    int hexToDec(char* hex_num)
    {
        long decimal_num = 0;
        int length = strlen(hex_num);
        
        for(int i = length - 1; i >= 0; i--)
        {
            int digit;
            if(hex_num[i] >= '0' && hex_num[i] <= '9')
            {
                digit = hex_num[i] - '0';
            }
            else if (hex_num[i] >= 'A' && hex_num[i] <= 'F')
            {
                digit = hex_num[i] - 'A' + 10;
            }
            else
            {
                printf("invalid var");
                return 1;
            }
            
            decimal_num += digit * pow(16, length - i - 1);
        }
        printf("他的十進制為: %11ld\n",decimal_num);
        
        return 0;
    }
};

#endif /* Conversion_hpp */

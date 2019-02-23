//
//  main.c
//  Задача 1
//
//  Created by Доктор Кларик on 21.02.19.
//  Copyright © 2019 Доктор Кларик. All rights reserved.
//

#include <stdlib.h>
#include <stdio.h>
#define bitOffset 2
#define bitCount (sizeof(int) * 8) - bitOffset

// Never! Listen to me, NEVER divide numbers using bit fields in C...
typedef struct {
    unsigned int rem: bitOffset;
    unsigned int result: bitCount;
} BitField;

// :DD
typedef unsigned long long int VeryLongInt;

int enterInt(const char *message) {
    int ret = 0;
    
    do {
        fflush(stdin);
        fseek(stdin, 0, SEEK_END);
        printf("%s", message);
    } while (!scanf("%d", &ret));
    
    return ret;
}

int main() {
    int number = enterInt("Enter number: ");
    
    BitField *field = (BitField*) &number;
    
    int sign = 1;
    if (number < 0) {
        sign = -1;
        number = -number;
    }
    
    // (number >> 2) << 2 == 0 >>_<<
    if (field->rem == 0) {
        // It's a little bit simpler to do this with a bit shifting... Can I just?
        // printf("%d", number >> 2);
        // (00001000) >> 2 = (00000010)
        printf("%d divided by 4 is %d\n", number, sign * field->result);
    } else {
        printf("Number %d is not dividable by 4!\n", number);
    }
    
    fflush(stdin);
    fseek(stdin, 0, SEEK_END);
    getchar();
    
    return 0;
}

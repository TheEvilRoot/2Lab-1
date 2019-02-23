//
//  main.c
//  Extra
//
//  Created by Доктор Кларик on 23.02.19.
//  Copyright © 2019 Доктор Кларик. All rights reserved.
//

#include <stdio.h>

struct bitField {
    unsigned int rem: 3;
};

int main(int argc, const char * argv[]) {
    int number = 0;
    
    do {
        printf("Enter number: ");
        fflush(stdin);
        fseek(stdin, 0, SEEK_END);
    } while (!scanf("%d", &number));
    
    int sign = 1;
    if (number < 0) {
        sign = -1;
        number = -number;
    }
    
    struct bitField *map = (struct bitField*) &number;
    
    printf("%d %c 8 = %d\n", number, '%', sign * map->rem);
    
    return 0;
}

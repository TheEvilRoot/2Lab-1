//
//  date.h
//  Задача 2
//
//  Created by Доктор Кларик on 24.02.19.
//  Copyright © 2019 Доктор Кларик. All rights reserved.
//

#ifndef date_h
#define date_h

#define true 1
#define false 0

#include <stdio.h>

typedef struct {
    // 00.00.0000\0
    char date[11];
} Date;


int isLeapYear(int);

int isValidDay(int, int, int);

Date newDate(char[11]);

#endif /* date_h */

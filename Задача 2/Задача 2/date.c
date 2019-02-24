//
//  date.c
//  Задача 2
//
//  Created by Доктор Кларик on 24.02.19.
//  Copyright © 2019 Доктор Кларик. All rights reserved.
//

#include "date.h"

// Constructor function
Date newDate(char date[11]) {
    Date d;
    for (int i = 0; i < 11; i++) {
        d.date[i] = date[i];
    }
    return d;
}

int isLeapYear(int year) {
    if (year % 4 == 0) {
        if (year % 100 == 0) {
            if (year % 400 == 0){
                return true;
            } else {
                return false;
            }
        } else {
            return true;
        }
    } else {
        return false;
    }
}

int isValidDay(int day, int month, int year) {
    if (day < 1 || month < 1 || month > 12 || day > 31) {
        return false;
    }
    
    if (month == 2) {
        int maxDay = isLeapYear(year) ? 29 : 28;
        
        if (day > maxDay) {
            return false;
        }
    } else {
        int maxDay = 28 + (month + month / 8) % 2 + 2 % month + 2 / month; // Dark magic
        
        if (day > maxDay) {
            return false;
        }
    }
    
    return true;
}


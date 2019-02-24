//
//  student.c
//  Задача 2
//
//  Created by Доктор Кларик on 24.02.19.
//  Copyright © 2019 Доктор Кларик. All rights reserved.
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "student.h"
#include "date.h"

// Constructor function
Student * newStudent(int recordBookID, char *surname, Date entranceDate, float avgMark) {
    Student *this = (Student*)malloc(sizeof(Student));
    
    this->recordBookID = recordBookID;
    this->surname = surname;
    this->entranceDate = entranceDate;
    this->avgMark = avgMark;
    
    return this;
}

void studentPrint(Student *student) {
    printf("======================================\n");
    printf("Student %s\n", student->surname);
    printf("Record Book ID: %d\n", student->recordBookID);
    printf("Entrance date: %s\n", student->entranceDate.date);
    printf("Avarage Mark: %.2f\n", student->avgMark);
    printf("======================================\n");
}

int findStudent(char *bySurname, Student **inGroup, int withLength) {
    for (int i = 0; i < withLength; i++) {
        if (strcmp(inGroup[i]->surname, bySurname) == false) {
            return i;
        }
    }
    return -1;
}

int handleStudentRemoval(int min, Student **group, int *length) {
    int count = 0;
    
    for (int i = 0; i < *length; i++) {
        for (int j = i; j < *length; j++) {
            if (group[i]->recordBookID < group[j]->recordBookID) {
                Student *buf = group[i];
                group[i] = group[j];
                group[j] = buf;
            }
        }
    }
    
    for (int i = *length - 1; i >= 0; i--) {
        if (group[i]->recordBookID < min) {
            length[0]--;
            free(group[i]->surname);
            free(group[i]);
            count++;
        }
    }
    
    return count;
}

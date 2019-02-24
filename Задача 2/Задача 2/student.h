//
//  student.h
//  Задача 2
//
//  Created by Доктор Кларик on 24.02.19.
//  Copyright © 2019 Доктор Кларик. All rights reserved.
//

#ifndef student_h
#define student_h

#include <stdio.h>
#include "date.h"

typedef struct {
    int recordBookID;
    char *surname;
    Date entranceDate;
    float avgMark;
} Student;

// Contructor function
Student * newStudent(int, char*, Date, float);

void studentPrint(Student*);

int findStudent(char*, Student**, int);

int handleStudentRemoval(int, Student**, int*);

#endif /* student_h */

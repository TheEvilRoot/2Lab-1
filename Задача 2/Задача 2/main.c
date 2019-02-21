//
//  main.c
//  Задача 2
//
//  Created by Доктор Кларик on 21.02.19.
//  Copyright © 2019 Доктор Кларик. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define clear "cls"
#define true 1
#define false 0

typedef struct {
    // 00.00.0000
    char *date;
} Date;

typedef struct {
    
    int recordBookID;
    char *surname;
    Date entranceDate;
    float avgMark;
    
} Student;

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

int enterInt(const char *message) {
    int ret = -1;
    
    do {
        fflush(stdin);
        fseek(stdin, 0, SEEK_END);
        printf("%s", message);
    } while (!scanf("%d", &ret) || ret < 0);
    
    return ret;
}

float enterFloat(const char *message) {
    float ret = -1;
    
    do {
        fflush(stdin);
        fseek(stdin, 0, SEEK_END);
        printf("%s", message);
        scanf("%f", &ret);
    } while (ret < 0);
    
    return ret;
}

char * enterString(const char *message, int length) {
    
    char *ret = (char*)calloc(length, sizeof(char));
    
    printf("%s", message);
    fflush(stdin);
    fseek(stdin, 0, SEEK_END);
    fgets(ret, length, stdin);
    
    return ret;
    
}

// Constructor function
Date newDate(char *date) {
    Date d;
    d.date = (char*) calloc(11, sizeof(char));
    for (int i = 0; i < 11; i++) {
        (d.date)[i] = date[i];
    }
    
    return d;
}

// Constructor function
Date enterDate() {
    
    int day = 0;
    int month = 0;
    int year = 0;
    
    do {
        fflush(stdin);
        fseek(stdin, 0, SEEK_END);
        printf("Enter year: ");
        scanf("%d", &year);
    } while (year < 1);
    
    do {
        fflush(stdin);
        fseek(stdin, 0, SEEK_END);
        printf("Enter month: ");
        scanf("%d", &month);
    } while (month < 1 || month > 12);
    
    do {
        fflush(stdin);
        fseek(stdin, 0, SEEK_END);
        printf("Enter day: ");
        scanf("%d", &day);
    } while (!isValidDay(day, month, year));
    
    char str[11];
    
    str[0] = '0' + day / 10;
    str[1] = '0' + day % 10;
    
    str[2] = '.';
    
    str[3] = '0' + month / 10;
    str[4] = '0' + month % 10;
    
    str[5] = '.';
    
    str[6] = '0' + year / 1000;
    str[7] = '0' + (year % 1000) / 100;
    str[8] = '0' + ((year % 1000) % 100) / 10;
    str[9] = '0' + ((year % 1000) % 100) % 10;
    str[10] = '\0';
    
    Date d = newDate(str);
    
    return d;
    
}

// Constructor function
Student * newStudent() {
    Student *student = (Student*)malloc(sizeof(Student));
    
    student->recordBookID = enterInt("Enter student's record book ID: ");
    student->surname = enterString("Enter student's surname (Max 25 symbols): ", 26);
    printf("Enter entrance date: \n");
    student->entranceDate = enterDate();
    student->avgMark = enterFloat("Enter student's avarage mark: ");
    
    return student;
}

void studentPrint(Student *student) {
    printf("======================================\n");
    printf("Student %s\n", student->surname);
    printf("Record Book ID: %d\n", student->recordBookID);
    printf("Entrance date: %s\n", student->entranceDate.date);
    printf("Avarage Mark: %.2f\n", student->avgMark);
    printf("======================================\n");
}

void handleStudentRemoval(int min, Student **group, int *length) {
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
        }
    }
}

int main(int argc, const char * argv[]) {
    // int maxGroupSize = 255;
    
    Student **group = (Student**)calloc(1, sizeof(Student*));
    
    int i = 0;
    do {
        group[i] = newStudent();
        
        if (group[i] == NULL) {
            printf("Error: Unable to allocate memory for student\n");
            break;
        }
        
        i++;
        
        group = (Student**)realloc(group, sizeof(Student*) * (i + 1));
        
        if (group == NULL) {
            printf("Error: Unable to reallocate group. Exiting program...\n");
            return 0;
        }
        
        printf("Do you want to enter another student?\n'y' to enter, anything else to manage group!\n");
        
        fflush(stdin);
        fseek(stdin, 0, SEEK_END);
        char c = getchar();
        fflush(stdin);
        fseek(stdin, 0, SEEK_END);
        
        if (c != 'y') {
            break;
        }
        
    } while (1);
    
    int length = i;
    
    
    // I'm tired of creating functions (._.)
    while (1) {
        
        // Menu enter
        printf("Menu!\nAvailable students: %d\n", length);
        
        printf("[0] Remove students with record book ID below than...\n");
        printf("[1] Find student by surname...\n");
        printf("[2] Show students...\n");
        printf("[3] Exit program\n");
        
        int result = enterInt("# ");
        
        if (result > 3) {
            continue;
        }
        
        // Menu handlering
        if (result == 0) {
            
            // Removing students with record book ID below than value
            
            system(clear);
            int value = enterInt("Enter record book ID: ");
            handleStudentRemoval(value, group, &length);
            group = (Student**)realloc(group, sizeof(Student*) * length);
        }
        else if (result == 1) {
            // Search for student by surname
            
            system(clear);
            
            char *expected = enterString("Enter surname for search (Max 25 symbols): ", 26);
            
            int found = -1;
            
            for (int i = 0; i < length; i++) {
                if (strcmp(group[i]->surname, expected) == false) {
                    found = i;
                }
            }
            
            if (found >= 0) {
                printf("Found!\n");
                studentPrint(group[found]);
            }
            else {
                printf("Not found\n");
            }
            
        }
        else if (result == 2) {
            
            // Display all students
            
            for (int i = 0; i < length; i++) {
                studentPrint(group[i]);
            }
        }
        else if (result == 3) {
            
            // Exit
            return 0;
        }
        
    }
    
    return 0;
}


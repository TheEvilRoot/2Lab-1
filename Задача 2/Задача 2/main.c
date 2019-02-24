//
//  main.c
//  Задача 2
//
//  Created by Доктор Кларик on 21.02.19.
//  Copyright © 2019 Доктор Кларик. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

#include "date.h"
#include "student.h"

#define clear ""

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

char enterChar(const char *message) {
    printf("%s", message);
    
    fflush(stdin);
    fseek(stdin, 0, SEEK_END);
    char ret = getchar();
    
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

Date enterDate(const char *message) {
    int day = 0;
    int month = 0;
    int year = 0;
    
    printf("%s", message);
    
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

Student * enterStudent() {
    Student *student = newStudent(
                enterInt("Enter student's record book ID: "),
                enterString("Enter student's surname (Max 25 symbols): ", 26),
                enterDate("Enter entrance date: \n"),
                enterFloat("Enter student's avarage mark: ")
    );
    
    return student;

}

int showMenu(int length) {
    printf("Menu!\nAvailable students count: %d\n", length);
    
    printf("[0] Remove students with record book ID below than...\n");
    printf("[1] Find student by surname...\n");
    printf("[2] Show students...\n");
    printf("[3] Exit program\n");
    
    int result = enterInt("# ");
    
    if (result > 3) {
        return -1;
    }
    
    return result;
}

int menuRemoveStudents(Student ***group, int *length) {
    int value = enterInt("Enter record book ID: ");
    int count = handleStudentRemoval(value, group, length);
    (*group) = (Student**)realloc((*group), sizeof(Student*) * (*length));
    
    if ((*group) == NULL) {
        printf("Error: Unable to reallocate group. Exiting program...\n");
        return 0;
    }
    
    printf("Removed %d students.\n", count);
    return 1;
}

void menuFindStudents(Student **group, int length) {
    char *expected = enterString("Enter surname for search (Max 25 symbols): ", 26);
    
    int index = findStudent(expected, group, length);
    
    if (index >= 0) {
        printf("Found!\n");
        studentPrint(group[index]);
    } else {
        printf("Not found\n");
    }
}

void menuDisplayStudents(Student **group, int length) {
    printf("Students: \n");
    for (int i = 0; i < length; i++) {
        studentPrint(group[i]);
    }
}

int main(int argc, const char * argv[]) {
    Student **group = (Student**)calloc(1, sizeof(Student*));
    
    int length = 0;
    do {
        group[length] = enterStudent();
        
        if (group[length] == NULL) {
            printf("Error: Unable to allocate memory for student\n");
            break;
        }
        
        length++;
        
        group = (Student**)realloc(group, sizeof(Student*) * (length + 1));
        
        if (group == NULL) {
            printf("Error: Unable to reallocate group. Exiting program...\n");
            return 0;
        }
        
        char confirm = enterChar("Do you want to enter another student?\n'y' to enter, anything else to manage group!\n");
        
        if (confirm != 'y') {
            break;
        }
        
    } while (1);
    
    // I'm tired of creating functions (._.)
    while (1) {
        
        int result = showMenu(length);
        if (result < 0) {
            continue;
        }
        
        system(clear);
        switch(result) {
            case 0: { // Remove students with record boot ID lower then value
                if (!menuRemoveStudents(&group, &length)) {
                    return 0;
                }
                break;
            }
            
            case 1: { // Find student by surname
                menuFindStudents(group, length);
                break;
            }
            
            case 2: { // Display students
                menuDisplayStudents(group, length);
                break;
            }
            case 3: {
                printf("Exiting...");
                enterChar("Goodby!");
                return 0;
            }
        }
        enterChar("Press any button to get back to menu...");
    }
    
    return 0;
}


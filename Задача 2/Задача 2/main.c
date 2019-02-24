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
#include "inputs.h"

#define clear ""

Date enterDate(const char *message) {
  
    printf("%s", message);
  
    enter(int, year, "Enter year: ", 1, 9999);
    enter(int, month, "Enter month: ", 1, 12);
    enter(int, day, "Enter day: ", 1, getMaxDay(month, year));
    
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
    enter(int, recordBookID, "Enter student's record book ID: ");
    enter(float, avgMark, "Enter student's avarage mark: ", 0);

    Student *student = newStudent(
                recordBookID,
                enterString("Enter student's surname: ", '\n'),
                enterDate("Enter entrance date: \n"),
                avgMark
    );
    
    return student;

}

int showMenu(int length) {
    printf("Menu!\nAvailable students count: %d\n", length);
    
    printf("[0] Remove students with record book ID below than...\n");
    printf("[1] Find student by surname...\n");
    printf("[2] Show students...\n");
    printf("[3] Exit program\n");
    
    enter(int, result, "# ", 0, 3);
    
    if (result > 3) {
        return -1;
    }
    
    return result;
}

int menuRemoveStudents(Student ***group, int *length) {
    enter(int, value, "Enter record book ID: ");
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
    char *expected = enterString("Enter surname for search: ", '\n');
    
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

int initGroup(Student ***group) {
    int length = 0;
    
    do {
        (*group)[length] = enterStudent();
        
        if ((*group)[length] == NULL) {
            printf("Error: Unable to allocate memory for student\n");
            break;
        }
        
        length++;
        
        (*group) = (Student**)realloc((*group), sizeof(Student*) * (length + 1));
        
        if ((*group) == NULL) {
            printf("Error: Unable to reallocate group. Exiting program...\n");
            return -1;
        }
        
        enter(char, confirm, "Do you want to enter another student?\n'y' to continue, anything else to manage group!\n");
        
        if (confirm != 'y') {
            break;
        }
        
    } while (1);
    
    return length;
}

int main(int argc, const char * argv[]) {
    system(clear);
    
    Student **group = (Student**)calloc(1, sizeof(Student*));
    
    int length = initGroup(&group);
    
    if (length < 0) {
        return 0;
    }
    
    while (1) {
        system(clear);
        int result = showMenu(length);
        if (result < 0) {
            continue;
        }
        
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
                enter(char, ___, "Goodby!");
                return 0;
            }
        }
        enter(char, ___,"Press any button to get back to menu...");
    }
    return 0;
}


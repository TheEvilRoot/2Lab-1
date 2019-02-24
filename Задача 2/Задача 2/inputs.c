//
//  inputs.c
//  CUtilities
//
//  Created by Доктор Кларик on 24.02.19.
//  Copyright © 2019 Доктор Кларик. All rights reserved.
//

#include "inputs.h"

#include <stdlib.h>
#include <limits.h>
#include <float.h>


int __e_int(const char* message, const int bounds[], int size) {
  int ret = 0;
  int max = INT_MAX;
  int min = INT_MIN;
 
  switch(size) {
    case 2: {
      max = bounds[1];
    }
    case 1: {
      min = bounds[0];
      break;
    }
  }
  
  do {
    fflush(stdin);
    fseek(stdin, 0, SEEK_END);
    printf("%s", message);
  } while (!scanf("%d", &ret) || ret < min || ret > max);
  
  return ret;
}

float __e_float(const char* message, const float bounds[], int size) {
  float ret = 0.0;
  float max = FLT_MAX;
  float min = FLT_MIN;
  
  switch(size) {
    case 2: {
      max = bounds[1];
    }
    case 1: {
      min = bounds[0];
      break;
    }
  }
  
  do {
    fflush(stdin);
    fseek(stdin, 0, SEEK_END);
    printf("%s", message);
  } while (!scanf("%f", &ret) || ret < min || ret > max);
  
  return ret;
}

double __e_double(const char* message, const double bounds[], int size) {
  double ret = 0.0;
  double max = DBL_MAX;
  double min = DBL_MIN;
  
  switch(size) {
    case 2: {
      max = bounds[1];
    }
    case 1: {
      min = bounds[0];
      break;
    }
  }
  
  do {
    fflush(stdin);
    fseek(stdin, 0, SEEK_END);
    printf("%s", message);
  } while (!scanf("%lf", &ret) || ret < min || ret > max);
  
  return ret;
}

char __e_char(const char *message, const char *bounds, int size) {
  char min = CHAR_MIN;
  char max = CHAR_MAX;
  
  char ret = 0;
  
  switch(size) {
    case 2: {
      max = bounds[1];
    }
    case 1: {
      min = bounds[0];
      break;
    }
  }
  
  do {
    printf("%s", message);
    fflush(stdin);
    fseek(stdin, 0, SEEK_END);
    ret = getchar();
  } while (ret < min || ret > max);
  
  return ret;
}


char * enterString(const char *message, char breakChar) {
  char *str = (char*) malloc(sizeof(char));
  
  if (!str) {
    return NULL;
  }
  
  int i = 0;
  char c;
  
  fflush(stdin);
  fseek(stdin, 0, SEEK_END);
  
  printf("%s", message);
  
  while ((c = getchar()) != -1) {
    str[i++] = c;
    
    if (c == breakChar) {
      str[i - 1] = '\0';
      break;
    }
    

    if (!(str = (char*) realloc(str, sizeof(char) * (i + 1)))) {
      str[i - 1] = '\0';
      break;
    }
  }
  
  return str;
}

#include "stdmine.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

str get_str(str ques)
{
    printf("%s", ques);
    str string = malloc(100);
    scanf("%99s", string);
    return string;
}
char get_char(str ques)
{
    char x;
    printf("%s", ques);
    scanf(" %c", &x);
    return x;
}
int get_int(str ques)
{
    int x;
    printf("%s", ques);
    scanf("%d", &x);
    return x;
}
float get_float(str ques)
{
    float x;
    printf("%s", ques);
    scanf("%f", &x);
    return x;
}
long get_long(str ques)
{
    long x;
    printf("%s", ques);
    scanf("%ld", &x);
    return x;
}
short get_short(str ques)
{
    short x;
    printf("%s", ques);
    scanf("%hd", &x);
    return x;
}
double get_double(str ques)
{
    double x;
    printf("%s", ques);
    scanf("%lf", &x);
    return x;
}



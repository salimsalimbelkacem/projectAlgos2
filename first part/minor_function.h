#ifndef MINOR_FUNCTION_H
#define MINOR_FUNCTION_H

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

void invert(char CH[], int index);
void toggle_case(char ch[], int indice);
void rotate(char CH[], int index);
void generate(int N, char sch[], char ch[]);
bool compare_strings(char ch[], char ch1[]);
bool same_parity_letter(char ch[], int N);
bool character_verification(char ch[]);
bool general_verification(char ch[], char sch[], bool dialogue);
void score_update(long newTime);


#endif
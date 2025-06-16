#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

void invert(char CH[], int index)
{
    char inter;
    inter       =   CH[index];
    CH[index]   = CH[index+1];
    CH[index+1] =       inter;
}

void toggle_case(char ch[], int index)
{
    if(ch[index] >='a' && ch[index]<='z'){
        ch[index] = ch[index] - 32;
    }
    else if (ch[index]>='A' && ch[index]<='Z'){
        ch[index] = ch[index] + 32;
    }
}

void rotate(char CH[], int index)
{
    invert            (CH, index-1);
    toggle_case (CH, index-1);
    toggle_case (CH, index);
}

bool same_parity_letter(char ch[], int N){

    int i, j, k, size=strlen(ch);

    for (i = 0; i < N-2; i++)
    {
        if (ch[i] != ch[i+2])
            return false;
    }
    return true;
}

bool compare_strings(char ch[], char ch1[])
{
    for(int i=0;i<strlen(ch);i++){
        if (ch[i]!=ch1[i]){
            return true;
        }
    }
    return false;
}//true pour re la boucle et false pour sortir de la boucle!

bool character_verification (char ch[])
{
    for(int i=0; i<strlen(ch); i++)
    {
        if(ch[i] <'a' || ch[i]>'z')
            return false;
    }
    return true;
}

bool general_verification (char ch[], char sch[], bool dialogue)
{
    if (!compare_strings(ch, sch)){
        if(dialogue)printf("\nError:The combination must not be the same as the string\n");
        return false;
    }

    if(strlen(ch) != strlen(sch)){
        if(dialogue)printf("\nError:Not the same size\n");
        return false;
    }
        if(!character_verification(sch)){
        if(dialogue)printf("\nErreur:invalid character\n");
        return false;
    }
    else 
    {
        int verif;
        for(int i=0; i<strlen(sch); i++)
        {
           verif = 0; 
           for(int j=0; j<strlen(ch); j++)
           {
               if(ch[j] == sch[i] && i%2 == j%2)
               {
                   verif ++;
               }
           }
           if(verif < 1)
           {
               if(dialogue)printf("\nError:invalid combination\n");
               return false;
           }
        }

        for(int i=0; i<strlen(sch); i++)
        {
            verif = 0; 
            for(int j=0; j<strlen(ch); j++)
            {
                if(ch[i] == sch[j] && i%2 == j%2)
                {
                    verif ++;
                }
            }
            if(verif < 1)
            {
                if(dialogue)printf("\nError:invalid combination\n");
                return false;
            }
        }
    }
    return true;
}

void generate(int N, char sch[], char ch[])
{
    int j=0, t[20];
    char aux;
    if (N == 3)
    {
        aux = sch[0];
        sch[0] = sch[2];
        sch[2] = aux;
        sch[N]= '\0';
    }
    else{
        do{
            srand(time(NULL)+j); 
            for (int i=0; i<20; i++){
            t[i]=rand()%(N-1)+1;
        }
        for(int i=0;i<20;i++){
            rotate(sch,t[i]);
        }
        sch[N]='\0';
        j++;
    }while(!general_verification(ch,sch, false));
    }
}

typedef struct score
{
    char name[30];
    char day[12];
    long time;
} score;

void score_update(long newTime) {
    FILE* fptr;
    score t[5], auxilary;
    bool modify_check;
    int min;

    for (int i = 0; i < 5; i++) {
        if (newTime < t[i].time) {
            fptr = fopen("score.bin", "rb");
            fread(t, sizeof(score), 5, fptr);
            fclose(fptr);

            modify_check = true;
            printf("\nEnter your name:\n");
            fgets(t[4].name, sizeof(t[4].name), stdin);
            t[4].name[strcspn(t[i].name, "\n")] = '\0';
            t[4].time = newTime;
            
            time_t current_time; 
            struct tm* time_info;
            time(&current_time);
            time_info = gmtime(&current_time);
            sprintf(t[4].day, "%d/%d/%d", time_info->tm_mday, time_info->tm_mon+1, time_info->tm_year+1900);
            break;
        }
    }

    if(modify_check){
        for (int i = 0; i < 4; i++) {
            min = i;
            for (int j = i + 1; j < 5; j++) {
                if (t[min].time > t[j].time)
                    min = j;
            }
            auxilary.time = t[i].time;
            t[i].time = t[min].time;
            t[min].time = auxilary.time;

            strcpy(auxilary.name, t[i].name);
            strcpy(t[i].name, t[min].name);
            strcpy(t[min].name, auxilary.name);

            strcpy(auxilary.day, t[i].day);
            strcpy(t[i].day, t[min].day);
            strcpy(t[min].day, auxilary.day);
        }

        fptr = fopen("score.bin", "wb");
        fwrite(t, sizeof(score), 5, fptr);
        fclose(fptr);
    }

}
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "minor_function.h"

int player_mode()
{
    char* ch = NULL;
    int indice, N;
    
    int i ;
    fflush(stdin);

    do {
        if(ch != NULL){
            free(ch);
            ch = NULL;
        }

        i = -1;
        printf("Enter the message: ");
        do { 
            i++; // en gros il lis la chaine letre par letre et a chauque fois il aloue
            ch = (char*)realloc(ch, sizeof(char) * (i + 2));
            ch[i] = getchar();
            
            if (ch[i] == '\n')
            ch[i] = '\0';
        }while(ch[i] != '\0');


        if ( i >10 || i<3){
            printf("\nError: Your string does not have the required size.\n");
        }
        if (!character_verification(ch)){
            printf("\nError: Invalid characters\n");
        }
        if (same_parity_letter(ch, i))
        {
            printf("\nError: your string has no possible combination.\n");
        }

    }while(!character_verification(ch) || same_parity_letter(ch, i) || i >10 || i<3);
    N = i;

    //generation de combinaison
    char sch[N];
    for(int i=0;i<strlen(ch);i++){
        sch[i]=ch[i];
    }
    generate(N, sch, ch);

    //la boucle de jeu
    time_t start=time(NULL), now=time(NULL);
    int vies = N*5;
    long elapsed_time;
    do{
        printf("\r\n%d seconds\t%d lives", -(start-now), vies);
        printf("\r\nthe string:\t|\tthe combination\n%s\t|\t%s\n", ch,sch);
        
        fflush(stdout);

        for (int i=0; i<N; i++){
            printf("%d",i+1);
        }

       //entrer indice
        do{
            printf("\nenter an index:\n");
            
            if( scanf("%d", &indice)==0 || indice > N-1 || indice <1){
                printf("\nError:your index is not valid\n");
                getchar();
                fflush(stdin);
            }
        }while(indice > N-1 || indice <1);
        
        rotate(ch, indice);
        now = time(NULL);
        vies--;
    }while(compare_strings(ch,sch) && vies>0);
    
    printf("\nthe string:\t|\tthe combination\n%s\t|\t%s\n", ch,sch);
    if (!compare_strings(ch, sch)){
        printf("congratulations you won!\n");
        printf("elapsed time: %lds\n", now-start);
        elapsed_time = now-start;
        getchar();
        if(N>=6) score_update(elapsed_time);
    }
    else{
        if (vies == 0)printf("your lives are up\n");
        printf("you lost\n");
    }
    return 0;
}

//**********************************************************************************************

void machine_mode()
{
    char *ch=NULL, *sch=NULL;
    int N, i;
    fflush(stdin);

    do {
        if(ch != NULL){
            free(ch);
            ch = NULL;
        }

        i = -1;
        printf("Enter the message: ");
        do { 
            i++; // en gros il lis la chaine letre par letre et a chauque fois il aloue
            ch = (char*)realloc(ch, sizeof(char) * (i + 2));
            ch[i] = getchar();
            
            if (ch[i] == '\n')
            ch[i] = '\0';
        }while(ch[i] != '\0');


        if ( i >10 || i<3){
            printf("\nError: Your string does not have the required size.\n");
        }
        if (!character_verification(ch)){
            printf("\nError: Invalid characters\n");
        }
        if (same_parity_letter(ch, i))
        {
            printf("\nError: your string has no possible combination.\n");
        }

    }while(!character_verification(ch) || same_parity_letter( ch, i) || i >10 || i<3);
    
    N = i;

    sch = (char*) malloc(sizeof(char)*N);

    do{
        printf("\nEnter the combination:\n");
        scanf(" %s", sch);
    }while(!general_verification(ch, sch, true));

    printf("\n%s", ch);
    for(int i=0; i<strlen(sch); i++)
    {
        for(int j=i; j<strlen(ch); j++)
        {
            if((sch[i] == ch[j] && i%2 == j%2) || (sch[i]-32 == ch[j] && i%2 !=j%2))
            {
                if(i>j)
                {
                    for(j=j; j<i+1; j++){
                        rotate(ch,j);
                        printf("\n%s",ch);
                    }
                    break;
                }
                else if (i<j)
                {
                    for(j = j; j>i; j--){
                        rotate(ch,j);
                        printf("\n%s",ch);
                    }
                    break;
                }
                else
                {
                    break;
                }
            }
        }
    if (!compare_strings(ch,sch))  break;
    }
    printf("\nI am done\n");
}

//***************************************************************************************************

void rules(){
    printf("\nPlayer mode:\n");
    printf("Input a word of a certain length, and the computer will create a combination of the word.\n");
    printf("Rotate letters to try and guess the combination before time and lives run out.\n");
    printf("The inputed word must:\n\t-Be only in lowercase\n\t-Not contain special characters\n\t-contain at least 3 characters and at most 10");

    printf("\n\nMachine mode:\n");
    printf("Input a word and a combination of the same length,");
    printf("and the computer will rotate letters in the word to try and guess the combination.\n");

    printf("the two inputed words must:\n\t-Not be the same as the generated word.\n\t");
    printf("-Each character in the input word must appear in the generated word\n\t");
    printf("-Appear in the same position (even or odd).\n\n");
}

//***************************************************************************************************

typedef struct player_score
{
    char name[30];
    char day[12];
    long time;
}player_score;

void score(){
    FILE *rating;
    player_score t[5];

    if(rating = fopen("score.bin", "rb")){
        fread(t, sizeof(player_score), 5, rating);
        fclose(rating);
        for (int i = 0; i < 5; i++)
        {
            printf("\nNumber %d:", i+1);
            printf("\nName: %s  Score:%lds  Day:%s", t[i].name, t[i].time, t[i].day);
        }
        printf("\n");
        return ;
    }
    else{
        printf("there is no current score for the moment\n");
    }
}
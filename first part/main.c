#include    <stdio.h>
#include    "modes.h"
#include    "ascci_art.h"
#include    <stdbool.h>

int main()
{
    char mode, ON;
    char name[30];
    

    big();
    printf("\n\t\t\t\t\tmade by: Hamma Anes\n\t\t\t\t\t\t Belkacem Salim\n");

    /*MENU*/
    menu:
    printf(" ");
    for (int i=0; i<25;i++) printf("_");
    printf("\\WELCOME/");
    for (int i=0; i<25;i++) printf("_");

    printf("\n|Main menu:\t\t\t\t\t\t    |\n");
    while(true){
        do{
        printf("|\t1-PLAYER mode.\t\t\t\t\t    |\n");
        printf("|\t2-MACHINE mode.\t\t\t\t\t    |\n");
        printf("|\t3-rules.\t\t\t\t\t    |\n");
        printf("|\t4-score.\t\t\t\t\t    |\n");
        printf("|\t(Enter 1 or 2 or 3 or 4)\t\t\t    |\n|");

        for (int i=0; i<59;i++) printf("_");
        printf("|\n\n\t>>");
        
        scanf(" %c", &mode);
        fflush(stdin);
        if(mode != '1' && mode != '2' && mode != '3' && mode != '4'){
            printf("\nError:invalid choice\n\n ");                
            for (int i=0; i<59;i++) printf("_");
            printf("\n");
            }
            
        }while(mode != '1' && mode != '2' && mode != '3' && mode != '4');
        
        if (mode == '1'){
            player_mode();
        }
        if (mode == '2') machine_mode();
        if (mode == '3'){
            rules();
            goto menu;
        }
        if(mode == '4'){
            score();
            goto menu;
        }

        printf("\nDo you want to continue? (Y/N)\n");
        
        do{
            scanf(" %c",&ON);
            if(ON != 'Y' && ON != 'y' && ON != 'N' && ON != 'n')
                printf("\nEnter Y (for yes) or N (for no).\n");
        
        }while(ON != 'Y' && ON != 'y' && ON != 'N' && ON != 'n');
    
        if(ON == 'N' || ON == 'n') break;
        printf("\n");
    }
}    
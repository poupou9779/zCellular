#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "def.h"

void purge(void)
{
    int c;
    do
        c = getchar();
    while(c != EOF && c != '\n');
}

struct zCellular init_cellular(void)
{
    struct zCellular ret;

    printf("length :\n\t");
    scanf("%u", &ret.length); purge();
    ret.plate = malloc(sizeof(char) * (ret.length+1));
    if(ret.plate == NULL)
        fprintf(stderr, "Error : allocation of %u bytes failed !\n", sizeof(*(ret.plate) * ret.length));
    else
    {
        ret.tmp = malloc(sizeof(char) * (ret.length+1));
        if(ret.tmp == NULL)
        {
            fprintf(stderr, "Error : allocation of %u bytes failed !\n", sizeof(*(ret.plate) * ret.length));
            free(ret.plate); ret.plate = NULL;
        }
        else
        {
            do
            {
                printf("G 0 ('%c' = 1 && '%c' = 0) : ", FILLED, EMPTY);
                fgets(ret.plate, (int)ret.length+1, stdin);
                purge();
                if(ret.plate[0] == 'R' || ret.plate[0] == 'r')
                    gen_rand(&ret);
            } while(!iscorrect(ret.plate));
            printf("gens :\n\t");
            scanf("%u", &ret.gens);
            purge();
        }
    }
    return ret;
}

void gen_rand(struct zCellular *cellular)
{
    unsigned int i;
    for(i = 0; i < cellular->length; ++i)
        cellular->plate[i] = (rand()%2)&1 ? FILLED : EMPTY;
    cellular->plate[cellular->length] = '\0';
}

int iscorrect(const char *plate)
{
    int ret = 1,
        i;

    if(plate == NULL)
        ret = 0;
    else
        for(i = 0; plate[i] != '\0'; ++i)
            if(plate[i] != EMPTY && plate[i] != FILLED)
                ret = 0;
    return ret;
}

void evolve(struct zCellular *cellular)
{
    unsigned int i;
    for(i = 0; i < cellular->length; ++i)
        cellular->tmp[i] = cellular->plate[i];
    for(i = 0; i < cellular->length; ++i)
        cellular->plate[i] = tab_evolution[     ((i != 0 ? (cellular->tmp[i-1] == FILLED) : 0) << 2)
                                            +   ((cellular->tmp[i] == FILLED) << 1)
                                            +   ((i != cellular->length-1 ? (cellular->tmp[i+1] == FILLED) : 0))];
}

void display(struct zCellular cellular, unsigned int g)
{
    unsigned int i;
    printf("G %04u : ", g);
    for(i = 0; i < cellular.length; ++i)
        putchar(cellular.plate[i]);
    putchar('\n');
}

void quit(struct zCellular *cellular)
{
    cellular->length = 0;
    free(cellular->plate); cellular->plate = NULL;
    free(cellular->tmp); cellular->tmp = NULL;
}

int main(void)
{
    struct zCellular cellular;
    unsigned int i;
    srand((unsigned int)time(NULL));
    printf("\t\t --- zCellular ! ---\n");
    cellular = init_cellular();
    display(cellular, 0);
    for(i = 0; i < cellular.gens; ++i)
    {
        evolve(&cellular);
        display(cellular, i+1);
    }
    quit(&cellular);
    return EXIT_SUCCESS;
}


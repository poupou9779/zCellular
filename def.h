#ifndef ZCELLULAR_DEF
#define ZCELLULAR_DEF

#define EMPTY   '_'
#define FILLED  '#'

const char tab_evolution[8] =  {EMPTY, FILLED, FILLED, FILLED, FILLED, EMPTY, EMPTY, EMPTY};

struct zCellular
{
    unsigned int length,
                 gens;
    char *board,
         *tmp;
};

void purge(void);
struct zCellular init_cellular(void);
void gen_rand(struct zCellular *);
int iscorrect(const char *);
void display(struct zCellular , unsigned int);
void evolve(struct zCellular *);
void quit(struct zCellular *);

#endif

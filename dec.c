#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<time.h>

#include"parameters.h"
FILE *best, *stats, *plot ;
long int seed;
int ex; // the example number
long int nevaluations = 0,nevalbest[runs];
clock_t  start_time;
double runtime[runs], besttime, passedtime;
int tourneypos, tourneysize, tourneylist[ANTS];
char *inpfname;

int fdimension, estimativainicial, posicao[500], n, pinicio, pfim;
double G[500], A[500], Gexp[500],  config[500], E, ponderacao, ro;

struct variable 
{
	float ulimit, llimit,increment;
	int nvalues;
	double *trail , *prob;
	char name[20];
} var[nov];

struct ant_struct 
{
	int variable[nov];
	float ofn;
	#if(constrained ==1)
	float penalty;
	#endif
	float bestofn;
	int iter;
} ant[ANTS],bestant,itbestant,itworstant,runbestant[runs];



struct values 
{
	float var[nov], ofn;
	int iter;
	#if(constrained ==1)
	float penalty;
	#endif
} itbestval,itworstval,bestval, runbestval[runs];

#if (lbt==1)
struct ant_struct lbest[ANTS];
#endif




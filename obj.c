#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include "parameters.h"
#include "dec.h"
#include "func.h"
#define pi 3.14
#define ks 10
#define ke 500


#if (constrained ==1)
float objective_function(float *varvalues, float *antpenalty);
#endif
#if (constrained ==0)
  float objective_function(float *varvalues);
#endif


extern long int nevaluations;

#define var10 0
#define ex1 1

#if(constrained==1)
float objective_function( float *varvalues, float *antpenalty)
/* takes array of varvalues of length nov and
 * returns objective function which is a float values*/
{
	extern long int nevaluations;
			nevaluations++;
	float ofn;

	float objfn, x1,x2 ;
	x1 = varvalues[0];
	x2 = varvalues[1];

	# if(ex1)
		objfn = 1.0f +( (x1*x1 +x2 -11.0f) *(x1*x1 +x2 -11.0f) ) + ( (x1 +x2*x2 - 7.0f) * (x1
			+ x2*x2 -7.0f));

		float g1,g2 ; 
		g1 = 1.0f - (( pow((x1 -5.0),2) + pow((x2),2) ) / 26.0f ) ;
		g2 = 1.0f - ( ( 4 * x1 + x2 ) / 20.0f) ;

		float sumconstr = 0.0, penaltyconst = 1;
		if(g1 >=0)
		{
			sumconstr += g1; 
		}
		if(g2 >=0)
		{
			sumconstr += g1; 
		}
		*antpenalty = penaltyconst * sumconstr;

		return objfn * ( 1.0f + *antpenalty) ;

	#endif
		//printf("x1= %f x2  is %g \n",x1,x2);
		//printf("sumconstr= %f g1 is %g \n",sumconstr,g1);
		//return objfn ;

	#if(var10)
		float constr[7]= {0.0,0.0,0.0,0.0,0.0,0.0}, sumconstr=0.0;
		float e,a,b,c1,c2,d1,d2,g1,g2,h,i;
//float x[]  =   { 1.000 , 6.000 , 0.000 , 0.000 , 0.000 , 8.000 , 1.000 , 5.000 , 0.000 , 6.000 , 5.000}  ;
// float x[]  =    { 1, 6, 0, 0,0, 8, 1,5,0,6,5};

		a=x[0];
		b=x[1];
		c1=x[2];
		c2=x[3];
		d1=x[4];
		d2=x[5];
		g1=x[6];
		g2=x[7];
		h=x[8];
		i=x[9];
		e= 20.0f- (a+b+c2+d2);
		
		constr[0] = ((b-c1)/7.0f )-1.0f;
		constr[1] = ((b+c2-d1)/6.0f) -1.0f;
		constr[2] = ((b+c2 - g1)/5.0f) -1.0f;
		constr[3] = ((d2 -g2 )/3.0f) -1.0f;
		constr[4] = ((c2+d2 -h -i )/2.0f) -1.0f;
		constr[5] = (e/5.0.0f) -1.0f  ;
		constr[6] =  -e   ;
//printf("e = %f\n",e);
		int cno;
		for(cno=0;cno<7;cno++){
			if(constr[cno] >=0.0f)
			{
				sumconstr += constr[cno];
			}
		//printf("constraint [%d] = %f \n",cno,constr[cno]);
		}
		sumconstr *= ks;

		ofn = (60.0f*a +10.0f*b + 20.0f*c1 +20.0f*c2 + 5.0f*d1+ 5.0f*d2 + 30.0f*e + 15.0f*g1 +15.0f*g2 + 12.0f*h +6.0f*i)* ( 1.0f + sumconstr ); 


		*antpenalty = sumconstr;

//printf(" ofn = %15.15f , sumconstr = %6.8f \n", ofn,sumconstr);   


		return ofn;

	#endif
}
#endif 
//fim do exemplo 1




#define ex2 1
#define f2 0
#define f3 0
#define f1 0


#if(constrained==0)
float objective_function( float *varvalues )
/* takes array of varvalues of length nov and
 * returns objective function which is a float values*/
{
nevaluations++;

float objfn=0;
int i, k;


for(i=0, k=pinicio; k<=pfim; i++, k++){
	config[k] = (double) varvalues[i];
}

prop_onda(G, config, E, ro, n, A[1]);

for (i=pinicio; i<=pfim; i++)
{
    objfn = objfn + ( (G[i] - Gexp[i]) * (G[i] - Gexp[i]));
}

/*for(i=0; i<n; i++){
	printf("%d %lf %lf\n",i, G[i], Gexp[i]);
}*/
return objfn;
}
#endif

/*---------------------------------------------------------------------------------*/
/*Identificacao de dano em estruturas de viga usando colonia de formigas e algoritmos algebricos*/
/*---------------------------------------------------------------------------------*/

/*

#if(constrained==3)
float objective_function( float *varvalues )
{
nevaluations++;

float  objfn ;
int i;

	objfn = 0.0f  ;

	dados_experimentais(Gexp,n,ponderacao, posicao, inicio1);
    estimativa_inicial(A,E,ro,n,estimativainicial);


    prop_onda(G, config, E, ro, fDimension, divisor);

	for (i=inicio; i<=fim; i++)
    {
        objfn = objfn + ( (G[i] - Gexp[i]) * (G[i] - Gexp[i]));
    }



return objfn ;
}
#endif

*/
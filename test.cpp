#include<stdio.h>
#include<math.h>
#include"parameters.h"




#if (constrained ==1)
float objective_function(float *varvalues, float * antpenalty);
#endif
#if (constrained ==0)
float objective_function(float *varvalues);
#endif

long nevaluations;



int main()
{
//	nevaluations = 0;

		float values[nov] ;
		float cost , penalty;
//exemplo 1		
/*		values[0] = 1  ;
		values[1] = 3  ;
		penalty = 0.0;
		cost = objective_function( values, &penalty);
		printf(" ofn = %lf , sumconstr = %f ", cost,penalty);
*/
//exemplo 2

		values[0] = 3  ;
		values[1] = 3  ;
		penalty = 0.0;
		cost = objective_function( values);
		printf(" ofn = %lf , sumconstr = %f ", cost, 0.0f);
		return 0;

}


#include"dec.h"
#include"func.h"
//#include <time.h>

void ant_colony()
{
	int runno, itno, antno;
	double time_used;
	read_data(inpfname);
	//print_data();
	init_out(inpfname);

	for(runno=0; runno<runs; runno++){
		seed = (long int) time(NULL);
		
		start_timers();
		initialize_ants_variables(runno);
		initialize_trail();

		for(itno=0; bestant.ofn != 436.00 && itno<ncmax; itno++){
			iteration_init(itno);
			find_values();
			analysis(itno);
			update_stats(itno, runno);
			#if(usels==1)
			if(lswithitbest==1){
				ls(&itbestval, itno);
				lsstats(itno, runno);
			}
			if(lswithbest==1){
				ls(&bestval, itno);
				lsstats(itno, runno);
			}
			#endif
			trail();

			if(!(itno%statsafterit))
				print_itstats(itno, runno);
		}
		update_stats(itno, runno);
		report_run(runno);
	}
	final_stats();
}

int main(int argc, char *argv[])
{
	printf("oi\n");
	int pi, final, laco, i, k;
	inpfname = argv[1];
	for(i=0;i<500;i++)
        G[i]=0.0;
	estimativainicial = 0;
	ponderacao = 1.0;
	ro = 2700;
	E=7.0;
	n = fim-inicio+3;
	pinicio = 3;
	pfim = n;
	pi = pinicio;
	final = pfim;
	dados_experimentais(Gexp, n, ponderacao, posicao, inicio);
	estimativa_inicial(A,E,ro,n,estimativainicial);
	pfim = (pinicio-1)+np;
	n=pfim;
	fdimension=n;
	laco=3;

	while(laco<=final){
		for(i=0; i<=n; i++)
			config[i] = A[i]/A[1];
		ant_colony();
		for(i=0, k=pinicio;k<=pfim; k++, i++){
			config[k]=bestval.var[i];
		}
		for(i=pinicio; i<=pfim; i++)
			A[i]=config[i]*300;
		pinicio+=np;
		pfim = pinicio-1+np;
		n=pfim;
		fdimension=n;
		laco = pinicio;
	}
	FILE *resultados = fopen("areas.txt", "w");
	fprintf(resultados, "Posição (mm)\t\tÁrea(mm²)\n");
	for(i=pi; i<n; i++){
		fprintf(resultados, "%d\t\t%.15e\n", posicao[i], config[i]);
	}
	fclose(resultados);
	return 0;
}
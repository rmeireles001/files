
#include"dec.h"
#include"func.h"

void analysis(int iterationno)
{
int antno,vno,valueno;
struct values tempval;
tempval.iter = iterationno;
for(antno=0;antno<ANTS;antno++)
{
ant[antno].iter = iterationno;
decode_varvalues ( tempval.var, antno);
/*
for(vno=0;vno<nov;vno++)
{
printf("variable no %d = %f for antno=%d \n",vno, tempval.var[vno], antno);
}
*/

#if (constrained ==0)
(ant[antno]).ofn = objective_function(tempval.var );
#endif

#if (constrained ==1)
(ant[antno]).ofn = objective_function(tempval.var ,&((ant[antno]).penalty));
#endif


tempval.ofn = (ant[antno]).ofn;

/*printf("tempval.ofn = %f ant[%d].ofn = %f \n\n",tempval.ofn,antno, (ant[antno]).ofn);*/

if((ant[antno]).ofn < (ant[antno]).bestofn )
{
 ant[antno].bestofn = (ant[antno]).ofn;
 ant[antno].iter = iterationno;
}


if((ant[antno]).ofn < itbestant.ofn)
{
copy_val(&tempval , &itbestval);
copy_ant(&ant[antno],&itbestant);
}

if((ant[antno]).ofn >itworstant.ofn)
{
copy_val(&tempval, &itworstval);
copy_ant(&ant[antno], &itworstant);
}
}//endof antno loop

}//end of analysis

void decode_varvalues(float * varvalues,int antno)
{
int vno , valueno;
for(vno=0;vno<nov;vno++)
{
 if((ant[antno]).variable[vno] == ((var[vno]).nvalues - 1 ))
  {
  varvalues[vno] = var[vno].ulimit;
  }
  else
  {
    varvalues[vno] = (  (var[vno]).llimit + (((ant[antno]).variable[vno])* (var[vno]).increment ));
  }
}//end of vno loop

}//end of decode varvaules

void estimativa_inicial (double A[],double E, double ro, int n, int estimativainicial)
{
    int i,j;

    FILE *resultados, *estimativa;

    resultados=fopen("areas_finais.txt", "w");
    if (resultados==NULL)
        printf("ERRO! ARQUIVO RESULTADOS_LJ2");

    
    E = 71 * pow(10,9);
    ro = 2700;

    for (i=0;i<=n;i++)
    {
        A[i]=300.0;
    }

    //fprintf(resultados, "Estimativa Inicial ---- \n");
    
    //for (i=1;i<=n;i++)
    //{
    //    fprintf(resultados, "%d \t %lf \n", i, A[i]/300);
    // }


   // fprintf (resultados, "------------------------ \n");
    //fprintf (resultados, " ");

    fclose(resultados);

}

void dados_experimentais (double Gexp[], int n, double ponderacao, int posicao[], int inicio1)
{

    int i, j, aux1[1000];
    double aux2[1000], tempo[500], aux;

    FILE *saida,*entrada;

    saida=fopen("saida_inverso.txt", "w");
    if (saida==NULL)
        printf("ERRO! ARQUIVO SAIDA_LJ2");
        
    entrada=fopen("eco.txt", "r");
    if (entrada== NULL)
       printf ("ERRO! Arquivo entrada");
       
    for (i=1; i<pontos; i++)
        fscanf (entrada, "%d %lf %lf", &aux1[i], &aux, &aux2[i]);
   
    j=3; 
    for (i=inicio1;i<=(inicio1+n-3);i++)
    {
        Gexp[j]=aux2[i];
        posicao[j]=i;
        j=j+1;
    }
    
    Gexp[1]=aux2[inicio1-2];
    posicao[1]=aux1[inicio1-2];
    Gexp[2]=aux2[inicio1-1];
    posicao[2]=aux1[inicio1-1];
    
    for (i=1;i<=n;i++)
    {
        Gexp[i]=(Gexp[i]*ponderacao);
        //printf ("Gexp= %lf", Gexp[i]);
        //posicao[i]=((VEL*tempo[i])/(2000));
        //printf("posicao= %d \n", posicao[i]);
        //system ("pause")        ;
    }
        
        
 	fprintf(saida, "--------------- \n");

    fclose(saida);
    fclose(entrada);
    
}

void prop_onda (double G[],double A[], double E, double ro, int n, double divisor)
{
       
    int i, j, k, n1, p1,nentrada;
    double Z[500], R[500],F[500], P[500];
    double c, inercia, somatorio1, ponderacao, aux;
    double **A1, **B1, **Y; 
      
      ponderacao=1.0;

    //Alocando as linhas das matrizes
      B1=(double **) calloc (500, sizeof (double *));
      if (B1 == NULL)
      {
        printf("ERRO na alocacao de B1!");
        return;
      }
    //printf("\n Alocou B1 \n");
     A1=(double **) calloc (500, sizeof (double *));
     if (A1 == NULL)
     {
        printf("ERRO na alocacao de A1");
        return;
      }

    //printf("\n Alocou A1 \n");
      Y = (double **) calloc (500, sizeof(double *));
      if (Y == NULL)
      {
        printf ("Erro na alocacao de Y");
        return;
      }
      //printf("\n Alocou Y \n");
     //aloca as colunas da matriz
     for (i = 0; i <500; i++)
     {
     Y[i] = (double*) calloc (500, sizeof(double));
     if (Y[i] == NULL)
     {
        printf ("Erro na alocacao DAS COLUNAS DE Y");
        return;
      }
     }
    //printf("\n Alocou Y \n");

     for (i =0; i<500; i++)
     {
     A1[i] = (double*) calloc (500, sizeof(double));
     if (A1[i] == NULL)
     {
        printf ("Erro na alocacao de A1");
        return;
      }
     }
    //printf("\n Alocou A1 \n");
     for (i=0; i<500; i++)
     {
     B1[i] = (double*) calloc (500, sizeof(double));
     if (B1[i] == NULL)
     {
        printf ("Erro na alocacao de B1");
        return;
      }
     }
    //printf("\n Alocou B1 \n");


    //printf("\n Zerou vetores e matrizes \n");
    for (i=0;i<500;i++)
    {
        for (j=0;j<500;j++)
            {
                A1[i][j]=0.0;
                B1[i][j]=0.0;
                Y[i][j]=0.0;
            }

    }


    //zera vetores e matrizes
    for (i=0; i<=n; i++)
        {
            R[i]=0.0;
            Z[i]=0.0;
            F[i]=0.0;
            P[i]=0.0;
            G[i]=0.0;
        }

    //printf("\n Zerou matrizes \n");

    A[0]=A[1]; //IMPORTANTE
    //printf("\n Atribuiu A[1] para A[0] \n");

    for (i=0;i<=n;i++)
    {
        //printf("%d %lf", i, A[i]);
        A[i]=A[i]*divisor;
        //printf("i=%d A=%lf \n", i, A[i]);
    }

    for (i=0; i<=n; i++)
    {
        for (j=0;j<=n;j++)
            Y[i][j]=0.0;
    }


    //inercia = 2.50d-09 //q notação é essa??


    F[1]=1.0;

    //cálculo da velocidade de propagação
    E=71*pow(10,9);
    c = sqrt(E/ro);

    //printf("E=%lf, ro=%lf \n", E, ro);
    //printf("Vel.= %lf \n", c);

//cálculo da impedância generalizada z(x)
    //printf("Impedancia");
    for (i=0; i<=n;i++)
    {
        Z[i]=A[i]*ro*c;
        //printf("\n Z[%d]=%lf A[%d]=%lf\n", i, Z[i], i, A[i]);
    }


//calculo dos coeficientes de reflexão

    for(i=1;i<=n;i++)
    {
        if ((Z[i]+Z[i-1])!=0.0)
            R[i]=((Z[i]-Z[i-1])/(Z[i]+Z[i-1]));
    }

//***************************************************************************
//condicao de contorno *****************************************************
//R[n]=1.0; //--- ENGASTADA
//***************************************************************************


    //calcula P(1) e P(2)
    P[1]=0.0;
    P[2]=0.0;


    //calculo G(1) e G(2)
    for (n1=1;n1<=1; n1++) //G[1]
    {
	   for (p1=1; p1<=n1-2; p1++)
           P[n1] = P[n1] + Y[p1][n1];

       G[1] = ((G[1] + (R[n1+1]+ P[n1]) * F[1-n1+1]));
       //printf("\n G[1]=%lf \n", G[1]);
    }


    for (n1=1;n1<=2;n1++) //G[2]
    {
        for (p1=1;p1<=n1-2;p1++)
            P[n1]=P[n1]+Y[p1][n1];

        G[2]=((G[2]+ (R[n1+1] + P[n1])* F[2-n1+1]));
        //printf("\n G[2]=%lf \n", G[2]);
    }


    for (n1=3;n1<=n;n1++)
    {
        for (p1=1;p1<=n1-2;p1++)
        {
            if (p1<=(n1-3)) A1[p1][n1]=A1[p1][n1-2] - B1[p1][n1-2];

            A1[n1-2][n1-1]=0.0;
            somatorio1=0.0;

            for (k=1;k<=p1-1;k++)
                somatorio1=somatorio1+Y[k][n1-1];

            B1[p1][n1-1] = (R[n1-p1-1]*(somatorio1+R[n1-1]));
            Y[p1][n1] = (R[n1-p1]*(A1[p1][n1-1] - B1[p1][n1-1]));
            P[n1] = (P[n1]+Y[p1][n1]);

        }

    }


    //calculo do eco G(j)--------------
    //printf("\n Calculo do eco\n");
    for (j=1;j<=n;j++)
    {
        for (n1=1;n1<=j;n1++)
        {
                //printf("R[%d]=%lf \n", n1, R[n1]);
                G[j]=((G[j]+(R[n1]+P[n1])) * F[j-n1+1]); //*100
        }

    }
    //printf("\n Valores depois da fórmula geral \n");
    //printf("G[1]= %lf \n", G[1]);
    //printf("G[2]= %lf \n", G[2]);
    //printf("G[3]= %lf \n", G[3]);

    for (i=0;i<=n+1;i++)
        A[i]=A[i]/divisor; //Dimensionalizando

        //Liberando memória
        for (i=0;i<500;i++)
            free (A1[i]);
        free (A1);

        for (i=0;i<500;i++)
            free (B1[i]);
        free (B1);

        for (i=0;i<500;i++)
            free (Y[i]);
        free (Y);
        
   }
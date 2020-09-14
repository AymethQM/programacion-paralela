
/*
 ============================================================================
 Name        : OMP_CalcEuler.c
 Author      : Aymeth Quispe Marin
 Version     :
 Copyright   : Your copyright notice
 Description : Compute Pi in MPI C++
 ============================================================================
 */

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int factorial(int f){
	int fact=f;
	if(fact>=1){
    	fact=f*factorial(f-1);
    	return fact;
	}else{
    	return 1;
	}
}

int main (int argc, char *argv[]) {
  int k;

  printf("\n ***************************************************");
  printf("\n Fuera de la región paralela, se utilizan 5 threads");
  printf("\n ***************************************************");
  printf("\n \n Ingresa un valor para k, (k>3) : ");
  scanf("%d",&k);
  omp_set_num_threads(5);

 	double ep = 0.0;
 	double time_ini, time_fin, time;
 	time_ini = omp_get_wtime();
  #pragma omp parallel reduction(+:ep)
  {
 	int id = omp_get_thread_num();
 	int nt = omp_get_num_threads();
 	double e=0;
 	for (int i=id; i<=k; i+=nt){
     	double m = factorial(i);
     	e+=1.0/m;  //e=e+1.0/fact

     	}	ep+=e;
     	time_fin = omp_get_wtime();
     	time = time_fin - time_ini;
  }
  printf("**El valor de euler es: %.10f",ep);
  printf("\n Tiempo de ejecucion: %.8f\n", time );

  return 0;
  }


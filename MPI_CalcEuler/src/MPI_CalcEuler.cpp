/*
 ============================================================================
 Name        : MPI_CalcEuler.c
 Author      : Aymeth Quispe Marin
 Version     :
 Copyright   : Your copyright notice
 Description : Compute Pi in MPI C++
 ============================================================================
 */

#include <math.h>
#include "mpi.h"   // Biblioteca de MPI
#include <cstdlib> // Incluido para el uso de atoi
#include <iostream>
using namespace std;

int fact(int f){
	int factorial=f;
	if(factorial>=1){
    	factorial=f*fact(f-1);
    	return factorial;
	}else{
    	return 1;
	}
}

int main(int argc, char *argv[]){

	int k, // Numero de sumas inversas
   	 rank, // Identificador de proceso
   	 size; // Numero de procesos
	double Epsilon = 2.718281828459045235360;
	double myep=0.0, // Valor local de epsilon
   	 ep;   // Valor global de Epsilon

	MPI_Init(&argc, &argv); // Inicializamos los procesos
	MPI_Comm_size(MPI_COMM_WORLD, &size); // Obtenemos el numero total de procesos
	MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Obtenemos el valor de nuestro identificador

	// Solo el proceso 0 va a conocer el numero de iteraciones que vamos a
	// ejecutar para la aproximacion de PI
    if (rank == 0) {
   	 printf("**Para hallar el valor de e, (k > 3)) \n**");
   	 cout<<"-> Ingresa el valor de K: ";
   	 cin>>k;
    }
    MPI_Bcast(&k, // Puntero al dato que vamos a enviar
   						   1,  // Numero de datos a los que apunta el puntero
   						   MPI_INT, // Tipo del dato a enviar
   						   0, // Identificacion del proceso que envia el dato
   						   MPI_COMM_WORLD);
   	 if (k <= 3){
   		 printf("***Ingrese numero mayor que 3***");
   		 MPI_Finalize();
   		 exit (0);
   	 }else{
   		 	 	 double e=0.0;

   				 for(int i = rank;i<=k;i+=size){
   					double u=double (fact(i));

   					 e+=1.0/u;

   				 }
   				 myep += e;

   				 MPI_Reduce(&myep, // Valor local de epsilon
   							 &ep,  // Dato sobre el que vamos a reducir el resto
   							 1,      // Numero de datos que vamos a reducir
   							 MPI_DOUBLE,  // Tipo de dato que vamos a reducir
   							 MPI_SUM,  // Operacion que aplicaremos
   							 0, // proceso que va a recibir el dato reducido
   							 MPI_COMM_WORLD);

   						 // Imprime el valor de Epsilon.
   						 if (rank == 0)
   						 {
   							 printf("**Epsilon: %.30f \n", Epsilon);
   							 printf("MyEpsilon es: %.30f \n ",ep );
   							 printf("El valor aproximado de Epsilon es: %.30f, con un error de %.30f \n", ep,fabs(ep - Epsilon));
   						 }

   		 }

	MPI_Finalize();
	return 0;
}

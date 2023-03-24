#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <math.h>
#include "Timming.h"

int main(int argc, char **argv){
  int numproc;
  int miproc;
  float x;
  float y;
  float data; //response
  MPI_Status status;
  float sum = 0.0;
  //int jojo;

  double utime0, stime0, wtime0, utime1, stime1, wtime1;
  double t0, t1;
  
  //int k;

  MPI_Init (&argc, &argv); /* Inicializar MPI */
  t0 = MPI_Wtime();
  MPI_Comm_rank(MPI_COMM_WORLD,&miproc); /* Determinar el rango del proceso invocado*/
  MPI_Comm_size(MPI_COMM_WORLD,&numproc); /* Determinar el numero de procesos */  
  
 // printf("numproc = %i\n",numproc);
  
  x = miproc;
  //printf("%i: Ready x = %f\n",miproc,x);
  MPI_Barrier (MPI_COMM_WORLD); 
  //y = x*x;
  //printf("%i:%f^2=%f\n",miproc,x,y);

  if (miproc == 0){ //master
    uswtime(&utime0, &stime0, &wtime0);
    for (int i=1;i<numproc;i++){
      data = i+1;
      //printf("Sending:%i->%i,%f:",0,i,data);
      MPI_Send(&data, sizeof(data), MPI_CHAR, i, 98, MPI_COMM_WORLD);
      //printf("ok\n");
    }
  MPI_Barrier (MPI_COMM_WORLD);
  }else{//slaves
        //printf("Receiving:%i->%i,:",0,miproc);
        MPI_Recv(&data, sizeof(data), MPI_CHAR, 0, 98, MPI_COMM_WORLD, &status);
        //printf("%f:ok\n",data);


	for (int j = 0; j<1000000; j++) { 
	  data = powf(sqrt((sin(j) + cos(j)) / 2.0), 7.1);
	}
        //MPI_Barrier (MPI_COMM_WORLD); 

  }

  MPI_Barrier (MPI_COMM_WORLD);


  //printf("Computing...\n");


if (miproc == 0){
  float data2 = -1;
  int k;
  float sum2;
  
  printf("Using %i processors\n",numproc);
  //k = 0;
  sum = 1.0;
  for(k=1;k<numproc;k++){
    //k = k+1;
    printf("RCV %i->%i\n",k,0);  
    MPI_Recv(&data, sizeof(data), MPI_CHAR, k, 99, MPI_COMM_WORLD, &status);
    sum += data;
    //printf("Suma=%f\n",sum);
  }
  printf("Suma = %f\n", sum);
  
  //MPI_Barrier(MPI_COMM_WORLD);

  t1 = MPI_Wtime();
  printf("Execution time: %.3lf sec \n", t1 - t0);
  uswtime(&utime1, &stime1, &wtime1);

  printf("\nBenchmarks (sec):\n");
  printf("real %.3f\n", wtime1 - wtime0);
  printf("user %.3f\n", utime1 - utime0);
  printf("sys %.3f\n", stime1 - stime0);
  printf("\n");
  printf("CPU/Wall %.3f %% \n", 100.0 * (utime1 - utime0 + stime1 - stime0) / (wtime1 - wtime0));
  printf("\n");
  
}else{
  //printf("SND %i->%i\n",miproc,0);
  MPI_Send(&data, sizeof(data), MPI_CHAR, 0, 99, MPI_COMM_WORLD);
  //MPI_Barrier(MPI_COMM_WORLD); 


}

 MPI_Barrier (MPI_COMM_WORLD); 
  //printf("%i: Termine!\n",miproc);

  MPI_Finalize ();

  return 0;

}

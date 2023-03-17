#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char **argv) {
	int numproc;
	int miproc;
	float x;
	float y;

	MPI_Init (&argc, &argv); /* Inicializar MPI */

	MPI_Comm_rank(MPI_COMM_WORLD, &miproc); /* Determinar el rango del proceso invocado */
	MPI_Comm_size(MPI_COMM_WORLD, &numproc); /* Determinar el numero de procesos */
	x = miproc;
	printf("%i: Ready x = %f\n", miproc, x);
	MPI_Barrier (MPI_COMM_WORLD);
	y = x*x
	printf("%i:%f^2 = %f\n", numproc, x, y);

	//printf("%i: Finished!\n", miproc);

	MPI_Finalize ();

	return 0;
}

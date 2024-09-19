#include <mpi.h>
#include <iostream>

constexpr int NUM_DATOS = 1;
constexpr int RANK_EMISOR = 0;
constexpr int RANK_RECEPTOR = 1;
constexpr int TAG = 0;

using namespace std;

int main(int argc, char* argv[]) {
	// Inicializar MPI
    MPI_Init(&argc, &argv);

    int rank, size = 0;

	// Obtener el rango y el tama�o del comunicador
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

	// Comprobar que hay al menos dos procesos; Emisor y Receptor
    if (size < RANK_RECEPTOR+1) {
		printf("Se necesitan al menos %d procesos para ejecutar el programa.\n", RANK_RECEPTOR+1);
		// Finalizar MPI con c�dgio de error 1
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    if (rank == RANK_EMISOR) {
        long double dato = 0;
		printf("Introduce un n�mero: ");
		cin >> dato;
		// Enviar el dato al proceso Receptor
        MPI_Send(&dato, NUM_DATOS, MPI_LONG_DOUBLE, RANK_RECEPTOR, TAG, MPI_COMM_WORLD);
        printf("El Proceso %d ha enviado el dato '%.2lf' al proceso %d.\n", rank, dato, RANK_RECEPTOR);
    }
    else if (rank == RANK_RECEPTOR) {
        long double dato = 0;
		// Recibir el dato del proceso Emisor
        MPI_Recv(&dato, NUM_DATOS, MPI_LONG_DOUBLE, RANK_EMISOR, TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		printf("El Proceso %d ha recibido el dato '%.2lf' del proceso %d.\n", rank, dato, RANK_EMISOR);
    }

	// Finalizar MPI
    MPI_Finalize();
    return 0;
}
/*
 �C�mo se podr�a enviar el mismo dato a varios procesos?

 Para enviar el mismo dato a varios procesos, se puede utilizar la funci�n MPI_Bcast, que permite enviar un dato desde un proceso a todos los dem�s procesos en un comunicador.
 */
/*
 �Qu� orden  de  recepci�n  se prev� que existir�a: por  rango, por proximidad geogr�fica, por
orden de programa...?

 El orden de recepci�n se prev� que sea por rango, ya que los procesos se comunican entre s� utilizando sus rangos. Sin embargo, el orden de recepci�n real puede depender de varios factores, como la implementaci�n de MPI, la carga de trabajo de los procesos y la topolog�a de la red. En general, se espera que los procesos con rangos m�s bajos reciban datos antes que los procesos con rangos m�s altos, pero esto no est� garantizado.
 */

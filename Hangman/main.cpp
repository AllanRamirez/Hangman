#include "Juego.h"

int main() {
	Juego Hangman;
	if (Hangman.cargarDatos())
		Hangman.jugar();
	else
		cout << "ERROR: No se han podido abrir el archivo para cargar los datos!" << endl << endl;

	return 0;
}
#ifndef JUEGO_H
#define JUEGO_H

#include <vector>
#include <cstdlib>
#include <sstream> //stringstream
#include <algorithm> //random_shuffle();
#include <fstream> //manejo de archivos
#include <iostream> //entrada y salida
#include <string> //leer del archivo
#include <ctime>  //funciones relacionadas con fecha y hora

using namespace std;

class Juego {
private:
	vector<string>contenedor; //Estructura de datos que almacena las palabras para el juego.
	vector<string>::iterator iterador;
	unsigned short int intentos;
	string palabraSeleccionada;
public:
	Juego();
	void jugar();
	bool letraReptida(string, char); //Devuelve true si la letra que se digita ya se ha buscado anteriormente.
	void seleccionarPalabra(); /*Se obtiene una letra del abecedario y se realiza un random_shuffle() al contenedor porque se recorre
							   de inicio a fin siempre o hasta que encuentre una palabra que inicie con la letra que se obtuvo.
							   Si no se hiciera el random_shuffle(), para la letra 'a' por ejemplo siempre se seleccionaria
							   la primera palabra que inicia con 'a' y seria la misma*/
	bool cargarDatos(); //Si hay un error abriendo el archivo, retorna false.
	string informacionDelJuego(string, int) const; //Recibe la palabra oculta por "_" y una cantidad de intentos que se va actualizando.
	string mensajeAlGanar();
	string mensajeAlPerder();
	~Juego();
};

#endif 
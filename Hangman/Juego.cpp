#include "Juego.h"



Juego::Juego(){
	this->intentos = 7;
	this->palabraSeleccionada = " ";
}

bool Juego::cargarDatos() {
	ifstream archivo;
	archivo.open("palabras.txt", ios::in); //Se abre el archivo para solo lectura
	if (archivo.fail()) 
		return false;

	string palabra;
	while (!archivo.eof()) {
		archivo >> palabra;
		contenedor.push_back(palabra);
	}
	archivo.close();
	return true;
}

string Juego::informacionDelJuego(string oculta, int inte) const{
	stringstream s;
	s << "--------------------Informacion del juego--------------------" << endl;
	s << "La cantidad de letras de la palabra oculta es de: " << palabraSeleccionada.size() << endl;
	s << "Intentos fallidos: (" << inte << "/" << this->intentos << ")" << endl << endl;
	s << oculta << endl << endl;
	s << "-------------------------------------------------------------" << endl;
	return s.str();
}

string Juego::mensajeAlGanar(){
	stringstream s;
	s << "             (0 0)" << endl;
	s << "   -- - oOO-- (_)----oOO-- -" << endl;
	s << "  @@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl;
	s << "  @  HA GANADO, FELICIDADES @" << endl;
	s << "  @@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl;
	s << "    --------------------" << endl;
	s << "	 | __ | __|" << endl;
	s << "            || ||" << endl;
	s << "           ooO Ooo" << endl;
	return s.str();
}

string Juego::mensajeAlPerder(){
	stringstream s;
	s << "88" << endl;
	s << "88" << endl;
	s << "88" << endl;
	s << "88, dPPYba,  ,adPPYYba,  8b,dPPYba,  ,aadPPYb,d8 88,dPYba, ,adPYba,  ,adPPYYba, 8b, dPPYba," << endl;
	s << "88P'    '8a  ''     `Y8  88P'   `'8a a8'    `Y88 88P'   '88'    '8a  ''     `Y8 88P'   `'8a" << endl;
	s << "88       88  ,adPPPPP88  88       88 8b       88 88      88      88  ,adPPPPP88 88       88" << endl;
	s << "88       88   88,   ,88  88       88 '8a,   ,d88 88      88      88  88,    ,88 88       88" << endl;
	s << "88       88  `'8bbdP'Y8  88       88  `'YbbdP'Y8 88      88      88  `'8bbdP'Y8 88       88" << endl;
	s << "                                      aa,    ,88" << endl;
	s << "                                       'Y8bbdP'" << endl;
	return s.str();
}

void Juego::seleccionarPalabra() {
	bool flag; //bandera para identificar que si se encontro la palabra
	string palabra;
	srand(static_cast<unsigned int>(time(nullptr)));
	random_shuffle(contenedor.begin(), contenedor.end());
	
	do {
		char letra = (97 + rand() % ((26 + 1) - 1)); //numeros entre 97 y 122 (letras entre la a y la z). https://elcodigoascii.com.ar/
		flag = false;
		for (iterador = contenedor.begin(); iterador != contenedor.end(); iterador++) {
			palabra = *iterador;
			if (palabra[0] == letra) {
				palabraSeleccionada = palabra;
				flag = true;
				break; //salgo del bucle si encuentro la primera palabra que empieza con "letra" para no buscar mas 
			}
		}
	} while (!flag); /*si no se encuentra la palabra es porque no hay una que empiece con esa letra, por lo que 
					 se busca otra diferente y se repite el procedimiento*/
}

void Juego::jugar() { 
	bool flag;
	char letra, respuesta = 'n';

	do {
		unsigned short int contadorIntentos = 0; //cantidad de intentos utilizados
		unsigned short int contadorLetras = 0; //contador para saber si gana
		seleccionarPalabra();
		string palabraOculta(palabraSeleccionada.size(), '_');

		//Descomentar para ver palabra seleccionada
		cout << "La palabra seleccionada aleatoriamente es: " << palabraSeleccionada << endl << endl;  

		do {
			flag = false;	
			cout << informacionDelJuego(palabraOculta, contadorIntentos);
			
			cout << "Digite una letra:  "; 
			cin >> letra;
			while (!isalpha(letra)) {
				cout << "Digite una letra:  ";
				cin >> letra;
			}
			cout << endl;

			while (letraReptida(palabraOculta, letra)) {
				cout << "La letra ya se ha descubierto" << endl;
				cout << "Digite una letra:  ";
				cin >> letra;
				while (!isalpha(letra)) {
					cout << "Digite una letra:  ";
					cin >> letra;
				}
				cout << endl;
			}

			for (unsigned short int i = 0; i < palabraOculta.size(); i++) {
				if (palabraSeleccionada[i] == letra) {
					contadorLetras++;
					palabraOculta[i] = letra;
					flag = true;
				}
			}

			system("clear");

			if (!flag) {
				cout << "La " << letra << " no forma parte de esta palabra. Ha perdido 1 intento!" << endl << endl;
				contadorIntentos++;
			}

		} while (contadorIntentos < this->intentos && contadorLetras < palabraSeleccionada.size()); 

		if (contadorLetras == palabraSeleccionada.size())
			cout << mensajeAlGanar() << endl << endl;
		else {
			cout << mensajeAlPerder() << endl;
			cout << "La palabra era: " << palabraSeleccionada << endl << endl;
		}

		cout << "Digite una 's' seguido de un ENTER para jugar nuevamente o digite otra tecla seguido de un ENTER para salir!" << endl;
		cin >> respuesta;
		tolower(letra);
		system("clear");
	} while (respuesta == 's');
	
}

bool Juego::letraReptida(string palabra, char letra){
	for (unsigned short int i = 0; i < palabra.size(); i++) {
		if (palabra[i] == letra)
			return true;
	}
	return false;
}

Juego::~Juego(){
}

#include <iostream>
#include <fstream>
#include <string.h>
#include <cstring>
#include <Windows.h>

using namespace std;

struct nodo_pasajeros {
	char NombreCompleto[100]; 
	char Nombres[50];
	char ApellidoP[25];
	char ApellidoM[25];
	int pasaporte;
	char nacionalidad[20];
	nodo_pasajeros* ant, * sig;
} *ini_pasajeros, * fin_pasajeros, * aux_pasajeros;

class CNombres {
private:
	char Nombres[50];
	char ApellidoP[25];
	char ApellidoM[25];

public:
	// Constructor
	CNombres() {}

	// Método para concatenar nombres y apellidos
	void concatenarNombres(char NombreCompleto[100]) {
		strcpy(NombreCompleto, Nombres);
		strcat(NombreCompleto, " ");
		strcat(NombreCompleto, ApellidoP);
		strcat(NombreCompleto, " ");
		strcat(NombreCompleto, ApellidoM);
	}

	// Setter para establecer los nombres y apellidos
	void setNombres(const char* nombres) {
		strcpy(Nombres, nombres);
	}

	void setApellidoP(const char* apellidoP) {
		strcpy(ApellidoP, apellidoP);
	}

	void setApellidoM(const char* apellidoM) {
		strcpy(ApellidoM, apellidoM);
	}
};




void agregar_pasajero(nodo_pasajeros* nuevo) {
	// agregar a la lista
	if (ini_pasajeros == 0) {
		ini_pasajeros = nuevo;
		fin_pasajeros = nuevo;
	}
	else {
		fin_pasajeros->sig = nuevo;
		nuevo->ant = fin_pasajeros;
		fin_pasajeros = nuevo;
	}
}

void captura_pasajeros(nodo_pasajeros* nodo, CNombres& nombres) {
	system("cls");
	char temp[100];
	printf("--Captura de pasajeros--\n");
	cout << "Pasaporte: ";
	cin >> nodo->pasaporte;
	cout << "Nacionalidad: ";
	cin >> nodo->nacionalidad;
	cin.ignore(); 
	cout << "Nombres: ";
	cin.getline(temp, 100); 
	nombres.setNombres(temp); 
	//nodo->Nombre = Nombre;
	cout << "Ingrese el primer apellido: ";
	cin.getline(temp, 100);
	nombres.setApellidoP(temp);
	//nodo->apellidoP = ApellidoP;
	cout << "Ingrese el  segundo apellido: ";
	cin.getline(temp, 100);
	nombres.setApellidoM(temp);
	nombres.concatenarNombres(nodo->NombreCompleto);  
}

void elimina_primer_pasajero() {
	aux_pasajeros = ini_pasajeros;
	if (ini_pasajeros != 0) {
		if (ini_pasajeros == fin_pasajeros) {
			ini_pasajeros = 0;
			fin_pasajeros = 0;
		}
		else {
			ini_pasajeros = aux_pasajeros->sig;
			ini_pasajeros->ant = 0;
		}
		delete aux_pasajeros;
	}
}

void elimina_ultimo_pasajero() {
	aux_pasajeros = fin_pasajeros;
	if (fin_pasajeros != 0) {
		if (ini_pasajeros == fin_pasajeros) {
			ini_pasajeros = 0;
			fin_pasajeros = 0;
		}
		else {
			fin_pasajeros = aux_pasajeros->ant;
			fin_pasajeros->sig = 0;
		}
		delete aux_pasajeros;
	}
}

void elimina_pasajero() {
	if (aux_pasajeros == ini_pasajeros) {
		elimina_primer_pasajero();
	}
	else {
		if (aux_pasajeros == fin_pasajeros) {
			elimina_ultimo_pasajero();
		}
		else
		{
			aux_pasajeros->ant->sig = aux_pasajeros->sig;
			aux_pasajeros->sig->ant = aux_pasajeros->ant;
			delete aux_pasajeros;
		}
	}

}

void leer_arch_pas(char archivo[]) {
	ifstream archivaldo;
	archivaldo.open(archivo, ios::binary);
	if (archivaldo.is_open()) {
		//leer archivo, byte x byte y crear la lista ligada
		aux_pasajeros = new nodo_pasajeros;
		archivaldo.read((char*)aux_pasajeros, sizeof(nodo_pasajeros));
		aux_pasajeros->ant = 0;
		aux_pasajeros->sig = 0;
		while (!archivaldo.eof()) {
			agregar_pasajero(aux_pasajeros);

			aux_pasajeros = new nodo_pasajeros;
			archivaldo.read((char*)aux_pasajeros, sizeof(nodo_pasajeros));
			aux_pasajeros->ant = 0;
			aux_pasajeros->sig = 0;
		}
	}
	archivaldo.close();
}

void escribe_arch_pas(char archivo[]) {
	ofstream archivaldo;
	archivaldo.open(archivo, ios::binary | ios::trunc);
	if (archivaldo.is_open()) {
		aux_pasajeros = ini_pasajeros;////1
		while (aux_pasajeros != 0) {//////2
			// escribir en el archivo, nodo x nodo
			archivaldo.write((char*)aux_pasajeros, sizeof(nodo_pasajeros));

			aux_pasajeros = aux_pasajeros->sig;////3
		}
		archivaldo.close();
		printf("archivo guardado");
	}
	else {
		printf("archivo no se pudo abrir");
	}
}

bool buscar_pasajero(int busqueda) {
	aux_pasajeros = ini_pasajeros;//1
	while (aux_pasajeros != 0)//2
	{
		if (aux_pasajeros->pasaporte == busqueda) { 
			return true;
			break;
		}

		aux_pasajeros = aux_pasajeros->sig;//3
	}
	return false;
}


int main() {
	CNombres nombres; 
	////string var = "hola";
	char carpeta[MAX_PATH] = "";
	char archi[] = "\\passengers.dat";
	string nombre, apellidoP, apellidoM; 
	GetCurrentDirectory(MAX_PATH, carpeta);
	strncat(carpeta, archi, sizeof(carpeta) - strlen(carpeta) - 1);
	short opc = 0, _opc = 0;
	char mensaje[40];
	int _pasa;

	//printf("%s", carpeta);
	//system("pause");


	leer_arch_pas(carpeta);

	do
	{
		system("cls");
		printf("  SISTEMA DE PASAJEROS\n");
		printf("1. Agregar pasajero\n");
		printf("2. Remover primer pasajero\n");
		printf("3. Remover ultimo pasajero\n");
		printf("4. Buscar pasajero\n");
		printf("5. Lista de pasajeros (ini)\n");
		printf("6. Lista de pasajeros (fin)\n");
		printf("7. Salir\n");
		cin >> opc;

		switch (opc)
		{
		case 1: {			 
			nodo_pasajeros* aux_pasajeros; 
			aux_pasajeros = new nodo_pasajeros; 
			aux_pasajeros->ant = nullptr; 
			aux_pasajeros->sig = nullptr; 

			captura_pasajeros(aux_pasajeros, nombres); 
			agregar_pasajero(aux_pasajeros); 

			
			strcpy(mensaje, "pasajero agregado"); 

		}break;
		case 2: // borrar como si fuera "cola"
			elimina_primer_pasajero();

			strcpy(mensaje, "primer pasajero eliminado");
			break;
		case 3: // borrar como si fuera "pila"
			elimina_ultimo_pasajero();

			strcpy(mensaje, "ultimo pasajero eliminado");
			break;
		case 4: // BUSCAR		
			system("cls");
			printf("Captura pasaporte: ");
			cin >> _pasa;
			if (buscar_pasajero(_pasa) == true) 
			{
				cout << "nombre: " << aux_pasajeros->NombreCompleto << endl;				
				printf("nacionalidad: %s\n", aux_pasajeros->nacionalidad);
				printf("pasaporte: %d\n", aux_pasajeros->pasaporte);
				printf("Desea 1) Modificar 2) Eliminar\n");
				cin >> _opc;
				if (_opc == 1) {
					
					captura_pasajeros(aux_pasajeros, nombres);
					strcpy(mensaje, "datos moficados");
				}
				if (_opc == 2) {
					elimina_pasajero();
					strcpy(mensaje, "pasajero eliminado");
				}

				strcpy(mensaje, "pasajero encontrado");
			}
			else
			{
				strcpy(mensaje, "no existe pasajero");
			}


			break;
		case 5:
			system("cls");
			aux_pasajeros = ini_pasajeros;
			
			while (aux_pasajeros != 0)
			{
				// mostrar el nodo
				cout << "Nombre:" << endl;
				cout << aux_pasajeros->NombreCompleto << endl;
				cout << "Nacionalidad" << endl;
				cout << aux_pasajeros->nacionalidad << endl;
				cout << "Pasaporte" << endl;
				cout << aux_pasajeros->pasaporte << endl;

				aux_pasajeros = aux_pasajeros->sig;
			}
			strcpy(mensaje, "fin de lista");
			system("pause");
			break;
		case 6:
			system("cls");
			aux_pasajeros = fin_pasajeros; //1			
			while (aux_pasajeros != 0) //2
			{
				// mostrar el nodo
				cout << "Nombre:" << endl;
				cout << aux_pasajeros->NombreCompleto << endl;
				cout << "Nacionalidad" << endl;
				cout << aux_pasajeros->nacionalidad << endl;
				cout << "Pasaporte" << endl;
				cout << aux_pasajeros->pasaporte << endl;

				aux_pasajeros = aux_pasajeros->ant; //3
			}
			strcpy(mensaje, "fin de lista");

			break;
		}
		printf("%s\n", mensaje);


	} while (opc < 7);


	escribe_arch_pas(carpeta); 

	system("pause");


}
#include<iostream>
#include<cstdlib>
#include<cctype>
#include<iomanip>
#include<string>
#include<fstream>
#include <string>
#include<Windows.h>
using namespace std;

//Daniel Ruiz Manero
//Ricardo de la Rosa Vivas

const int N = 9;

typedef int tNumeros[N]; // para los posibles candidatos
typedef int tMatrizTablero [N][N];
typedef bool tMatrizIniciales[N][N];

typedef enum { negro, azul, verde, aguamarina, rojo, purpura, amarillo, blanco } tColor;

typedef struct
{
	tNumeros numeros;
	int contador;
} tCandidatos;

typedef struct
{
	int casillasVacias;
	tMatrizTablero valores;
	tMatrizIniciales iniciales;
} tTablero;

char menu(); /*menu del programa principal
			entrada:
			salida: Caracter que selecciona la opcion deseada del usuario
*/
void colorear(tColor color); /*sirve para colorear las letras y diferenciarlas del resto
			entrada: El color en que apareceran los caracteres
			salida:
*/
void Inicializacion(tTablero &tablero); /*Inicializa el tablero por completo
			entrada:  La estructura tTablero que contiene el numero de casillas vacias, el array booleano con true donde hay valores y el array de valores

			salida: La inicializacion a 81 , false y 0 (respectivamente) de el numero de casillas vacias, el array de booleanos que indica los valores iniciales y 
			los numeros de los valores iniciales

*/
void nombreSudoku(string &ArSudoku); /*pide el nombre del sudoku
			entrada:
			salida: Nombre del archivo donde esta guardado el sudoku
*/
void nombreSolucion(string &SolSudoku); /*pide el nombre de la solucion
			entrada:
			salida: Nombre del archivo donde esta guardado la solucion del sudoku
*/
bool cargaValoresIniciales(tTablero &tablero, string ArSudoku, ifstream &input); /*carga los valores del sudoku(los iniciales)
			entrada: Nombre del archivo donde esta guardado el sudoku
			salida: Carga los numero en el array valores, carga true donde haya numeros en el array iniciales y disminuye las casillas vacias

					Devuelve false si ha habido un error en el contenido del archivo o al abrirlo
			
*/
bool cargaValoresSolucion(tMatrizTablero solucion, string SolSudoku, ifstream &sol);/* carga la solucion del sudoku
			entrada: Nombre del archivo donde esta guardado la solucion del sudoku
			salida: Carga el array de 2 dimensiones llamado solucion con los valores de la solucion

					Devuelve false si ha habido un error en el contenido del archivo o al abrirlo
*/
void dibujarSudoku(tTablero tablero); /*dibuja el sudoku
			entrada: La estructura tTablero que contiene el numero de casillas vacias, el array booleano con true donde hay valores y el array de valores
			salida:
*/
void valoresCasilla(const tMatrizTablero valores); /*mira los posibles valores de una casilla en el caso de que sea posible(ej: que no este vacia)
			entrada: El array que contiene los numeros con los que se esta jugando actualmente
			salida:
*/
void colocarValor(tTablero &tablero);/* coloca el valor en una casilla si es posible
			entrada: La estructura tTablero que contiene el numero de casillas vacias, el array booleano con true donde hay valores y el array de valores
			salida:  Los componentes de la estructura tTablero con los valores modificados
*/
void borrarValor(tTablero &tablero);/* borra el valor de una casilla si es posible
			entrada: La estructura tTablero que contiene el numero de casillas vacias, el array booleano con true donde hay valores y el array de valores
			salida:  Los componentes de la estructura tTablero con los valores modificados 
*/
void valoresIncorrectos(tTablero tablero, const tMatrizTablero solucion); /*muestra los valores incorrectos
			entrada: La estructura tTablero que contiene el numero de casillas vacias, el array booleano con true donde hay valores y el array de valores
			y el array con los valores de la solucion
			salida:
*/
void reiniciar(tTablero &tablero, int &ayuda); /*reinicia por completo el sudoku
			entrada: La estructura tTablero que contiene el numero de casillas vacias, el array booleano con true donde hay valores y el array de valores
			salida: Los componentes de la estructura tTablero con los valores modificados (en este caso, con los valores del archivo inicial)
*/
void completarCasillasSimples(tTablero &tablero, int &ayuda); /*completa las casillas en las que solo haya un posible candidato
			entrada: La estructura tTablero que contiene el numero de casillas vacias, el array booleano con true donde hay valores y el array de valores
			salida: Los componentes de la estructura tTablero con los valores modificados y la variable ayuda que indica la cantidad de veces que se a usado esta funcion
*/
void introducirValores(int &fila, int &columna); /*evalua si las filas y columnas introducidas son correctas
			entrada:
			salida:
*/
bool vacia(int fila, int columna, const tMatrizTablero valores); /*evalua si una casilla esta vacia
			entrada: Fila y columna de la casilla que se quiere evauluar, y el array de dos dimensiones que contiene los numeros actuales del sudoku
			salida:
					Devuelve false si la casilla no esta vacia
*/
void calcularCandidatos(int fila, int columna, const tMatrizTablero valores,tCandidatos &candidatos); /*calcula los candidatos posibles de una casilla
			entrada: Fila y columna de la casilla que se quiere evauluar, el array de dos dimensiones que contiene los numeros actuales del sudoku y la estructura tCandidatos
			que contiene un contador de candidatos y un array unidimensional que guardara los candidatos
			salida: El array candidatos modificado con los candidatos para esa casilla
*/
void mostrarCandidatos(tCandidatos candidatos); /*muestra por pantalla los posibles candidatos
			entrada:  El array candidatos modificado con los condidatos para esa casilla
			salida:
*/
bool evaluacionFila(int fila, int numero,const tMatrizTablero valores); /* evalua si un numero esta en una fila
			entrada: Fila y numero que se quiere evaluar, y el array de dos dimensiones que contiene los numeros actuales del sudoku
			salida:
					Devuelve false si el numero esta en la fila
*/
bool evaluacionColumna(int columna,int numero,const tMatrizTablero valores); /* evalua si un numero esta en una columna
			entrada: Fila y numero que se quiere evaluar, y el array de dos dimensiones que contiene los numeros actuales del sudoku
			salida:
					Devuelve false si el numero esta en la columna
*/
bool evaluacionRegion(int fila, int columna,int numero,const tMatrizTablero valores); /* evalua si un numero esta en una region
			entrada: Fila,columna y numero que se quiere evaluar, y el array de dos dimensiones que contiene los numeros actuales del sudoku
			salida:
					Devuelve false si el numero esta en la region
*/
void ganar(tTablero tablero, const tMatrizTablero solucion, int ayuda);/*evalua si has ganado o no(evalua si lo has hecho con trampas o no)
			entrada: La estructura tTablero que contiene el numero de casillas vacias, el array booleano con true donde hay valores y el array de valores; el array que 
			contiene la solucion; y la variable ayuda
			salida:
*/




int main()
{

	int ayuda = 0; //ayuda sirve para ver si se ha usado el rellenar las casillas simples
	bool salir = false, error = false;
	char finalizar;
	string ArSudoku = "sudoku1.txt", SolSudoku="solsdk1.txt";
	ifstream input, sol;
	tTablero tablero;
	tMatrizTablero solucion;

	Inicializacion(tablero);
	
	nombreSudoku(ArSudoku);

	if(cargaValoresIniciales(tablero, ArSudoku, input))
	{
		nombreSolucion(SolSudoku);

		if(cargaValoresSolucion(solucion, SolSudoku, sol))
		{

			do
			{
				dibujarSudoku(tablero);

				switch(menu())
				{
					case '0': salir = true; break;
					case '1': valoresCasilla(tablero.valores); break;
					case '2': colocarValor(tablero); break;
					case '3': borrarValor(tablero); break;
					case '4': valoresIncorrectos(tablero, solucion); break;
					case '5': reiniciar(tablero,ayuda); break;
					case '6': completarCasillasSimples(tablero, ayuda); break;
				}
			}while(!salir);
			
			ganar(tablero, solucion, ayuda);
		}
	}
	else 
		error = true;
				
	if(error) 
		cout << "Se ha producido un ERROR al iniciar el programa";
	cout << "(pulse enter para finalizar)";
	finalizar = cin.get();
	return 0;
}
void colorear(tColor color)
{
	SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),color); 
}
char menu()
{
	char opcion;
	
	cout << "0.- SALIR" << endl;
	cout << "1.- Ver posibles valores de una casilla" << endl;
	cout << "2.- Colocar un valor en una casilla" << endl;
	cout << "3.- Borrar el valor de una casilla" << endl;
	cout << "4.- Mostrar valores incorrectos" << endl;
	cout << "5.- Reiniciar tablero" << endl;
	cout << "6.- Completar casillas simples" << endl << endl;

	do
	{
		cout << "Introduce una opcion valida: ";
		cin >> opcion;
		cin.sync();
	}while((opcion < '0')||(opcion > '6')); 

	return opcion;
}
void Inicializacion(tTablero &tablero)
{
	for(int fila = 0; fila < N; fila++)
		for(int columna = 0; columna < N; columna++)
		{
			tablero.valores[fila][columna] = 0;
			tablero.iniciales[fila][columna] = false;
		}
	tablero.casillasVacias = 81;
}
void nombreSudoku(string &ArSudoku)
{
	char caracter;

	cout << "Nombre del sudoku (Intro -> archivo por defecto 'sudoku1.txt'):"<< endl;

	caracter = cin.peek();
	if(caracter != '\n') //sino es enter, recibe el nombre
	getline (cin, ArSudoku);

	cin.sync();
}
void nombreSolucion(string &SolSudoku)
{
	char caracter;

	cout << "Nombre de la solucion (Intro -> archivo por defecto 'solsdk1.txt'):"<< endl;

	caracter = cin.peek();
	if(caracter != '\n') //sino es enter, recibe el nombre
	getline(cin,SolSudoku);

	cin.sync();
}
bool cargaValoresIniciales(tTablero &tablero, string ArSudoku, ifstream &input)
{
	int fila, columna, valor;
	bool ok = true;

	input.open(ArSudoku); //abre el archivo donde se encuentra el sudoku
	if (!input.is_open()) //evalua si se abre correctamente
		ok = false;
	else
	{
		do
		{
			input >> fila;
			if(fila != -1)
			{
				input >> columna;
				input >> valor;
				if(((fila < 1)||(fila > 9)) || ((columna < 1)||(columna > 9)) || ((valor < 1)||(valor > 9))) //evalua si la fila,columna y valor son correctos
					ok = false;
				else 
				{
					fila = fila -1;
					columna = columna -1;
					tablero.valores[fila][columna] = valor; // si todo es correcto inicializa el numero en todo el tablero
					tablero.iniciales[fila][columna] = true;
					tablero.casillasVacias = tablero.casillasVacias -1;
				}				
			}
		}while((fila != -1)&&(ok));
	}
	return ok; //devuelve false si algo va mal
}
bool cargaValoresSolucion(tMatrizTablero solucion, string SolSudoku, ifstream &sol)
{ 
	int numero;
	bool ok = true;

	sol.open(SolSudoku); //abre el archivo solucion
	if(!sol.is_open()) //evalua si se abre correctamente
		ok = false;
	else
	{
	for(int fila = 0; fila < N; fila++)
		for(int columna = 0; columna < N; columna++)
		{
			sol >> numero;
			solucion[fila][columna] = numero;
		}
	sol.close(); //cierra el archivo con la solucion
	}
	
	return ok;
}
void dibujarSudoku(tTablero tablero)
{
	int contColumnas = 2, contFilas = 2; // variables que sirven para dibujar correctamente el sudoku

	colorear(verde);
	cout << "    1 2 3   4 5 6   7 8 9" <<endl; //numero de columnas
	colorear(blanco);
	cout << "  -------------------------" <<endl;

	for(int fila = 0; fila < N ; fila++) //recorre filas
	{
		colorear(verde);
		cout << fila + 1; 
		colorear(blanco);
		cout << " | ";

		for(int columna = 0 ; columna < N; columna++) //recorre columnas
		{
			if(tablero.valores[fila][columna] == 0) //mostrar nada si es cero el valor
				cout << "  ";
			else if (tablero.iniciales[fila][columna])
			{
				colorear(aguamarina);
				cout << tablero.valores[fila][columna] << " ";
				colorear(blanco);
			}
			else
				cout << tablero.valores[fila][columna] << " ";

				if(columna == contColumnas) // ecribir | cada tres valores en una fila
				{
					cout << "| ";
					contColumnas = contColumnas + 3;
				}
		}
		if (fila == contFilas)
		{
			cout << endl << "  -------------------------"; //escribir ------------------------- cada tres valores de una columna
			contFilas = contFilas + 3;
		}
		contColumnas = 2; //ajuste de la variable para la siguiente fila
		cout <<endl;
	}
	cout <<endl;
}
void valoresCasilla(const tMatrizTablero valores)
{
	tCandidatos candidatos;
	int fila, columna;
	
	introducirValores(fila, columna); //introducir valores

	if(!vacia(fila, columna,valores)) // evalua si esta vacia
		cout << "Casilla NO VACIA" << endl;
	else
	{
		calcularCandidatos(fila, columna, valores,candidatos); //valora los candidatos posibles

		mostrarCandidatos(candidatos); // los muestra por pantalla
	}
}
void colocarValor(tTablero &tablero)
{
	tCandidatos candidatos;
	int fila, columna, valor; //cont se usa para saber si es un digito valido o no
	bool digitoValido = false; //para saber si un digito es valido o no

	introducirValores(fila,columna); //entrada de la fila y columna

	if(tablero.iniciales[fila][columna]) //evalua si ese se puede modificar
		cout << "NO MODIFICABLE" << endl;

	else if(!vacia(fila,columna, tablero.valores)) //evalua si la casilla esta llena
		cout << "Casilla NO VACIA" << endl;
	else
	{
		do
		{
			cout << "Introduce el Valor: ";
			cin >> valor;
		}while((valor < 1)||(valor > 9));

		calcularCandidatos(fila, columna, tablero.valores, candidatos);

		for(int i = 0; i < candidatos.contador; i++)
			if(candidatos.numeros[i] == valor)
				digitoValido = true;

		if(digitoValido)
			tablero.valores[fila][columna] = valor;
		else
			cout << "Digito NO VALIDO" << endl;
	}
}
void borrarValor(tTablero &tablero)
{
	int fila, columna;

	introducirValores(fila,columna);

	if(tablero.iniciales[fila][columna]) //evalua si ese valor se puede modificar
		cout << "NO MODIFICABLE" << endl;

	else if(vacia(fila,columna, tablero.valores)) //evalua si la casilla esta llena
		cout << "CASILLA VACIA" << endl;
	else
	{
		tablero.valores[fila][columna] = 0; // lo borra y aumentan las casillas vacias
		tablero.casillasVacias = tablero.casillasVacias + 1;
	}
}
void valoresIncorrectos(tTablero tablero, const tMatrizTablero solucion)
{
	int cont = 0;

	cout << "ERRORES:" << endl;
	for(int fila = 0; fila < N; fila++)
		for(int columna = 0; columna < N; columna++)
		{
			if(((tablero.valores[fila][columna] != solucion[fila][columna])&&(tablero.valores[fila][columna] != 0))&&(!tablero.iniciales[fila][columna])) //compara el tablero de juego con la solucion y excluye los valores iniciales del sudoku
			{
				colorear(rojo);
				cout << "["<< fila + 1 << "," << columna + 1<< "] (" << tablero.valores[fila][columna] << ")" << endl; //los muestra por pantalla
				colorear(blanco);
				cont = cont + 1;
			}
		}
		if(cont == 0)
			cout << "NO HAY ERRORES" << endl;

}
void reiniciar(tTablero &tablero, int &ayuda)
{
	for(int fila = 0; fila < N; fila++)
		for(int columna = 0; columna < N; columna++)
			if((tablero.valores[fila][columna]!= 0)&&(!tablero.iniciales[fila][columna]))
			{
				tablero.valores[fila][columna] = 0; //pone a 0 aquellos valores no iniciales
				tablero.casillasVacias = tablero.casillasVacias + 1; //aumentan las casillas vacias
			}
	ayuda = 0; //pone a 0 la veces utilizada la opcion de completar casillas simples
}
void completarCasillasSimples(tTablero &tablero, int & ayuda)
{
	int numerosResueltos = 0;
	tCandidatos candidatos;

	for(int fila = 0; fila < N; fila++) //recorre el sudoku
		for(int columna = 0; columna < N; columna++)
		
			if(!tablero.iniciales[fila][columna])//mira si el numero es modificable o no
			{
				calcularCandidatos(fila, columna, tablero.valores, candidatos); //calula los candidatos de la primera casilla

				if(candidatos.contador == 1) //si hay un solo candidato
				{
					tablero.valores[fila][columna] = candidatos.numeros[candidatos.contador - 1]; //si solo hay uno lo guarda, se resta uno para acceder al array
					numerosResueltos = numerosResueltos + 1; // aumenta los resueltos
					tablero.casillasVacias = tablero.casillasVacias - 1; //disminuye las vacias
				}		
			}	
	cout << "Casillas Resueltas: " << numerosResueltos << endl;	
	ayuda ++; //aumenta el contador de ayuda
}
void introducirValores(int &fila, int &columna) //evalua que las filas y las columnas que se introducen son correctas
{
	do
	{
		cout << "Intrduce la fila y la columna(del 1 al 9): ";
		cin >> fila;
		cin >> columna;
	}while((fila < 0)||(fila > 9)||(columna < 0)||(columna > 9)); //evalua que las opciones son validas
	fila = fila -1; //ajusta las filas y columnas para los arrays
	columna = columna - 1;
}
bool vacia(int fila, int columna, const tMatrizTablero valores)
{
	bool ok = true;

	if(valores[fila][columna] != 0)
	{
		ok = false;
	}
	return ok; //falso si la casilla no esta vacia
}
void calcularCandidatos(int fila, int columna,const tMatrizTablero valores,tCandidatos &candidatos)
{
	candidatos.contador = 0; // no hay ningun candidato

	for(int numero = 1; numero <= N; numero++) /*genera los numeros que se van a evaluar en fila, columna y region
		(en las evaluaciones encuentra el numero, sale del bucle) */										

		if((evaluacionFila(fila, numero, valores))&&(evaluacionColumna(columna, numero, valores))&&(evaluacionRegion(fila, columna, numero, valores))) //cada una devuelve true si es un posible candidato y es candidato si lo cumple en las tres
		{
			candidatos.numeros[candidatos.contador] = numero;
			candidatos.contador++; //aumentan los candidatos
		}
	
}
void mostrarCandidatos(tCandidatos candidatos) //muestra por pantalla los candidatos de una casilla
{
	cout << "Posibles candidatos: ";

	for(int i = 0; i < candidatos.contador; i++)
			cout << candidatos.numeros[i] << " "; 
	
	cout << endl;
}
bool evaluacionFila(int fila,int numero,const tMatrizTablero valores)
{
	bool ok = true;
	int columna = 0;

	do
	{
			if(valores[fila][columna] == numero)
				ok = false;		
		columna++;
	}while((ok)&&(columna < 9));
	
	return ok;
	
}						
bool evaluacionColumna(int columna,int numero,const tMatrizTablero valores)
{
	bool ok = true;
	int fila = 0;

	do
	{
		if(valores[fila][columna] == numero)
				ok = false;		
		fila++;
	}while((ok)&&(fila < 9));
	
	return ok;
	
}

bool evaluacionRegion(int fila, int columna, int numero,const tMatrizTablero valores)
{
	bool ok = true;
	int i = 0, j = 0; // contadores: i para las filas, j para las columnas

	do
	{
		do
		{
			if(valores[((fila/3)*3)+i][((columna/3)*3)+j] == numero) //accede a las posiciones de la region de este modo
				ok = false;
			j++;
		}while((ok)&&(j < 3));
		j = 0; //ajuste para que en la siguiente iteracion empiece desde 0 
		i++;
	}while((ok)&&(i < 3));
	
	return ok; //devuelve falso si el numero esta en la region
}

void ganar(tTablero tablero, const tMatrizTablero solucion, int ayuda)
{
	int casillasCorrectas = 0;

	for(int fila = 0; fila < N; fila++) //mira haber cuantas casillas son correctas
		for(int columna = 0; columna < N; columna++)
			if(tablero.valores[fila][columna] == solucion[fila][columna])
					casillasCorrectas = casillasCorrectas + 1;

	if((casillasCorrectas == 81)&&(ayuda == 0)) //en funcion de si son todas correctas o no, salta un mensaje u otro
		cout << "ENHORABUENA HAS CONSEGUIDO SOLUCIONARLO!!(NO HAS USADO SOLUCIONAR CASILLAS SIMPLES!!)" << endl;
	else if ((casillasCorrectas == 81)&&(ayuda != 0))
		cout << "ENHORABUENA HAS CONSEGUIDO SOLUCIONARLO!!(Numero de veces usado solucionar casillas simples: " << ayuda << ")" << endl;
	else
		cout << "NO HAS CONSEGUIDO SOLUCIONARLO";
}
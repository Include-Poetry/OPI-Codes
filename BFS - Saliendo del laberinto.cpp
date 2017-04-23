#include <iostream>
#include <queue>
#define MAX 1000
using namespace std;

char mapa[MAX][MAX]; 		// Mapa
bool visitado[MAX][MAX];	// Mapa de visitados
int movx[4] = {1, -1, 0, 0};	// Posibles movimientos en x
int movy[4] = {0, 0, 1, -1};	// Posibles movimientos en y

class estado{
  public:
	int x;	// Coordenada en x
	int y;  // Coordenada en y
	int d;	// Distancia recorrida
	estado(int ix, int iy, int id){		// Constructor
		x = ix, y = iy, d = id;
	}
};

int BFS(int h, int l, int x, int y){
	estado inicial(x, y, 0);	// Estado inicial con coordenadas iniciales y 0 pasos dados
	queue<estado> cola;			// Cola con los estados a revisar

	cola.push(inicial);			// El estado inicial es el primero en procesar

	while(!cola.empty()){ 		// Mientras existan estados por revisar
		estado actual = cola.front();		// Sacamos el estado a procesar
		cola.pop();							// Sacamos ese estado de la cola
		if (mapa[actual.x][actual.y] == 'f'){ 	// Con 'f' como caracter que marca la salida
			return actual.d;		// Regresamos el número de pasos dados
		}

		visitado[actual.x][actual.y] = true;	// Marcamos como visitada la casilla actual
		for (int i=0; i<4; i++){				// Probamos por validar los posibles cuatro movimientos
			int nuevox = actual.x + movx[i];	// Modificamos con posibles cambios en x
			int nuevoy = actual.y + movy[i];	// Modificamos con posibles cambios en y

			if (nuevox >= 0 && nuevox < l && nuevoy >= 0 && nuevoy < h){ 	// Revisamos que esté en los límites
				if (!visitado[nuevox][nuevoy] && mapa[nuevox][nuevoy] != 'x'){ 	// Revisamos que no esté visitado y que no sea pared
					estado nuevo(nuevox, nuevoy, actual.d + 1); 	// Creamos el nuevo estado válido con un paso más
					cola.push(nuevo);
				}	
			}
		}
	}
	return -1; // Si no encontró una forma de llegar al objetivo, regresamos un número control conocido
}

int main(){
	int iniciox,	// Inicio en x
		inicioy,	// Inicio en y
		filas,		// Filas en el mapa
		columnas;	// Columnas en el mapa

	cin >> filas >> columnas;

	/* ------- Leemos el tablero ---------*/
	for (int i=0; i<filas; i++){
		for (int j=0; j<columnas; j++){
			cin >> mapa[j][i];
			if (mapa[j][i] == 'i'){		// 'i' como indicador de inicio
				iniciox = j;	// Coordenada de inicio en x
				inicioy = i;	// Coordenada de inicio en y
			}
		}
	}

	int pasos = BFS(filas, columnas, iniciox, inicioy);

	if (pasos == -1){
		cout << "Error 404: Destino not found\n";
	} else {
		cout << "Minima cantidad de pasos: "<< pasos << '\n';
	}
	
	return 0;
}

/*
10 10
x.........
i.x..xx.x.
.x........
...x...x..
...x...x..
.......x..
..x.x..x..
...x..x...
....x..f..
.x..x..x..
*/

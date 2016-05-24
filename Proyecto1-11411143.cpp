// GITHUB: https://github.com/Salgado93/Proyecto1.git
// WIKI:   http://fia.unitec.edu/wiki/index.php/11411143,DANIEL_SANTIAGO_SALGADO_PINTO
#include<iostream>
#include <curses.h>
#include <cstdlib>
#include <ctime>
using namespace::std;
void shuffleDeck( int[][14], int[], int[] );
void mostrarMano( int[][14] );
void imprimeJugadas(int[], int[], double, double*);
int escaleraColor( int[]);
int escaleraReal( int[]);

int main (int argc,char* argv[]){
	srand(time(NULL));
	initscr();
	cbreak(); // Cerrar con Ctrl z
	int input;
	double apuesta = 0.00;
	double dinero = 1000.00;
	int y,x; // Posicion de Pantalla
	int palos[53] = {0};
 	int valores[53] = { 0 };
	getmaxyx(stdscr,y,x);
	mvprintw(0,5,"Bienvenido");
	mvprintw(1,5,"Dinero: %4.2f",dinero);
	mvprintw(2,5,"Ingrese Apuesta: 1. 100 2. 500 3. 1000\n");
	refresh();
	move(3,5);
	input = getch();
	if (input == 49){
                apuesta = 100;
        }
        if (input == 50){
                apuesta = 500;
        }
        if(input == 51){
                apuesta = 1000;
        }
		do{
			clear();	
			int cartas[5][14]= {{0,0}};
			dinero -= apuesta;
			mvprintw(0,5,"Buena Suerte!");
                        mvprintw(0,x/2,"Apuesta: %4.2f\n", apuesta);
                        mvprintw(1,x/2,"Dinero: %4.2f\n", dinero);
			mvprintw(27,5,"-------------------------");
			mvprintw(28,5,"Par                 x  1");
			mvprintw(29,5,"Par Doble           x  2");
			mvprintw(30,5,"Trio                x  3");
			mvprintw(31,5,"Escalera            x  4");
			mvprintw(32,5,"Flush               x  5");
			mvprintw(33,5,"Full House          x  9" );
			mvprintw(34,5,"Poker               x  25");
			mvprintw(35,5,"Escalera De Color   x  50");
			mvprintw(36,5,"Escalera Real       x 250");
			mvprintw(37,5,"-------------------------");
	                refresh();
			move(15,30);
			shuffleDeck( cartas, palos, valores );
                        mostrarMano( cartas );
                        imprimeJugadas(palos, valores,apuesta,&dinero);
			if(dinero <= 0){
				break;
			}
                        move(20,57);
			printw("Press Any Key To DEAL! (Esc) To Exit!\n");
			refresh();
			move(21,57);
		}while((input = getch()) != 27);
	move(23,57);
	clear();
        mvprintw(y/2,(x/2)-10,"El Juego Ha Terminado");
	mvprintw((y/2)+1,(x/2)-10,"Pulse Cualquier Tecla");
       	refresh();
	move((y/2)+2,(x/2)-10);
	getch();
        endwin(); 
	return 0;
}
void shuffleDeck(int cartas[][14], int palos[], int valores[] ) {
	int tipoCarta;;
 	int numeroCarta;
 	for ( int contador = 1; contador <= 52; contador++ ){
		do{
			tipoCarta = 1 + rand() % 4;
 			numeroCarta = 1 + rand() % 13;
		} while( 0 != cartas[tipoCarta][numeroCarta]);
 		if (0  == cartas[tipoCarta][numeroCarta] ){
 			cartas[tipoCarta][numeroCarta] = contador;
 			palos[contador] = tipoCarta;
 			valores[contador] = numeroCarta;
 		}
	
 	}	 
}


void mostrarMano( int deck[][14]){
 	const char *valores[14] = { "0", "As", "Dos", "Tres", "Cuatro", "Cinco",
 	"Seis", "Siete", "Ocho", "Nueve", "Diez",
 	"Jota", "Reina", "Rey"};
	const char *palos[5] = { "0", "Corazones", "Treboles", "Espadas","Diamantes"}; 	
 	for ( int r = 1; r <= 5; r++ ){
 		for ( int y = 1; y <= 4; y++ ){
 			for ( int z = 1; z <= 13; z++ ){
 				if ( r == deck[y][z]){
					printw(" [%s  %s] ",valores[z],palos[y]);	
				}	
 			}
 		} 
 	}
 }

void imprimeJugadas(int cartas[], int valores[],double apuesta,double *nPtr){
	int contadorPares = 0;
        int contadorTrios = 0;
        int contadorPoker = 0;
 	int temp = cartas[1];
 	int iguales = 1;
 	int escaleraCorrida = 0;
	int y,x;
	getmaxyx(stdscr,y,x);
	y=1;
	// Revisa los numeros
	int temp2[14] = {0};	
 	for ( int s = 1; s <= 5; s++ ){
 		temp2[valores[s]]++; // Se guardan los numeros de la mano en el arreglo temporal.
 	}
 	for ( int w = 1; w <= 14; w++ ){
 		if ( 2 == temp2[w] ) //Si hay un par en la mano lo guarda en contador de pares.
 			contadorPares++;
 		if ( 3 == temp2[w] ) //Si hay un trio en la mano lo guarda en contador de trios.
 			contadorTrios = 1;
 		if ( 4 == temp2[w] ){ // Si hay cuatro cartas iguales en la mano lo guarda en contador de poker.
 			contadorPoker = 1;
 		}

	}

 	if ( 0 != contadorPares ){
		if(1 == contadorPares){
			mvprintw(10,70,"Tiene 1 Par! Gano: %4.2f$",apuesta*1);
			*nPtr += apuesta*1;
			mvprintw(y,x/2,"Dinero: %4.2f\n", *nPtr);
		}
		else{
		 	mvprintw(10,70,"Tiene 2 Pares! Gano: %4.f$",apuesta*2);
			*nPtr += apuesta*2;
			mvprintw(y,x/2,"Dinero: %4.2f\n", *nPtr);
		}
 	}
 	if ( 1 == contadorTrios ){
		if(0 != contadorPares){
			mvprintw(10,70,"Tiene Un Full! Gano: %4.2f$",apuesta*9);
			*nPtr += apuesta*9;
                        mvprintw(y,x/2,"Dinero: %4.2f\n", *nPtr);

		}
		else{
			mvprintw(10,70,"Tiene 1 Trio! Gano: %4.2f$",apuesta*3);
			*nPtr += apuesta*3;
                        mvprintw(y,x/2,"Dinero: %4.2f\n", *nPtr);

		}
 	}
 	if ( 1 == contadorPoker ){
		mvprintw(10,70,"Tiene Un Poker! Gano: %4.2f$",apuesta*25);
		*nPtr += apuesta*25;
                mvprintw(y,x/2,"Dinero: %4.2f\n", *nPtr);

 	}
	//Figuras
 	for ( int i = 2; i <= 5; i ++ ){
 		if ( cartas[ i ] != temp ){
 			iguales = -1;
 		} 
	}	
 	if ( 1 == iguales ){
 		escaleraCorrida = escaleraColor(valores); //Revisa si los numeros estan consecutivamente
 		int royal;
 		if ( 0 == escaleraCorrida ){
 			royal = escaleraReal(valores); //Revisa si hay escalera real
 			if ( 0 == royal ){
				mvprintw(10,70,"Tiene Un Color (Flush)! Gano: %4.2f$",apuesta*5);
				*nPtr += apuesta*5;
                        	mvprintw(y,x/2,"Dinero: %4.2f\n", *nPtr);

 			}
 			else{
				mvprintw(10,70,"Tiene Una Escalera Real! Gano: %4.f$",apuesta*250);
				*nPtr += apuesta*250;
                        	mvprintw(y,x/2,"Dinero: %4.2f\n", *nPtr);
			}	
 		}	
 		else{
			mvprintw(10,70,"Tiene Una Escalera De Color! Gano: %4.2f$",apuesta*2);
			*nPtr += apuesta*2;
                        mvprintw(y,x/2,"Dinero: %4.2f\n", *nPtr);

 		}
 	}
 	else{
 		int escalera;
		escalera = escaleraColor(valores);
 		if ( 1 == escalera){
			mvprintw(10,70,"Usted tiene 1 escalera");
			*nPtr += apuesta*4;
                        mvprintw(y,x/2,"Dinero: %4.2f\n", *nPtr);

 		}
		
 	}
	
}

int escaleraColor( int numeros[]){
		int temporal;
 		for ( int l = 1; l < 5; l++){
 			for ( int d = 1; d < 5; d++ ){
 				if ( numeros[d + 1] < numeros[d] ){ 
 					temporal = numeros[d];
 					numeros[d] = numeros[d + 1];
 					numeros[d + 1] = temporal;
 				}
 			}
 		}
 		int ordenados = 0;
 		for ( int t = 1; t < 5; t++ ){
 			if ( numeros[t + 1] == numeros[t] + 1 ){
 				ordenados++;
 			}
 		}
	 	if ( 4 != ordenados )
 			return 0;

 		else
 			return 1;
}

int escaleraReal( int numeros[] ){
	int tempor;
 	for ( int f = 1; f < 5; f++){ // Ordena de menor a mayor los numeros
 		for ( int d = 1; d < 5; d++ ){ 
 			if ( numeros[d + 1] < numeros[d] ){
 				tempor = numeros[d];
 				numeros[d] = numeros[d + 1];
 				numeros[d + 1] = tempor;
 			}
 		}
	}
 	int variable = 10;
 	int cambio = 0;
 	if ( 1 != numeros[1] )
 		return 0;
 	else{
 		for ( int z = 2; z <= 5; z++ ){
 			if ( numeros[z] != variable ){
 				cambio = 1;
 			}
 			variable++;
 		}
 	}
 	if ( 0 != cambio )
 		return 0;
 	else
 		return 1;
}


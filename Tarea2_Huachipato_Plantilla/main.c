#include "list.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashmap.h"

//------------------STRUCT-------------------------//

typedef struct {
	char *nombre;
	char *tipo;
	char *marca;
	int stock;
	int precioIndividual;
} Producto;

typedef struct {
	Producto * comprado;
	int cantidadComprada;
	int precioTotal;
} Vendido;

typedef struct {
	char *nombreCarrito;
	List *carro;
	int productosComprar;
	int precioPagar;
} Carrito;


//------------------FUNCIONES-------------------------//


/*------- Limpiar pantalla al ejecutarse -------*/
void cleanScreen() { // Limpia la pantalla al ejecutarse en el programa
	printf("\e[1;1H\e[2J");
}
//-----------------------------------------//

/*------- Copiar string en un nuevo espacio de memoria -------*/
char * _strdup(const char * str) {
    char * aux = (char *)malloc(strlen(str) + 1);
    strcpy(aux, str);
    return aux;
}
//-----------------------------------------//

/*-------  -------*/
char *get_csv_field(char *tmp, int k) {
	int open_mark = 0; //Variable que guardara si hay comillas abiertas
	char *ret = (char *)malloc(100 * sizeof(char)); //Cadena de retorno
	int ini_i = 0, i = 0; //indice inicial e indice relativo al campo
	int j = 0; //Indice del campo en la cadena leida
	while (tmp[i] != '\n') {

		if (tmp[i] == '\"') {
			//Pasa a ser 1 si son las primeras comillas leidas, 0 si son las segundas
			open_mark = 1 - open_mark;

			if (open_mark)
				ini_i = i + 1; //Aumenta el indice inicial para que no sean leidas las comillas
			i++;
			continue;
		}

		if (open_mark || tmp[i] != ',') { 
			//Comprueba si estan las comillas abiertas o si tmp[i] no es una coma
			
			if (k == j){
				ret[i - ini_i] = tmp[i];//Guarda el caracter en la cadena de retorno
			}
			i++;
			continue;
		}

		if (tmp[i] == ',') {
			if (k == j) { //Comprueba que el indice del campo coincida con el leido actualmente
				ret[i - ini_i] = '\0'; //Añade el caracter nulo
				return ret;
			}
			j++; //Se aumenta el indice del campo leido actualmente
			ini_i = i + 1;
		}

		i++;
	}

	if (k == j) { //Ultimo if seria para retornar en caso de que el campo a ser leido sea el ultimo
		ret[i - ini_i] = '\0';
		return ret;
	}

	return NULL;
}
//-----------------------------------------//

/*-------  -------*/
//-----------------------------------------//

/*-------  -------*/
//-----------------------------------------//

/*-------  -------*/
//-----------------------------------------//

/*-------  -------*/
//-----------------------------------------//

/*-------  -------*/
//-----------------------------------------//

/*-------  -------*/
//-----------------------------------------//

/*-------  -------*/
//-----------------------------------------//


//------------------MAIN-------------------------//

int main() {
	HashMap *productosTipo, 
	        *productosNombre, 
			*productosMarca;
	HashMap *Carritos;
	
	int option = 0; //Variable que decide la opcion del menun seleccionada

	cleanScreen();
	printf("Antes de empezar, siempre que se le pida datos, evite usar: \n");
	printf(" Vocales con tilde, procure no poner nunca tilde \n");
	printf(" La letra '%c', de ser necesaria utilice 'ny' \n", 164);
	printf(" El simbolo de inicio de pregunta %c, simplemente no lo ponga \n", 168);
	printf("\nPresione ENTER si comprendio que es lo que no pude usar  ");
	getchar();

	while (option != 11) { // Muestra el menu y actua segun la opcion seleccionada 
		cleanScreen();
		printf(" 1.- Importar productos\n");
		printf(" 2.- Exportar productos\n");
		printf(" 3.- Agregar producto\n");
		printf(" 4.- Buscar productos por tipo\n");
		printf(" 5.- Buscar productos por marca\n");
		printf(" 6.- Buscar producto por nombre\n");
		printf(" 7.- Mostrar todos los productos\n");
		printf(" 8.- Agregar al carrito\n");
		printf(" 9.- Eliminar del carrito\n");
		printf("10.- Concretar compra\n");
		printf("11.- Mostrar carritos de compra\n");
		printf("12.- Salir\n");
		printf("Introduzca una opci%cn: ", 162);
		scanf("%d", &option);
		getchar(); /* Importante poner getchar luego de cada scanf pues de lo 
        contrario un futuro scanf leera un '\n' y no recibira el input */

		switch (option) {// Entra a la opcion seleccionada para llevarla a cabo
		case 1:
            /*------- Importar Productis -------*/
			cleanScreen();
			break;
            //-----------------------------------------//
        case 2:
			/*------- Exportar productos -------*/
			cleanScreen();
			break;
			//-----------------------------------------//
        case 3:
            /*------- Agregar producto -------*/
			cleanScreen();
            
			//-----------------------------------------//
		case 4:
			/*------- Buscar productos por tipo -------*/
			cleanScreen();
			
			break;
			//-----------------------------------------//
		case 5:
			/*------- Buscar productos por marca -------*/
			cleanScreen();
			
			break;
			//-----------------------------------------//
		case 6:
			/*------- Buscar producto por nombre -------*/
			cleanScreen();
			
			break;
			//-----------------------------------------//
		case 7:
			/*------- Mostrar todos los productos -------*/
			cleanScreen();
			
			break;
			//-----------------------------------------//
		case 8:
			/*------- Agregar al carrito -------*/
			cleanScreen();
			break;
			//-----------------------------------------//
        case 9:
			/*------- Eliminar del carrito -------*/
			cleanScreen();
			break;
			//-----------------------------------------//
		case 10:
			/*------- Concretar compra -------*/
			cleanScreen();
			break;
			//-----------------------------------------//
		case 11:
			/*------- Mostrar carritos de compra -------*/
			cleanScreen();
			break;
			//-----------------------------------------//
        case 12:
			/*------- Salir -------*/
			cleanScreen();
			break;
			//-----------------------------------------//
        default:
			/*------- Opcion no valida -------*/
        	cleanScreen();
			printf("Opci%cn inv%clida", 162, 160);
			break;
			//-----------------------------------------//
        }
        
		if (option == 11) {
			break;
		}

		printf("\n\nPresione ENTER para volver al men%c  ",163);
		getchar();
	}

	return 0;
}

// Funciones que no estan en el siguiente formato:
/*------- Opcion del menu -------*/
//-----------------------------------------//
// Es porque la(s) funcion(s) necesarias 
// se crearon en la(s) funcion(es) de una opcion 
// anterior, lo mismo si falta en las funciones de la opcion
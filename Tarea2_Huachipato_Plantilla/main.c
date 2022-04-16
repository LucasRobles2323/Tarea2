#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "Map.h"

//------------------STRUCT-------------------------//

typedef struct {
	char *nombre;
	char *tipo;
	char *marca;
	unsigned int stock;
	unsigned int precioIndividual;
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

/*------- Copiar string en un nuevo espacio de memoria -------*/
char * _strdup(const char * str) {
    char * aux = (char *)malloc(strlen(str) + 1);
    strcpy(aux, str);
    return aux;
}
//-----------------------------------------//

/*
  función para comparar claves de tipo string
  retorna 1 si son iguales
*/
int is_equal_string(void * key1, void * key2) {
    if(strcmp((char*)key1, (char*)key2)==0) return 1;
    return 0;
}

/*
  función para comparar claves de tipo string
  retorna 1 si son key1<key2
*/
int lower_than_string(void * key1, void * key2) {
    if(strcmp((char*)key1, (char*)key2) < 0) return 1;
    return 0;
}

/*
  función para comparar claves de tipo int
  retorna 1 si son iguales
*/
int is_equal_int(void * key1, void * key2) {
    printf("%d\n\n", key2);
    if(*(int*)key1 == *(int*)key2) return 1;
    return 0;
}

/*
  función para comparar claves de tipo int
  retorna 1 si son key1<key2
*/
int lower_than_int(void * key1, void * key2) {
    if(*(int*)key1 < *(int*)key2) return 1;
    return 0;
}

/*------- Leer Archivo -------*/
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

Producto *crearProducto(char *nombre, char *tipo, char *marca, int stock, int precio) {
    // Guarda los datos recibidos en una struct de cancion con lo que corresponde y retorna la cancion 

	Producto *new = (Producto *)malloc(sizeof(Producto));
	new->nombre = strdup(nombre);
	new->tipo = strdup(tipo);
	new->marca =  strdup(marca);
	new->stock = (unsigned int)stock;
	new->precioIndividual = (unsigned int)precio;

	return new;
}

int leerArchivoCanciones(char *nombreArchivo, Map* Nombre)
{ // Abre un archivo especifico y guarda sus datos
    FILE *F = fopen(nombreArchivo, "r"); // Abre el archivo con el nombre recibido en modo lectura
    
	if (!F){ return 1;}// Si no existe el archivo, cierra el programa
	
	Producto *product;
	char linea[1024]; // Cadena de caracter para guardar una linea del archivo

	char *nombre, *tipo, *marca;
	int stock;
	int precioIndividual;

	while (fgets(linea, 1023, F) != NULL) { 
        // Recorre el archivo leyendo linea por linea
        // guardando los datos de cada linea en listas
		
        // Separa los datos de la linea leida y los guarda en variables correspondientes
        nombre = get_csv_field(linea, 0);
		marca = get_csv_field(linea, 1);
		tipo = get_csv_field(linea, 2);
		stock = atoi(get_csv_field(linea, 3));
		precioIndividual = atoi(get_csv_field(linea, 4));

		// Se crea el producto con las variables leidas de la string 'linea'
		product = crearProducto(nombre, tipo, marca, stock, precioIndividual);
		
		if(searchMap(Nombre, product->nombre) == NULL){
			insertMap(Nombre, product->nombre, product);
		}
		else{
			Producto* cambiarStock = searchMap(Nombre, product->nombre);
			cambiarStock->stock += product->stock;
		}
	}
	
	fclose(F);// Se cierra el archivo
	return 0;
}
//-----------------------------------------//

/*------- Guardar Productos en Mapa -------*/
List *crearLista(Producto *Save){
	List *new = createList();
	pushBack(new, Save);
	return new;
}

void crearMapasFaltantes(Map* general, Map* type, Map* brand){
	Producto *save = firstMap(general);
	List *newList;
	while(save != NULL){
		if(searchMap(type, save->tipo) == NULL){
			newList = crearLista(save);
			insertMap(type, save->tipo, newList);
		}
		else{
			newList = searchMap(type, save->tipo);
			pushBack(newList, save);
		}

		if(searchMap(brand, save->marca) == NULL){
			newList = crearLista(save);
			insertMap(brand, save->marca, newList);
		}
		else{
			newList = searchMap(brand, save->marca);
			pushBack(newList, save);
		}
		save = nextMap(general);
	}
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

/*------- Imprimir Producto -------*/
void imprimirProducto(Producto* dato){
	printf("Nombre: %s\n", dato->nombre);
	printf("  Tipo: %s\n", dato->tipo);
	printf(" Marca: %s\n", dato->marca);
	printf(" Stock: %u\n", dato->stock);
	printf("Precio: %u\n", dato->precioIndividual);
}
//-----------------------------------------//


//------------------MAIN-------------------------//

int main() {
	Map *nombre, *tipo, *marca, *carritos;
	nombre = createMap(is_equal_string);
    setSortFunction(nombre,lower_than_string);
	tipo = createMap(is_equal_string);
    setSortFunction(tipo,lower_than_string);
	marca = createMap(is_equal_string);
    setSortFunction(marca,lower_than_string);
	carritos = createMap(is_equal_string);
    setSortFunction(carritos,lower_than_string);

	int option = 0; //Variable que decide la opcion del menun seleccionada

	printf("\n\nAntes de empezar, siempre que se le pida datos, evite usar: \n");
	printf(" Vocales con tilde, procure no poner nunca tilde \n");
	printf(" La letra '%c', de ser necesaria utilice 'ny' \n", 164);
	printf(" El simbolo de inicio de pregunta %c, simplemente no lo ponga \n", 168);
	printf("\nPresione ENTER si comprendio que es lo que no pude usar  ");
	getchar();

	while (option != 12) { // Muestra el menu y actua segun la opcion seleccionada 
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

		printf("\n");

		switch (option) {// Entra a la opcion seleccionada para llevarla a cabo
		case 1:
            /*------- Importar Productis -------*/
			printf("Introduzca el nombre del archivo (max 30 caracteres): ");
			char nombreArchivo[31];

			scanf("%s", nombreArchivo);
			getchar();

			int errorArchivo = leerArchivoCanciones(nombreArchivo, nombre);

			crearMapasFaltantes(nombre, tipo, marca);

			if (errorArchivo)// Envia un mensaje con la situacion que corresponda
				printf("Ha ocurrido un error al cargar el archivo o no existe el archivo");
			else
				printf("Archivo Cargado");
			break;
            //-----------------------------------------//
        case 2:
			/*------- Exportar productos -------*/
			break;
			//-----------------------------------------//
        case 3:
            /*------- Agregar producto -------*/
            
			//-----------------------------------------//
		case 4:
			/*------- Buscar productos por tipo -------*/
			
			break;
			//-----------------------------------------//
		case 5:
			/*------- Buscar productos por marca -------*/
			
			break;
			//-----------------------------------------//
		case 6:
			/*------- Buscar producto por nombre -------*/
			
			break;
			//-----------------------------------------//
		case 7:
			/*------- Mostrar todos los productos -------*/
			printf("A continuacion se imprimiran los datos de 10 en 10 (cada 10 mostrado, presione ENTER)\n\n");
			getchar();
			int cont = 0;
			Producto *prod = firstMap(nombre);
			while (prod !=NULL)
			{
				imprimirProducto(prod);
				printf("\n");
				cont++;
				if(cont == 10){
					cont = 0;
					getchar();
				}
				prod = nextMap(nombre);
			}

			/*List *prod = firstMap(tipo);
			Producto *imprime;
			while (prod != NULL)
			{
				imprime = firstList(prod);
				while (imprime != NULL)
				{
					imprimirProducto(imprime);
					cont++;
					printf("\n");
					if(cont == 10){
						cont = 0;
						getchar();
					}
					imprime = nextList(prod);
				}
				prod = nextMap(tipo);
			}*/
			
			/*List *prod = firstMap(marca);
			Producto *imprime;
			while (prod != NULL)
			{
				imprime = firstList(prod);
				while (imprime != NULL)
				{
					imprimirProducto(imprime);
					cont++;
					printf("\n");
					if(cont == 10){
						cont = 0;
						getchar();
					}
					imprime = nextList(prod);
				}
				prod = nextMap(marca);
			}*/
			break;
			//-----------------------------------------//
		case 8:
			/*------- Agregar al carrito -------*/
			break;
			//-----------------------------------------//
        case 9:
			/*------- Eliminar del carrito -------*/
			break;
			//-----------------------------------------//
		case 10:
			/*------- Concretar compra -------*/
			break;
			//-----------------------------------------//
		case 11:
			/*------- Mostrar carritos de compra -------*/
			
			break;
			//-----------------------------------------//
        case 12:
			/*------- Salir -------*/
			break;
			//-----------------------------------------//
        default:
			/*------- Opcion no valida -------*/
			printf("Opci%cn inv%clida", 162, 160);
			break;
			//-----------------------------------------//
        }
        
		if (option == 12) {
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
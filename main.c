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



/*------- Crear Mapa de String -------*/
Map *crearMapaString() {
    Map *map = createMap(is_equal_string);
    setSortFunction(map,lower_than_string);
	return map;
}
//-----------------------------------------//

/*------- Advertencia -------*/
void Advertencia() {
    printf("\n\nAntes de empezar, siempre que se le pida datos, evite usar: \n");
	printf(" Vocales con tilde, procure no poner nunca tilde \n");
	printf(" La letra '%c', de ser necesaria utilice 'ny' \n", 164);
	printf(" El simbolo de inicio de pregunta %c, simplemente no lo ponga \n", 168);
}
//-----------------------------------------//

/*------- Presionar Enter -------*/
void pressEnter(){
	printf("\n\nPresione ENTER para volver al men%c",163);
	getchar();
	printf("\n\n");
}
//-----------------------------------------//

/*------- Mostrar Menú -------*/
void MostrarMenu(){
	printf("\n\n");
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
}

/*------- Copiar string en un nuevo espacio de memoria -------*/
char * _strdup(const char * str) {
    char * aux = (char *)malloc(strlen(str) + 1);
    strcpy(aux, str);
    return aux;
}
//-----------------------------------------//

/*------- Leer Archivo -------*/
char *get_csv_field(char *tmp, int k) {
	char *ret = (char *)malloc(100 * sizeof(char)); //Cadena de retorno
	int ini_i = 0, i = 0; //indice inicial e indice relativo al campo
	int j = 0; //Indice del campo en la cadena leida
	int cont = 0; //Si es 0, es el primer caracter del string
	while (tmp[i] != '\n') {
		
		if (tmp[i] != ',') { 
			//Comprueba si tmp[i] no es una coma
			if (k == j){
				if(cont == 0){
					ret[i - ini_i] = toupper(tmp[i]);
					//Guarda el caracter en la cadena de retorno en mayuscula
					cont = 1;
				}
				else{
					ret[i - ini_i] = towlower(tmp[i]);
					//Guarda el caracter en la cadena de retorno en minuscula
				}
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

//	/*------- Guardar Productos en Mapa -------*/
List *crearLista(Producto *Save){
	List *new = createList();
	pushBack(new, Save);
	return new;
}

void addProductoaMapa(Map *name, Map *type, Map *brand, Producto *product){
	List *liste;
	if ((searchMap(name, product->nombre)) == NULL)
	{
		insertMap (name, product->nombre, product);

		if ((searchMap(type, product->tipo)) == NULL){
			liste = crearLista(product);
			insertMap(type, product->tipo, liste);
		}
		else{
			liste = searchMap(type, product->tipo);
			pushBack(liste, product);
		}

		if ((searchMap(brand, product->marca)) == NULL){
			liste = crearLista(product);
			insertMap(brand, product->marca, liste);
		}
		else{
			liste = searchMap(brand, product->marca);
			pushBack(liste, product);
		}
	}
	else{

		Producto *cambiarStock = searchMap (name, product->nombre);
		cambiarStock->stock += product->stock;

	}
}
//	//-----------------------------------------//

int leerArchivoCanciones(char *nombreArchivo, Map* Nombre, Map *Tipo, Map* Marca)
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
		
		addProductoaMapa(Nombre, Tipo, Marca, product);
	}
	
	fclose(F);// Se cierra el archivo
	return 0;
}
//-----------------------------------------//

/*----------------- OPCIóN 1: Importar Producto -----------------*/
void ImportarProductos(Map *name, Map *type, Map *brand){
	printf("Introduzca el nombre del archivo (max 30 caracteres): ");
	char nombreArchivo[31];
	scanf("%s", nombreArchivo);
	getchar();

	int errorArchivo = leerArchivoCanciones(nombreArchivo, name, type, brand);

	if (errorArchivo)// Envia un mensaje con la situacion que corresponda
	{printf("Ha ocurrido un error al cargar el archivo o no existe el archivo");}
	else
	{printf("Productos Exportados Exitosamente");}
}
//-------------------------------------------------------------//




/*------- Crear o Sobreescribir Archivo -------*/
void sobreescribirArchivo(char *Archive, Map *mapa) {
    //Funcion que crea un archivo o sobreescribe un archivo

	FILE *file = fopen(Archive, "w");// Abre el archivo con el nombre recibido en modo escritura
	Producto *onlyProduct = firstMap(mapa);

	while (onlyProduct != NULL) { 
        // Recorre todas las canciones de la lista general
		// y las guarda en el archivo una por una
        
        /*------- Guarda los datos de un producto en una linea -------*/
        fprintf(file, "%s,", onlyProduct->nombre);

		fprintf(file, "%s,", onlyProduct->marca);

		fprintf(file, "%s,", onlyProduct->tipo);

		fprintf(file, "%d,", onlyProduct->stock);

		fprintf(file, "%d\n", onlyProduct->precioIndividual);
        

		onlyProduct = nextMap(mapa);
	}

	fclose(file);// Cierra el archivo
}
//-----------------------------------------//

/*----------------- OPCIóN 2: Exportar Producto -----------------*/
void ExportarProductos(Map *name){
	printf("Introduzca el nombre del archivo donde desea guardar los "
			"datos (max 30 caracteres): ");
	char nameArchive[31];
	scanf("%s", nameArchive);
	getchar();

	sobreescribirArchivo(nameArchive, name);

	printf("\n\nProductos Exportados Exitosamente");
}
//-------------------------------------------------------------//




/*----------------- OPCIóN 3: Aggregar Producto -----------------*/
void leerProducto (Map *nombre_map, Map *tipo_map, Map *marca_map){
	Producto *produkt;
	char nombre[101];
	char tipo[101];
	char marca[101];
	unsigned int stock;
	unsigned int precio;

	printf("Introduzca el nombre del producto: ");       
	scanf("%[0-9a-zA-Z ,-]", nombre);
	getchar();
	//char *name = get_csv_field(nombre ,0);

	printf("Introduzca el nombre del tipo del producto: ");
	scanf("%[0-9a-zA-Z ,-]", tipo);
	getchar();
	//char *type = get_csv_field(tipo ,0);

	printf("Introduzca el nombre de la marca del producto: ");
	scanf("%[0-9a-zA-Z ,-]", marca);
	getchar();
	//char *brand = get_csv_field(marca ,0);

	printf("Introduzca el stock del producto: ");
	scanf("%d", &stock);
	getchar();

	printf("Introduzca el precio del producto: ");
	scanf("%d", &precio);
	getchar();

	printf("\nLa informacion  del producto escrito: \n");
	printf("Nombre: %s\n", get_csv_field(nombre, 0));
	printf("Tipo: %s\n", get_csv_field(tipo, 0));
	printf("Marca: %s\n", get_csv_field(marca, 0));
	printf("Stock: %d\n", stock);
	printf("Precio: %d\n", precio);
	printf("Ingrese ENTER para confirmar o 'n' para cancelar y volver "
				"al menu: ");

	if (getchar() != 'n') {
		produkt = crearProducto(get_csv_field(nombre, 0), get_csv_field(tipo, 0), 
		                        get_csv_field(marca, 0), stock, precio);
		addProductoaMapa(nombre_map, tipo_map, marca_map, produkt);
		printf("Producto guardada exitosamente");
	}
}
//-------------------------------------------------------------//

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
	printf(" Marca: %s\n", dato->marca);
	printf("  Tipo: %s\n", dato->tipo);
	printf(" Stock: %u\n", dato->stock);
	printf("Precio: %u\n", dato->precioIndividual);
}
//-----------------------------------------//

/*----------------- OPCIÓN 7: Mostrar Mapa -----------------*/
void ImprimirMapaSeleccionado(int opt, Map *name_map, Map *type_map, Map *brand_map){
	printf("A continuacion se imprimiran los datos de 10 en 10 (cada 10 mostrado, presione ENTER)\n\n");
	getchar();

	List *prodList;
	Producto *prod;
	int cont = 0;
	switch (opt)
	{
	case 1:
		prod = firstMap(name_map);
		while (prod !=NULL)
		{
			imprimirProducto(prod);
			printf("\n");
			cont++;
			if(cont == 10){
				cont = 0;
				getchar();
			}
			prod = nextMap(name_map);
		}
		break;
	
	case 2:
		prodList = firstMap(type_map);
		while (prodList != NULL)
		{
			prod = firstList(prodList);
			while (prod != NULL)
			{
				imprimirProducto(prod);
				cont++;
				printf("\n");
				if(cont == 10){
					cont = 0;
					getchar();
				}
				prod = nextList(prodList);
			}
			prodList = nextMap(type_map);
		}
		break;
	case 3:
		prodList = firstMap(brand_map);
		while (prodList != NULL)
		{
			prod = firstList(prodList);
			while (prod != NULL)
			{
				imprimirProducto(prod);
				cont++;
				printf("\n");
				if(cont == 10){
					cont = 0;
					getchar();
				}
				prod = nextList(prodList);
			}
			prodList = nextMap(brand_map);
		}
		break;
	default:
		break;
	}
}

void ImprimirMapa(int opt, Map *nameMap, Map *typeMap, Map *brandMap){
	printf("1.- Imprimir por Nombre\n");
	printf("2.- Imprimir por Tipo\n");
	printf("3.- Imprimir por Marca\n");
	while(true)
	{
		printf("Introduzca una opci%cn valida: ", 162);
		scanf("%d", &opt);
		if (opt == 1 || opt == 2 || opt == 3)
		{break;}
		else
		{
			printf("\nOpci%cn invalida\n", 162);
		}
	}
	ImprimirMapaSeleccionado(opt, nameMap, typeMap, brandMap);
	
	// ponga 1 para imprimir por nombre
	// ponga 2 para imprimir por tipo
	// ponga 3 para imprimir por marca
}
//-------------------------------------------------------------//


//------------------MAIN-------------------------//

int main() {
	Map *nombre = crearMapaString();
	Map *tipo = crearMapaString();
	Map *marca = crearMapaString();
	Map *carritos = crearMapaString();

	int option = 0; //Variable que decide la opcion del menun seleccionada

	Advertencia();
	pressEnter();

	while (option != 12) { // Muestra el menu y actua segun la opcion seleccionada 
		MostrarMenu();
		
		scanf("%d", &option);
		getchar(); /* Importante poner getchar luego de cada scanf pues de lo 
        contrario un futuro scanf leera un '\n' y no recibira el input */

		printf("\n\n");

		switch (option) {// Entra a la opcion seleccionada para llevarla a cabo
		case 1:
            /*------- Importar Productos -------*/
			ImportarProductos(nombre, tipo, marca);
			break;
            //-----------------------------------------//
        case 2:
			/*------- Exportar productos -------*/
			ExportarProductos(nombre);
			break;
			//-----------------------------------------//
        case 3:
            /*------- Agregar producto -------*/
			leerProducto (nombre, tipo, marca);
            break;
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
			ImprimirMapa(0, nombre, tipo, marca);
			
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

		pressEnter();
		
	}

	return 0;
}

// Funciones que no estan en el siguiente formato:
/*------- Opcion del menu -------*/
//-----------------------------------------//
// Es porque la(s) funcion(s) necesarias 
// se crearon en la(s) funcion(es) de una opcion 
// anterior, lo mismo si falta en las funciones de la opcion
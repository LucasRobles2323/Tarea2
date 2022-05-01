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
	// Crea y retorna un mapa adecuado para usar string como claves.
    Map *map = createMap(is_equal_string);
    setSortFunction(map,lower_than_string);
	return map;
}
//-----------------------------------------//

/*------- Advertencia -------*/
void Advertencia() {
	// Imprime una advertencia en pantalla antes de iniciar.
    printf("\n\nAntes de empezar, siempre que se le pida datos, evite usar: \n");
	printf(" Vocales con tilde, procure no poner nunca tilde \n");
	printf(" La letra '%c', de ser necesaria utilice 'ny' \n", 164);
	printf(" El simbolo de inicio de pregunta %c, simplemente no lo ponga \n", 168);
}
//-----------------------------------------//

/*------- Presionar Enter -------*/
void pressEnter(int opcion){
	// Funcion que detiene temporalmente el programa 
	// hasta que el usuario presione enter.
	printf("\n\nPresione ENTER");
	if(opcion == 1){printf(" para volver al men%c",163);}
	getchar();
	printf("\n\n");
}
//-----------------------------------------//

/*------- Mostrar Menú -------*/
void MostrarMenu(){
	//Muestra las opciones del menu y un mensaje para que seleccione una opcion,
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
char * _strdup(const char * str){
	// Recibe un string y la copia en una string nueva con una direccion de 
	// memoria nueva y retorna la nueva string.
    char * aux = (char *)malloc(strlen(str) + 1);
    strcpy(aux, str);
    return aux;
}
//-----------------------------------------//


//**************************  OPCIÓN 1  ***********************//

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
    // Guarda los datos recibidos en una struct de Producto con lo que corresponde
	// y retorna el producto 

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
	// Crea una lista y guarda el dato enviado en la ultima posicion de la lista
	// para despues retornar la lista
	List *new = createList();
	pushBack(new, Save);
	return new;
}

void addProductoaMapa(Map *name, Map *type, Map *brand, Producto *product){
	// Agrega el producto recibido a los 3 mapas recibidos
	List *liste; //variable para guardar las listas de los mapas
	
	if ((searchMap(name, product->nombre)) == NULL) // revisa si el producto existe o no
	{
		//Si el producto no existe se inserta en los mapas

		insertMap (name, product->nombre, product); // Se inserta en el mapa de nombres
		
		// Revisa si existe el tipo del producto en el mapa de tipos
		if ((searchMap(type, product->tipo)) == NULL){
			// si no existe, se crea una lista, se guarda el producto en la lista
			// y la lista se guarda en el mapa con la clave de el tipo del producto
			liste = crearLista(product);
			insertMap(type, product->tipo, liste);
		}
		else{
			// si existe, se guarda al final de la lista en el tipo del producto
			liste = searchMap(type, product->tipo);
			pushBack(liste, product);
		}

		// Revisa si existe marca del producto en el mapa de marcas
		if ((searchMap(brand, product->marca)) == NULL){
			// si no existe, se crea una lista, se guarda el producto en la lista
			// y la lista se guarda en el mapa con la clave de la marca del producto
			liste = crearLista(product);
			insertMap(brand, product->marca, liste);
		}
		else{
			// si existe, se guarda al final de la lista en la marca del producto
			liste = searchMap(brand, product->marca);
			pushBack(liste, product);
		}
	}
	else{
		// Si el producto existe, simplemente se aumentara su stock segun corresponda
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

	// Variables para guardar los datos de una linea
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

		if(stock > 0 && precioIndividual > 0){
			// Se crea el producto con las variables leidas de la string 'linea'
			product = crearProducto(nombre, tipo, marca, stock, precioIndividual);
		
			// Se agrega el producto a los 3 mapsa de nombre, tipo, marca
			addProductoaMapa(Nombre, Tipo, Marca, product);
		}
	}
	
	fclose(F);// Se cierra el archivo
	return 0;
}
//-----------------------------------------//

/*----------------- OPCIÓN 1: Importar Producto -----------------*/
void ImportarProductos(Map *name, Map *type, Map *brand){
	// Realiza la operacion correspondiente a la opcion 1 del menu
	// , es decir, importa los productos de un archivo.
	printf("Introduzca el nombre del archivo (max 30 caracteres): ");
	char nombreArchivo[31];
	scanf("%s", nombreArchivo);
	getchar();

	int errorArchivo = leerArchivoCanciones(nombreArchivo, name, type, brand);

	if (errorArchivo)// Envia un mensaje con la situacion que corresponda
	{printf("\n\nHa ocurrido un error al cargar el archivo o no existe el archivo");}
	else
	{printf("\n\nProductos Importados Exitosamente");}
}
//-------------------------------------------------------------//

//**************************************************************//



//**************************  OPCIÓN 2  ***********************//

/*------- Crear o Sobreescribir Archivo -------*/
void sobreescribirArchivo(char *Archive, Map *mapa) {
    //Funcion que crea un archivo o sobreescribe un archivo

	FILE *file = fopen(Archive, "w");// Abre el archivo con el nombre recibido en modo escritura
	Producto *onlyProduct = firstMap(mapa);

	while (onlyProduct != NULL) { 
        // Recorre todas las canciones de la lista general
		// y las guarda en el archivo una por una
        
        if(onlyProduct->stock > 0 && onlyProduct->precioIndividual > 0){
        	/*------- Guarda los datos de un producto en una linea -------*/
        	fprintf(file, "%s,", onlyProduct->nombre);

			fprintf(file, "%s,", onlyProduct->marca);

			fprintf(file, "%s,", onlyProduct->tipo);

			fprintf(file, "%d,", onlyProduct->stock);

			fprintf(file, "%d\n", onlyProduct->precioIndividual);
		}
	}

	fclose(file);// Cierra el archivo
}
//-----------------------------------------//

/*----------------- OPCIÓN 2: Exportar Producto -----------------*/
void ExportarProductos(Map *name){
	// Realiza la operacion correspondiente a la opcion 2 del menu
	// , es decir, Emporta los productos en un archivo.
	printf("Introduzca el nombre del archivo donde desea guardar los "
			"datos (max 30 caracteres): ");
	char nameArchive[31];
	scanf("%s", nameArchive);
	getchar();

	sobreescribirArchivo(nameArchive, name);

	printf("\n\nProductos Exportados Exitosamente");
}
//-------------------------------------------------------------//

//**************************************************************//



//**************************  OPCIÓN 3  ***********************//

/*----------------- OPCIÓN 3: Agregar Producto -----------------*/
void mayuscula (char *ptrCadena){
    
	int verificador = 0;
	//Recorre la palabra hasta que encuentra la primera letra
    bool dentro_de_palabra = false; // Al principio esta fuera
    for (int i = 0; ptrCadena[i] != '\0'; i++)
    {
        if (ptrCadena[i] == ' ')
        {
            dentro_de_palabra = false; // Fuera de palabra
        }
        else
        {
            if (dentro_de_palabra)
            {
                // Ya estabamos dentro de una palabra
                ptrCadena[i] = tolower(ptrCadena[i]);
            }
            else
            {
               if (verificador == 0){

				   dentro_de_palabra = true;
                   ptrCadena[i] = toupper(ptrCadena[i]);
				   verificador++;
			   }

			   dentro_de_palabra = true;
			   ptrCadena[i] = tolower(ptrCadena[i]);
            }
        }
    }
}

void leerProducto (Map *nombre_map, Map *tipo_map, Map *marca_map){
	// Realiza la operacion correspondiente a la opcion 3 del menu
	// , es decir, guarda un producto ingresado por el usuario
	Producto *produkt;
	char nombre[101];
	char tipo[101];
	char marca[101];
	unsigned int stock;
	unsigned int precio;
    
	//aqui se le pregunta los datos al usuario
	printf("Introduzca el nombre del producto: ");       
	scanf("%[0-9a-zA-Z ,-]", nombre);
	getchar();

	printf("Introduzca el nombre del tipo del producto: ");
	scanf("%[0-9a-zA-Z ,-]", tipo);
	getchar();

	printf("Introduzca el nombre de la marca del producto: ");
	scanf("%[0-9a-zA-Z ,-]", marca);
	getchar();

	printf("Introduzca el stock del producto (Colocar numero mayor a 0): ");
	scanf("%d", &stock);
	getchar();

	printf("Introduzca el precio del producto (Colocar numero mayor a 0): ");
	scanf("%d", &precio);
	getchar();

    if (stock <= 0 || precio <= 0){
		printf ("Siga las instrucciones porfavor\n");
		printf ("Tanto el stock como el precio tienen que ser mayores que 0\n");
		return;
	}
    

	//aqui se le coloca mayuscula a la primera letra de la palabra
    mayuscula (nombre);
	mayuscula(tipo);
	mayuscula(marca);
    
	//Se muestra por pantalla los datos colocados por el usuario
	printf("\nLa informacion  del producto escrito: \n");
	printf("Nombre: %s\n",nombre);
	printf("Tipo: %s\n", tipo);
	printf("Marca: %s\n", marca);
	printf("Stock: %d\n", stock);
	printf("Precio: %d\n", precio);
	printf("Ingrese ENTER para confirmar o 'n' para cancelar");
	
	// El usuario decide si guardar o no el producto con los datos que ingreso
	if (getchar() != 'n') { 
		produkt = crearProducto(nombre, tipo, marca, stock, precio);
		addProductoaMapa(nombre_map, tipo_map, marca_map, produkt);
		printf("Producto guardado exitosamente en el almacen");
		return;
	}

	printf ("No se guardo el producto al almacen");
}
//-------------------------------------------------------------//

//**************************************************************//



//**************************  OPCIÓN 4, 5 ,6  ***********************//

/*------- Imprimir Producto -------*/
void imprimirProducto(Producto* dato){
	if(dato->stock <= 0 || dato->precioIndividual <= 0){return;}
	// Imprime los datos de un producto
	printf("Nombre: %s\n", dato->nombre);
	printf(" Marca: %s\n", dato->marca);
	printf("  Tipo: %s\n", dato->tipo);
	printf(" Stock: %u\n", dato->stock);
	printf("Precio: %u\n", dato->precioIndividual);
}
//-----------------------------------------//

/*------- Comparar cadenas de caracteres -------*/
int compare_strings(char cadena1[101], char *cadena2)
{   size_t largo = sizeof(cadena2)/sizeof(char); // SIRVE PARA ENCONTRAR EL LARGO DE LA CADENA DINAMICA
    for(int i = 0; i < largo; i++){
		if (cadena1[i] != cadena2[i]) {return 1;}
		}return 0;
}
//-----------------------------------------//

//----------- Búsqueda tipo -------------//

void BusquedaTipo(char* prod, Map* tipo)
{
	Producto* producto; int cont = 0; int cont_invalid = 0;
	prod = get_csv_field(prod, 0);
	
	List* prodList = (List*) searchMap(tipo, prod);
	producto = firstList(prodList);
			while(producto != NULL)
			{
				
				if(compare_strings(prod, producto->tipo) == 0)
				{

					if(cont == 0){printf("Productos econtrados respecto al tipo '%s' : \n \n", producto->tipo);}
					if(producto->stock > 0 && (producto->precioIndividual) > 0){
					imprimirProducto(producto); printf("\n");} 
					else {printf("\n Producto de nombre %s, precio invalido o stock vacio. Intente ingresar un producto con existencias. \n", producto->nombre);
					cont_invalid++;}
					producto = nextList(prodList);
					cont++;
					
				}	
				else
				{
					producto = nextList(prodList);
				}
			}
		if(cont_invalid == 0){
		if(cont == 0 || tipo == NULL){printf("No se fue posible encontrar producto/s valido/s"); return;}}

}

//-----------------------------------------//


/*------- Busqueda marca -------*/
void BusquedaMarca(char* prod, Map* marca)
{
	Producto* producto; int cont = 0; int cont_invalid = 0;
	prod = get_csv_field(prod, 0);
	List* prodList = (List*) searchMap(marca, prod);
	producto = firstList(prodList);
	
	
			producto = firstList(prodList);
			while(producto != NULL)
			{
				
				if(compare_strings(prod, producto->marca) == 0)
				{
					if(cont == 0){printf("Productos econtrados respecto a la marca '%s' : \n \n", producto->marca);}
					if(producto->stock > 0 && (producto->precioIndividual) > 0){
					imprimirProducto(producto); printf("\n");}
					else {printf("\n Producto de nombre %s, precio invalido o stock vacio. Intente ingresar un producto con existencias. \n", producto->nombre);
					cont_invalid++;}
					producto = nextList(prodList);
					cont++;
				}	
				else
				{
					producto = nextList(prodList);
				}
			}
		if(cont_invalid == 0){
		if(cont == 0 || marca == NULL){printf("No se fue posible encontrar producto/s valido/s"); return;}}

}

//-----------------------------------------//


/*------- 	Busqueda nombre -------*/
void BusquedaNombre(char* prod, Map* nombre)
{
	int cont_invalid = 0;
	prod = get_csv_field(prod, 0);
	Producto* producto = (Producto*) searchMap(nombre, prod);
	
		
				if(compare_strings(prod, producto->nombre) == 0)
				{
					
					printf("Producto econtrado respecto al nombre '%s': \n \n", producto->nombre);
					if(producto->stock > 0 && (producto->precioIndividual) > 0){
					imprimirProducto(producto); printf("\n");
					} else {printf("\n Producto de nombre %s, precio invalido o stock vacio. Intente ingresar un producto con existencias. \n", producto->nombre);
					 cont_invalid++;}
					return;
				}	
		
		if(cont_invalid == 0){
		printf("No se a encontrado el producto producto especificado"); return;}
		
}

/*------- 	Opción 4,5,6: Búsqueda -------*/
void BuscarProducto(Map *tipo, Map *nombre, Map* marca, int opt)
{
	char prod[101];
	switch(opt)
	{
		case 4:
			printf("Ingrese el producto que desea buscar por tipo: ");
			scanf("%[0-9a-zA-Z ,-]", prod);
			getchar();
			BusquedaTipo(prod, tipo);
			break;
		case 5:
			printf("Ingrese el producto que desea buscar por marca: ");
			scanf("%[0-9a-zA-Z ,-]", prod);
			getchar();
			BusquedaMarca(prod, marca);
			break;
		case 6:
			printf("Ingrese el producto que desea buscar por nombre: ");
			scanf("%[0-9a-zA-Z ,-]", prod);
			getchar();
			BusquedaNombre(prod, nombre);
			break;
	}
}
//-----------------------------------------//

//**************************************************************//




//**************************  OPCIÓN 7  ***********************//

/*----------------- OPCIÓN 7: Mostrar Mapa -----------------*/
void ImprimirMapaSeleccionado(int opt, Map *name_map, Map *type_map, Map *brand_map){
	printf("\n\nA continuacion se imprimiran los datos de 10 en 10 (cada 10 mostrado, presione ENTER)\n\n");
	getchar();
	
	// Variables que llegaran a ser necesarias dependiendo de la opt recibida.
	List *prodList;
	Producto *prod;
	int cont = 0;


	switch (opt)
	{
	case 1:
		// Recorre el mapa nombre e imprime cada producto en el mapa
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
		// Recorre el mapa tipo, en cada posicion recorre 
		// la lista guardada e imprime cada producto en la lista
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
		// Recorre el mapa marca, en cada posicion recorre la 
		// lista guardada e imprime cada producto en la lista
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
		printf("No existe el mapa seleccionado\n\n");
		break;
	}
}

void ImprimirMapa(int opt, Map *nameMap, Map *typeMap, Map *brandMap){
	// Realiza la operacion correspondiente a la opcion 7 del menu
	// , es decir, muestra todos los productos guardados por el codigo.

	// Nos permite seleccionar como imprimir los productos antes de imprimirlos 
	while(true)
	{
		printf("\n\n\n1.- Imprimir por Nombre\n");
		printf("2.- Imprimir por Tipo\n");
		printf("3.- Imprimir por Marca\n");
		printf("Introduzca una opci%cn valida: ", 162);
		scanf("%d", &opt);
		if (opt == 1 || opt == 2 || opt == 3)
		{break;}
		else
		{
			printf("\nOpci%cn invalida\n", 162);
		}
	}

	// Imprime el mapa de acuerdo a la opcion seleccionada
	ImprimirMapaSeleccionado(opt, nameMap, typeMap, brandMap);
}
//-------------------------------------------------------------//

//**************************************************************//



//**************************  OPCIÓN 8  ***********************//

/*------- Opcion 8: Agregar producto a un carrito -------*/
void agregarProdCarrito(Map *mapCarritos, Map *mapNombre)
{
	char nameCarrito[101], nameProducto[101];
	int cantidad;

	printf("Introduzca nombre del carrito: ");
	scanf("%[0-9a-zA-Z ,-]", nameCarrito);
	getchar();
	char *nombreCarrito = get_csv_field(nameCarrito, 0);

	printf("Introduzca nombre del producto a agregar: ");
	scanf("%[0-9a-zA-Z ,-]", nameProducto);
	getchar();
	char *nombreProducto = get_csv_field(nameProducto, 0);

	printf("Introduzca cantidad a agregar: ");
	scanf("%d", &cantidad);
	getchar();

	//Busqueda / Creacion carrito.
	Carrito *carrito = (Carrito *) searchMap(mapCarritos, nombreCarrito);
	if (!carrito)
	{
		printf("Carrito no encontrado, creando uno nuevo...\n");

		carrito = (Carrito *) malloc(sizeof(Carrito));

		carrito->nombreCarrito = (char *) malloc(strlen(nombreCarrito) + 1);
		strcpy(carrito->nombreCarrito, nombreCarrito);

		carrito->carro = createList();
		carrito->productosComprar = 0;
		carrito->precioPagar = 0;

		insertMap(mapCarritos, nombreCarrito, carrito);
	}

	//Creacion de variable Vendido
	Vendido *venta = (Vendido *) malloc(sizeof(Vendido));

	venta->comprado = (Producto *) searchMap(mapNombre, nombreProducto);
	if(!venta->comprado)
	{
		printf("No se ha encontrado producto con el nombre indicado\n");
		free(venta); //Se libera venta debido al error 
		return;
	}

	// Revisa si hay stock suficiente del producto
	venta->cantidadComprada = cantidad;
	if(venta->cantidadComprada > venta->comprado->stock)
	{
		printf("La cantidad ingresada es mayor al stock del producto\n");
		free(venta);
		return;
	}

	venta->precioTotal = venta->comprado->precioIndividual * cantidad;

	//Se añade venta al carrito
	pushBack(carrito->carro, venta);
	//carrito->productosComprar++; Esto es por si productosComprar cuenta solo los prod diferentes
	carrito->productosComprar += cantidad;
	carrito->precioPagar += venta->precioTotal;

	printf("Agregado %s a carrito %s exitosamente.\n", nombreProducto, nombreCarrito);
}
//-----------------------------------------//

//**************************************************************//



//**************************  OPCIÓN 9  ***********************//

/*------- Opción 9: Eliminar Producto de un carrito  -------*/
void eliminarProdCarrito(Map *mapCarritos)
{
	char nameCarrito[101];
	Vendido *eliminar;

	printf("Introduzca nombre del carrito: ");
	scanf("%[0-9a-zA-Z ,-]", nameCarrito);
	getchar();
	char *nombreCarrito = get_csv_field(nameCarrito, 0);

	// Busca el carrito
	Carrito *carrito = (Carrito *) searchMap(mapCarritos, nombreCarrito);
	if (!carrito) {printf("No existe carrito con el nombre indicado\n"); return;}

	// Elimina el ultimo producto ingresado al carrito
	eliminar = popBack(carrito->carro);
	if (!eliminar) {printf("El carrito ya esta vacio\n"); return;}

	// Actualiza los datos
	carrito->productosComprar -= eliminar->cantidadComprada;
	carrito->precioPagar -= eliminar->precioTotal;

	printf("Eliminado %s de carrito %s exitosamente\n", eliminar->comprado->nombre, nombreCarrito);

	free(eliminar);
}
//-----------------------------------------//

//**************************************************************//



//**************************  OPCIÓN 10 ***********************//

/*------- Opción 10: Concretar compra y disminuir stock -------*/
void concretarCompra(Map *mapCarritos)
{
	char nameCarrito[101], opt;
	Vendido *aux;

	printf("Introduzca nombre del carrito: ");
	scanf("%[0-9a-zA-Z ,-]", nameCarrito);
	getchar();
	char *nombreCarrito = get_csv_field(nameCarrito,0);

	//Busca el carrito
	Carrito *carrito = (Carrito *) searchMap(mapCarritos, nombreCarrito);
	if (!carrito) {printf("No existe carrito con el nombre indicado\n"); return;}

	//Muestra los productos del carrito
	aux = firstList(carrito->carro);
	while(aux)
	{
		printf("Producto: %s\n", aux->comprado->nombre);
		printf("Precio individual: %d\n", aux->comprado->precioIndividual);
		printf("Cantidad: %d (Disponible: %d)\n", aux->cantidadComprada, aux->comprado->stock);

		//Confirma si hay stock suficiente (Por si el stock ha cambiado desde que se agrego el producto)
		if(aux->cantidadComprada > aux->comprado->stock)
		{
			printf("No hay stock suficiente, se actualizara automaticamente al stock disponible\n");

			carrito->productosComprar -= aux->cantidadComprada;
			carrito->precioPagar -= aux->precioTotal;

			aux->cantidadComprada = aux->comprado->stock;
			aux->precioTotal = aux->cantidadComprada * aux->comprado->precioIndividual;

			carrito->productosComprar += aux->cantidadComprada;
			carrito->precioPagar += aux->precioTotal;
		}

		printf("\n");
		aux = nextList(carrito->carro);
	}

	printf("Cantidad a pagar: %d\n", carrito->precioPagar);
	
	//Pide al usuario que confirme la compra
	do
	{
		printf("Introduzca s para concretar la compra o n para cancelar: ");
		scanf("%c", &opt);
		getchar();
		if(opt == 'n' || opt == 'N') return;
	} while(opt != 's' && opt != 'S' && opt != 'n' && opt != 'N');

	// Va eliminando el stock de los productos vendidos
	aux = popFront(carrito->carro);
	while(aux)
	{
		aux->comprado->stock -= aux->cantidadComprada;
		free(aux);
		aux = popFront(carrito->carro);
	}

	//Elimina el carrito
	eraseMap(mapCarritos, carrito->nombreCarrito);

	printf("Compra efectuada.\n");
}
//-----------------------------------------//

//**************************************************************//



//**************************  OPCIÓN 11  ***********************//

//----------------- Opción 11: Mostrar Carrito ------------------//
void mostrarCarrito (Map *carro){
	Carrito *carrinho = (Carrito *) firstMap(carro);

	if (carrinho == NULL){
		printf ("No hay ningun carrito creado\n");
		printf ("\n");
		return;
	}
    
	printf ("Mostrando Carrito\n");
	while (carrinho != NULL){ // Recorre el mapa de los carritos y los va mostrando
		printf ("Nombre del carrito: %s\n", carrinho->nombreCarrito);
		Vendido *product = firstList (carrinho->carro);
		while (product != NULL){
			imprimirProducto(product->comprado);
			printf ("Cantidad a comprar : %i\n", product->cantidadComprada);
			printf ("Precio total del producto : %i\n", product->precioTotal);
			product = nextList (carrinho->carro);
		}
        printf ("---------------------------------------------------------------\n");
		printf ("Cantidad de productos en el carrito: %d\n", carrinho->productosComprar);
		printf ("Total precio a pagar: %d\n", carrinho->precioPagar);
		carrinho = nextMap (carro);
	}
}
//-----------------------------------------//

//**************************************************************//







//------------------MAIN-------------------------//

int main() {
	// Crea los 4 mapas que se podrian usar a lo largo del codigo
	Map *nombre = crearMapaString();
	Map *tipo = crearMapaString();
	Map *marca = crearMapaString();
	Map *carritos = crearMapaString();

	int option = 0; //Variable que decide la opcion del menun seleccionada

	Advertencia();
	pressEnter(0);

	while (option != 12) { // Muestra el menu y actua segun la opcion seleccionada 
		MostrarMenu();
		
		scanf("%d", &option);
		getchar(); /* Importante poner getchar luego de cada scanf pues de lo 
        contrario un futuro scanf leera un '\n' y no recibira el input */

		if (option == 12) {break;} //Sale del while si la opcion escogida en el menu era Salir

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
			BuscarProducto(tipo, nombre, marca, option);
			break;
			//-----------------------------------------//
		case 5:
			/*------- Buscar productos por marca -------*/
			BuscarProducto(tipo, nombre, marca, option);
			break;
			//-----------------------------------------//
		case 6:
			/*------- Buscar producto por nombre -------*/
			BuscarProducto(tipo, nombre, marca, option);
			break;
			//-----------------------------------------//
		case 7:
			/*------- Mostrar todos los productos -------*/
			ImprimirMapa(0, nombre, tipo, marca);
			
			break;
			//-----------------------------------------//
		case 8:
			/*------- Agregar al carrito -------*/
			agregarProdCarrito(carritos, nombre);

			break;
			//-----------------------------------------//
        case 9:
			/*------- Eliminar del carrito -------*/
			eliminarProdCarrito(carritos);
			break;
			//-----------------------------------------//
		case 10:
			/*------- Concretar compra -------*/
			concretarCompra(carritos);
			break;
			//-----------------------------------------//
		case 11:
			/*------- Mostrar carritos de compra -------*/
			mostrarCarrito (carritos);
			break;
			//-----------------------------------------//
        default:
			/*------- Opcion no valida -------*/
			printf("Opci%cn inv%clida", 162, 160);
			break;
			//-----------------------------------------//
        }

		pressEnter(1);
		
	}

	return 0;
}

// Funciones que no estan en el siguiente formato:
/*------- Opcion del menu -------*/
//-----------------------------------------//
// Es porque la(s) funcion(s) necesarias 
// se crearon en la(s) funcion(es) de una opcion 
// anterior, lo mismo si falta en las funciones de la opcion
# Tarea2 Huachipato

Estudiantes PUCV curso: ICI2240-1  ESTRUCTURA DE DATOS

## **_Integrantes_**

- ### Ademir Muñoz: 
    Pts premio/castigo: 0.

    Siento que de manera individual hice poco y nada para la tarea estaba perdido con eso de la lista enlazada, me costo entenderlo. Así que mi aspecto a mejorar seria estudiar mas la materia para poder aportar mas próximamente.


- ### Lucas Robles: 
    Pts premio/castigo: 0.

    Siento que podria mejorar mi eficiencia, siento que hice muchos commit, para despues darme cuenta de un pequeño detalle que falta o sobra, haciendo muchos commit con cambios pequeñps, ademas de no manejar bien el .md tambien me hizo hacer commit con pequeños cambios. Otra cosa es el de informarme mejor porque no habia hecho el git config, asi que hay muchos commit que no aparece quien los hizo


- ### Sebastián Aguilera: 
    Pts premio/castigo: 0.

    Creo que debería organizar mejor mi manera de trabajar ya que tarde bastante en hacer las funciones que se me designaron debido a que no tenia un planeado bien como hacerlo.

- ### Gerard Espinoza: 
    Pts premio/castigo: 0.

    Siento que a pesar que un principio se me complicó comprender el tema de las listas enlazadas pude terminar entendiendo como funcionaban. También sentí que no hice mucho trabajo en solitario, sino que necesité ayuda para poder seguir avanzando. Así que debo de mejorar en un aspecto más individual y estudiar.

### ¡Grande Huachipato!

![Grande Huachipato](https://pbs.twimg.com/profile_images/1494832822099451910/NgCFzNKt_400x400.jpg)


## 1. Como compilar y ejecutar la tarea:
Abrir la carpeta en el VSCode.

Abrir terminal.

Escribir lo siguiente en el terminal:
~~~
gcc -g main.c list.c -o Tarea1 // Para crear o sobrescribir Tarea1 con lo último guardado
~~~

De esa forma se creo o modifico el ejecutable, que se ejecuta de la siguiente manera:
~~~
./Tarea1 //Para ejecutar
~~~

Este sería el menú.
~~~
    1. Importar productos
    2. Exportar productos
    3. Agregar producto
    4. Buscar productos por tipo
    5. Buscar productos por marca
    6. Buscar producto por nombre
    7. Mostrar todos los productos
    8. Agregar al carrito
    9. Eliminar del carrito
    10. Concretar compra
    11. Mostrar carritos de compra
    12. Salir
~~~

## 2. Las opciones que funcionan correctamente y las que no lo hacen indicando posibles causas
Hasta ahora todas las funciones están funcionales en casos normales ósea sin que el usuario intente apretar letras al azar o colocando datos sin pensar.


## Structs:
Contiene 2 struct, una para las canciones y otra destinada a las listas de reproducción

~~~
typedef struct {
	char *nombre;
	char *tipo;
	char *marca;
	unsigned int stock;
	unsigned int precioIndividual;
} Producto; // Struct que guarda los datos de un producto

typedef struct {
	Producto * comprado;
	int cantidadComprada;
	int precioTotal;
} Vendido; // Struct que guarda los productos a vender, con la cantidad a vender y precio total

typedef struct {
	char *nombreCarrito;
	List *carro;
	int productosComprar;
	int precioPagar;
} Carrito; // Struct que guarda los datos de un carrito de compra
~~~


## Funciones:
---
~~~
int is_equal_string(void * key1, void * key2)
{
Función para comparar claves de tipo string retorna 1 si son iguales y 0 en caso contrario.
}


int lower_than_string(void * key1, void * key2)
{
Función para comparar claves de tipo string retorna 1 si son key1<key2 y, en caso de no ser asi retorna 0.
}


int is_equal_int(void * key1, void * key2)
{
Función para comparar claves de tipo int retorna 1 si son iguales y 0 si no lo son.
}


int lower_than_int(void * key1, void * key2)
{
Función para comparar claves de tipo int retorna 1 si son key1<key2.
}
~~~
---
~~~
/*------- Crear Mapa de String -------*/
Map *crearMapaString()
{
Función que crea un mapa que contendra claves tipo string.
}
//-----------------------------------------//



/*------- Advertencia -------*/
void Advertencia()
{
Muestra en pantalla una advertencia sobre que tipo de caracteres no se pueden ingresar.
}
//-----------------------------------------//



/*------- Presionar Enter -------*/
void pressEnter()
{
Solicita que se presione Enter, deteniendo el programa hasta que se cumpla lo solicitado.
}
//-----------------------------------------//



/*------- Mostrar Menú -------*/
void MostrarMenu()
{
Muestra en pantalla las 12 opciones disponibles en el menu y nos solicitan escoger 1.
}
//-----------------------------------------//


/*------- Copiar string en un nuevo espacio de memoria -------*/
char * _strdup(const char * str)
{
Crea un string con una nueva direccion de memoria, donde copiara el string recibido y retornara el string creado.
}
//-----------------------------------------//
~~~
---
~~~
//**************************  OPCIÓN 1  ***********************//

/*------- Leer Archivo -------*/
char *get_csv_field(char *tmp, int k)
{
Función que separa una string por comas a menos que un campo este contenido entre comillas.
Tambien se asegura que la primera letra del string quede en mayuscula y el resto en minusculas.

Crea una función de tipo int que determinara si se han leído comillas.

Crea una cadena de máximo 100 caracteres (Contando el carácter nulo) que guardara el campo leído para ser retornado.

Dos variables de tipo int, una guardando el índice inicial del campo leído y la otra del índice de la letra leída relativa al campo leído.

Otra variable de tipo int que comprobara que el índice del campo coincide con el índice ingresado para ser leído (k).

Un ciclo while que lee hasta un carácter de salto de línea
        - El primer if ve si están las comillas abiertas o si el carácter leído no es una coma, de ser así, se 
          comprueba si el índice del campo actual coincide con 'k' para poder guardar el carácter dentro de la cadena de retorno. Al guardarlo, si es la primera letra, sera mayuscula, y si no se guardara en minuscula.
        - El segundo if comprueba si se están leyendo una coma, de ser asi se comprueba que el índice del
          campo siendo leído coincide con 'k', si lo es significa que el campo que se quería leer ya ha sido
          leído y se retorna la cadena en cuestión, si no lo es se aumenta el índice del campo leído para posteriormente continuar con el ciclo.
        - Un if al final del ciclo que haría retornar la cadena de retorno si se está leyendo el ultimo campo  
          (debido a que esta no tiene una coma al final y no entraría en el tercer if).
        - Un retorno de NULL que sería en caso de que 'k' no coincida con el índice de algún campo en la 
          string original.
}

Producto *crearProducto(char *nombre, char *tipo, char *marca, int stock, int precio)
{
Recibe los datos de un producto, crea una variable tipo struct Producto y guarda los datos recibidos con strdup cada vez para asegurarse que esten en distintos espacios de memoria sin importar cuanto se use la funcion.

Luego retorna la variable tipo Producto que contiene los datos guardados
}

//	/*------- Guardar Productos en Mapa -------*/
List *crearLista(Producto *Save)
{
Recibe un producto y crea una lista nueva donde guarda la variable recibida al final.

Después retorna la lista
}

void addProductoaMapa(Map *name, Map *type, Map *brand, Producto *product)
{
La funcion recipe los mapas y el struct de tipo producto.

Se pregunta si es que el producto esta en el mapa general de key nombre
    -Si no se encuentra, se inserta en los mapas
    -Si el tipo de la marca no esta en el mapa, se crea.
    -Si la marca del producto no esta en el mapa, se crea.
    
Si el producto se encuentra en el mapa solo se le suma el stock del producto.    
}
//	//-----------------------------------------//

int leerArchivoCanciones(char *nombreArchivo, Map* Nombre, Map *Tipo, Map* Marca)
{ 
Recibe el nombre del archivo a leer y los mapas donde guardar lo leido.

Abre el mapa con el nombre recibido y si no existe archivo con un nombre que coincida, retona 1, mostrando que la funcion fallo.
  
Crea una variable tipo Producto para guardar el cada producto leido.
Crea una gran string para guardar una linea del archivo.

Crea variables para guardar los datos de una linea.

Crea un while que guarda una linea del archivo cada vez en una string y termina el ciclo cuando la string sea nula.
    - Separa los datos de la linea y los guarda en variables correspondientes.
    - Crea un if para verificar que stock y precio sean mayores que 0.
        - Guarda los datos en una struct Producto con la funcion crearProducto()
          enviando los datos correspondientes.
        - Guarda el producto en los 3 mapas, enviando el producto y los 3 mapas
          a la función addProductoaMap().
	
Cierra el archivo y retorna 0, para mostrar que la función realizo su labor de forma exitosa.
}
//-----------------------------------------//

/*----------------- OPCIÓN 1: Importar Producto -----------------*/
void ImportarProductos(Map *name, Map *type, Map *brand)
{
Solicita un nombre de archivo.

Utiliza la función leerArchivoCanciones() para importar los datos del archivo y el numero que retorna lo guarda en una variable int.

Usa el numero retornado para decidir con un if si mostrar un mensaje de exito o fracaso respecto a importar el archivo.
}
//-------------------------------------------------------------//

//**************************************************************//
~~~
***
~~~
//**************************  OPCIÓN 2  ***********************//

/*------- Crear o Sobreescribir Archivo -------*/
void sobreescribirArchivo(char *Archive, Map *mapa)
{
Funcion que recibe un nombre para el archivo y un mapa con los datos.

La funcion abre el archivo con el nombre recibido en modo escritura.

La funcion crea una variable tipo struct Producto.

La variable tipo Producto toma el valor del primer dato del mapa con firstList()

Crea una while para recorrer el mapa con los datos, que se detendra cuando la variable tipo Producto sea NULL.
    - Usa un if para saber si el producto tiene stock y precio mayores que 0.
        - Utiliza fprintf para guardar el nombre, marca, tipo, stock y precio
          que contiene la variable tipo struct Producto separados por coma en una linea del archivo y al final poniendo un salto de linea.
    - Usa nextMap() guardando un nuevo producto en la variable struct Producto.

Cierra el archivo.
}
//-----------------------------------------//
~~~
---
~~~
/*----------------- OPCIÓN 2: Exportar Producto -----------------*/
void ExportarProductos(Map *name)
{
Función que solicita un nombre para el archivo a exportar, si el nombre existe, el archivo se sobreescribe, si no existe se creara un archivo con el nombre ingresado. 
  
El archivo sera .txt a menos que al ingresar el nombre pongan '.' y especifiquen el tipo de archivo mediante la función sobreescribirArchivo, enviando el nombre del archivo y un mapa con los productos.
  
Después imprimira el exito de la operación.
}
//-------------------------------------------------------------//

//**************************************************************//
~~~
---
~~~
//**************************  OPCIÓN 3  ***********************//

/*----------------- OPCIÓN 3: Aggregar Producto -----------------*/
void leerProducto (Map *nombre_map, Map *tipo_map, Map *marca_map)
{
La funcion recibe los mapas correspondientes.
Se declara variables de tipo char y unsigned int para almacenar la informacion.
Se pregunta al usuario la informacion correspondiente.

Se pregunta si la variable de stock y precio son menores o iguales a 0.
    -En caso de ser verdadero se muestra por pantalla un error diciendole al usuario que se equivoco.
    
Se muestra por pantalla la informacion dada por el usuario y se le pregunta si esta conforme o no.
    -Si el usuario acepta se crea la struct de tipo producto con la informacion puesta.
    -Despues se inserta la struct creada en los mapas.
    -Se le dice al usuario que se guardo perfectamente el producto.
    
En caso de que el usuario no acepte se dira al usuario que no se guardo el producto.  
}
//-------------------------------------------------------------//

//**************************************************************//
~~~
---
~~~
//**************************  OPCIÓN 4, 5, 6  ***********************//

/*------- Imprimir Producto -------*/
void imprimirProducto(Producto* dato){
La funcion recibe una variable tipo struct Producto.

Crea un if, donde si el producto tiene stock o precio menor o igual a 0, entonces no imprime el producto

Utiliza printf para mostrar en pantalla cada variable del struct con un titulo correspondiente y con un salto de linea entre cada uno.
}
//-----------------------------------------//

/*------- Comparar cadenas de caracteres -------*/
int compare_strings(char cadena1[101], char *cadena2)
{
  Compara 2 cadenas, similar a strcpm, si las 2 cadenas tienen un 100% de coincidencias quiere decir que son iguales. Compara 
  carácter a carácter.
}
//-----------------------------------------//


/*------- Buscar por tipo  -------*/
void BusquedaTipo(char* prod, Map* tipo)
{
	Utilizando la función SearchMap encuentra la posición donde se encuentra la lista deseada, una vez la encontramos 
	crea un ciclo que nos permite recorrer la lista buscando la cadena con 100% de coincidencias, si no es el caso entonces 
	avisa al operador que no se a encontrado ningún producto.
}
//-----------------------------------------//

/*------- 	Busqueda nombre -------*/
void BusquedaNombre(char* prod, Map* nombre)
{
	
}

/*------- 	Busqueda marca -------*/
void BusquedaMarca(char* prod, Map* marca)
{
	Utilizando SearchMap, la función localiza la posición donde debería estar la lista que deseamos recorrer ( en este caso la lista de marcas)
	y crea un ciclo que recorre uno a uno los nodos de la lista comparando para encontrar la cadena indicada, si no la encuentra
	avisa al operador que no hay ningún producto coincidente.
	
}

/*------- 	Opciòn 4,5,6: Busqueda -------*/
void BuscarProducto(Map *tipo, Map *nombre, Map* marca, int opt)
{
	Es similar a un "lobby", donde según los criterios ingresados a la función ingresa a los distintos casos posibles. Cada caso
	escanea la cadena a consultar.
	
}
//-----------------------------------------//

//**************************************************************//
~~~
---
~~~
//**************************  OPCIÓN 7  ***********************//

/*------- Imprimir Producto -------*/
void imprimirProducto(Producto* dato)
{
Recibe una variable tipo Producto e imprime en pantalla de forma ordenada todos los datos guardados en la variable tipo struct.
}
//-----------------------------------------//

/*----------------- OPCIÓN 7: Mostrar Mapa -----------------*/
void ImprimirMapaSeleccionado(int opt, Map *name_map, Map *type_map, Map *brand_map)
{
Funcion que imprime todos los prodictos del mapa seleccionado de acuerdo a la variable opt que recibe la funcion.
    -Si opt = 1, mostrara los productos por nombre.
    -Si opt = 2, mostrara los productos por tipo.
    -Si opt = 3, mostrara los productos por marca.
}

void ImprimirMapa(int opt, Map *nameMap, Map *typeMap, Map *brandMap)
{
Funcion que nos pide de que forma mostrar el mapa y utiliza la funcion ImprimirMapaSeleccionado() para mostrarlo en pantalla de la forma que el usuario escogio.
}
//-------------------------------------------------------------//

//**************************************************************//
~~~
---
~~~
//**************************  OPCIÓN 8  ***********************//

/*------- Opcion 8: Agregar producto a un carrito -------*/
void agregarProdCarrito(Map *mapCarritos, Map *mapNombre)
{
  La funcion comienza pidiendo al usuario que ingrese los datos del carrito al que desea agregar un producto y del producto en cuestión.

  Usando searchmap busca el carrito y si este no existe crea uno nuevo.

  Luego se crea la variable de tipo Vendido que llevará registro del producto, su cantidad y precio total, a su vez revisa si hay stock suficiente.

  La variable de tipo Vendido se añade a la lista enlazada del carrito.
}
//-----------------------------------------//

//**************************************************************//
~~~
---
~~~
//**************************  OPCIÓN 9  ***********************//

/*------- Opción 9: Eliminar Producto de un carrito  -------*/
void eliminarProdCarrito(Map *mapCarritos)
{
  La funcion pide el nombre del carrito para eliminar el ultimo producto ingresado.

  Busca el carrito con searchmap y luego utiliza popBack para eliminar el producto en cuestion de la lista enlazada.

  Finalmente actualiza los datos del carrito.
}
//-----------------------------------------//

//**************************************************************//
~~~
---
~~~
//**************************  OPCIÓN 10 ***********************//

/*------- Opción 10: Concretar compra y disminuir stock -------*/
void concretarCompra(Map *mapCarritos)
{
  La funcion pide al usuario que ingrese el nombre del carrito cuya compra desea efectuar.

  Busca el carrito y finaliza la funcion si es que no sirve.

  Un ciclo while que cumple dos funciones:
    -Mostrar los productos del carrito.
    -Confirmar que el stock disponible corresponde con la cantidad de X producto
     (Esto es por si el stock de un producto cambio luego de ingresarlo al carrito).

  Muestra la cantidad a pagar y luego pide al usuario que confirme la compra.

  Un ciclo while se encarga de ir actualizando el stock e ir eliminando los productos de la lista del carrito.

  Finalmente elimina el carrito.
}
//-----------------------------------------//

//**************************************************************//
~~~
---
~~~
//**************************  OPCIÓN 11  ***********************//

//----------------- Opción 11: Mostrar Carrito ------------------//
void mostrarCarrito (Map *carro){
La funcion recibe el mapa de carrito.

se declara carrinho de tipo carrito igual al firstMap de carro.

Se pregunta si carrinho es igual a NULL
    -Si es asi es porque no existe aun un carrito con productos.
    -Se le dice al usuario que aun no crea el carrito y se retorna.
    
Se dice que se empezara a mostrar el carrito.
Con un while mientras carrinho sea distinto de NULL
    -Se muestra el nombre del carrito.
    -Se declara una variable llamado product de tipo Vendido que es igual a al firstList de la lista relacionada al carrito.
    
    -Un while de producto sea distinto de NULL
              -Se muestra el producto relacionado al carrito que es de tipo vendidos.
              -Muestra la cantidad que se comprara de ese producto.
              -Muestra el total a pagar de ESE producto.
	      -Product sera igual al nextList.      
    	
    -Se muestra la cantidad de productos que contiene el carrito.
    -Se muestra el Total a pagar.
    -Carrinho = nextMap.
}
//-----------------------------------------//

//**************************************************************//
~~~
---

////////////////////////////////////////////////////////
////////////////////////////////////////////////////////
////////////////////////////////////////////////////////
////////////////////////////////////////////////////////

## Codigo:

Parte creando 3 mapasa para guardar los productos por nombre, marca y tipo.

Y crea un mapa para guardar los carritos de compra.

Crea una variable int 'option' en 0.

Imprime una advertencia con la función Advertencia() y solicita enter para continuar con la funcion pressEnter().

Crea un while con la condicion 'option != 12'.
- Dentro del while imprime un menu en pantalla con la funcion MostrarMenu().
- Solicita escoger una opcion y guarda la respuesta en la variable 'option'.
- Usa un if('option == 12') donde si se cumple, se sale del while con break.
- Crea un switch con 'option de condicion', con casos del 1 al 11, mas un default que realizara el proceso que corresponde de acuerdo a los numeros de cada opción en el menu mostrado previamente.
- Solicita que el usuario presione Enter para continuar con la funcion pressEnter().
---

#### A continuacion se explicaran cada caso del switch que esta presente dentro del while:
~~~
/--------------------------------------------------------------------------------------------------------------/

 option =  1:
 Solicita un nombre de archivo al usuario. Si existe el archivo, se guardaran los datos
 en los mapas creados al comienzo del main y mandara un mensaje de exito. Si no existe, 
 mandara un mensaje de error. 

 El archivo debe ser de productos de la misma manera en que esta el ejemplo 
 'Archivo_100productos.csv' en la carpeta de este codigo. Tambien puede ser .txt, pero el orden debe
 ser el del ejemplo.
 
 Realiza este proceso con la función ImportarProductos().

/--------------------------------------------------------------------------------------------------------------/

 option =  2:
 Solicita un nombre de archivo al usuario. Si existe el archivo, se soobrescribe con los datos
 en el mapa que usa los nombres como clave. Si no existe, se crea una archivo con el nombre ingresado
 con los datos por el usuario y se guardan los datos en el mapa que usa los nombres 
 como clave en el archivo.

 El archivo debe ser de productos de la misma manera en que esta el ejemplo 
 'Archivo_100productos.csv' en la carpeta de este codigo. Tambien puede ser .txt, pero el orden debe
 ser el del ejemplo.
 
 Realiza este proceso con la función ExportarProductos().

/--------------------------------------------------------------------------------------------------------------/

 option =  3:
 Solicita 5 datos al usuario (nombre, marca, tipo, stock y precio) una vez hecho se le muestra al usuario
 si esta conforme o si esta correcto la informacion dada.
 
 Pero en caso de que el usuario coloque stock o precio menor o igual a 0 este dara un error diciendole al 
 usuario que ingreso datos erroneos.
 
 En caso de que el usuario confirme que todo esta bien esta se transformara a traves de una funcion en una struct
 de tipo producto para que esta sea añadida a los mapas  correcpondientes, despues se le dice al usuario que 
 todo el proceso se realizo con exito.
 
 En caso de que el usuario no este conforme este entregara un aviso que no se guardo el producto en el almacen.
 Realiza este proceso con la función leerProducto().
/--------------------------------------------------------------------------------------------------------------/

 option =  4:
 
/--------------------------------------------------------------------------------------------------------------/

 option =  5:
/--------------------------------------------------------------------------------------------------------------/

 option =  6:
 
/--------------------------------------------------------------------------------------------------------------/

 option =  7:
 Imprime todos los productos guardados en pantalla, ya sea por nombre, tipo o marca, dependiendo de nuestra eleccion.

 Realiza este proceso con la función ImprimirMapa().

/--------------------------------------------------------------------------------------------------------------/

 option =  8:
 
/--------------------------------------------------------------------------------------------------------------/

 option =  9:
 
/--------------------------------------------------------------------------------------------------------------/

 option = 10:
 
/--------------------------------------------------------------------------------------------------------------/

 option = 11:
 Muestra el mapa Carrito.
 
 Realiza este proceso con la función mostrarCarrito().
/--------------------------------------------------------------------------------------------------------------/

 default:
 Se entra aquí si el número ingresado no pertenece a ninguna opción del menú.
 Solamente imprime el mensaje "Opcion invalida".

/--------------------------------------------------------------------------------------------------------------/
~~~

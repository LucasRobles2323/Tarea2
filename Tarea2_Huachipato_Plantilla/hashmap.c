#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "hashmap.h"


typedef struct HashMap HashMap;
int enlarge_called=0;

struct HashMap {
    Pair ** buckets;
    long size; //cantidad de datos/pairs en la tabla
    long capacity; //capacidad de la tabla
    long current; //indice del ultimo dato accedido
};

Pair * createPair( char * key,  void * value) {
    Pair * new = (Pair *)malloc(sizeof(Pair));
    new->key = key;
    new->value = value;
    return new;
}

long hash( char * key, long capacity) {
    unsigned long hash = 0;
    char * ptr;

    for (ptr = key; *ptr != '\0'; ptr++) {
        hash += hash*32 + tolower(*ptr);
    }
    return hash%capacity;
}

int is_equal(void* key1, void* key2){
    if(key1==NULL || key2==NULL) return 0;
    if(strcmp((char*)key1,(char*)key2) == 0) return 1;
    return 0;
}


void insertMap(HashMap * map, char * key, void * value) {
    if(key==NULL) return;
    long index = hash(key, map->capacity);

    while ((map->buckets[index] != NULL) && (map->buckets[index]->key != NULL))
    {
       if(is_equal(key, map->buckets[index]->key))
       {
           return;
       }
       index = (index + 1) % map->capacity;
    
    }

    if(map->buckets[index] != NULL){
        map->buckets[index]->key =key;
        map->buckets[index]->value = value;
    }
    else{
        map->buckets[index] = createPair(key, value);
        map->size++;
    }
    if((double) map->size/(double) map->capacity > 0.75){enlarge(map);}

}

void enlarge(HashMap * map) {
    enlarge_called = 1; //no borrar (testing purposes)
    Pair **aux = (Pair**) calloc(map->capacity ,sizeof(Pair*));

    for (size_t i = 0; i < map->capacity; i++)
    {
        aux[i] = map->buckets[i];
    }

    map->capacity *= 2;
    map->buckets = (Pair**) calloc (map->capacity, sizeof(Pair*));
    map->size = 0;
    map->current = -1;

    for (size_t i = 0; i < (map->capacity/2); i++)
    {
        if(aux[i] != NULL && aux[i]->key != NULL){
            insertMap(map, aux[i]->key, aux[i]->value);
        }
    }
    
    free(aux);
}


HashMap * createMap(long capacity) {
    HashMap *Map = (HashMap*) malloc (sizeof(HashMap));
    Map->capacity = capacity;
    Map->current = -1;
    Map->size = 0;
    Map->buckets = (Pair**) calloc (Map->capacity, sizeof(Pair*));
    
    return Map;
}

void eraseMap(HashMap * map,  char * key) {    
    if(key==NULL) return;
    long index = hash(key, map->capacity);

    while ((map->buckets[index] != NULL) && (map->buckets[index]->key != NULL))
    {
       if(is_equal(key, map->buckets[index]->key))
       {
           map->buckets[index]->key = NULL;
           map->size--;
           return;
       }
       index = (index + 1) % map->capacity;
    
    }

}

Pair * searchMap(HashMap * map,  char * key) {   
    long indice = hash(key, map->capacity);

    while (map->buckets[indice] != NULL)
    {
        if (is_equal(key, map->buckets[indice]->key))
        {
            map->current = indice;
            return map->buckets[indice];
        }
        if(indice < map->capacity){indice++;}
        else{indice = 0;}
    }
    return NULL;
}

Pair * firstMap(HashMap * map) {
    map->current = 0;

    while (map->current < map->capacity)
    {
        if( (map->buckets[map->current] != NULL) && (map->buckets[map->current]->key != NULL) ) {
            return map->buckets[map->current];
        }
        map->current++;
    }
    
    return NULL;
}

Pair * nextMap(HashMap * map) {
    map->current++;
    while (map->current < map->capacity)
    {
        if( (map->buckets[map->current] != NULL) && (map->buckets[map->current]->key != NULL) ) {
            return map->buckets[map->current];
        }
        map->current++;
    }
    
    return NULL;
}
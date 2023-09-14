#ifndef HASH_MAP_C
#define HASH_MAP_C
#include <stdlib.h>
#include "hash_map.h"

HashMap* new_hash_map(){
	Pair** buckets = (Pair**) malloc(DEFAULT_CAPACITY * sizeof(Pair*));
	memset(buckets,0,DEFAULT_CAPACITY * sizeof(Pair*));

	HashMap* map = (HashMap*) malloc(sizeof(HashMap));
	map->capacity = DEFAULT_CAPACITY;
	map->buckets = buckets;
	map->size = 0;
	map->threshold = DEFAULT_THRESHOLD;
	map->extend_ratio = DEFAULT_EXTEND_RATIO;
	return map;
}

unsigned int hash(char* key,int capacity){
	int i = 0;
	unsigned int hash_code = 0;
	char ch = key[i];
	while(ch != '\0'){
		hash_code += ch;	
		ch = key[i++];
	}
	return hash_code % capacity;
}

double load_factor(HashMap* map){
	return (double) map->size / map->capacity;
}

int get(HashMap* map,char* key){
	unsigned int hash_code = hash(key, map->capacity);
	Pair* p = map->buckets[hash_code];

	if(p != NULL){
		if(p->next == NULL){
			return p->val;
		}
		Pair* ptr = p;
		while(ptr != NULL){
			if(strcmp(ptr->key,key) == 0){
				return ptr->val;
			}
			ptr = ptr->next;
		}
	}
	return -1;
}

void put(HashMap* map,char* key, int val){
	if(load_factor(map) > map->threshold){
		extend_hash_map(map);
	}
	unsigned int hash_code = hash(key, map->capacity);
	Pair* pair = map->buckets[hash_code];
	if(pair != NULL){
		Pair* ptr = pair;
		while(ptr != NULL){
			if(strcmp(ptr->key,key) == 0){
				ptr->val = val;
				map->size = map->size + 1;
				return;
			}
			if(ptr->next == NULL){
				ptr->next = create_item(key,val);
				map->size = map->size + 1;
				return;
			}
			ptr = ptr->next;
		}
	}
	else{
		map->buckets[hash_code] = create_item(key,val);
		map->size = map->size + 1;
	}
}

Pair* create_item(char* key, int val){
	Pair* p =(Pair*) malloc(sizeof(Pair));
	p->key = (char*) malloc((strlen(key) + 1) * sizeof(char));
	strcpy(p->key,key);
	p->val = val;
	p->next = NULL;
	return p;
}

int has(HashMap* map, char* key){
	unsigned int hash_code = hash(key,map->capacity);
	Pair* p = map->buckets[hash_code];
	if(p != NULL) return 0;
	return -1;
}

int remove_item(HashMap* map,char* key){
	int hash_code = hash(key, map->capacity);
	Pair* ptr = map->buckets[hash_code];
	if(ptr != NULL){
		free(ptr->key);
		free(ptr);
		map->buckets[hash_code] = NULL;
		map->size = map->size -1;
		return 0;
	}
	return -1;
}

Pair** pair_set(HashMap* map){
	Pair** buckets = map->buckets;
	return buckets;
}

void destroy(HashMap* map){
	for(int i = 0; i < map->capacity;i++){
		free(map->buckets[i]);
	}
	map->buckets = NULL;
	free(map);
}

void display(HashMap* map){
	int len = map->capacity;
	Pair* ptr;
	for(int i =0;i < map->capacity; i++){
		ptr = map->buckets[i];
		if(ptr != NULL){
			while(ptr != NULL){
				printf("{key:%s, val:%d} \n",ptr->key,ptr->val);
				ptr = ptr->next;
			}
		}
	}
	ptr = NULL;
}

void extend_hash_map(HashMap* map){
	int old_capacity = map->capacity;
	Pair** old_buckets = map->buckets;

	map->capacity = map->capacity * map->extend_ratio;
	map->buckets = (Pair**) malloc(map->capacity * sizeof(Pair*));
	memset(map->buckets,0,map->capacity * sizeof(Pair*));
	map->size = 0;

	for(int i = 0; i < old_capacity; i++){
		Pair* ptr = old_buckets[i]; 
		while(ptr != NULL){
			put(map,ptr->key,ptr->val);
			ptr = ptr->next;
		}
	}

	for(int i = 0; i < old_capacity; i++){
		Pair* ptr = old_buckets[i]; 
		while(ptr != NULL){
			Pair* temp = ptr;
			free(temp->key);
			free(temp);
			ptr = ptr->next;
		}
	}
	free(old_buckets);
}

#endif //HAHS_MAP_C

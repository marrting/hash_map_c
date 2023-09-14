#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "hash_map.c"

int main(){
	HashMap *map = new_hash_map();

	// test put and get function
	assert(get(map,"a") == -1);

	// test hash collision
	put(map,"abc",123);
	put(map,"bac",321);
	assert(get(map,"abc") != get(map,"bac"));

	// testing extend hash map
	// default capacity is 16
	// when size is over 12 which load factor is over 0.75
	for(int i =0; i< 13;i++){
		char key[2] = {65 + i,'\0'};
		put(map,key,i);
	}
	assert(map->capacity == DEFAULT_CAPACITY * DEFAULT_EXTEND_RATIO);

	display(map);
	destroy(map);
}

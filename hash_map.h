#ifndef HASH_MAP_H
#define HASH_MAP_H

typedef struct Pair
{
	char *key;
	int val;
	struct Pair *next;
} Pair;

#define DEFAULT_CAPACITY 16
#define DEFAULT_THRESHOLD 0.75
#define DEFAULT_EXTEND_RATIO 2
typedef struct HashMap
{
	// current size of hashMap
	int size;
	// capacity of hash map
	int capacity;
	double threshold;
	int extend_ratio;
	Pair **buckets;
} HashMap;

HashMap *new_hash_map();

unsigned int hash(char *key, int capacity);

double load_factor(HashMap *map);

int get(HashMap *map, char *key);

void put(HashMap *map, char *key, int val);

Pair *create_item(char *key, int val);

int has(HashMap *map, char *key);

int remove_item(HashMap *map, char *key);

Pair **pair_set(HashMap *map);

void destroy(HashMap *map);

void extend_hash_map(HashMap *map);

#endif // HASH_MAP_H

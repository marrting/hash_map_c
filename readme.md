# HashMap Implementation In C
This is a simple implementation of a hash map data structure in the C programming language. The hash map is designed to store key-value pairs, where keys are strings and values are integers. This implementation uses separate chaining to handle collisions.

> TODO:
 Implementing AVL Tree when buckets size is over 8

## Usage 
1. Initialization: To create a new hash map, use the new_hash_map function. This initializes an empty hash map with default settings.
	```
	HashMap* map = new_hash_map();
	```

2. Insertion: You can add key-value pairs to the hash map using the put function.
	```
	put(map, "key1", 42);
	put(map, "key2", 17);
	```

3. Retrieval: To retrieve a value associated with a key, use the get function.
	```
	int value = get(map, "key1");
	```

4. Removal: To remove a key-value pair, use the remove_item function.
	```
	remove_item(map, "key2");
	```

5. Destroy: To release the memory allocated for the hash map, use the destroy function.
	```
	destroy(map);
	```

6. Extension: The hash map automatically extends its capacity when necessary to maintain efficiency. The extension ratio can be configured in the HashMap structure.

## Example
Check the main.c file for example and tests;

***
*README Generated by Chat-GPT*
#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 20

struct buckets {
    int key;
    int value;
    struct buckets* next;
};

struct map {
    struct buckets* buckets[MAX_SIZE];  // Array of pointers to buckets
};

// Function to create a new key-value pair (bucket)
struct buckets* get_pair(int key, int value) {
    struct buckets* pair = (struct buckets*)malloc(sizeof(struct buckets));
    if (!pair) {
        printf("\nMalloc Failed");
        exit(1);  // Exit if memory allocation fails
    }
    pair->key = key;
    pair->value = value;
    pair->next = NULL;
    return pair;
}

// Function to initialize the map
struct map* init() {
    struct map* map = (struct map*)malloc(sizeof(struct map));
    if (!map) {
        printf("\nMap Allocation failed");
        exit(1);  // Exit if memory allocation fails
    }
    
    for (int i = 0; i < MAX_SIZE; i++) {
        map->buckets[i] = NULL;  // Initialize each bucket to NULL
    }

    return map;
}

// Hash function to map keys to an index in the array
unsigned int hash_function(int key) {
    unsigned int hash = 0;
    key = (key < 0) ? (~key) : key;  // Handle negative values eg. for x= -1, x=0 
    hash = (key * 7) % (MAX_SIZE);   // Modulo MAX_SIZE to ensure within bounds
    return hash;
}

// Function to insert key-value pair into the map
void insert_map(struct map* map, int key, int value) {
    unsigned int hash = hash_function(key);
    struct buckets* pair = get_pair(key, value);
    
    if (hash >= MAX_SIZE) {
        printf("\nHash Out of bounds %d", hash);
        return;
    }

    struct buckets* temp = map->buckets[hash];
    if (temp == NULL) {
        map->buckets[hash] = pair;
    } else {
        while (temp != NULL) {
            if (temp->key == key) {
                printf("\nKey %d already exists with value %d, do you want to update it to %d? (y/N): ", temp->key, temp->value, value);
                char choice = getchar();
                while (getchar() != '\n');  // Clear the newline from the buffer
                if (!(choice == 'y' || choice == 'Y')) {
                    return;
                }
                temp->value = value;  // Update value for existing key
                free(pair);  
                return;
            }
            temp = temp->next;
        }
        pair->next = map->buckets[hash]; // set the new pair as the head of linkedlist
        map->buckets[hash] = pair;
    }
}

// Function to print the map
void print_map(struct map* map) {
    struct buckets* pair;
    for (int i = 0; i < MAX_SIZE; i++) {
        if(map->buckets[i]!=NULL){
            printf("\nIndex %d: ", i);
        }
        else{continue;}
        pair = map->buckets[i];
        printf("\n");
        while (pair != NULL) {
            printf("\tKey: %d, Value: %d -> ", pair->key, pair->value);
            pair = pair->next;
        }
        printf("NULL\n");
    }
}

// Function to free allocated memory
void free_memory(struct map* map) {
    struct buckets* pair;
    struct buckets* temp;
    
    for (int i = 0; i < MAX_SIZE; i++) {
        pair = map->buckets[i];
        while (pair != NULL) {
            temp = pair;
            pair = pair->next;
            free(temp);  // Free the individual bucket nodes
        }
    }
    free(map);  // Free the map itself
}

int* get_value(struct map* map, int key) {
    unsigned int hash = hash_function(key);
    if (map->buckets[hash] == NULL) {
        return NULL;
    }
    struct buckets* pair = map->buckets[hash];
    while (pair != NULL) {
        if (pair->key == key) {
            return &(pair->value);
        }
        pair = pair->next;
    }
    return NULL;  // Return NULL if the key is not found
}

void remove_pair(struct map* map, int key) {
    unsigned int hash = hash_function(key);
    struct buckets* pair = map->buckets[hash];
    struct buckets* temp;
    struct buckets* prev = NULL;

    while (pair != NULL) {
        if (pair->key == key) {
            if (prev == NULL) {  // Removing the first node in the list
                map->buckets[hash] = pair->next;
            } else {
                prev->next = pair->next;
            }
            free(pair);
            return;
        }
        prev = pair;
        pair = pair->next;
    }

    printf("\nKey %d Not Found!", key);
}

int main() {
    struct map* HashMap = init(); 

    insert_map(HashMap, 5, 15);
    insert_map(HashMap, 7, 17);
    insert_map(HashMap, 8, 18);
    insert_map(HashMap, 55, 155);
    insert_map(HashMap, 2999, 12999);
    insert_map(HashMap, 1, 11);
    insert_map(HashMap, 0, 10);
    insert_map(HashMap, -1, 111);
    insert_map(HashMap, 2, 17);
    insert_map(HashMap, 3, 18);
    insert_map(HashMap, 4, 14);

    insert_map(HashMap, -8, 18);
    insert_map(HashMap, 555, 155);
    insert_map(HashMap, 299, 12999);
    insert_map(HashMap, 115, 11);
    insert_map(HashMap, 151, 10);
    insert_map(HashMap, -11, 111);
    insert_map(HashMap, 292, 17);
    insert_map(HashMap, 369, 18);
    insert_map(HashMap, 458, 14);

    print_map(HashMap);

    int* val = get_value(HashMap, 7);
    if (val) {
        printf("\nValue for key 7: %d", *val);
    } else {
        printf("\nKey not found.");
    }

    remove_pair(HashMap, 1);

    printf("\nAfter Removing %d",1);
    print_map(HashMap);  

    free_memory(HashMap);
    HashMap = NULL;

    return 0;
}

#include "mru_cache.h"
#include <stdlib.h>
#include <stdio.h>

#define CACHE_SIZE 100

typedef struct CacheNode {
    int length;
    int value;
    struct CacheNode *next;
} CacheNode;

CacheNode *cacheHead = NULL;
int cacheCount = 0;

void initCache() {
    cacheHead = NULL;
    cacheCount = 0;
}

void insertIntoCache(int length, int value) {
    CacheNode *node = (CacheNode *)malloc(sizeof(CacheNode));
    node->length = length;
    node->value = value;
    node->next = cacheHead;

    cacheHead = node;
    cacheCount++;

    if (cacheCount > CACHE_SIZE) {
        CacheNode *current = cacheHead;
        while (current->next && current->next->next) {
            current = current->next;
        }
        free(current->next);
        current->next = NULL;
        cacheCount--;
    }
}

int getFromCache(int length) {
    CacheNode *current = cacheHead;
    if (current && current->length == length) {
        return current->value;  
    }
    return -1;
}

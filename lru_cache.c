#include "lru_cache.h"
#include <stdlib.h>
#include <stdio.h>

#define CACHE_SIZE 100

typedef struct CacheNode {
    int length;
    int value;
    struct CacheNode *prev, *next;
} CacheNode;

CacheNode *cacheHead = NULL, *cacheTail = NULL;
int cacheCount = 0;

void initCache() {
    cacheHead = cacheTail = NULL;
    cacheCount = 0;
}

void moveToFront(CacheNode *node) {
    if (node == cacheHead) return;

    if (node == cacheTail) {
        cacheTail = node->prev;
        cacheTail->next = NULL;
    }

    if (node->prev) node->prev->next = node->next;
    if (node->next) node->next->prev = node->prev;

    node->next = cacheHead;
    node->prev = NULL;
    cacheHead->prev = node;
    cacheHead = node;
}

void insertIntoCache(int length, int value) {
    CacheNode *node = (CacheNode *)malloc(sizeof(CacheNode));
    node->length = length;
    node->value = value;
    node->prev = NULL;
    node->next = cacheHead;

    if (cacheHead) cacheHead->prev = node;
    cacheHead = node;
    if (!cacheTail) cacheTail = node;

    cacheCount++;

    if (cacheCount > CACHE_SIZE) {
        CacheNode *lru = cacheTail;
        cacheTail = lru->prev;
        if (cacheTail) cacheTail->next = NULL;
        free(lru);
        cacheCount--;
    }
}

int getFromCache(int length) {
    CacheNode *current = cacheHead;
    while (current) {
        if (current->length == length) {
            moveToFront(current);
            return current->value;
        }
        current = current->next;
    }
    return -1;
}


#ifndef MRU_CACHE_H
#define MRU_CACHE_H

void initCache();
void insertIntoCache(int length, int value);
int getFromCache(int length);

#endif

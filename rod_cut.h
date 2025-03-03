#ifndef ROD_CUT_H
#define ROD_CUT_H

int rodCut(int remainingLength, int *cutCounts);

void initCache();
void insertIntoCache(int length, int value);
int getFromCache(int length);

#endif

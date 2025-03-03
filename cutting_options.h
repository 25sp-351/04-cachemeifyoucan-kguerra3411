#ifndef CUTTING_OPTIONS_H
#define CUTTING_OPTIONS_H

#define MAX_CUTTING_OPTIONS 100

typedef struct {
    int length;
    int value;
} CuttingOption;

extern CuttingOption cutting_options[];
extern int num_cutting_options;

void read_cutting_options(void);

#endif

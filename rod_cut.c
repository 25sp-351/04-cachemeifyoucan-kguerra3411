#include "rod_cut.h"

#include <stdio.h>
#include <stdlib.h>

#include "cutting_options.h"
#include "rod_cut.h"

// Read cutting options from the input file
void readCuttingOptions(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(1);
    }

    while (fscanf(file, "%d,%d", &cutting_options[num_cutting_options].length,
                  &cutting_options[num_cutting_options].value) != EOF)
        num_cutting_options++;

    fclose(file);
}

void printCuttingSolution(int *cutCounts, int totalValue, int rodLength) {
    printf("Cutting List:\n");
    for (int i = 0; i < num_cutting_options; i++) {
        if (cutCounts[i] > 0) {
            printf("%d @ %d = %d\n", cutCounts[i], cutting_options[i].length,
                   cutting_options[i].value * cutCounts[i]);
        }
    }
    printf("Remainder: %d\n", rodLength);
    printf("Value: %d\n", totalValue);
}

// Recursive rod cutting without cache interaction
int rodCut(int remainingLength, int *cutCounts) {
    if (remainingLength == 0)
        return 0;

    int maxValue                          = 0;
    int subCutCounts[MAX_CUTTING_OPTIONS] = {0};

    for (int i = 0; i < num_cutting_options; i++) {
        if (cutting_options[i].length <= remainingLength) {
            int tempCutCounts[MAX_CUTTING_OPTIONS] = {0};
            int currentValue =
                cutting_options[i].value +
                rodCut(remainingLength - cutting_options[i].length,
                       tempCutCounts);

            if (currentValue > maxValue) {
                maxValue = currentValue;
                for (int j = 0; j < num_cutting_options; j++)
                    subCutCounts[j] = tempCutCounts[j];
                subCutCounts[i]++;
            }
        }
    }

    for (int j = 0; j < num_cutting_options; j++)
        cutCounts[j] = subCutCounts[j];

    return maxValue;
}

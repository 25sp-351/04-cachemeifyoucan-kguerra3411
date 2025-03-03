#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cutting_options.h"
#include "lru_cache.h"
#include "rod_cut.h"

// Function to read cutting options from a file
void readcutting_options_from_file(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Error: Unable to open file '%s'\n", filename);
        exit(1);
    }

    int length, value;
    while (fscanf(file, "%d, %d", &length, &value) == 2) {
        if (num_cutting_options < MAX_CUTTING_OPTIONS) {
            cutting_options[num_cutting_options].length = length;
            cutting_options[num_cutting_options].value  = value;
            num_cutting_options++;
        }
    }

    fclose(file);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <input_file_with_cutting_data>\n", argv[0]);
        return 1;
    }

    // Read cutting options from the input file
    readcutting_options_from_file(argv[1]);

    if (num_cutting_options == 0) {
        fprintf(stderr, "Error: No valid segment data provided.\n");
        return 1;
    }

    // Initialize the cache
    initCache();

    // Keep running the program until the user decides to exit
    while (1) {
        int totalRodLength;
        if (scanf("%d", &totalRodLength) != 1 || totalRodLength <= 0) {
            printf("Exiting\n");
            break;  // Exit loop when user enters 0 or invalid input
        }

        int cutCounts[MAX_CUTTING_OPTIONS] = {0};

        // Check cache first before calling rodCut()
        int maxValue = getFromCache(totalRodLength);
        if (maxValue == -1) {
            maxValue = rodCut(totalRodLength,
                              cutCounts);  // Call rodCut if not in cache
            insertIntoCache(totalRodLength,
                            maxValue);  // Insert the result into cache
        }

        int remainingRod = totalRodLength;
        int totalValue   = 0;

        for (int i = 0; i < num_cutting_options; i++) {
            if (cutCounts[i] > 0) {
                int value = cutCounts[i] * cutting_options[i].value;
                printf("%d @ %d = %d\n", cutCounts[i],
                       cutting_options[i].length, value);
                totalValue += value;
                remainingRod -= cutCounts[i] * cutting_options[i].length;
            }
        }

        printf("Remainder: %d\n", remainingRod);
        printf("Value: %d\n", totalValue);
    }

    return 0;
}

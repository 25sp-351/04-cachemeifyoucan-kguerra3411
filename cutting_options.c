#include "cutting_options.h"

#include <stdio.h>
#include <stdlib.h>

#define MAX_CUTTING_OPTIONS 100  // Define this or include it from somewhere

// Define the global variables here (no extern)
CuttingOption cutting_options[MAX_CUTTING_OPTIONS];
int num_cutting_options = 0;

void read_cutting_options() {
    while (num_cutting_options < MAX_CUTTING_OPTIONS) {
        int cutting_optionLength, cutting_optionValue;
        int user_input =
            scanf("%d, %d", &cutting_optionLength, &cutting_optionValue);

        if (user_input == EOF)
            break;

        if (user_input != 2) {
            fprintf(
                stderr,
                "Error: Invalid input format. Expected <length>, <value>.\n");
            exit(1);
        }

        if (cutting_optionLength > 0 && cutting_optionValue >= 0) {
            cutting_options[num_cutting_options].length = cutting_optionLength;
            cutting_options[num_cutting_options].value  = cutting_optionValue;
            num_cutting_options++;
        } else {
            fprintf(stderr,
                    "Error: Invalid cutting_option data. Ensure length > 0 and "
                    "value >= 0.\n");
            exit(1);
        }
    }
}

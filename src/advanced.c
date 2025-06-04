#include "advanced.h"

#define CBREAK current++; break;
char *largument;
char *gargument;
int current = 1;

int extras(int current, int argc, char **argv) {
    char *extras[current];
    while (current < argc) {
        if (strcmp(argv[current], "git")) extras[current] = "git";
        current++;
    }

    return 0;
}

int advanced_mode(int argc, char **argv) {
    char *name, *location, *language;
    while (current < argc) {
        if (argv[current][0] == '-') {
            largument = argv[current];
            gargument = largument;
            current++;
        } else {
            largument = NULL;
        }

        if (largument == NULL) {
            switch (gargument[1]) {
                case 'n':
                    name = argv[current];
                    CBREAK
                case 'o':
                    location = argv[current];
                    CBREAK
                case 'l':
                    language = argv[current];
                    CBREAK
                case 'e':
                    extras(current, argc, argv);
                    CBREAK;
            }
        }
    }

    if (name != NULL && location != NULL) {
        chdir(location);
        char buffer[64];
        sprintf(buffer, "mkdir -p %s", name);
        system(buffer);
    } else if (name != NULL) {
        char buffer[64];
        sprintf(buffer, "mkdir -p %s", name);
        system(buffer);
    } else {
        return 1;
    }

    return 0;
}
#include <string.h>
#include <ncurses.h>
#include "basic.h"
#include "advanced.h"


#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))

int main(int argc, char **argv) {
    if (argc < 2) { return basic_mode(); }
    else { return advanced_mode(argc, argv); }
}
#include "terminal.h"


void kernel_main(void) {
    terminal_initalize();
    terminal_write_cstring("Hello, kernel World!\n");

}


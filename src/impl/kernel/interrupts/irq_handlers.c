#include "irq_handlers.h"

void handle_irq0() {
    static int ticks = 0;
    ticks++;
    // Print the number of ticks (optional)
}

void handle_irq1() {
    // Handle keyboard interrupt here
}

#include "print.h"
#include "idt.h"
#include "irq.h"
#include "filesystem.h"

void kernel_main() {
    print_clear();
    print_set_color(PRINT_COLOR_YELLOW, PRINT_COLOR_BLACK);
    print_str("                               WELCOME TO VOXY OS\n");
    print_str("                     type 'help' to get a list of all commands\n");
    
    // First remap PIC
    remap_pic();    
    // Then initialize IDT
    idt_init();    
    // Finally enable interrupts
    asm volatile("sti");    
    // Initialise FileSystem
    init_filesystem();
    // Main kernel loop - prevent exit
    while(1) {
        asm volatile("hlt");
    }
}
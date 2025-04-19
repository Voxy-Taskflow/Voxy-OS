#include "print.h"
#include "idt.h"
#include "irq.h"

void kernel_main() {
    print_clear();
    print_set_color(PRINT_COLOR_YELLOW, PRINT_COLOR_BLACK);
    print_str("Welcome to our 64-bit kernel!\n");
    
    // First remap PIC
    remap_pic();
    print_str("PIC remapped\n");
    
    // Then initialize IDT
    idt_init();
    print_str("IDT initialized\n");
    
    // Finally enable interrupts
    asm volatile("sti");
    print_str("Interrupts enabled\n");
    
    // Main kernel loop - prevent exit
    while(1) {
        asm volatile("hlt");
    }
}
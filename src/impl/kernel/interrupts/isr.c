#include "print.h"
#include <stdint.h>

const char* exception_messages[] = {
    "Division by zero",
    "Debug",
    "Non Maskable Interrupts",
    "Breakpoint",
    "Into Detected Overflow",
    "Out of Bounds",
    "Invalid Opcode",
    "No Coprocessor",
    "Double Fault",
    "Coproccesor Segment Overrun",
    "Bad TSS",
    "Segment Not Present",
    "Stack Fault",
    "General Protection Fault",
    "Page Fault",
    "Unknown Interrupt",
    "FPU Fault",
    "Alignment Check",
    "Machine Check",
    "Reserved",
};

void isr_handler(int vector) {
    print_str("Interrupt Service Routine Handler\n");
    // Only halt on truly fatal exceptions
    if (vector == 8) {  // Double Fault
        print_str("Fatal double fault occurred. Halting.\n");
        while(1) asm volatile("hlt");
    }
    handle_exception(vector);
}

void handle_exception(int interrupt_number) {
    if (interrupt_number >= 32 && interrupt_number < 48) {
        // This is a hardware interrupt - let it pass through silently
        return;
    }

    print_set_color(PRINT_COLOR_RED, PRINT_COLOR_BLACK);
    print_str("Exception: ");
    
    if (interrupt_number >= 0 && interrupt_number < 20) {
        print_str(exception_messages[interrupt_number]);
        print_str("\n");
        // Only halt on severe exceptions
        if (interrupt_number == 0 || // Division by zero
            interrupt_number == 8 || // Double fault
            interrupt_number == 13 || // General Protection Fault
            interrupt_number == 14) { // Page Fault
            print_str("Fatal exception. System halted.\n");
            while(1) asm volatile("hlt");
        }
    } else {
        print_str("Unhandled interrupt: ");
        char num[8];
        int i = 0;
        int temp = interrupt_number;
        if (temp == 0) {
            print_char('0');
        } else {
            while (temp > 0) {
                num[i++] = '0' + (temp % 10);
                temp /= 10;
            }
            while (i > 0) {
                print_char(num[--i]);
            }
        }
        print_str("\n");
    }
}
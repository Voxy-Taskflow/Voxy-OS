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
    "Unkown Interrupt",
    "FPU Fault",
    "Alignment Check",
    "Machine Check",
    "Reserved",
};
void isr_handler(int vector){
    printf("[EXCEPTION] %s (vector %d)\n", exception_messages[vector], vector);
    if (vector == 8 || vector == 13, vector == 14 || vector == 18){
        printf("Fatal exception occured. Halting. \n");
        while(1) asm volatile("hlt");
    }
}
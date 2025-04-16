#include <idt.h>
#include <irq.h>

#define IDT_ENTRIES 256
struct idt_entry idt[IDT_ENTRIES];
struct idt_ptr idtp;

extern void irq0();
extern void irq1();
extern void (*isr_stub_table[])(); // for exceptions 0-31 (optional)

void set_idt_gate(int n, uint64_t handler) {
    idt[n].offset_low    = handler & 0xFFFF;
    idt[n].selector      = 0x08; // kernel code segment
    idt[n].ist           = 0;
    idt[n].type_attr     = 0x8E; // interrupt gate
    idt[n].offset_middle = (handler >> 16) & 0xFFFF;
    idt[n].offset_high   = (handler >> 32) & 0xFFFFFFFF;
    idt[n].zero          = 0;
}

void load_idt() {
    idtp.limit = sizeof(struct idt_entry) * IDT_ENTRIES - 1;
    idtp.base = (uint64_t)&idt;
    asm volatile("lidt %0" : : "m"(idtp));
}

void idt_init() {
    // CPU exceptions
    for (int i = 0; i < 32; i++) {
        set_idt_gate(i, (uint64_t)isr_stub_table[i]);
    }

    // Hardware IRQs
    set_idt_gate(32, (uint64_t)irq0); // Timer
    set_idt_gate(33, (uint64_t)irq1); // Keyboard

    load_idt();
}

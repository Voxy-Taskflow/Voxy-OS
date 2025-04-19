#ifndef IRQ_H
#define IRQ_H

void remap_pic();
void send_eoi(unsigned char irq);

#endif

section .text
global irq0, irq1
extern send_eoi

extern handle_irq0
extern handle_irq1

irq0:
    cli
    push rbp
    mov rbp, rsp
    call handle_irq0
    pop rbp
    call send_eoi
    iretq

irq1:
    cli
    push rbp
    mov rbp, rsp
    call handle_irq1
    pop rbp
    call send_eoi
    iretq

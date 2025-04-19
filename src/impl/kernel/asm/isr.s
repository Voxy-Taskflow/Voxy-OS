section .text
global isr_stub_table
global isr_stub_0
global isr_common_stub

extern handle_exception
global unhandled_interrupt_stub

; Table of 32 exception stub addresses
isr_stub_table:
%assign i 0
%rep 32
    dq isr_stub_%+i
%assign i i+1
%endrep

; Define ISR stub macro
%macro ISR_STUB 1
global isr_stub_%1
isr_stub_%1:
    cli
    push 0
    push %1
    jmp isr_common_stub
%endmacro

; Expand ISR_STUB macro to generate 32 handlers
%assign i 0
%rep 32
    ISR_STUB i
%assign i i+1
%endrep

; Common stub handler
isr_common_stub:
    ; Save registers manually, since x86_64 doesn't support pushaq/popa
    push rax
    push rcx
    push rdx
    push rbx
    push rsp
    push rbp
    push rsi
    push rdi
    push r8
    push r9
    push r10
    push r11
    push r12
    push r13
    push r14
    push r15

    mov rdi, [rsp + 15*8] ; rdi = interrupt number (it's after 15 pushes)
    call handle_exception

    pop r15
    pop r14
    pop r13
    pop r12
    pop r11
    pop r10
    pop r9
    pop r8
    pop rdi
    pop rsi
    pop rbp
    pop rsp
    pop rbx
    pop rdx
    pop rcx
    pop rax

    add rsp, 16 ; clean up interrupt number + error code
    sti
    iretq


unhandled_interrupt_stub:
    cli
    pushaq
    mov rdi, 999           ; Use a dummy number or dynamically load it later
    call handle_exception
    popaq
    sti
    iretq

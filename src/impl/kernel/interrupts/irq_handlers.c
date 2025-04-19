#include "irq_handlers.h"
#include "print.h"
#include <irq.h>
#include <stdint.h>
#include <io.h>

int x;
int y;

#define a_released 0x9E
#define b_released 0xB0
#define c_released 0xAE
#define d_released 0xA0
#define e_released 0x92
#define f_released 0xA1
#define g_released 0xA2
#define h_released 0xA3
#define i_released 0x97
#define j_released 0xA4
#define k_released 0xA5
#define l_released 0xA6
#define m_released 0xB2
#define n_released 0xB1
#define o_released 0x98
#define p_released 0x99
#define q_released 0x90
#define r_released 0x93
#define s_released 0x9F
#define t_released 0x94
#define u_released 0x96
#define v_released 0x9F
#define w_released 0x91
#define x_released 0xAD
#define y_released 0x95
#define z_released 0xAC
#define released_1 0x82
#define released_2 0x83
#define released_3 0x84
#define released_4 0x85
#define released_5 0x86
#define released_6 0x87
#define released_7 0x88
#define released_8 0x89
#define released_9 0x8A
#define released_0 0x8B
#define enter_released 0x9C
#define space_released 0xB9
#define backspace_released 0x8E

static inline void outb(uint16_t port, uint8_t val) {
    asm volatile ("outb %0, %1" : : "a"(val), "Nd"(port));
}
void set_cursor(int pos){
    outb(0x3D4, 0x0E);
    outb(0x305, (pos >> 8) & 0xFF);
    outb(0x3D4, 0x0F);
    outb(0X3D5, pos & 0xFF);
}

void irq1_keyboard(uint16_t scan_code){
    if (x < 0){
        x = 0;
    }else if (x > 79){
        x = 79;
    }
    if (y < 0){
        y = 0;
    }else if (y > 24){
        y = 24;
    }

    int cursor_pos = y * 80 + x;

    set_cursor(cursor_pos);

    if(scan_code == a_released){
        print_set_color(PRINT_COLOR_YELLOW, PRINT_COLOR_BLACK);
        print_char('a');
    }
    if(scan_code == b_released){
        print_set_color(PRINT_COLOR_YELLOW, PRINT_COLOR_BLACK);
        print_char('b');
    }
    if(scan_code == c_released){
        print_set_color(PRINT_COLOR_YELLOW, PRINT_COLOR_BLACK);
        print_char('c');
    }
    if(scan_code == d_released){
        print_set_color(PRINT_COLOR_YELLOW, PRINT_COLOR_BLACK);
        print_char('d');
    }
    if(scan_code == e_released){
        print_set_color(PRINT_COLOR_YELLOW, PRINT_COLOR_BLACK);
        print_char('e');
    }
    if(scan_code == f_released){
        print_set_color(PRINT_COLOR_YELLOW, PRINT_COLOR_BLACK);
        print_char('f');
    }
    if(scan_code == g_released){
        print_set_color(PRINT_COLOR_YELLOW, PRINT_COLOR_BLACK);
        print_char('g');
    }
    if(scan_code == h_released){
        print_set_color(PRINT_COLOR_YELLOW, PRINT_COLOR_BLACK);
        print_char('h');
    }
    if(scan_code == i_released){
        print_set_color(PRINT_COLOR_YELLOW, PRINT_COLOR_BLACK);
        print_char('i');
    }
    if(scan_code == j_released){
        print_set_color(PRINT_COLOR_YELLOW, PRINT_COLOR_BLACK);
        print_char('j');
    }
    if(scan_code == k_released){
        print_set_color(PRINT_COLOR_YELLOW, PRINT_COLOR_BLACK);
        print_char('k');
    }
    if(scan_code == l_released){
        print_set_color(PRINT_COLOR_YELLOW, PRINT_COLOR_BLACK);
        print_char('l');
    }
    if(scan_code == m_released){
        print_set_color(PRINT_COLOR_YELLOW, PRINT_COLOR_BLACK);
        print_char('m');
    }
    if(scan_code == n_released){
        print_set_color(PRINT_COLOR_YELLOW, PRINT_COLOR_BLACK);
        print_char('n');
    }
    if(scan_code == o_released){
        print_set_color(PRINT_COLOR_YELLOW, PRINT_COLOR_BLACK);
        print_char('o');
    }
    if(scan_code == p_released){
        print_set_color(PRINT_COLOR_YELLOW, PRINT_COLOR_BLACK);
        print_char('p');
    }
    if(scan_code == q_released){
        print_set_color(PRINT_COLOR_YELLOW, PRINT_COLOR_BLACK);
        print_char('q');
    }
    if(scan_code == r_released){
        print_set_color(PRINT_COLOR_YELLOW, PRINT_COLOR_BLACK);
        print_char('r');
    }
    if(scan_code == s_released){
        print_set_color(PRINT_COLOR_YELLOW, PRINT_COLOR_BLACK);
        print_char('s');
    }
    if(scan_code == t_released){
        print_set_color(PRINT_COLOR_YELLOW, PRINT_COLOR_BLACK);
        print_char('t');
    }
    if(scan_code == u_released){
        print_set_color(PRINT_COLOR_YELLOW, PRINT_COLOR_BLACK);
        print_char('u');
    }
    if(scan_code == v_released){
        print_set_color(PRINT_COLOR_YELLOW, PRINT_COLOR_BLACK);
        print_char('v');
    }
    if(scan_code == w_released){
        print_set_color(PRINT_COLOR_YELLOW, PRINT_COLOR_BLACK);
        print_char('w');
    }
    if(scan_code == x_released){
        print_set_color(PRINT_COLOR_YELLOW, PRINT_COLOR_BLACK);
        print_char('x');
    }
    if(scan_code == y_released){
        print_set_color(PRINT_COLOR_YELLOW, PRINT_COLOR_BLACK);
        print_char('y');
    }
    if(scan_code == z_released){
        print_set_color(PRINT_COLOR_YELLOW, PRINT_COLOR_BLACK);
        print_char('z');
    }
    if(scan_code == released_1){
        print_set_color(PRINT_COLOR_YELLOW, PRINT_COLOR_BLACK);
        print_char('1');
    }
    if(scan_code == released_2){
        print_set_color(PRINT_COLOR_YELLOW, PRINT_COLOR_BLACK);
        print_char('2');
    }
    if(scan_code == released_3){
        print_set_color(PRINT_COLOR_YELLOW, PRINT_COLOR_BLACK);
        print_char('3');
    }
    if(scan_code == released_4){
        print_set_color(PRINT_COLOR_YELLOW, PRINT_COLOR_BLACK);
        print_char('4');
    }
    if(scan_code == released_5){
        print_set_color(PRINT_COLOR_YELLOW, PRINT_COLOR_BLACK);
        print_char('5');
    }
    if(scan_code == released_6){
        print_set_color(PRINT_COLOR_YELLOW, PRINT_COLOR_BLACK);
        print_char('6');
    }
    if(scan_code == released_7){
        print_set_color(PRINT_COLOR_YELLOW, PRINT_COLOR_BLACK);
        print_char('7');
    }
    if(scan_code == released_8){
        print_set_color(PRINT_COLOR_YELLOW, PRINT_COLOR_BLACK);
        print_char('8');
    }
    if(scan_code == released_9){
        print_set_color(PRINT_COLOR_YELLOW, PRINT_COLOR_BLACK);
        print_char('9');
    }
    if(scan_code == released_0){
        print_set_color(PRINT_COLOR_YELLOW, PRINT_COLOR_BLACK);
        print_char('0');
    }
    if(scan_code == enter_released){
        print_set_color(PRINT_COLOR_YELLOW, PRINT_COLOR_BLACK);
        print_str("\n");
    }
    if (scan_code == space_released)
    {
        print_str(" ");
    }
    if(scan_code == backspace_released){
        // Go Back
        //Remove letter
    }
    
}


void handle_irq0() {
    static int ticks = 0;
    ticks++;
    if (ticks % 100 == 0) {

    }
    send_eoi(0);
}

void handle_irq1() {
    uint16_t scan_code = inb(0x60);
    irq1_keyboard(scan_code);
    send_eoi(1);
}

// Add this function to handle other IRQs
void handle_irq_default(int irq) {
    send_eoi(irq);
}
#include "irq_handlers.h"
#include "print.h"
#include <irq.h>
#include <stdint.h>
#include <io.h>
#include <strings.h>

int x = 0;
int y = 1;
int capslock = 0; // capslock = 0 (turned off), capslock = 1 (turned on)
int is_extended = 0;
char buffer_input[128];
int index = 0;

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
#define v_released 0xAF
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
#define backspace_pressed 0x0E
#define capslock_pressed 0x3A

void clear_buffer(){
    for(int i; i < 128; i++){
        buffer_input[i] = '\0';
    }
    index = 0;
}

void help_called(){
    print_set_color(PRINT_COLOR_GREEN, PRINT_COLOR_BLACK);
    print_str("Called for help\n");
}

void ver_called(){
    print_set_color(PRINT_COLOR_GREEN, PRINT_COLOR_BLACK);
    print_str("beta-0.01\n");
}
void start_installation(){
    //INSTALLATION
    print_set_color(PRINT_COLOR_GREEN, PRINT_COLOR_BLACK);
    print_str("Starting Installation...\n");
}

void check_command(){
    //help
    if(strings_equal(buffer_input, "help")){
        help_called();
    }
    //version
    if(strings_equal(buffer_input, "ver")){
        ver_called();
    }
    //install
    if (strings_equal(buffer_input, "install"))
    {
        start_installation();
    }
    //Clear Buffer(SHOULD BE AT LAST)
    clear_buffer();
}

static inline void outb(uint16_t port, uint8_t val) {
    asm volatile ("outb %0, %1" : : "a"(val), "Nd"(port));
}

void set_cursor(int pos){
    outb(0x3D4, 0x0E);
    outb(0x305, (pos >> 8) & 0xFF);
    outb(0x3D4, 0x0F);
    outb(0X3D5, pos & 0xFF);
}

void check_bounds(){
    if (x < 0){
        x = 0;
    }else if (x > 79){
        y++;
        x = 0;
    }
    if (y < 0){
        y = 0;
    }else if (y > 24){
        y = 24;
    }
    
    int cursor_pos = y * 80 + x;
    set_cursor(cursor_pos);
}

void addToBuffer(char typed_char){
    if(index < 255){
        buffer_input[index++] = typed_char;
    }
}

void removeFromBuffer(){
    if(index > 0){
        buffer_input[index--] = ' ';
    }
}

void irq1_keyboard(uint16_t scan_code){
    if(scan_code == a_released && capslock == 0){
        x++;
        check_bounds();
        print_set_color(PRINT_COLOR_YELLOW, PRINT_COLOR_BLACK);
        print_char('a');
        addToBuffer('a');
    }else if(scan_code == a_released && capslock == 1){
        x++;
        check_bounds();
        print_set_color(PRINT_COLOR_YELLOW, PRINT_COLOR_BLACK);
        print_char('A');
        addToBuffer('A');
    }
    if(scan_code == b_released && capslock == 0){
        x++;
        check_bounds();
        print_set_color(PRINT_COLOR_YELLOW, PRINT_COLOR_BLACK);
        print_char('b');
        addToBuffer('b');
    }else if (scan_code == b_released && capslock == 1)
    {
        x++;
        check_bounds();
        print_set_color(PRINT_COLOR_YELLOW, PRINT_COLOR_BLACK);
        print_char('B');
        addToBuffer('B');
    } 
    if(scan_code == c_released && capslock == 0){
        x++;
        check_bounds();
        print_set_color(PRINT_COLOR_YELLOW, PRINT_COLOR_BLACK);
        print_char('c');
        addToBuffer('c');
    }else if (scan_code == c_released && capslock == 1)
    {
        x++;
        check_bounds();
        print_set_color(PRINT_COLOR_YELLOW, PRINT_COLOR_BLACK);
        print_char('C');
        addToBuffer('C');
    }
    if(scan_code == d_released && capslock == 0){
        x++;
        check_bounds();
        print_set_color(PRINT_COLOR_YELLOW, PRINT_COLOR_BLACK);
        print_char('d');
        addToBuffer('d');
    }else if(scan_code == e_released && capslock == 1){
        x++;
        check_bounds();
        print_set_color(PRINT_COLOR_YELLOW, PRINT_COLOR_BLACK);
        print_char('D');
        addToBuffer('D');
    }
    if(scan_code == e_released && capslock == 0){
        x++;
        check_bounds();
        print_set_color(PRINT_COLOR_YELLOW, PRINT_COLOR_BLACK);
        print_char('e');
        addToBuffer('e');
    }else if(scan_code == e_released && capslock == 1){
        x++;
        check_bounds();
        print_set_color(PRINT_COLOR_YELLOW, PRINT_COLOR_BLACK);
        print_char('E');
        addToBuffer('E');
    }
    if(scan_code == f_released && capslock == 0){
        x++;
        check_bounds();
        print_set_color(PRINT_COLOR_YELLOW, PRINT_COLOR_BLACK);
        print_char('f');
        addToBuffer('f');
    }else if(scan_code == f_released && capslock == 1){
        x++;
        check_bounds();
        print_set_color(PRINT_COLOR_YELLOW, PRINT_COLOR_BLACK);
        print_char('F');
        addToBuffer('F');
    }
    if(scan_code == g_released && capslock == 0){
        x++;
        check_bounds();
        print_set_color(PRINT_COLOR_YELLOW, PRINT_COLOR_BLACK);
        print_char('g');
        addToBuffer('g');
    }else if(scan_code == g_released && capslock == 1){
        x++;
        check_bounds();
        print_set_color(PRINT_COLOR_YELLOW, PRINT_COLOR_BLACK);
        print_char('G');
        addToBuffer('G');
    }
    if(scan_code == h_released && capslock == 0){
        x++;
        check_bounds();
        print_set_color(PRINT_COLOR_YELLOW, PRINT_COLOR_BLACK);
        print_char('h');
        addToBuffer('h');
    }else if(scan_code == h_released && capslock == 1){
        x++;
        check_bounds();
        print_set_color(PRINT_COLOR_YELLOW, PRINT_COLOR_BLACK);
        print_char('H');
        addToBuffer('H');
    }
    if(scan_code == i_released && capslock == 0){
        x++;
        check_bounds();
        print_set_color(PRINT_COLOR_YELLOW, PRINT_COLOR_BLACK);
        print_char('i');
        addToBuffer('i');
    }else if(scan_code == i_released && capslock == 1){
        x++;
        check_bounds();
        print_set_color(PRINT_COLOR_YELLOW, PRINT_COLOR_BLACK);
        print_char('I');
        addToBuffer('I');
    }
    if(scan_code == j_released && capslock == 0){
        x++;
        check_bounds();
        print_set_color(PRINT_COLOR_YELLOW, PRINT_COLOR_BLACK);
        print_char('j');
        addToBuffer('j');
    }else if(scan_code == j_released && capslock == 1){
        x++;
        check_bounds();
        print_set_color(PRINT_COLOR_YELLOW, PRINT_COLOR_BLACK);
        print_char('J');
        addToBuffer('J');
    }
    if(scan_code == k_released && capslock == 0){
        x++;
        check_bounds();
        print_set_color(PRINT_COLOR_YELLOW, PRINT_COLOR_BLACK);
        print_char('k');
        addToBuffer('k');
    }else if(scan_code == k_released && capslock == 1){
        x++;
        check_bounds();
        print_set_color(PRINT_COLOR_YELLOW, PRINT_COLOR_BLACK);
        print_char('K');
        addToBuffer('K');
    }
    if(scan_code == l_released && capslock == 0){
        x++;
        check_bounds();
        print_set_color(PRINT_COLOR_YELLOW, PRINT_COLOR_BLACK);
        print_char('l');
        addToBuffer('l');
    }else if(scan_code == l_released && capslock == 1){
        x++;
        check_bounds();
        print_set_color(PRINT_COLOR_YELLOW, PRINT_COLOR_BLACK);
        print_char('L');
        addToBuffer('L');
    }
    if(scan_code == m_released && capslock == 0){
        x++;
        check_bounds();
        print_set_color(PRINT_COLOR_YELLOW, PRINT_COLOR_BLACK);
        print_char('m');
        addToBuffer('m');
    }else if(scan_code == m_released && capslock == 1){
        x++;
        check_bounds();
        print_set_color(PRINT_COLOR_YELLOW, PRINT_COLOR_BLACK);
        print_char('M');
        addToBuffer('M');
    }
    if(scan_code == n_released && capslock == 0){
        x++;
        check_bounds();
        print_set_color(PRINT_COLOR_YELLOW, PRINT_COLOR_BLACK);
        print_char('n');
        addToBuffer('n');
    }else if(scan_code == n_released && capslock == 1){
        x++;
        check_bounds();
        print_set_color(PRINT_COLOR_YELLOW, PRINT_COLOR_BLACK);
        print_char('N');
        addToBuffer('N');
    }
    if(scan_code == o_released && capslock == 0){
        x++;
        check_bounds();
        print_set_color(PRINT_COLOR_YELLOW, PRINT_COLOR_BLACK);
        print_char('o');
        addToBuffer('o');
    }else if(scan_code == o_released && capslock == 1){
        x++;
        check_bounds();
        print_set_color(PRINT_COLOR_YELLOW, PRINT_COLOR_BLACK);
        print_char('O');
        addToBuffer('O');
    }
    if(scan_code == p_released && capslock == 0){
        x++;
        check_bounds();
        print_set_color(PRINT_COLOR_YELLOW, PRINT_COLOR_BLACK);
        print_char('p');
        addToBuffer('p');
    }else if(scan_code == p_released && capslock == 1){
        x++;
        check_bounds();
        print_set_color(PRINT_COLOR_YELLOW, PRINT_COLOR_BLACK);
        print_char('P');
        addToBuffer('P');
    }
    if(scan_code == q_released && capslock == 0){
        x++;
        check_bounds();
        print_set_color(PRINT_COLOR_YELLOW, PRINT_COLOR_BLACK);
        print_char('q');
        addToBuffer('q');
    }else if(scan_code == q_released && capslock == 1){
        x++;
        check_bounds();
        print_set_color(PRINT_COLOR_YELLOW, PRINT_COLOR_BLACK);
        print_char('Q');
        addToBuffer('Q');
    }
    if(scan_code == r_released && capslock == 0){
        x++;
        check_bounds();
        print_set_color(PRINT_COLOR_YELLOW, PRINT_COLOR_BLACK);
        print_char('r');
        addToBuffer('r');
    }else if(scan_code == r_released && capslock == 1){
        x++;
        check_bounds();
        print_set_color(PRINT_COLOR_YELLOW, PRINT_COLOR_BLACK);
        print_char('R');
        addToBuffer('R');
    }
    if(scan_code == s_released && capslock == 0){
        x++;
        check_bounds();
        print_set_color(PRINT_COLOR_YELLOW, PRINT_COLOR_BLACK);
        print_char('s');
        addToBuffer('s');
    }else if(scan_code == s_released && capslock == 1){
        x++;
        check_bounds();
        print_set_color(PRINT_COLOR_YELLOW, PRINT_COLOR_BLACK);
        print_char('S');
        addToBuffer('S');
    }
    if(scan_code == t_released && capslock == 0){
        x++;
        check_bounds();
        print_set_color(PRINT_COLOR_YELLOW, PRINT_COLOR_BLACK);
        print_char('t');
        addToBuffer('t');
    }else if(scan_code == t_released && capslock == 1){
        x++;
        check_bounds();
        print_set_color(PRINT_COLOR_YELLOW, PRINT_COLOR_BLACK);
        print_char('T');
        addToBuffer('T');
    }
    if(scan_code == u_released && capslock == 0){
        x++;
        check_bounds();
        print_set_color(PRINT_COLOR_YELLOW, PRINT_COLOR_BLACK);
        print_char('u');
        addToBuffer('u');
    }else if(scan_code == u_released && capslock == 1){
        x++;
        check_bounds();
        print_set_color(PRINT_COLOR_YELLOW, PRINT_COLOR_BLACK);
        print_char('U');
        addToBuffer('U');
    }
    if(scan_code == v_released && capslock == 0){
        x++;
        check_bounds();
        print_set_color(PRINT_COLOR_YELLOW, PRINT_COLOR_BLACK);
        print_char('v');
        addToBuffer('v');
    }else if(scan_code == v_released && capslock == 1){
        x++;
        check_bounds();
        print_set_color(PRINT_COLOR_YELLOW, PRINT_COLOR_BLACK);
        print_char('V');
        addToBuffer('V');
    }
    if(scan_code == w_released && capslock == 0){
        x++;
        check_bounds();
        print_set_color(PRINT_COLOR_YELLOW, PRINT_COLOR_BLACK);
        print_char('w');
        addToBuffer('a');
    }else if(scan_code == w_released && capslock == 1){
        x++;
        check_bounds();
        print_set_color(PRINT_COLOR_YELLOW, PRINT_COLOR_BLACK);
        print_char('W');
        addToBuffer('W');
    }
    if(scan_code == x_released && capslock == 0){
        x++;
        check_bounds();
        print_set_color(PRINT_COLOR_YELLOW, PRINT_COLOR_BLACK);
        print_char('x');
        addToBuffer('x');
    }else if(scan_code == x_released && capslock == 1){
        x++;
        check_bounds();
        print_set_color(PRINT_COLOR_YELLOW, PRINT_COLOR_BLACK);
        print_char('X');
        addToBuffer('X');
    }
    if(scan_code == y_released && capslock == 0){
        x++;
        check_bounds();
        print_set_color(PRINT_COLOR_YELLOW, PRINT_COLOR_BLACK);
        print_char('y');
        addToBuffer('y');
    }else if(scan_code == y_released && capslock == 1){
        x++;
        check_bounds();
        print_set_color(PRINT_COLOR_YELLOW, PRINT_COLOR_BLACK);
        print_char('Y');
        addToBuffer('Y');
    }
    if(scan_code == z_released && capslock == 0){
        x++;
        check_bounds();
        print_set_color(PRINT_COLOR_YELLOW, PRINT_COLOR_BLACK);
        print_char('z');
        addToBuffer('z');
    }else if(scan_code == z_released && capslock == 1){
        x++;
        check_bounds();
        print_set_color(PRINT_COLOR_YELLOW, PRINT_COLOR_BLACK);
        print_char('Z');
        addToBuffer('Z');
    }
    if(scan_code == released_1){
        x++;
        check_bounds();
        print_set_color(PRINT_COLOR_YELLOW, PRINT_COLOR_BLACK);
        print_char('1');
        addToBuffer('1');
    }
    if(scan_code == released_2){
        x++;
        check_bounds();
        print_set_color(PRINT_COLOR_YELLOW, PRINT_COLOR_BLACK);
        print_char('2');
        addToBuffer('2');
    }
    if(scan_code == released_3){
        x++;
        check_bounds();
        print_set_color(PRINT_COLOR_YELLOW, PRINT_COLOR_BLACK);
        print_char('3');
        addToBuffer('3');
    }
    if(scan_code == released_4){
        x++;
        check_bounds();
        print_set_color(PRINT_COLOR_YELLOW, PRINT_COLOR_BLACK);
        print_char('4');
        addToBuffer('4');
    }
    if(scan_code == released_5){
        x++;
        check_bounds();
        print_set_color(PRINT_COLOR_YELLOW, PRINT_COLOR_BLACK);
        print_char('5');
        addToBuffer('5');
    }
    if(scan_code == released_6){
        x++;
        check_bounds();
        print_set_color(PRINT_COLOR_YELLOW, PRINT_COLOR_BLACK);
        print_char('6');
        addToBuffer('6');
    }
    if(scan_code == released_7){
        x++;
        check_bounds();
        print_set_color(PRINT_COLOR_YELLOW, PRINT_COLOR_BLACK);
        print_char('7');
        addToBuffer('7');
    }
    if(scan_code == released_8){
        x++;
        check_bounds();
        print_set_color(PRINT_COLOR_YELLOW, PRINT_COLOR_BLACK);
        print_char('8');
        addToBuffer('8');
    }
    if(scan_code == released_9){
        x++;
        check_bounds();
        print_set_color(PRINT_COLOR_YELLOW, PRINT_COLOR_BLACK);
        print_char('9');
        addToBuffer('9');
    }
    if(scan_code == released_0){
        x++;
        check_bounds();
        print_set_color(PRINT_COLOR_YELLOW, PRINT_COLOR_BLACK);
        print_char('0');
        addToBuffer('0');
    }
    if(scan_code == enter_released){
        y++;
        x = 0;
        check_bounds();
        print_str("\n");
        check_command();
    }
    if(scan_code == space_released)
    {
        x++;
        check_bounds();
        print_str(" ");
        addToBuffer(' ');
    }
    if(scan_code == backspace_pressed){
        if (x == 0){
            y--;
            x = 79;
        }else{
            x--;
        }
        uint16_t pos = y * 80 + x;
        char* video = (char*) 0xB8000;
        video[pos * 2] = ' ';
        video[pos * 2 + 1] = 0x07;
        int pos_cursor = y * 80 + x;
        set_cursor(pos_cursor);
        removeFromBuffer();
    }
    if(scan_code == capslock_pressed){
        if(scan_code == capslock_pressed){
            capslock = 1; // Turn on
        }
        if(capslock == 1){
            capslock = 0;
        }
    }
    if (is_extended == 1) // movement inside the terminal
    {
        is_extended = 0;
        if(scan_code == 0x4B){//left
            if(x>0) x--;
        }else if(scan_code == 0x4D){//right
            if(x<79) x++;
        }else if(scan_code == 0x48){//up
            if(y>0) y--;
        }else if(scan_code == 0x50){//down
            if(y<24) y++;
        }
        set_cursor(y*80+x);
        return;
    }
}


void handle_irq0() {
    static int ticks = 0;
    ticks++;
    send_eoi(0);
}

void handle_irq1() {
    uint16_t scan_code = inb(0x60);
    if (scan_code == 0XE0){
        is_extended = 1;
        send_eoi(1);
        return;
    }
    irq1_keyboard(scan_code);
    send_eoi(1);
}

// Add this function to handle other IRQs
void handle_irq_default(int irq) {
    send_eoi(irq);
}
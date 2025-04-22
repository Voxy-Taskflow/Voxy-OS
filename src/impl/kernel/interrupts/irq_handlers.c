#include "irq_handlers.h"
#include "print.h"
#include <irq.h>
#include <stdint.h>
#include <io.h>
#include <strings.h>
#include <filesystem.h>

int x = 0;
int y = 2;
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

static inline void outb(uint16_t port, uint8_t val) {
    asm volatile ("outb %0, %1" : : "a"(val), "Nd"(port));
}

void set_cursor(int pos) {
    if(pos >= 0 && pos < 2000) { // 80x25 = 2000 positions
        outb(0x3D4, 0x0F);
        outb(0x3D5, (uint8_t)(pos & 0xFF));
        outb(0x3D4, 0x0E);
        outb(0x3D5, (uint8_t)((pos >> 8) & 0xFF));
    }
}

void clear_buffer(){
    for(int i; i < 128; i++){
        buffer_input[i] = '\0';
    }
    index = 0;
}

void clear_screen(){
    print_clear();
    clear_buffer();
}

void help_called(){
    print_set_color(PRINT_COLOR_GREEN, PRINT_COLOR_BLACK);
    print_str("Available Commands :-\n");
    print_str("1) ver :- check the vesion of VoxyOS you are running\n");
    print_str("2) install :- start the installation process\n");
    print_str("3) clear :- clear the screen\n");
    print_str("4) fnd :- find a file\n");
    print_str("5) cr :- create a file\n");
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

void find_called(){
    print_set_color(PRINT_COLOR_BLUE, PRINT_COLOR_BLACK);
    print_str("Please enter the name of the file you want to find:-  ");
    clear_buffer();
    uint16_t scan_code = inb(0x60);
    int a = 0;
    while(a==0)
    {
        if (scan_code == enter_released)
        {
            find_file(buffer_input);
            a = 1;
        }
    }
}

void create_called(){
    print_set_color(PRINT_COLOR_BLUE, PRINT_COLOR_BLACK);
    print_str("Name the file{max length 32 chars}:-  ");
    clear_buffer();
    uint16_t scan_code = inb(0x60);
    int a = 0;
    while(a==0)
    {
        if (scan_code == enter_released)
        {
            create_file(buffer_input);
            a = 1;
        }
    }
}

void check_command() {
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
    //clear screen and reset cursor
    if(strings_equal(buffer_input, "clear")){
        clear_screen();
        x=0;
        y=0;
        int cursor_pos = y*80+x;
        set_cursor(cursor_pos);
    }
    //find a file
    if(strings_equal(buffer_input, "fndf")){
        find_called();
    }
    //create a file
    if(strings_equal(buffer_input, "crtf")){
        create_called();
    }
    
    // Add new commands
    if(strings_equal(buffer_input, "ld")) {
        list_directories();
    }
    if(strings_equal(buffer_input, "fndd")) {
        print_set_color(PRINT_COLOR_BLUE, PRINT_COLOR_BLACK);
        print_str("\nEnter directory name to find: ");
        clear_buffer();
        while(1) {
            uint16_t scan_code = inb(0x60);
            if (scan_code == enter_released) {
                find_folder(buffer_input);
                break;
            }
        }
    }
    // Clear buffer remains at the end
    clear_buffer();
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

void print_char_at_cursor(char c, uint8_t color) {
    uint16_t pos = y * 80 + x;
    char* video = (char*)0xB8000;
    video[pos * 2] = c;
    video[pos * 2 + 1] = color;
    x++;
    if(x >= 80) {
        x = 0;
        y++;
        if(y >= 25) {
            // Scroll screen
            for(int i = 0; i < 24 * 80 * 2; i++) {
                video[i] = video[i + 160];
            }
            // Clear last line
            for(int i = 24 * 80 * 2; i < 25 * 80 * 2; i += 2) {
                video[i] = ' ';
                video[i + 1] = color;
            }
            y = 24;
        }
    }
    set_cursor(y * 80 + x);
}

// Update the keyboard handler to use print_char_at_cursor
// Replace all instances of print_char with print_char_at_cursor in the keyboard handling code
// Example:
void irq1_keyboard(uint16_t scan_code) {
    if(scan_code == a_released && capslock == 0) {
        print_char_at_cursor('a', PRINT_COLOR_YELLOW | (PRINT_COLOR_BLACK << 4));
        addToBuffer('a');
    } else if(scan_code == a_released && capslock == 1) {
        print_char_at_cursor('A', PRINT_COLOR_YELLOW | (PRINT_COLOR_BLACK << 4));
        addToBuffer('A');
    }
    if(scan_code == b_released && capslock == 0) {
        print_char_at_cursor('b', PRINT_COLOR_YELLOW | (PRINT_COLOR_BLACK << 4));
        addToBuffer('b');
    } else if (scan_code == b_released && capslock == 1) {
        print_char_at_cursor('B', PRINT_COLOR_YELLOW | (PRINT_COLOR_BLACK << 4));
        addToBuffer('B');
    } 
    if(scan_code == c_released && capslock == 0) {
        print_char_at_cursor('c', PRINT_COLOR_YELLOW | (PRINT_COLOR_BLACK << 4));
        addToBuffer('c');
    } else if (scan_code == c_released && capslock == 1) {
        print_char_at_cursor('C', PRINT_COLOR_YELLOW | (PRINT_COLOR_BLACK << 4));
        addToBuffer('C');
    }
    if(scan_code == d_released && capslock == 0) {
        print_char_at_cursor('d', PRINT_COLOR_YELLOW | (PRINT_COLOR_BLACK << 4));
        addToBuffer('d');
    } else if(scan_code == e_released && capslock == 1) {
        print_char_at_cursor('D', PRINT_COLOR_YELLOW | (PRINT_COLOR_BLACK << 4));
        addToBuffer('D');
    }
    if(scan_code == e_released && capslock == 0) {
        print_char_at_cursor('e', PRINT_COLOR_YELLOW | (PRINT_COLOR_BLACK << 4));
        addToBuffer('e');
    } else if(scan_code == e_released && capslock == 1) {
        print_char_at_cursor('E', PRINT_COLOR_YELLOW | (PRINT_COLOR_BLACK << 4));
        addToBuffer('E');
    }
    if(scan_code == f_released && capslock == 0) {
        print_char_at_cursor('f', PRINT_COLOR_YELLOW | (PRINT_COLOR_BLACK << 4));
        addToBuffer('f');
    } else if(scan_code == f_released && capslock == 1) {
        print_char_at_cursor('F', PRINT_COLOR_YELLOW | (PRINT_COLOR_BLACK << 4));
        addToBuffer('F');
    }
    if(scan_code == g_released && capslock == 0) {
        print_char_at_cursor('g', PRINT_COLOR_YELLOW | (PRINT_COLOR_BLACK << 4));
        addToBuffer('g');
    } else if(scan_code == g_released && capslock == 1) {
        print_char_at_cursor('G', PRINT_COLOR_YELLOW | (PRINT_COLOR_BLACK << 4));
        addToBuffer('G');
    }
    if(scan_code == h_released && capslock == 0) {
        print_char_at_cursor('h', PRINT_COLOR_YELLOW | (PRINT_COLOR_BLACK << 4));
        addToBuffer('h');
    } else if(scan_code == h_released && capslock == 1) {
        print_char_at_cursor('H', PRINT_COLOR_YELLOW | (PRINT_COLOR_BLACK << 4));
        addToBuffer('H');
    }
    if(scan_code == i_released && capslock == 0) {
        print_char_at_cursor('i', PRINT_COLOR_YELLOW | (PRINT_COLOR_BLACK << 4));
        addToBuffer('i');
    } else if(scan_code == i_released && capslock == 1) {
        print_char_at_cursor('I', PRINT_COLOR_YELLOW | (PRINT_COLOR_BLACK << 4));
        addToBuffer('I');
    }
    if(scan_code == j_released && capslock == 0) {
        print_char_at_cursor('j', PRINT_COLOR_YELLOW | (PRINT_COLOR_BLACK << 4));
        addToBuffer('j');
    } else if(scan_code == j_released && capslock == 1) {
        print_char_at_cursor('J', PRINT_COLOR_YELLOW | (PRINT_COLOR_BLACK << 4));
        addToBuffer('J');
    }
    if(scan_code == k_released && capslock == 0) {
        print_char_at_cursor('k', PRINT_COLOR_YELLOW | (PRINT_COLOR_BLACK << 4));
        addToBuffer('k');
    } else if(scan_code == k_released && capslock == 1) {
        print_char_at_cursor('K', PRINT_COLOR_YELLOW | (PRINT_COLOR_BLACK << 4));
        addToBuffer('K');
    }
    if(scan_code == l_released && capslock == 0) {
        print_char_at_cursor('l', PRINT_COLOR_YELLOW | (PRINT_COLOR_BLACK << 4));
        addToBuffer('l');
    } else if(scan_code == l_released && capslock == 1) {
        print_char_at_cursor('L', PRINT_COLOR_YELLOW | (PRINT_COLOR_BLACK << 4));
        addToBuffer('L');
    }
    if(scan_code == m_released && capslock == 0) {
        print_char_at_cursor('m', PRINT_COLOR_YELLOW | (PRINT_COLOR_BLACK << 4));
        addToBuffer('m');
    } else if(scan_code == m_released && capslock == 1) {
        print_char_at_cursor('M', PRINT_COLOR_YELLOW | (PRINT_COLOR_BLACK << 4));
        addToBuffer('M');
    }
    if(scan_code == n_released && capslock == 0) {
        print_char_at_cursor('n', PRINT_COLOR_YELLOW | (PRINT_COLOR_BLACK << 4));
        addToBuffer('n');
    } else if(scan_code == n_released && capslock == 1) {
        print_char_at_cursor('N', PRINT_COLOR_YELLOW | (PRINT_COLOR_BLACK << 4));
        addToBuffer('N');
    }
    if(scan_code == o_released && capslock == 0) {
        print_char_at_cursor('o', PRINT_COLOR_YELLOW | (PRINT_COLOR_BLACK << 4));
        addToBuffer('o');
    } else if(scan_code == o_released && capslock == 1) {
        print_char_at_cursor('O', PRINT_COLOR_YELLOW | (PRINT_COLOR_BLACK << 4));
        addToBuffer('O');
    }
    if(scan_code == p_released && capslock == 0) {
        print_char_at_cursor('p', PRINT_COLOR_YELLOW | (PRINT_COLOR_BLACK << 4));
        addToBuffer('p');
    } else if(scan_code == p_released && capslock == 1) {
        print_char_at_cursor('P', PRINT_COLOR_YELLOW | (PRINT_COLOR_BLACK << 4));
        addToBuffer('P');
    }
    if(scan_code == q_released && capslock == 0) {
        print_char_at_cursor('q', PRINT_COLOR_YELLOW | (PRINT_COLOR_BLACK << 4));
        addToBuffer('q');
    } else if(scan_code == q_released && capslock == 1) {
        print_char_at_cursor('Q', PRINT_COLOR_YELLOW | (PRINT_COLOR_BLACK << 4));
        addToBuffer('Q');
    }
    if(scan_code == r_released && capslock == 0) {
        print_char_at_cursor('r', PRINT_COLOR_YELLOW | (PRINT_COLOR_BLACK << 4));
        addToBuffer('r');
    } else if(scan_code == r_released && capslock == 1) {
        print_char_at_cursor('R', PRINT_COLOR_YELLOW | (PRINT_COLOR_BLACK << 4));
        addToBuffer('R');
    }
    if(scan_code == s_released && capslock == 0) {
        print_char_at_cursor('s', PRINT_COLOR_YELLOW | (PRINT_COLOR_BLACK << 4));
        addToBuffer('s');
    } else if(scan_code == s_released && capslock == 1) {
        print_char_at_cursor('S', PRINT_COLOR_YELLOW | (PRINT_COLOR_BLACK << 4));
        addToBuffer('S');
    }
    if(scan_code == t_released && capslock == 0) {
        print_char_at_cursor('t', PRINT_COLOR_YELLOW | (PRINT_COLOR_BLACK << 4));
        addToBuffer('t');
    } else if(scan_code == t_released && capslock == 1) {
        print_char_at_cursor('T', PRINT_COLOR_YELLOW | (PRINT_COLOR_BLACK << 4));
        addToBuffer('T');
    }
    if(scan_code == u_released && capslock == 0) {
        print_char_at_cursor('u', PRINT_COLOR_YELLOW | (PRINT_COLOR_BLACK << 4));
        addToBuffer('u');
    } else if(scan_code == u_released && capslock == 1) {
        print_char_at_cursor('U', PRINT_COLOR_YELLOW | (PRINT_COLOR_BLACK << 4));
        addToBuffer('U');
    }
    if(scan_code == v_released && capslock == 0) {
        print_char_at_cursor('v', PRINT_COLOR_YELLOW | (PRINT_COLOR_BLACK << 4));
        addToBuffer('v');
    } else if(scan_code == v_released && capslock == 1) {
        print_char_at_cursor('V', PRINT_COLOR_YELLOW | (PRINT_COLOR_BLACK << 4));
        addToBuffer('V');
    }
    if(scan_code == w_released && capslock == 0) {
        print_char_at_cursor('w', PRINT_COLOR_YELLOW | (PRINT_COLOR_BLACK << 4));
        addToBuffer('a');
    } else if(scan_code == w_released && capslock == 1) {
        print_char_at_cursor('W', PRINT_COLOR_YELLOW | (PRINT_COLOR_BLACK << 4));
        addToBuffer('W');
    }
    if(scan_code == x_released && capslock == 0) {
        print_char_at_cursor('x', PRINT_COLOR_YELLOW | (PRINT_COLOR_BLACK << 4));
        addToBuffer('x');
    } else if(scan_code == x_released && capslock == 1) {
        print_char_at_cursor('X', PRINT_COLOR_YELLOW | (PRINT_COLOR_BLACK << 4));
        addToBuffer('X');
    }
    if(scan_code == y_released && capslock == 0) {
        print_char_at_cursor('y', PRINT_COLOR_YELLOW | (PRINT_COLOR_BLACK << 4));
        addToBuffer('y');
    } else if(scan_code == y_released && capslock == 1) {
        print_char_at_cursor('Y', PRINT_COLOR_YELLOW | (PRINT_COLOR_BLACK << 4));
        addToBuffer('Y');
    }
    if(scan_code == z_released && capslock == 0) {
        print_char_at_cursor('z', PRINT_COLOR_YELLOW | (PRINT_COLOR_BLACK << 4));
        addToBuffer('z');
    } else if(scan_code == z_released && capslock == 1) {
        print_char_at_cursor('Z', PRINT_COLOR_YELLOW | (PRINT_COLOR_BLACK << 4));
        addToBuffer('Z');
    }
    if(scan_code == released_1) {
        print_char_at_cursor('1', PRINT_COLOR_YELLOW | (PRINT_COLOR_BLACK << 4));
        addToBuffer('1');
    }
    if(scan_code == released_2) {
        print_char_at_cursor('2', PRINT_COLOR_YELLOW | (PRINT_COLOR_BLACK << 4));
        addToBuffer('2');
    }
    if(scan_code == released_3) {
        print_char_at_cursor('3', PRINT_COLOR_YELLOW | (PRINT_COLOR_BLACK << 4));
        addToBuffer('3');
    }
    if(scan_code == released_4) {
        print_char_at_cursor('4', PRINT_COLOR_YELLOW | (PRINT_COLOR_BLACK << 4));
        addToBuffer('4');
    }
    if(scan_code == released_5) {
        print_char_at_cursor('5', PRINT_COLOR_YELLOW | (PRINT_COLOR_BLACK << 4));
        addToBuffer('5');
    }
    if(scan_code == released_6) {
        print_char_at_cursor('6', PRINT_COLOR_YELLOW | (PRINT_COLOR_BLACK << 4));
        addToBuffer('6');
    }
    if(scan_code == released_7) {
        print_char_at_cursor('7', PRINT_COLOR_YELLOW | (PRINT_COLOR_BLACK << 4));
        addToBuffer('7');
    }
    if(scan_code == released_8) {
        print_char_at_cursor('8', PRINT_COLOR_YELLOW | (PRINT_COLOR_BLACK << 4));
        addToBuffer('8');
    }
    if(scan_code == released_9) {
        print_char_at_cursor('9', PRINT_COLOR_YELLOW | (PRINT_COLOR_BLACK << 4));
        addToBuffer('9');
    }
    if(scan_code == released_0) {
        print_char_at_cursor('0', PRINT_COLOR_YELLOW | (PRINT_COLOR_BLACK << 4));
        addToBuffer('0');
    }
    if(scan_code == enter_released) {
        y++;
        x = 0;
        check_bounds();
        print_str("\n");
        check_command();
    }
    if(scan_code == space_released) {
        print_char_at_cursor(' ', PRINT_COLOR_YELLOW | (PRINT_COLOR_BLACK << 4));
        addToBuffer(' ');
    }
    if(scan_code == backspace_pressed) {
        if (x == 0) {
            y--;
            x = 79;
        } else {
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
    if(scan_code == capslock_pressed) {
        if(capslock == 1) {
            capslock = 0;
        }
        capslock = 1; // Turn on
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
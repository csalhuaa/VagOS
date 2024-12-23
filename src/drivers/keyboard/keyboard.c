#include "keyboard.h"
#include "../../util/string.h"
#include "../../apps/console.h"
#include "../../apps/integrate.h"
#include "../../util/printf.h"
#include "../../memory/heap.h"
#include <stdlib.h>
volatile struct keyboard *keyboard;
//buffer de entrada del teclado
char* keyboardInput;
char asciitable[] = {
    0,   0, '1', '2',
    '3', '4', '5', '6',
    '7', '8', '9', '0',
    '-', '=',   0,   0,
    'q', 'w', 'e', 'r',
    't', 'y', 'u', 'i',
    'o', 'p', '[', ']',
    0,   0, 'a', 's',
    'd', 'f', 'g', 'h',
    'j', 'k', 'l', ';',
    '\'','`',   0,'\\',
    'z', 'x', 'c', 'v',
    'b', 'n', 'm', ',',
    '.', '/',   0, '*',
    0, ' '
};

char translate(uint8_t scancode, uint8_t uppercase) {
    if (scancode > 58) return 0;
    if (uppercase) return keyboard->ASCII_table[scancode] - 32;

    return keyboard->ASCII_table[scancode];
}

void init_keyboard() {
    keyboardInput = (char*) malloc(sizeof(char) * 256);
    keyboard = (struct keyboard *)malloc(sizeof(struct keyboard));

    memset((void*)keyboard, 0, sizeof(struct keyboard));

    keyboard->ASCII_table = (char*)malloc(ASCII_SIZE);

    memset(keyboard->ASCII_table, 0, ASCII_SIZE);
    memcpy(keyboard->ASCII_table, asciitable, ASCII_SIZE);

    keyboard->index = 0;
    keyboard->left_shift_pressed = 0;
    keyboard->right_shift_pressed = 0;
    keyboard->intro_buffered = 0;
}

void command(char* buffer, uint8_t size) {
    if (strncmp(buffer, "help", size) == 0) {
        system_printf("Available commands:\n");
        system_printf("help - Display this message\n");
        system_printf("clear - Clear the screen\n");
        system_printf("echo - Echo a message\n");
        system_printf("exit - Exit the shell\n");
    } else if (!strcmp(buffer, "clear")) {
        system_printf("\033[2J\033[1;1H");
    } else if (!strcmp(buffer, "echo")) {
        system_printf("Enter a message: ");
        halt_until_enter();
        system_printf("You entered: ");
        system_printf(keyboardInput);
        system_printf("\n");
    } else if (!strcmp(buffer, "exit")) {
        system_printf("Exiting...\n");
        halt_until_enter();
        // exit(0);
    } else {
        printf("Unknown command: %s\n", buffer);
    }
}

//Añadir input al Buffer
void addInput(char x){
    keyboardInput[keyboard->index] = x;
    keyboard->index++;
}

//Borrar input del Buffer
void backInput(){
    keyboard->index--;
    keyboardInput[keyboard->index] = 0;
}

//Reset input
void resetInput(){
    memset(keyboardInput, 0, 256);
    keyboard->index = 0;
}

//Entradas de Teclado
void handle_keyboard(uint8_t scancode) {

    switch(scancode) {
        case Spacebar:
            addInput(' ');
            user_input(" ");
            return;
        case LeftShift:
            keyboard->left_shift_pressed = 1;
            return;
        case LeftShift+0x80:
            keyboard->left_shift_pressed = 0;
            return;
        case RightShift:
            keyboard->right_shift_pressed = 1;
            return;
        case RightShift+0x80:
            keyboard->right_shift_pressed = 0;
            return;
        case Enter:
            // keyboardInput[keyboard->index] = ' ';
            keyboard->intro_buffered = 1;
            system_printf("\n");
            // command(keyboardInput, keyboard->index++);
            execute_command(keyboardInput);
            resetInput();
            keyboard->index = 0;
            user_printf("> ");
            return;
        case Backspace:
            if ( keyboard-> index > 0){
                backInput();
                user_input("\b \b");
            }
            return;
    }

    char ascii = translate(scancode, keyboard->left_shift_pressed || keyboard->right_shift_pressed);
    if (ascii != 0) {
        addInput(ascii);
        user_input(&ascii);

    }
}

void halt_until_enter() {
    keyboard->intro_buffered = 0;
    printf("Press enter to continue...");
    while (1) {
        if (keyboard->intro_buffered) {
            keyboard->intro_buffered = 0;
            return;
        }
    }
}
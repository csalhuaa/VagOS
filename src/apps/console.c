#include "console.h"
#include "../util/printf.h"
#include <time.h>

enum CONSOLE_COLOR{
  BLACK = 30,
  RED = 31,
  GREEN = 32,
  YELLOW = 33,
  BLUE = 34,
  MAGENTA = 35,
  CYAN = 36,
  WHITE = 37
};

struct ConsoleConfig{
  enum CONSOLE_COLOR output;
  enum CONSOLE_COLOR input;
};

struct ConsoleConfig userConsole = {
  GREEN, MAGENTA 
};
struct ConsoleConfig systemConsole = {
  WHITE, CYAN
};

void user_printf(const char* str){
  printf("\033[%dm", userConsole.output);
  printf(str);
  printf("\033[0m");
}

void system_printf(const char* str){
  printf("\033[%dm", systemConsole.output);
  printf(str);
  printf("\033[0m");
}

void user_input(const char* str){
  printf("\033[%dm", userConsole.input);
  printf(str);
  printf("\033[0m");
}

void system_input(const char* str){
  printf("\033[%dm", systemConsole.input);
  printf(str);
  printf("\033[0m");
}
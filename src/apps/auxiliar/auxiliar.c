#include "auxiliar.h"
#include "../integrate.h"
#include "../console.h"
#include <time.h>

void help(char* command){
  system_printf("Available commands:\n");
  int nc = getNumCommands();
  struct Command* commands = getCommands();
  for(int i = 0; i < nc; i++){
    system_printf("> ");
    system_input(commands[i].name);
    system_printf("\n");
  }
}

void hello(char* command){
  system_input("Welcome to VagOS\n");
  system_input("Type 'help' for a list of available commands\n");
};

void clear(char* command){
  system_printf("\033[2J\033[1;1H");
}

void echo(char* command){
  system_printf("Enter a message: ");
  user_input("");
  system_printf("You entered: ");
  system_printf(command);
  system_printf("\n");
}

void show_time() {
    time_t now = time(NULL);
    struct tm *local_time = localtime(&now);
    char buffer[256];
    sprintf(buffer, "Hora actual: %02d:%02d:%02d\n", local_time->tm_hour, local_time->tm_min, local_time->tm_sec);
    system_input(buffer);
}

void exit(char* command){
  system_printf("Exiting...\n");
  // halt_until_enter();
  exit(0);
}

struct Command hello_command = {
  "hello",
  6,
  &hello,
  &get1Option
};

struct Command time_command = {
  "time",
  5,
  &show_time,
  &get1Option
};

struct Command help_command = {
  "help",
  5,
  &help,
  &get1Option
};

struct Command clear_command = {
  "clear",
  6,
  &clear,
  &get1Option
};

struct Command exit_command = {
  "exit",
  5,
  &exit,
  &get1Option
};

void init_aux_services(){
  suscribe_command(hello_command);
  suscribe_command(help_command);
  suscribe_command(clear_command);
  suscribe_command(exit_command);
  suscribe_command(time_command);
}

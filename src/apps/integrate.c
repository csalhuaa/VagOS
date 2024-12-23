#include "integrate.h"
#include "auxiliar/auxiliar.h"
#include "FileSystem/FileSystem.h"
#include "ProcessManager/ProcessManager.h"
#include "Scheduler/Scheduler.h"
#include "../memory/heap.h"
#include "console.h"

int num_commands = 0;
struct Command commands[20];

void suscribe_command(struct Command command){
  commands[num_commands++] = command;
}

void execute_command(char* command){
  for(int i = 0; i < num_commands; i++){
    if(strncmp(command, commands[i].name, commands[i].size) == 0){
      commands[i].execute(commands[i].process(command));
      return;
    }
  }
  char buffer[256];
  sprintf(buffer, "Command not found : %s\n", command);
  system_printf(buffer);
  // system_printf(command);
  // system_printf("\n");
}



char** getOptions(char* command, int n){
  // separar n argumentos del comando
  char** options = (char**) malloc(sizeof(char*) * n);
  int f = 0;
  for(int i = 0; i < n; i++){
    options[i] = (char*) malloc(sizeof(char) * 16);
    int j = 0;
    while(command[f] != ' ' && command[f] != '\0'){
      options[i][j] = command[f];
      f++;
      j++;
    }
    options[i][j] = '\0';
    f++;
  }
  return options;
}

char** get1Option(char* command){
  return getOptions(command, 1);
}

char** get2Options(char* command){
  return getOptions(command, 2);
}

char** get3Options(char* command){
  return getOptions(command, 3);
}

char** get4Options(char* command){
  return getOptions(command, 4);
}

void init_integration(){
  init_aux_services();
  init_fs_services();
  init_pm_services();
  init_sc_services();

  execute_command("clear");
  execute_command("hello");
}

struct Command* getCommands(){
  return commands;
}

int getNumCommands(){
  return num_commands;
}
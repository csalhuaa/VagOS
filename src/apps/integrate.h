#ifndef M_INTEGRATE
#define M_INTEGRATE

struct Command{
  char* name;
  int size;
  void (*execute)(char**);
  char** (*process)(char*);
};

void execute_command(char* );
void suscribe_command(struct Command);
void init_integration();

char** get1Option(char* command);
char** get2Options(char* command);
char** get3Options(char* command);
char** get4Options(char* command);

struct Command* getCommands();
int getNumCommands();

#endif
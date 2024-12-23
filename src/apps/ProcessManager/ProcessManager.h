#ifndef PROCESSMANAGER_H
#define PROCESSMANAGER_H

#define MAX_PROCESSES 5

typedef struct {
    int pid;
    char name[20];
    int runtime;
    int remaining_time;
    int paused; 
} Process;

extern Process process_queue[MAX_PROCESSES];
extern int process_count;

// Funciones públicas
void init_process_manager();
void add_process(const char *name, int runtime);
void list_active_processes();
void pause_process(int pid);
void remove_process(int pid);

void init_pm_services();
#endif

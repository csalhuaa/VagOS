#include "ProcessManager.h"
#include "../console.h"
#include "../integrate.h"
Process process_queue[MAX_PROCESSES];
int process_count = 0;

void init_process_manager() {
    process_count = 0;
}

void add_process(const char *name, int runtime) {
    if (process_count >= MAX_PROCESSES) {
        system_printf("No se pueden agregar más procesos.\n");
        return;
    }
    Process new_process = {process_count + 1, "", runtime, runtime, 0};
    system_printf("Proceso creado:\n"); 
    strcpy(new_process.name, name);
    process_queue[process_count++] = new_process;
    system_printf("Proceso agregado:\n"); 
    char buffer[256];
    sprintf(buffer, "PID=%d, Nombre=%s, Runtime=%d\n", new_process.pid, new_process.name, runtime);
    system_input(buffer);
}

void add_process_com(char** args){
    add_process(args[1], atoi(args[2]));
}

struct Command add_process_command = {
    "add-proc ",
    9,
    &add_process_com,
    &get3Options
};

void list_active_processes() {
    if (process_count == 0) {
        system_printf("No hay procesos activos.\n");
        return;
    }
    system_printf("Procesos activos:\n");
    char buffer[256];
    for (int i = 0; i < process_count; i++) {
        sprintf(buffer, "- PID=%d, Nombre=%s, Tiempo restante=%d, Pausado=%s\n",
               process_queue[i].pid,
               process_queue[i].name,
               process_queue[i].remaining_time,
               process_queue[i].paused ? "Sí" : "No");
        system_input(buffer);
    }
}

struct Command list_processes_command = {
    "list-proc ",
    10,
    &list_active_processes,
    &get1Option
};

void pause_process(int pid) {
    char buffer[256];
    for (int i = 0; i < process_count; i++) {
        if (process_queue[i].pid == pid) {
            process_queue[i].paused = !process_queue[i].paused;
            sprintf(buffer, "Proceso PID=%d %s.\n", pid, process_queue[i].paused ? "pausado" : "reanudado");
            system_input(buffer);
            return;
        }
    }
    sprintf(buffer,"Proceso con PID=%d no encontrado.\n", pid);
    system_printf(buffer);
}

void pause_process_com(char** args){
    pause_process(atoi(args[1]));
}

struct Command pause_process_command = {
    "pause-proc ",
    11,
    &pause_process,
    &get2Options
};

void remove_process(int pid) {
    char buffer[256];
    for (int i = 0; i < process_count; i++) {
        if (process_queue[i].pid == pid) {
            for (int j = i; j < process_count - 1; j++) {
                process_queue[j] = process_queue[j + 1];
            }
            process_count--;
            sprintf(buffer,"Proceso PID=%d eliminado.\n", pid);
            system_input(buffer);
            return;
        }
    }
    sprintf(buffer,"Proceso con PID=%d no encontrado.\n", pid);
    system_printf(buffer);
}

void remove_process_com(char** args){
    remove_process(atoi(args[1]));
}

struct Command remove_process_command = {
    "remove-proc ",
    12,
    &remove_process,
    &get2Options
};

void init_pm_services() {
    suscribe_command(list_processes_command);
    suscribe_command(add_process_command);
    suscribe_command(pause_process_command);
    suscribe_command(remove_process_command);
}

#include "../ProcessManager/ProcessManager.h"
#include <stdio.h>
#include "../console.h"
#include "../integrate.h"

void run_scheduler() {
  char buffer [256];
    int quantum = 2;
    sprintf(buffer, "Ejecutando procesos con Round Robin (Quantum = %d)...\n", quantum);
    system_printf(buffer);

    while (process_count > 0) {
        Process *current = &process_queue[0];
        sprintf(buffer, "> Ejecutando PID=%d, Nombre=%s, Tiempo restante=%d\n", current->pid, current->name, current->remaining_time);
        system_input(buffer);
        if (current->remaining_time <= quantum) {
            sprintf(buffer, "Proceso PID=%d terminado.\n", current->pid);
            system_input(buffer);
            // Elimina el proceso terminado
            for (int i = 1; i < process_count; i++) {
                process_queue[i - 1] = process_queue[i];
            }
            process_count--;
        } else {
            current->remaining_time -= quantum;
            Process temp = *current;
            // Reorganiza la cola
            for (int i = 1; i < process_count; i++) {
                process_queue[i - 1] = process_queue[i];
            }
            process_queue[process_count - 1] = temp;
        }
    }
    system_printf("Todos los procesos han terminado.\n");
}

struct Command run_scheduler_command = {
  "run-scheduler",
  13,
  &run_scheduler,
  &get1Option,
};

void init_sc_services(){
  suscribe_command(run_scheduler_command);
}
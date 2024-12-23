#include "FileSystem.h"
#include "../../util/string.h"

#include "../console.h"
#include "../integrate.h"
#include "../../memory/heap.h"

#define MAX_FILES 10

typedef struct {
    char name[20];
    char content[100];
} File;

static File filesystem[MAX_FILES];
static int file_count = 0;

void init_filesystem() {
    file_count = 0;
}

void list_files() {
    if (file_count == 0) {
        system_printf("No hay archivos en el sistema.\n");
        return;
    }
    system_printf("Archivos en el sistema:\n");
    for (int i = 0; i < file_count; i++) {
        system_input("- ");
        system_input(filesystem[i].name);
        system_input("\n");
    }
}

struct Command list_files_command = {
    "ls ",
    3,
    &list_files,
    &get1Option
};

void create_file(const char *filename, const char *content) {
    if (file_count >= MAX_FILES) {
        system_printf("No se pueden agregar más archivos.\n");
        return;
    }
    strcpy(filesystem[file_count].name, filename);
    strcpy(filesystem[file_count].content, content);
    file_count++;
    system_printf("Archivo '");
    system_printf(filename);
    system_printf("'creado.\n"); 
}


void create_file_com(char** args){
    create_file(args[1], args[2]);
}

struct Command create_file_command = {
    "create ",
    7,
    &create_file_com,
    &get3Options
};

void delete_file(const char *filename) {
    for (int i = 0; i < file_count; i++) {
        if (strcmp(filesystem[i].name, filename) == 0) {
            for (int j = i; j < file_count - 1; j++) {
                filesystem[j] = filesystem[j + 1];
            }
            file_count--;
            system_printf("Archivo '");
            system_printf(filename);
            system_printf("' eliminado.\n");
            return;
        }
    }
    system_printf("Archivo no encontrado.\n");
}

void delete_file_com(char** args){
    delete_file(args[1]);
}

struct Command delete_file_command = {
    "delete",
    7,
    &delete_file_com,
    &get2Options
};

void show_file_content(const char *filename) {
    for (int i = 0; i < file_count; i++) {
        if (strcmp(filesystem[i].name, filename) == 0) {
            system_printf("Contenido de '");
            system_printf(filename);
            system_printf("' :\n");
            system_input(filesystem[i].content);
            system_printf("\n");
            return;
        }
    }
    system_printf("Archivo no encontrado.\n");
}

void show_file_content_com(char** args){
    show_file_content(args[1]);
}

struct Command show_file_content_command = {
    "cat ",
    4,
    &show_file_content_com,
    &get2Options
};

void edit_file(const char *filename, const char *new_content) {
    for (int i = 0; i < file_count; i++) {
        if (strcmp(filesystem[i].name, filename) == 0) {
            strcpy(filesystem[i].content, new_content);
            system_printf("Archivo '");
            system_printf(filename);
            system_printf("' editado con éxito.\n");
            return;
        }
    }
    system_printf("Archivo no encontrado.\n");
}

void edit_file_com(char** args){
    edit_file(args[1], args[2]);
}

struct Command edit_file_command = {
    "edit ",
    5,
    &edit_file_com,
    &get3Options
};


void init_fs_services() {
    suscribe_command(list_files_command);
    suscribe_command(create_file_command);
    suscribe_command(delete_file_command);
    suscribe_command(show_file_content_command);
    suscribe_command(edit_file_command);
}

#include <math.h>
#include <stdio.h>

#include <time.h>
#include "employee.h"
#include "menu.h"

int main(void) {
    FILE *file_employees, *file_pontos;

    // file = fopen("part_emp_3.dat", "r");
    file_employees = fopen("employees.dat", "w+b");
    file_pontos = fopen("pontos.dat", "w+b");


    if(file_employees == NULL || file_pontos == NULL) {
        printf("Erro ao abrir o file\n");
        exit(1);
    }

    // rewind(file);
    // Employee *e = read_employee(file);
    // print_employee(e);
    menu(file_employees, file_pontos);


    //free(e);
    return 0;
}

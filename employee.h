#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <stdlib.h>
#include <stdio.h>

#include <time.h>

typedef struct Employee {
    int id;
    char name[64];
    char role[20];
    double salary;
    time_t hire_date;
    time_t resignation_date;
    double entry_time;
    double exit_time;
    double lunch_start;
    double lunch_end;
    char state;
} Employee;

// Retorna um ponteiro para um funcionario salvo na memória
Employee *employee(
    int id,
    char *name,
    char *role,
    double salary,
    time_t hire_date,
    time_t resignation_date,
    double entry_time,
    double exit_time,
    double lunch_start,
    double lunch_end,
    char state
);

// Imprimie os dados de um funcionário
void print_employee(Employee *employee);

// Salva um funcionário na posição atual do cursor
void save_employee(FILE *out, Employee *employee);
// Adiciona um funcionário no final do arquivo
void add_employee(FILE *file, Employee *employee);
// Salva um novo valor em uma linha do arquivo
void update_employee(FILE *file, Employee *employee, int index);

// Le o funcionario na posição atual do cursor
Employee *read_employee(FILE *arq);

// Retorna o tamanho do registro da struct Employee
size_t get_employee_size();
// Retorna quantos funcionários estão cadastrados
int get_employees_count(FILE *file);

// Retorna um funcionario pelo seu index na tabela
Employee *get_employee_by_index(FILE *file, int index);
#endif //EMPLOYEE_H

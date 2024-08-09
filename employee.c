#include "employee.h"
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <tgmath.h>

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
) {

    Employee *employee = malloc(sizeof(Employee)); // Aloca o espaço apra os dados do funcionário na memória
    if(employee == NULL) exit(1); // Verifica se o usuário foi criado com sucesso
    memset(employee, 0, sizeof(Employee)); // Preenche os espaços com 0;

    // Copia os dados dos parametros para a memora;
    employee->id = id;
    strcpy(employee->name, name);
    strcpy(employee->role, role);
    employee-> salary = salary;
    employee->hire_date = hire_date;
    employee->resignation_date = resignation_date;
    employee->entry_time = entry_time;
    employee->exit_time = exit_time;
    employee->lunch_start = lunch_start;
    employee->lunch_end = lunch_end;
    employee->state = state;

    return employee;
};

void print_employee(Employee *employee) {
    if(employee == NULL) {
        printf("Funcionario nulo passado!\n");
        return;
    }

    printf("id:              %d\n", employee->id);
    printf("Nome:            %s\n", employee->name);
    printf("Cargo:           %s\n", employee->role);
    printf("Salario:         R$%.2f\n", employee->salary);
    printf("Contatacao:      ");
    printf(ctime(&employee->hire_date));
    if(employee->resignation_date) {
        printf("Demissao: ");
        printf(ctime(&employee->resignation_date));
    }
    printf("Entrada:         %f\n", employee->entry_time);
    printf("Saida:           %f\n", employee->exit_time);
    printf("Inicio almoco:   %f\n", employee->lunch_start);
    printf("Fim almoco:      %f\n", employee->lunch_end);
    printf("State:           %c\n", employee->state);
};

void add_employee(FILE *file, Employee *employee) {
    fseek(file, 0, SEEK_END);
    save_employee(file, employee);
}

void save_employee(FILE *file, Employee *employee) {
    fwrite(&employee->id, sizeof(int), 1, file);
    fwrite(employee->name, sizeof(char), sizeof(employee->name), file);
    fwrite(employee->role, sizeof(char), sizeof(employee->role), file);
    fwrite(&employee->salary, sizeof(double), 1, file);
    fwrite(&employee->hire_date, sizeof(time_t), 1, file);
    fwrite(&employee->resignation_date, sizeof(time_t), 1, file);
    fwrite(&employee->entry_time, sizeof(double), 1, file);
    fwrite(&employee->exit_time, sizeof(double), 1, file);
    fwrite(&employee->lunch_start, sizeof(double), 1, file);
    fwrite(&employee->lunch_end, sizeof(double), 1, file);
    fwrite(&employee->state, sizeof(char), 1, file);
};

Employee *read_employee(FILE *file) {
    Employee *employee = malloc(sizeof(Employee));
    fread(&employee->id, sizeof(int), 1, file);
    fread(employee->name, sizeof(char), sizeof(employee->name), file);
    fread(employee->role, sizeof(char), sizeof(employee->role), file);
    fread(&employee->salary, sizeof(double), 1, file);
    fread(&employee->hire_date, sizeof(time_t), 1, file);
    fread(&employee->resignation_date, sizeof(time_t), 1, file);
    fread(&employee->entry_time, sizeof(double), 1, file);
    fread(&employee->exit_time, sizeof(double), 1, file);
    fread(&employee->lunch_start, sizeof(double), 1, file);
    fread(&employee->lunch_end, sizeof(double), 1, file);
    fread(&employee->state, sizeof(char), 1, file);

    return employee;
};

size_t get_employee_size() {
    size_t totalSize = 0;

    totalSize += sizeof(((Employee *)0)->id);
    totalSize += sizeof(((Employee *)0)->name);
    totalSize += sizeof(((Employee *)0)->role);
    totalSize += sizeof(((Employee *)0)->salary);
    totalSize += sizeof(((Employee *)0)->hire_date);
    totalSize += sizeof(((Employee *)0)->resignation_date);
    totalSize += sizeof(((Employee *)0)->entry_time);
    totalSize += sizeof(((Employee *)0)->exit_time);
    totalSize += sizeof(((Employee *)0)->lunch_start);
    totalSize += sizeof(((Employee *)0)->lunch_end);
    totalSize += sizeof(((Employee *)0)->state);

    return totalSize;
}

int get_employees_count(FILE *file) {
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);
    int num_employees = file_size / get_employee_size();
    return num_employees;
}

Employee *get_employee_by_index(FILE *file, int index) {

    int offset = get_employee_size() * index;

    fseek(file, offset, SEEK_SET);
    return read_employee(file);
};

void update_employee(FILE *file, Employee *employee, int index) {
    rewind(file);
    long offset = index * get_employee_size();
    fseek(file, offset, SEEK_SET);
    save_employee(file, employee);
}

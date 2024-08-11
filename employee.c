#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <tgmath.h>

#include "employee.h"
#include "utils.h"

#include "classificacaoInterna.h"
#include "intercalacaoBasica.h"

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
    fwrite(employee->name, sizeof(char), 64, file);
    fwrite(employee->role, sizeof(char), 20, file);
    fwrite(&employee->salary, sizeof(double), 1, file);
    fwrite(&employee->hire_date, sizeof(time_t), 1, file);
    fwrite(&employee->resignation_date, sizeof(time_t), 1, file);
    fwrite(&employee->entry_time, sizeof(double), 1, file);
    fwrite(&employee->exit_time, sizeof(double), 1, file);
    fwrite(&employee->lunch_start, sizeof(double), 1, file);
    fwrite(&employee->lunch_end, sizeof(double), 1, file);
    fwrite(&employee->state, sizeof(char), 1, file);
};

void add_random_employees(FILE *file, int count) {
    int id_list[count];
    for (int i = get_employees_count(file); i < count; i++) {
        id_list[i] = i + 1;
    }

    shuffle(id_list, count);

    // fseek(file, 0, SEEK_END);
    Employee *new_employee;
    for(int i = 0; i < count; i++){
        new_employee = employee(id_list[i],"Carlos Alberto","repositor",2000,time(NULL),0,6,18,12,13,'o');
        add_employee(file, new_employee);
    }
    free(new_employee);
};

int verify_sorted_employees(FILE *file) {
    rewind(file);
    Employee *employee;
    int last;

    for(int i = 0; i < get_employees_count(file); i++) {
        fseek(file, get_employee_size()*i, SEEK_SET);
        employee = read_employee(file);
        if(employee -> id < last){
            free(employee);
            return 0;
        }

        last = employee -> id;
    }


    free(employee);
    return 1;
}

Employee *read_employee(FILE *file) {
    Employee *employee = malloc(sizeof(Employee));

    // if (0 >= fread(&employee->id, sizeof(int), 1, file)) { free(employee);return NULL;}

    fread(&employee->id, sizeof(int), 1, file);
    fread(employee->name, sizeof(char), 64, file);
    fread(employee->role, sizeof(char), 20, file);
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
    rewind(file);
    Employee *employee;
    employee = read_employee(file);
    // fseek(file, (get_employee_size() * index), SEEK_SET);
    return employee;
};

void sort_employees(FILE *file)
{
    printf("> Realizando a classificacao interna.\n");
    int n_partitions = classificacao_interna(file, 200);
    printf("> Realizando a intercalacao basica.\n");
    intercalacao_basica(file, n_partitions);
    printf("> Base funcionarios ordenada\n");
}

void update_employee(FILE *file, Employee *employee, int index) {
    rewind(file);
    long offset = index * get_employee_size();
    fseek(file, offset, SEEK_SET);
    save_employee(file, employee);
}

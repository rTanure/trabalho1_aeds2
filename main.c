#include <math.h>
#include <stdio.h>

#include <time.h>
#include "employee.h"
#include "menu.h"

int main(void) {
    FILE *file;

    file = fopen("employees.dat", "w+b");

    if(file == NULL) {
        printf("Erro ao abrir o file\n");
        exit(1);
    }
    
    menu(file);

    int id_list[1000];
    for (int i = 0; i < 1000; i++) {
        id_list[i] = i + 1;
    }

    Employee *e;
    for (int i = 0; i < 1000; i++)
    {
        e = employee(id_list[i], "a", "a", 1, 0, 0, 1, 1, 1, 1, 'o');
        add_employee(file, e);
        rewind(file);
    }

    rewind(file);
    // fseek(file, get_employee_size() * 500, SEEK_SET);
    e = read_employee(file);
    print_employee(e);

    free(e);
    return 0;
}

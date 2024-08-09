#include <math.h>
#include <stdio.h>

#include <time.h>
#include "employee.h"
#include "menu.h"

int main(void) {
    FILE *file;

    file = fopen("employees.dat", "w+b");

    if(file == NULL) {
        printf("Erro ao abrir o fileuivo\n");
        exit(1);
    }
    
    menu(file);

    return 0;
}

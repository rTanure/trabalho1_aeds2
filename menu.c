#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <string.h>

#include "employee.h"

void wait_for_enter() {
    printf("Pressione Enter para continuar...\n");
    _getch();
}

void clear_screen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void add_employee_menu(FILE *file) {
    // Aloca um espaco na memoria para salvar os dados do input
    Employee *employee = malloc(sizeof(Employee));

    // Captura os dados do novo funcionario
    clear_screen();

    printf("====== ADICIONAR NOVO FUNCIONARIO ======\n");
    printf("Nome: ");
    scanf(" %[^\n]s", employee->name);
    printf("Funcao: ");
    scanf(" %[^\n]s", employee->role);
    printf("Salario: ");
    scanf(" %lf", &employee->salary);
    printf("Hora de entrada: ");
    scanf(" %lf", &employee->entry_time);
    printf("Hora de saida: ");
    scanf(" %lf", &employee->exit_time);
    printf("Inicio almoco: ");
    scanf(" %lf", &employee->lunch_start);
    printf("Fim almoco: ");
    scanf(" %lf", &employee->lunch_end);

    // Completa os dados gerados automaticamente
    employee-> id = get_employees_count(file) + 1;
    employee-> hire_date = time(NULL);
    employee-> resignation_date = 0;
    employee-> state = 'o';

    // Confirma a criação do novo funcionario
    char confirmation;
    do {
        clear_screen();
        printf("Confirme os dados do novo funcionario:\n\n");
        print_employee(employee);
        printf("\nSalvar dados? [s/n]: ");
        scanf("%c", &confirmation);
    } while (confirmation != 's' && confirmation != 'n');

    // Salva os dados no arquivo ou cancela a opeação
    if(confirmation == 's') {
        clear_screen();
        add_employee(file, employee);
        printf("\nDados salvos com sucesso!");
        wait_for_enter();
    } else {
        clear_screen();
        printf("\nOperacao cancelada com sucesso!");
        wait_for_enter();
    }

    // Libera o espaço na memoria em que os dados estavam
    free(employee);
}

void admin_menu(FILE *file) {
    unsigned int selection = 0;

    do {
        system("cls");
        printf("======= PAINEL ADMIN =======\n");
        printf("1. Adicionar funcionário.\n");
        printf("2. Quantidade de funcionarios\n");
        printf("\n0. Voltar\n");
        printf("\n>>> Opcao selecionada: ");
        scanf("%d", &selection);

        switch (selection) {
            case 1:
                add_employee_menu(file);
                break;
            case 2:
                clear_screen();
                printf("Quantidade de funcioarios: %d\n", get_employees_count(file));
                wait_for_enter();
                break;
            default:
                break;
        }
    } while(selection != 0);
}

void menu(FILE *file) {
    unsigned int selection = 0;

    do {
        system("cls");
        printf("======= MENU INICIAL =======\n");
        printf("1. Sistema de ponto.\n");
        printf("2. Painel admin\n");
        printf("\n0. Sair\n");
        printf("\n>>> Opcao selecionada: ");
        scanf("%d", &selection);

        switch (selection) {
            case 1:
                printf("implementar... \n");
                wait_for_enter();
                break;
            case 2:
                admin_menu(file);
                break;
            default:
                break;

        }
    } while(selection != 0);
}

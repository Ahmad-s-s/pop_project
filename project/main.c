#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "phase_one.h"
#include "phase_two.h"
#include "phase_three.h"


void choose_mode () {
    int mode;
    while (1) {
        char **view_port = (char **) malloc(12 * sizeof(char*));
        for (int i = 0; i < 12; ++i) {
            view_port[i] = (char *) malloc(121 * sizeof(char));
            if (i != 0 && i != 11) {
                view_port[i][0] = '|';
                view_port[i][119] = '|';
                for (int j = 1; j < 119; ++j) {
                    view_port[i][j] = ' ';
                }
            }else {
                for (int j = 0; j < 120; ++j) {
                    view_port[i][j] = '-';
                }
            }
            view_port[i][120] = '\0';
        }
        char **view_port_oc = (char **) malloc(10* sizeof(char *));
        for (int i = 0; i < 10; ++i) {
            view_port_oc[i] = (char *) malloc(119* sizeof(char));
            for (int j = 0; j < 119; ++j) {
                view_port_oc[i][j] = ' ';
            }
        }
        system("cls");
        printf("Welcome, choose a mode to start :\n"
               "1. Design a form    2. Edit a form    3. Run a form    9.exit\n-> ");
        scanf("%d", &mode);
        int flag_accept = 0;
        switch (mode) {
            case 1:
                design(view_port, view_port_oc);
                break;
            case 2:
                edit(view_port, view_port_oc);
                break;
            case 3:
                run(view_port, view_port_oc);
                break;
            case 9:
                flag_accept = 1;
                break;
            default:
                system("cls");
                printf("invalid input, try again : \n"
                       "1. Design a form    2. Edit a form    3. Run a form\n-> ");
                scanf("%d", &mode);
                break;
        }
        if (flag_accept == 1) {
            break;
        }
    }
    printf("finished");
}

int main() {
    choose_mode();
    return 0;
}

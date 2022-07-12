#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "phase_one.h"
#include "phase_two.h"

void print_selected_but_2 (int ind, char b[][7]) {
    for (int i = 0; i < 46; ++i) {
        printf("_");
    }
    printf("\n");
    for (int i = 1; i < 6; ++i) {
        if (i != ind)
            printf("|%s|", b[i]);
        else if(i != 1)
            printf("   |~%s~|   ", b[i]);
        else
            printf("|~%s~|     ", b[i]);
        if (i != 5 && i != ind && i != ind-1)
            printf("*");
    }
    printf("\n");
    for (int i = 0; i < 46; ++i) {
        printf("-");
    }
    printf("\n");
    printf("\n");
}
void print_selected_but (int ind, char b[][7]) {
    for (int i = 0; i < 46; ++i) {
        printf("_");
    }
    printf("\n");
    for (int i = 0; i < 6; ++i) {
        if (i != ind)
            printf("|%s|", b[i]);
        else if(i != 0)
            printf("   |~%s~|   ", b[i]);
        else
            printf("|~%s~|     ", b[i]);
        if (i != 5 && i != ind && i != ind-1)
            printf("*");
    }
    printf("\n");
    for (int i = 0; i < 46; ++i) {
        printf("-");
    }
    printf("\n");
    printf("\n");
}

void print_but (char b[][7]) {
    for (int i = 0; i < 40; ++i) {
        printf("_");
    }
    printf("\n");
    for (int i = 0; i < 6; ++i) {
        printf("|%s|", b[i]);
        if (i != 5)
            printf("*");
    }
    printf("\n");
    for (int i = 0; i < 40; ++i) {
        printf("-");
    }
    printf("\n");
}

void print_view_updated (char **v) {
    for (int i = 0; i < 12; ++i) {
        printf("%s\n", v[i]);
    }
    printf("\n");
}

typedef struct point{
    int x;
    int y;
}point;

point find_component(char **v, char s[]) {
    int len = strlen(s);
    char *test = (char *) malloc((len + 1)*sizeof(char));
    char *line = (char *) malloc(119* sizeof(char));
    for (int i = 0; i < 12; ++i) {
        for (int j = 0; j < 120-len; ++j) {
            for (int k = 0; k < len; ++k) {
                line[k] = v[i][j+k];
            }
            strncpy(test, line, len);
            test[len] = '\0';
            if (strcmp(s, test) == 0) {
                point p;
                p.x = i;
                p.y = j;
                free(test);
                free(line);
                return p;
            }
        }
    }
    point nun;
    nun.x = 0;
    nun.y = 0;
    free(test);
    free(line);
    return nun;
}

int find_width (char **v, point n) {
    int res = 0;
    for (int j = n.y; j < 119; ++j) {
        if (v[n.x+1][j] == '#' || v[n.x+1][j] == '^') {
            return res;
        }else {
            res += 1;
        }
    }
    return res;
}

int find_height (char **v, point n) {
    int res = 0;
    for (int i = n.x+1; i < 12; ++i) {
        if (v[i][n.y] == '#' || v[i][n.y] == '^'){
            return res;
        }else {
            res += 1;
        }
    }
    return res;
}

void replace_line (char **v, int line, int width, int col, char s[]){
    for (int i = 0; i < width; ++i) {
        v[line][i+col] = s[i];
    }
}

void get_line(char *line) {
    char c;
    int ind = 0;
    while (1) {
        c = getchar();
        if (c == '\n')
            break;
        line[ind++] = c;
    }
    line[ind] = '\0';
}

void fill_component(char **v, point n, char b[][7]){
    int w = find_width(v, n);
    int h = find_height(v, n);
    printf("to fill this component you have %d line with maximum %d len, we will start from"
           " first line, if you want to skip a line, just use a single : .\n", h, w);
    for (int i = 0; i < h; ++i) {
        char *line = (char *) malloc((1+w)* sizeof(char));
//        scanf("%s", line);
//        gets(line);
        printf("-> ");
        get_line(line);
        if (strcmp(line, ".") != 0) {
            int len = strlen(line);
            for (int j = len; j < w+1; ++j) {
                line[j] = ' ';
            }
            line[w+1] = '\0';
            replace_line(v, n.x+1+i, w, n.y, line);
            system("cls");
            printf("replacing\n");
            sleep(1);
            print_view_updated(v);
            print_but(b);
        }
    }
}

int in_but (char b[][7], char s[], int *ind) {
    for (int i = 0; i < 6; ++i) {
        if (strcmp(b[i], s) == 0) {
            *ind = i;
            return 1;
        }
    }
    *ind = -1;
    return -1;
}

int repeated_check_2 (char s[], char file_name[]) {
    FILE *fp = fopen(file_name, "r");
    char form[21];
    int ind = 0;
    while (1) {
        char c;
        c = fgetc(fp);
        if (c == EOF) {
            break;
        }else if (c == '\n') {
            form[ind] = '\0';
            ind = 0;
            if (strcmp(s, form) == 0) {
                fclose(fp);
                return -1;
            }
        }else {
            form[ind++] = c;
        }
    }
    fclose(fp);
    return 1;
}

void add_complete_form (char **v, char file[]) {
    FILE *fp;
    char name[21], final_name[45], include_name[31];
    include_name[0] = '\0';
    final_name[0] = '\0';
    strcat(include_name, file);
    strcat(include_name, "_designs.txt");
    fp = fopen(include_name, "a+");
    fclose(fp);
    while (1) {
        printf("Enter your form name (less than 20 characters):\n-> ");
        scanf("%s", name);
        if (repeated_check_2(name, include_name) == 1){
            break;
        }else {
            printf("wrong input, try again");
        }
    }
    strcat(final_name, file);
    strcat(final_name, "_");
    strcat(final_name, name);
    fp = fopen(include_name, "a");
    fprintf(fp, "%s\n", name);
    fclose(fp);
    strcat(final_name, ".txt");
    fp = fopen(final_name, "w");
    print_in_file(fp, v);
    fclose(fp);

}

void run (char **v, char **v_o) {
    char buttons[6][7] = {"ADD", "FIND", "EDIT", "REMOVE", "OK", "EXIT"};
    FILE *fp = fopen("all_forms.txt", "r+");
    int t;
    char **all_forms = all_form_finder(fp, &t);
    char selected_form[25];
    fclose(fp);
    printf("welcome to run part, at first, choose a design to continue :\n");
    while (1){
        int flag_accepted = 0;
        for (int i = 0; i < t; ++i) {
            printf("^ %s ^\n", all_forms[i]);
        }
        printf("-> ");
        scanf("%s", selected_form);
        for (int i = 0; i < t; ++i) {
            if (strcmp(all_forms[i], selected_form) == 0) {
                flag_accepted = 1;
                break;
            }
        }
        if (flag_accepted ==1) {
            break;
        }else {
            printf("wrong name, try again :\n");
        }
    }
    strcat(selected_form, ".txt");
    fp = fopen(selected_form, "r");
    read_from_file(fp, v);
    fclose(fp);
    selected_form[strlen(selected_form)-4] = '\0';
    create_v_o(v, v_o);
    int but_ind, flag_exit = 0;
    while (1){
        system("cls");
        sleep(1);
        print_view_updated(v);
        print_but(buttons);
        char selected_com[119];
        printf("the aim content or button :\n-> ");
        scanf("%s", selected_com);
        getchar();
        point new = find_component(v, selected_com);
         if (in_but(buttons, selected_com, &but_ind) == 1){
            switch (but_ind) {
                case 0:
                    system("cls");
                    sleep(1);
                    print_view_updated(v);
                    print_selected_but(0, buttons);
                    add_complete_form(v, selected_form);
                    break;
                case 1:
                    system("cls");
                    sleep(1);
                    print_view_updated(v);
                    print_selected_but_2(1, buttons);
                    find_form(v, selected_form);
                    break;
                case 2:
                    system("cls");
                    sleep(1);
                    print_view_updated(v);
                    print_selected_but_2(2, buttons);
                    break;
                case 3:
                    system("cls");
                    sleep(1);
                    print_view_updated(v);
                    print_selected_but_2(3, buttons);
                    break;
                case 4:
                    system("cls");
                    sleep(1);
                    print_view_updated(v);
                    print_selected_but_2(4, buttons);
                    break;
                case 5:
                    flag_exit = 1;
                    break;
            }
        }else if (new.x == 0) {
            printf("wrong component");
        }else {
            fill_component(v, new, buttons);
        }
        if (flag_exit == 1){
            break;
        }
    }
}

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

/*
 * char **view_port = (char **) malloc(12 * sizeof(char*));
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
    text_box t;
    t.l = (char *) malloc(21* sizeof(char));
    printf("text box line : ");
    scanf("%d", &t.x);
    printf("text box column : ");
    scanf("%d", &t.y);
    printf("text box width : ");
    scanf("%d", &t.w);
    printf("text box height : ");
    scanf("%d", &t.h);
    printf("text box label (less than 20 character) : ");
    scanf("%s", t.l);
    t.x -= 1;
    t.y -= 1;
    printf("%d", check_avalibity_text_box(t, view_port, view_port_oc));
    return 0;
 */
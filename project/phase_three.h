//
// Created by Ehsan on 7/13/2022.
//

#ifndef PROJECT_PHASE_THREE_H
#define PROJECT_PHASE_THREE_H

#endif //PROJECT_PHASE_THREE_H

char **create_view_port() {
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
    return view_port;
}


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
    v[n.x][n.y-1] = '*';
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

char **find_all_forms(char all[], int *t) {
    FILE *fp = fopen(all, "r");
    char **all_names = (char **) malloc(sizeof(char*));
    int all_ind = 0, ind = 0;
    char form[21];
    char c;
    while (1) {
        c = fgetc(fp);
        if (c == EOF) {
            break;
        }else if (c == '\n') {
            all_names[all_ind] = (char *)malloc(21* sizeof(char));
            form[ind] = '\0';
            ind = 0;
            all_names[ind][0] = '\0';
            strcpy(all_names[ind], form);
            all_ind++;
            all_names = (char **) realloc(all_names, (all_ind+1)* sizeof(char *));
        }else {
            form[ind++] = c;
        }
    }
    *t = all_ind;
    return all_names;
}

int is_found (char **v, char name[], char s[]) {
    char file_name[46];
    file_name[0] = '\0';
    strcat(file_name, s);
    strcat(file_name, "_");
    strcat(file_name, name);
    strcat(file_name, ".txt");
    char **check_view = create_view_port();
    FILE *fp = fopen(file_name, "r");
    read_from_file(fp, check_view);
    fclose(fp);
    for (int i = 0; i < 12; ++i) {
        for (int j = 0; j < 120; ++j) {
            if (v[i][j] == '*' && check_view[i][j] == '*') {
                int x = i+1;
                int y = j+1;
                char line_v[119], line_v_file[119];
                int ind = 0;
                while (v[x+1][j+1] != '#' && v[x+1][j+1] != '^'){
                    while (v[i + 1][y + 1] != '#' && v[i + 1][y + 1] != '^') {
                        line_v[ind] = v[x][y];
                        line_v_file[ind] = v[x][y];
                        ind++;
                        y++;
                    }
                    line_v_file[ind] = '\0';
                    line_v[ind] = '\0';
                    if (strcmp(line_v, line_v_file) != 0) {
                        return -1;
                    }
                    x += 1;
                    ind = 0;
                }
            }
        }
    }
    return 1;
}


void print_but_find (char b[][7]) {
    for (int i = 0; i < 33; ++i) {
        printf("_");
    }
    printf("\n");
    for (int i = 0; i < 4; ++i) {
        printf("|%s|", b[i]);
        if (i != 3)
            printf("*");
    }
    printf("\n");
    for (int i = 0; i < 33; ++i) {
        printf("-");
    }
    printf("\n");
}

void fill_component_2(char **v, point n, char b[][7]){
    int w = find_width(v, n);
    int h = find_height(v, n);
    v[n.x][n.y-1] = '*';
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
            print_but_find(b);
        }
    }
}

void edit_form(char **v, char b[][7], char file_name[]) {
    while (1) {
        system("cls");
        sleep(1);
        print_view_updated(v);
        print_but_find(b);
        char selected_com[119];
        printf("the aim content or button :\n-> ");
        scanf("%s", selected_com);
        getchar();
        point new = find_component(v, selected_com);
        if (strcmp(selected_com, "EXIT") == 0){
            printf("is it ok ? 1. YES 2. NO\n->");
            int flag;
            scanf("%d", &flag);
            if (flag == 1)
                break;
        }else if (new.x == 0) {
            printf("wrong component");
        }else {
            fill_component_2(v, new, b);
        }
    }
    FILE *fp = fopen(file_name, "w");
    print_in_file(fp, v);
    fclose(fp);
}

void remove_form(char design_name[], char name[], char **all, int t){
    printf("do you want to remove this form? 1. yes 2. no\n-> ");
    int flag_continue;
    scanf("%d", &flag_continue);
    if (flag_continue == 1){
        FILE *fp = fopen(design_name, "w");
        for (int i = 0; i < t; ++i) {
            if(strcmp(all[i], name) != 0){
                fprintf(fp, "%s\n", all[i]);
            }
        }
    }
}

void find_form (char **v, char s[]) {
    char all_forms[29];
    int t_forms, accepted = 0;
    all_forms[0] = '\0';
    strcpy(all_forms, s);
    strcat(all_forms, "_designs.txt");
    char **all_form_names = find_all_forms(all_forms, &t_forms);
    char **accepted_form = (char **) malloc(t_forms * sizeof(char *));
    for (int i = 0; i < t_forms; ++i) {
        if (is_found(v, all_form_names[i], s) == 1) {
            accepted_form[accepted] = (char *) malloc(21* sizeof(char));
            strcpy(accepted_form[accepted], all_form_names[i]);
            accepted += 1;
        }
    }
    char **new_view;
    char file_name[46];
    char name[21];
    while (1){
        system("cls");
        sleep(1);
        printf("here's all matched form :\n");
        for (int i = 0; i < accepted; ++i) {
            printf("^ %s ^\n", accepted_form[i]);
        }
        printf("now you can choose one of these\n-> ");
        scanf("%s", name);
        file_name[0] = '\0';
        strcat(file_name, s);
        strcat(file_name, "_");
        strcat(file_name, name);
        strcat(file_name, ".txt");
        new_view = create_view_port();
        FILE *fp = fopen(file_name, "r");
        read_from_file(fp, new_view);
        system("cls");
        sleep(1);
        print_view_updated(new_view);
        printf("\nis it accepted ? 1. YES 2. NO\n-> ");
        int check;
        scanf("%d", &check);
        if (check == 1)
            break;
        else
            printf("choose another\n");
    }
    char button_new[4][7] = {"EDIT", "REMOVE", "OK", "EXIT"};
    system("cls");
    sleep(1);
    print_view_updated(new_view);
    print_but_find(button_new);
    printf("now choose one\n-> ");
    char butt[7];
    while(1) {
        scanf("%s", butt);
        if (strcmp(butt, "EDIT") == 0) {
            edit_form(new_view, button_new, file_name);
        }else if (strcmp(butt, "REMOVE")==0) {
            remove_form(all_forms, name, all_form_names, t_forms);
        }else if (strcmp(butt, "EXIT") == 0 || strcmp(butt, "OK") == 0){
            break;
        }else {
            printf("wrong input, try again\n-> ");
        }
    }
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
                    strcat(selected_form, ".txt");
                    fp = fopen(selected_form, "r");
                    read_from_file(fp, v);
                    fclose(fp);
                    selected_form[strlen(selected_form)-4] = '\0';
                    break;
                case 1:
                    system("cls");
                    sleep(1);
                    print_view_updated(v);
                    print_selected_but_2(1, buttons);
                    find_form(v, selected_form);
                    strcat(selected_form, ".txt");
                    fp = fopen(selected_form, "r");
                    read_from_file(fp, v);
                    fclose(fp);
                    selected_form[strlen(selected_form)-4] = '\0';
                    break;
                case 2:
                    system("cls");
                    sleep(1);
                    print_view_updated(v);
                    print_selected_but_2(2, buttons);
                    printf("not allowed\n");
                    sleep(2);
                    break;
                case 3:
                    system("cls");
                    sleep(1);
                    print_view_updated(v);
                    print_selected_but_2(3, buttons);
                    printf("not allowed\n");
                    sleep(2);
                    break;
                case 4:
                    system("cls");
                    sleep(1);
                    print_view_updated(v);
                    print_selected_but_2(4, buttons);
                    printf("not allowed\n");
                    sleep(2);
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

//
// Created by Ehsan on 7/12/2022.
//

#ifndef PROJECT_PHASE_TWO_H
#define PROJECT_PHASE_TWO_H

#endif //PROJECT_PHASE_TWO_H

char **all_form_finder (FILE *fp, int *t) {
    char **all_forms = (char**) malloc(sizeof(char*));
    char form[21];
    char c;
    int t_forms = 0;
    int ind = 0;
    while (1) {
        c = fgetc(fp);
        if (c == EOF) {
            break;
        }
        else if (c == '\n') {
            form[ind] = '\0';
            all_forms[t_forms] = (char *) malloc(21 * sizeof(char));
            strcpy(all_forms[t_forms++], form);
            all_forms = (char **) realloc(all_forms, (t_forms+1) * sizeof(char *));
            ind = 0;
        }else {
            form[ind++] = c;
        }
    }
    *t = t_forms;
    return all_forms;
}

int is_char (char c) {
    if (c >= 'A' && c <= 'Z')
        return 1;
    else if (c >= 'a' && c <= 'z')
        return 1;
    return -1;
}

void create_v_o (char **v, char **v_o) {
    for (int i = 1; i < 10; ++i) {
        for (int j = 1; j < 118; ++j) {
            v_o[i][j] = v[i][j];
        }
        v_o[i][119] = '\0';
    }
}

void edit (char **v, char **v_o) {

    FILE *fp = fopen("all_forms.txt", "r+");
    int t;
    char **all_forms = all_form_finder(fp, &t);
    char selected_form[25];
    fclose(fp);
    printf("welcome to edit part, you can choose a form design to edit it, here's all"
           " form name, choose one :\n");
    for (int i = 0; i < t; ++i) {
        printf("^ %s ^\n", all_forms[i]);
    }
    printf("-> ");
    scanf("%s", selected_form);
    strcat(selected_form, ".txt");
    fp = fopen(selected_form, "r");
    read_from_file(fp, v);
    fclose(fp);
    create_v_o(v, v_o);
    while (1){
        system("cls");
        print_view(v);
        printf("choose a command to continue :\n"
               "1. Create text box    2. Create label    4. Exit design\n");
        int mode, flag_exit = 0;
        scanf("%d", &mode);
        switch (mode) {
            case 1:
                create_text_box(v, v_o, selected_form);
                break;
            case 2:
                create_label(v, v_o, selected_form);
                break;
            case 4:
                flag_exit = 1;
                break;
            default:
                printf("wrong input, try again\n");
                sleep(1);
        }
        if (flag_exit == 1) {
            printf("your form designed and saved successfully\n");
            break;
        }else {
            system("cls");
            sleep(1);
            print_view(v);
        }
    }
}

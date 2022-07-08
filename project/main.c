#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void print_view (char **v) {
    for (int i = 0; i < 10; ++i) {
        printf("%s\n", v[i]);
    }
}

char *add_form_name (char s[]) {
    FILE *fp;
    fp = fopen("all_forms.txt", "a+");
    fprintf(fp, "%s\n", s);
    fclose(fp);
    char *file_s = (char *) malloc(25* sizeof(char));
    strcpy(file_s, s);
    strcat(file_s, ".txt");
    fp = fopen(file_s, "w");
    fclose(fp);
    return file_s;
}

typedef struct text {
    int x; //the line
    int y; //the col
    int w; //width
    int h; //height
    char* l; //text box label
}text_box;

typedef struct label {
    int x;
    int y;
    int w;
    int h;
    char* content;
}label;

int occupied(text_box t, char **v) {
    for (int i = t.x-1; i <= t.x+t.h; ++i) {
        for (int j = t.y-1; j <= t.y+t.w; ++j) {
            if (v[i][j] == '#') {
                return -1;
            }
        }
    }
    return 1;
}

int check_avalibity_text_box (text_box t, char **v, char **v_o) {
    if (t.x >= 11 || t.x <= 0) {
        return -1;
    }else if (t.y <= 0 || t.y >= 120) {
        return -1;
    }else if (t.x + t.h >= 11 || t.y + t.w >= 120) {
        return -1;
    }else if (t.h <=0 || t.w <= 0) {
        return -1;
    }else if (occupied(t, v_o) == 1) {
        return -1;
    }
    return 1;
}
void replace (text_box t, char **v, char **v_o, char *file) {
    for (int i = t.x-1; i <= t.x+t.h; ++i) {

    }
}

void create_text_box (char **v, char** v_o, char *file) {
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
    if (check_avalibity_text_box(t, v, v_o) != -1) {
        replace(t, v, v_o, file);
    }
}


void create_label (char **v, char** v_o, char *file) {}

void design (char **v, char **v_o) {
    system("cls");
    print_view(v);
    printf("welcome to design, first enter your form name, it shouldn't be more than 20 character\n-> ");
    char form_name[21];
    scanf("%s", form_name);
    char *file_name = add_form_name(form_name);
    while (1){
        system("cls");
        print_view(v);
        printf("choose a command to continue :\n"
               "1. Create text box    2. Create label    3. Exit design\n");
        int mode, flag_exit = 0;
        scanf("%d", &mode);
        switch (mode) {
            case 1:
                create_text_box(v, v_o, file_name);
                break;
            case 2:
                create_label(v, v_o, file_name);
                break;
            case 3:
                flag_exit = 1;
                break;
            default:
                printf("wrong input, try again\n");
        }
        if (flag_exit == 1) {
            printf("your form designed and saved successfully\n");
            break;
        }
    }
}

void edit () {

}

void run () {
    scanf("%d");
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
        printf("Welcome, choose an mode to start :\n"
               "1. Design a form    2. Edit a form    3. Run a form    9.exit\n-> ");
        scanf("%d", &mode);
        int flag_accept = 0;
        switch (mode) {
            case 1:
                design(view_port, view_port_oc);
                break;
            case 2:
                edit();
                break;
            case 3:
                run();
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

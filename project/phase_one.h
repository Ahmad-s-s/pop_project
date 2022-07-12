 //
// Created by Ehsan on 7/12/2022.
//

#ifndef PROJECT_PHASE_ONE_H
#define PROJECT_PHASE_ONE_H

#endif //PROJECT_PHASE_ONE_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

 void print_view_o (char **v) {
     for (int i = 0; i < 10; ++i) {
         printf("%s\n", v[i]);
     }
     for (int i = 0; i < 120; ++i) {
         printf("*");
     }
     printf("\n");
 }

void print_view (char **v) {
    for (int i = 0; i < 12; ++i) {
        printf("%s\n", v[i]);
    }
    for (int i = 0; i < 120; ++i) {
        printf("*");
    }
    printf("\n");
}

void print_in_file (FILE *fp, char **v) {
    for (int i = 0; i < 12; ++i) {
        for (int j = 0; j < 121; ++j) {
            fputc(v[i][j], fp);
        }
    }
}

void read_from_file (FILE *fp, char **v) {
    for (int i = 0; i < 12; ++i) {
        for (int j = 0; j < 121; ++j) {
            v[i][j] = fgetc(fp);
        }
        v[i][121] = '\0';
    }
}


char *add_form_name (char s[]) {
    FILE *fp = fopen("all_forms.txt", "a+");
    fprintf(fp,"%s\n",s);
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
    for (int i = t.x; i < t.x+t.h; ++i) {
        for (int j = t.y; j < t.y+t.w; ++j) {
            if (v[i][j] == '#') {
                return -1;
            }
        }
    }
    return 1;
}

int check_avalibity_text_box (text_box t, char **v_o) {
    if (t.x >= 11 || t.x <= 0) {
        return -1;
    }else if (t.y <= 0 || t.y >= 120) {
        return -1;
    }else if (t.x + t.h >= 11 || t.y + t.w >= 120) {
        return -1;
    }else if (t.h <=0 || t.w <= 0) {
        return -1;
    }else if (occupied(t, v_o) != 1) {
        return -1;
    }
    return 1;
}
void replace_text_box (text_box t, char **v, char **v_o, char *file) {
    for (int i = t.x-1; i <= t.x+t.h; ++i) {
        for (int j = t.y-1; j <=t.y+t.w ; ++j) {
            v_o[i][j] = '#';
        }
    }
    for (int j = t.y-1; j <=t.y+t.w ; ++j) {
        v[t.x-1][j] = '#';
        v[t.x+t.h][j] = '#';
    }
    for (int i = t.x-1; i <= t.x+t.h; ++i) {
        v[i][t.y-1] = '#';
        v[i][t.y+t.w] = '#';
    }
    int ind = 0;
    for (int i = t.y; i <t.y + strlen(t.l) ; ++i) {
        v[t.x-1][i] = t.l[ind++];
    }
    FILE *fp = fopen(file, "w");
    print_in_file(fp, v);
    fclose(fp);
}

void create_text_box (char **v, char** v_o, char *file) {
    text_box t;
    printf("text box line : ");
    scanf("%d", &t.x);
    printf("text box column : ");
    scanf("%d", &t.y);
    printf("text box width : ");
    scanf("%d", &t.w);
    printf("text box height : ");
    scanf("%d", &t.h);
    t.l = (char *) malloc(t.w* sizeof(char));
    printf("text box label (less than its width) : ");
    scanf("%s", t.l);
    t.l[t.w] = '\0';
    if (check_avalibity_text_box(t, v_o) != -1) {
        printf("replacing");
        sleep(1);
        replace_text_box(t, v, v_o, file);
    }else {
        printf("unavailable data, choose again and try harder :) \n");
        sleep(1);
    }
}
///////////////////////////////////////////////////////////////////////////
int occupied_label(label l, char **v_o) {
    for (int i = l.x; i < l.x+l.h; ++i) {
        for (int j = l.y; j < l.y+l.w; ++j) {
            if (v_o[i][j] == '#') {
                return -1;
            }
        }
    }
    return 1;
}

int check_avalibity_label(label l, char **v_o) {
    if (l.x >= 11 || l.x <= 0) {
        return -1;
    }else if (l.y <= 0 || l.y >= 120) {
        return -1;
    }else if (l.x + l.h >= 11 || l.y + l.w >= 120) {
        return -1;
    }else if (l.h <=0 || l.w <= 0) {
        return -1;
    }else if (occupied_label(l, v_o) != 1) {
        return -1;
    }
    return 1;
}

void replace_label (label l, char **v,char **v_o, char* file) {
    for (int i = l.x-1; i <= l.x+l.h; ++i) {
        for (int j = l.y-1; j <=l.y+l.w ; ++j) {
            v_o[i][j] = '#';
        }
    }
    int ind = 0;
    for (int i = l.y; i < l.y+strlen(l.content); ++i) {
        v[l.x][i] = l.content[ind++];
    }
    for (int j = l.y-1; j <=l.y+l.w ; ++j) {
        v[l.x-1][j] = '^';
        v[l.x+l.h][j] = '^';
    }
    for (int i = l.x-1; i <= l.x+l.h; ++i) {
        v[i][l.y-1] = '^';
        v[i][l.y+l.w] = '^';
    }
    FILE *fp = fopen(file, "w");
    print_in_file(fp, v);
    fclose(fp);
}

void create_label (char **v, char** v_o, char *file) {
    label l;
    printf("label line : ");
    scanf("%d", &l.x);
    printf("label column : ");
    scanf("%d", &l.y);
    printf("label width : ");
    scanf("%d", &l.w);
    printf("label height : ");
    scanf("%d", &l.h);
    l.content = (char *) malloc(l.w* sizeof(char));
    printf("label content (less than it's width) : ");
    scanf("%s", l.content);
    l.content[l.w] = '\0';
    if (check_avalibity_label(l, v_o) == 1){
        printf("replacing\n");
        sleep(1);
        replace_label (l, v, v_o, file);
    }else {
        printf("error!\n");
        sleep(1);
    }
}
//////////////////////////////////////////////////////////////////////

int repeated_check (char s[]) {
    FILE *fp = fopen("all_forms.txt", "r");
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

void design (char **v, char **v_o) {
    system("cls");
    print_view(v);
    printf("welcome to design, first enter your form name, it shouldn't be more than 20 character\n-> ");
    char form_name[21];
    while (1){
        scanf("%s", form_name);
        if (repeated_check(form_name) == 1) {
            break;
        }else {
            printf("already exist, try again\n-> ");
        }
    }
    char *file_name = add_form_name(form_name);
    while (1){
        system("cls");
        print_view(v);
        printf("choose a command to continue :\n"
               "1. Create text box    2. Create label    4. Exit design\n");
        int mode, flag_exit = 0;
        scanf("%d", &mode);
        switch (mode) {
            case 1:
                create_text_box(v, v_o, file_name);
                break;
            case 2:
                create_label(v, v_o, file_name);
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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

int menu = 1;
char studentID[100];
char name[128];
char array[240][100];
char array2D[240][300];
float arrayint2D[128][2];
int num;
int ii = 0;
char patchID[100];
char variable[200];
char fileModule[240];
char moduleSelected[100];
char fileModule[240];

int selectModule() {
    ii = 0;
    system("cls");

    int test = 0;
    int test2 = 1;
    char array2[240];

    if (menu == 1) {
        printf("ID \n");
        scanf("%s", studentID);
    }
    int student = atoi(studentID);

    for (int j = 0; j < strlen(studentID); ++j) {
        if (studentID[j] < 48 || studentID[j] > 57) {
            test2 = 0;
        }
    }
    if (test2 == 0) {
        selectModule(patchID, variable, fileModule,
                     moduleSelected);
    } else {

        struct dirent *lecture2;
        DIR *patch2;
        patch2 = opendir("./grades/");
        while ((lecture2 = readdir(patch2))) {
            strcpy(array2, lecture2->d_name);
            int array22 = atoi(array2);
            if (array22 == student) {
                test = 1;
            }
        }


        if (test == 1) {
            sprintf(patchID, "..\\grades\\%s", studentID);
            strcpy(variable, "./grades/");
            strcat(variable, studentID);
            struct dirent *lecture;
            DIR *patch;
            patch = opendir(variable);
            int i = 1;

            while ((lecture = readdir(patch))) {
                if (!(i - 2 == -1 || i - 2 == 0)) {
                    printf("%d %s\n", i - 2, lecture->d_name);
                    strcpy(array[i - 2], lecture->d_name);
                }
                i++;
            }
            closedir(patch);
            if (menu == 1 || menu == 2) {
                printf("\n\nSELECT A MODULE : ");
                scanf("%s", moduleSelected);
            }

            num = atoi(moduleSelected);
            if (num < 1 || num > i - 3) {
                menu = 2;
                selectModule();
                return num;
            }


        } else {

            selectModule(patchID, variable, fileModule,
                         moduleSelected);
        }
    }


}

int readModule() {

    sprintf(fileModule, "grades\\%s\\%s",
            studentID, array[num]);
    FILE *file;
    file = fopen(fileModule, "r");


    char line[128][240];
    if (file != NULL) {

        while (fgets(line[ii], sizeof line, file) != NULL) {

            int iii = 0;
            char separator[] = " ";
            char *sentence = strtok(line[ii], separator);
            while (sentence != NULL) {

                if (iii == 2) {
                    strcpy(array2D[ii], sentence);

                } else if (iii == 0) {
                    float number = atoi(sentence);
                    arrayint2D[ii][0] = number;

                } else if (iii == 1) {
                    float number = atoi(sentence);
                    arrayint2D[ii][1] = number;

                }
                sentence = strtok(NULL, separator);
                iii++;
            }
            ii++;
        }

    }
    fclose(file);
    return ii;
}

void getStudentName() {
    FILE *fileStudentsID;
    fileStudentsID = fopen("grades\\studentsID.txt", "r");

    char nameStudent[240][300];
    int lineID[128];
    int jj = 0;
    char line2[128][240];
    if (fileStudentsID != NULL) {
        while (fgets(line2[jj], sizeof line2, fileStudentsID) != NULL) {
            int jjj = 0;
            char separatorID[] = "-";
            char *sentenceID = strtok(line2[jj], separatorID);
            while (sentenceID != NULL) {
                if (jjj == 1) {
                    strcpy(nameStudent[jj], sentenceID);
                } else if (jjj == 0) {
                    lineID[jj] = atoi(sentenceID);
                }
                sentenceID = strtok(NULL, separatorID);
                jjj++;
            }
            jj++;
        }
        fclose(fileStudentsID);
    }


    int student = atoi(studentID);
    for (int k = 0; k < jj; ++k) {
        if (lineID[k] == student) {
            strcpy(name, nameStudent[k]);
        }
    }
}

void result() {
    float total = 0;
    printf("%s - %s\n\n", name, studentID, array[num]);
    printf("%s\n\n", array[num]);
    printf("   Weighting     Grade Item               Grade\n");

    for (int j = 0; j < ii; ++j) {
        printf("%d  %.0f/100", j + 1, arrayint2D[j][0]);
        printf("            %s              ", array2D[j]);
        printf("%.2f/100\n", arrayint2D[j][1]);
        total += (arrayint2D[j][0] / 100) * arrayint2D[j][1];
    }
    printf("                     TOTAL               %.2f/100\n\n", total);
}

void addRow() {
    char easy[40];
    float weighting;
    float grade;
    printf("\nWrite Easy: \n");
    scanf("%s", easy);
    printf("\nWrite Weighting: \n");
    scanf("%f", &weighting);
    printf("\nWrite Grade: \n");
    scanf("%f", &grade);

    FILE *f = NULL;
    f = fopen(fileModule, "a");
    fprintf(f, "\n%.0f %.0f %s ", weighting, grade, easy);
    fclose(f);

    system("pause");
}

void deleteRow() {
    int deleteLine;
    printf("\nSelect the line for delete :   ");
    scanf("%d", &deleteLine);
    FILE *file;
    file = fopen(fileModule, "r");
    char tempArray[240][240];
    int kk = 1;
    char line[128][240];
    if (file != NULL) {

        while (fgets(line[kk], sizeof line, file) != NULL) {
            strcpy(tempArray[kk], line[kk]);
            kk++;
        }
    }
    fclose(file);
    FILE *f = NULL;
    f = fopen(fileModule, "w");
    for (int i = 1; i <= kk; ++i) {
        if (i != deleteLine) {
            fprintf(f, "%s", tempArray[i]);
        }
    }
    fclose(f);
}

void viderBuffer() {
    int c = 0;
    while (c != '\n' && c != EOF) {
        c = getchar();
    }
}

void modifyRow() {
    int deleteLine;
    char easy[40];
    float weighting;
    float grade;

    printf("\nSelect the line for modify :   ");
    scanf("%d", &deleteLine);
    printf("\nWrite Easy: \n");
    scanf("%s", easy);
    printf("\nWrite Weighting: \n");
    scanf("%f", &weighting);
    printf("\nWrite Grade: \n");
    scanf("%f", &grade);

    FILE *file;
    file = fopen(fileModule, "r");
    char tempArray[240][240];
    int kk = 1;
    char line[128][240];
    if (file != NULL) {

        while (fgets(line[kk], sizeof line, file) != NULL) {
            strcpy(tempArray[kk], line[kk]);
            kk++;
        }
    }
    fclose(file);
    FILE *f = NULL;
    f = fopen(fileModule, "w");
    for (int i = 1; i <= kk; ++i) {
        if (i != deleteLine) {
            fprintf(f, "%s", tempArray[i]);
        } else {
            fprintf(f, "%.0f %.0f %s \n", weighting, grade, easy);
        }
    }
    fclose(f);
}

int main() {
    system("cls");


    char patchID[100];
    char variable[200];
    char fileModule[240];


    char moduleSelected[100];
    int test3 = 1;

    num = selectModule(patchID, variable, fileModule, moduleSelected);

    ii = readModule(fileModule);
    getStudentName(studentID);
    system("cls");
    result();
    printf("\n\n1 select an other UP number\n2 select an other module\n3 modify a grade\n4 delete a grade\n5 add a grade\n6 EXIT");
    printf("\n\nSELECT THE CORRESPONDING NUMBER");
    char menuString[1000];
    scanf("%s", menuString);
    for (int j = 0; j < strlen(menuString); ++j) {
        if (studentID[j] < 48 || studentID[j] > 57) {
            test3 = 0;
        }
    }
    if (test3 == 1) {
        menu = atoi(menuString);
    } else {
        menu = 7;
        system("cls");
        main();
    }


    switch (menu) {
        case 1:

        case 2:
            main();
            break;
        case 3:
            system("cls");
            result();
            modifyRow();

            main();
            break;
        case 4:
            system("cls");
            result();
            deleteRow();

            main();
            break;
        case 5:
            result();
            addRow();
            break;
        case 6:
            system("exit");
            break;
        default:
            main();
    }

    return 0;
}

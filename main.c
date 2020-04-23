#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

int menu = 1;
char studentID[100];

int selectModule(char patchID[100], char variable[200], char studentID[100], char fileModule[240], char array[240][100],
                 char moduleSelected[100]) {
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

    printf("\n\nSELECT A MODULE : ");
    scanf("%s", moduleSelected);
    int num = atoi(moduleSelected);
    return num;
}

int readModule(char fileModule[240], char studentID[100], char array[240][100], int num, char array2D[240][300],
               float arrayint2D[128][2]) {

    sprintf(fileModule, "grades\\%s\\%s",
            studentID, array[num]);
    FILE *file;
    file = fopen(fileModule, "r");

    int ii = 0;
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

void getStudentName(char studentID[100], char name[128]) {


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

void result(char studentID[100], char name[128], int num, char array2D[240][300],
            float arrayint2D[128][2], char array[240][100], int ii) {
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

void addRow(char fileModule[240]) {
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

void deleteRow(char fileModule[240]) {
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

int main() {
    system("cls");
    char name[128];
    int num;
    int ii;
    char patchID[100];
    char variable[200];
    char fileModule[240];
    char array[240][100];
    char moduleSelected[100];
    char array2D[240][300];
    float arrayint2D[128][2];

    if (menu == 1) {
        printf("ID \n");
        scanf("%s", studentID);
    }
    num = selectModule(patchID, variable, studentID, fileModule, array, moduleSelected);
    ii = readModule(fileModule, studentID, array, num, array2D, arrayint2D);
    getStudentName(studentID, name);
    system("cls");
    result(studentID, name, num, array2D,
           arrayint2D, array, ii);
    printf("\n\n1 select an other UP number\n2 select an other module\n3 modify a grade\n4 delete a grade\n5 add a grade\n6 EXIT");
    printf("\n\nSELECT THE CORRESPONDING NUMBER");
    scanf("%d", &menu);
    switch (menu) {
        case 1:
            system("cls");
            main();
            break;
        case 2:
            system("cls");
            main();
            break;
        case 3:
            break;
        case 4:
            system("cls");
            result(studentID, name, num, array2D,
                   arrayint2D, array, ii);
            deleteRow(fileModule);
            system("pause");
            break;
        case 5:
            system("cls");
            addRow(fileModule);
            break;
        case 6:
            system("exit");
            break;
        default:
            printf("vide");
    }
    return 0;
}

void deleteRow2(char fileModule[240]) {
    FILE *fileptr1;
    FILE *fileptr2;
    int temp2 = 0;
    char ch;
    int delete_line, temp = 1;
    fileptr1 = fopen(fileModule, "r");
    ch = getc(fileptr1);
    while (ch != EOF) {
        ch = getc(fileptr1);
    }
    rewind(fileptr1);
    printf(" \n Enter line number of the line to be deleted:");
    scanf("%d", &delete_line);
    //open new file in write mode
    fileptr2 = fopen("replica.txt", "a");
    ch = getc(fileptr1);
    while (ch != EOF) {
        ch = getc(fileptr1);

        if (ch == '\n')
            temp++;
        //except the line to be deleted
        if (temp != delete_line) {
            //copy all lines in file replica.c
            putc(ch, fileptr2);
        }
        temp2++;
    }
    fclose(fileptr1);
    fclose(fileptr2);
    remove(fileModule);
    //rename the file replica.c to original name
    // rename("replica.txt", fileModule);


}
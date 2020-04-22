#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

int modules(char patchID[100], char variable[200], char studentID[100], char fileModule[240], char array[240][100],
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

int module(char fileModule[240], char studentID[100], char array[240][100], int num,char array2D[240][300],float arrayint2D[128][2]) {

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
        fclose(file);
    }
    return ii;
}

int main() {
    int num;
    int ii;
    char patchID[100];
    char variable[200];
    char studentID[100];
    char fileModule[240];
    char array[240][100];
    char moduleSelected[100];
    char array2D[240][300];
    float arrayint2D[128][2];

    printf("ID \n");
    scanf("%s", studentID);


    num = modules(patchID, variable, studentID, fileModule, array, moduleSelected);
    ii = module(fileModule,studentID, array, num,array2D, arrayint2D);

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
    printf("\n");
    char name[128];
    int student = atoi(studentID);
    for (int k = 0; k < jj; ++k) {


        if (lineID[k] == student) {
            strcpy(name, nameStudent[k]);
        }

    }

    system("cls");

    float total = 0;
    printf("%s - %s\n\n%s\n", name, studentID, array[num]);
    printf("Weighting     Grade Item               Grade\n");

    for (int j = 0; j < ii; ++j) {
        printf(" %.0f/100", arrayint2D[j][0]);
        printf("            %s              ", array2D[j]);
        printf("%.2f/100\n", arrayint2D[j][1]);
        total += (arrayint2D[j][0] / 100) * arrayint2D[j][1];
    }
    printf("                  TOTAL               %.2f/100\n\n", total);
    int menu;
    printf("\n\n1 : select an other UP number\n2 : select module\n3 : edit\n4 : delete\n5 : EXIT");
    printf("\n\nSELECT THE CORRESPONDING NUMBER");
    scanf("%d", &menu);
    switch (menu) {
        case 1:
            system("cls");
            main();
            break;
        case 2:
          //  num = modules(patchID, variable, studentID, fileModule, array, moduleSelected);
      //      ii = module(fileModule,studentID, array, num,array2D, arrayint2D);
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            system("exit");
            break;
        default:
            printf("vide");

    }
    return 0;
}
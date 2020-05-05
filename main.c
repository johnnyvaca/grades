/*
 * title : grades
 * description : it’s an app that allows us to manage students' grades and annual averages.
 * Date : 06-05-2020
 * Author : Dinis Esteves
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

int menu = 1;
char studentID[100];
char name[128];
char moduleName[240][100];
char array2D[240][300];
float arrayint2D[128][2];
int num;
int ii = 0;
char patchID[100];
char variable[200];
char fileModule[240];
char moduleSelected[100];
char fileModule[240];
char message[200];
int testDelete = 2;
int indexDelete = 1;
int testAdd = 2;
int testAddGrade = 2;
char easy[40];
float weighting;
float grade;
char weightingString[100];
char gradeString[100];


int selectModule() {
    ii = 0;
    system("cls");
    int test = 0;
    int test2 = 1;
    char array2[240];
    if (menu == 1) {
        printf("Select an UP number \n");
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
            system("cls");
            while ((lecture = readdir(patch))) {
                if (!(i - 2 == -1 || i - 2 == 0)) {
                    printf("%d %s\n", i - 2, lecture->d_name);
                    strcpy(moduleName[i - 2], lecture->d_name);
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
            studentID, moduleName[num]);
    FILE *file;
    file = fopen(fileModule, "r");


    char line[128][240];
    if (file != NULL) {

        while (fgets(line[ii], sizeof line, file) != NULL) {

            int iii = 0;
            char separator[] = "-";
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

void displayMessages() {
    strcpy(message, "");
    switch (menu) {
        case 1:


        case 2:

            break;
        case 3:

            break;
        case 4:
            if (testDelete == 0) {
                strcpy(message, "\nerror!!! select a number by 1 to ");
                sprintf(message, "%s%d\n", message, indexDelete);

            }
            if (testDelete == 1) {
                strcpy(message, "\nsuccessful deletion\n");
            }
            break;
        case 5:
            if (testAdd == 0 || testAddGrade  == 0) {
                strcpy(message, "\nerror!!! select a number by 1 to 100");

            }
            if (testAdd == 1 || testAddGrade  == 1) {
                strcpy(message, "\nsuccessful add\n");
            }
            break;
        case 6:

            break;
        default:
            strcpy(message, "\nerror!!! select a number by 1 to 6\n");

    }
    printf("%s", message);

}

void result() {
    float total = 0;
    printf("%s - %s\n\n", name, studentID);
    printf("%s\n\n", moduleName[num]);
    printf("   Weighting     Grade Item               Grade\n");

    for (int j = 0; j < ii; ++j) {
        printf("%d  %.0f/100", j + 1, arrayint2D[j][0]);
        printf("            %s              ", array2D[j]);
        printf("%.2f/100\n", arrayint2D[j][1]);
        total += (arrayint2D[j][0] / 100) * arrayint2D[j][1];
    }
    printf("                     TOTAL               %.2f/100\n\n", total);
    displayMessages();
}

void addRow() {
if( testAdd == 2){
    printf("\nWrite Easy: \n");
    scanf("%s", easy);
}else{
    printf("\neasy :    %s",easy);
}
    testAdd = 2;
    if( testAddGrade == 2){
        printf("\nWrite Weighting: \n");
        scanf("%s", &weightingString);
    }else{
        printf("\nWeighting :    %s",weightingString);
    }

    testAddGrade = 2;
    for (int j = 0; j < strlen(weightingString); ++j) {
        if (weightingString[j] < 48 || weightingString[j] > 57) {
            testAdd = 0;
            break;
        } else {
            testAdd = 1;
        }
    }
    if (testAdd != 0) {
        weighting = atof(weightingString);

        printf("\nWrite Grade: \n");
        scanf("%s", &gradeString);
        for (int j = 0; j < strlen(gradeString); ++j) {
            if (gradeString[j] < 48 || gradeString[j] > 57) {
                testAddGrade = 0;
                testAdd = testAddGrade;
                break;
            } else {
                testAddGrade = 1;
                testAdd = testAddGrade;
            }
        }
    }

        if (testAddGrade !=0 && testAdd == 1) {
            grade = atof(gradeString);
            FILE *f = NULL;
            f = fopen(fileModule, "a");
            fprintf(f, "\n%.0f-%.0f-%s-", weighting, grade, easy);
            fclose(f);

            testAdd = 2;
            testAddGrade = 2;
        }

}

void deleteRow() {
    indexDelete = 1;
    testDelete = 2;
    FILE *file1;
    file1 = fopen(fileModule, "r");
    char line1[128][240];
    if (file1 != NULL) {
        while (fgets(line1[indexDelete], sizeof line1, file1) != NULL) {
            indexDelete++;
        }
    }

    fclose(file1);
    int deleteLine;
    char deleteLineString[100];
    testDelete = 1;
    printf("\nSelect the line for delete : ");
    scanf("%s", deleteLineString);
    for (int j = 0; j < strlen(deleteLineString); ++j) {
        if (deleteLineString[j] < 48 || deleteLineString[j] > 57) {
            testDelete = 0;
            break;
        } else {
            testDelete = 1;
        }
    }

    if (testDelete != 0) {
        FILE *file;
        file = fopen(fileModule, "r");
        char tempArray[240][240];
        char line[128][240];
        int index = 1;
        if (file != NULL) {
            while (fgets(line[index], sizeof line, file) != NULL) {
                strcpy(tempArray[index], line[index]);
                index++;
            }
        }
        fclose(file);
        deleteLine = atoi(deleteLineString);
        if (deleteLine < 1 || deleteLine >= indexDelete) {
            testDelete = 0;
        } else {
            testDelete = 1;
        }
        if (testDelete != 0) {
            FILE *f = NULL;
            f = fopen(fileModule, "w");
            for (int i = 1; i <= indexDelete; ++i) {
                if (i != deleteLine) {
                    fprintf(f, "%s", tempArray[i]);
                }
            }
            fclose(f);
        }

    }
    indexDelete--;
    testDelete = 2;
}

void modifyRow() {
    int deleteLine;
    char easy[40];
    float weighting;
    float grade;
    printf("\nSelect the line for modify :\n");
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
            fprintf(f, "%.0f-%.0f-%s-\n", weighting, grade, easy);
        }
    }
    fclose(f);
}

int main() {
    system("cls");
    int test = 1;
    num = selectModule();
    ii = readModule();
    getStudentName();
    system("cls");
    result();
    switch (menu) {
        case 3:
            system("cls");
            result();
            modifyRow();
         return main();
        case 4:
            if (testDelete == 0) {
                system("cls");
                result();
                deleteRow();
               return main();
            }
            break;
        case 5:
            if (testAdd == 0 || testAddGrade == 0) {
                system("cls");
                result();
                addRow();
                return main();
            }
            break;
        default:;
    }
    printf("\n\n1 select an other UP number\n2 select an other module\n3 modify a grade\n4 delete a grade\n5 add a grade\n6 EXIT");
    printf("\n\nSELECT THE CORRESPONDING NUMBER");
    char menuString[1000];
    scanf("%s", menuString);
    for (int j = 0; j < strlen(menuString); ++j) {
        if (studentID[j] < 48 || studentID[j] > 57) {
            test = 0;
        }
    }
    if (test == 1) {
        menu = atoi(menuString);
    } else {
        menu = -1;
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
            system("cls");
            result();
            addRow();
            main();
            break;
        case 6:
            system("exit");
            break;
        default:
            main();

    }
    return 0;
}

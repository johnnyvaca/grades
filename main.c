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
char studentName[128];
char moduleName[240][100];
char gradeAssessements[240][300];
float valuesAssessements[128][2];
int moduleSelected_int;
int numberLine = 0;
char patchSelected[100];
char patch[200];
char fileModule[240];
char moduleSelected[100];
char fileModule[240];
char message[200];
int testDelete = 2;
int indexDelete = 1;
int testAdd = 2;
int testAddGrade = 2;
char assessements[40];
float weighting;
float grade;
char weightingString[100];
char gradeString[100];
// this function displays the messages after the operation
// 0 = error || 1 = successfull
void displayMessages() {
    strcpy(message, "");
    switch (menu) {
        case 1:
        case 2:
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
            if (testAdd == 0 || testAddGrade == 0) {
                strcpy(message, "\nerror!!! select a number by 1 to 100");

            }
            if (testAdd == 1 || testAddGrade == 1) {
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
// this function get the number UP and the module
int selectUpModule() {
    numberLine = 0;
    system("cls");
    int testModule = 0;
    int testUpNumber = 1;
    char arrayName[240];
    if (menu == 1) {
        printf("Select an UP number \n");
        displayMessages();   // display message
        scanf("%s", studentID);
    }
    int student = atoi(studentID); // convert string to int
    for (int j = 0; j < strlen(studentID); ++j) { // between 0 and the string selected
        if (studentID[j] < 48 || studentID[j] > 57) { // if the string contain numbers between 0 to 9 in the ASCII table
            testUpNumber = 0;
        }
    }
    if (testUpNumber == 0) {
        selectUpModule(); // return to the same function
    } else {

        // TEST IF THE UP NUMBER EXIST
        struct dirent *readStudent;
        DIR *patchStudent;
        patchStudent = opendir("./grades/");
        while ((readStudent = readdir(patchStudent))) {
            strcpy(arrayName, readStudent->d_name); // taking back contain's name of the folder grades (UP NUMBERS)
            int array22 = atoi(arrayName);
            if (array22 == student) { // IF THE UP NUMBER EXIST, THE TEST IS 1
                testModule = 1;
            }
        }

        if (testModule == 1) {
            sprintf(patchSelected, "..\\grades\\%s", studentID); // GET PATCH UNTIL FILE SELECTED
            strcpy(patch, "./grades/");
            strcat(patch, studentID);
            struct dirent *lecture;
            DIR *fileValue; // open a Directory constance
            fileValue = opendir(patch);
            int indexModules = 1;
            system("cls");
            while ((lecture = readdir(fileValue))) {
                if (!(indexModules - 2 == -1 || indexModules - 2 == 0)) { // taking back folder's name without "." or ".."
                    printf("%d %s\n", indexModules - 2, lecture->d_name);
                    strcpy(moduleName[indexModules - 2], lecture->d_name); // save module's name
                }
                indexModules++;
            }
            closedir(fileValue); // close the directory constant
            if (menu == 1 || menu == 2) {
                printf("\n\nSELECT A MODULE : ");
                scanf("%s", moduleSelected);
            }

            moduleSelected_int = atoi(moduleSelected);

            if (moduleSelected_int < 1 || moduleSelected_int > indexModules - 3) {  //IF THE MODULE DO NOT EXIST, RETURN TO THE SAME FUNCTION
                menu = 2;
                selectUpModule();
                return moduleSelected_int;
            }

        } else { //IF THE UP NUMBER DO NOT EXIST, THE TEST IS 0 AND RETURN TO THE SAME FUNCTION

            selectUpModule();
        }
    }


}

int readModule() {

    sprintf(fileModule, "grades\\%s\\%s",
            studentID, moduleName[moduleSelected_int]); // get the patch to the variable fileModule

    // OPEN THE MODULE FILE IN READ MODE
    FILE *file;
    file = fopen(fileModule, "r");
    char line[128][240];
    if (file != NULL) {

        while (fgets(line[numberLine], sizeof line, file) != NULL) { // read the file line by line

            int indexWords = 0;
            char separator[] = "-";
            char *fileContent = strtok(line[numberLine], separator); // stock all separate words by the separator "-" of the modules file
            while (fileContent != NULL) {
                if (indexWords == 2) {
                    strcpy(gradeAssessements[numberLine], fileContent); // stock the name of the assessments

                } else if (indexWords == 0) {
                    float number = atoi(fileContent);
                    valuesAssessements[numberLine][0] = number; // stock the weighting

                } else if (indexWords == 1) {
                    float number = atoi(fileContent);
                    valuesAssessements[numberLine][1] = number;  // stock the grade

                }
                fileContent = strtok(NULL, separator);
                indexWords++;
            }
            numberLine++;
        }
    }
    fclose(file);
    return numberLine;
}

void getStudentName() {
    FILE *fileStudentsID;
    fileStudentsID = fopen("grades\\studentsID.txt", "r");

    char arrayStudentName[240][300];
    int lineID[128];
    int jj = 0;
    char line2[128][240];
    if (fileStudentsID != NULL) {
        while (fgets(line2[jj], sizeof line2, fileStudentsID) != NULL) {
            int jjj = 0;
            char separatorID[] = "-";
            char *fileContentID = strtok(line2[jj], separatorID);
            while (fileContentID != NULL) {
                if (jjj == 1) {
                    strcpy(arrayStudentName[jj], fileContentID);
                } else if (jjj == 0) {
                    lineID[jj] = atoi(fileContentID);
                }
                fileContentID = strtok(NULL, separatorID);
                jjj++;
            }
            jj++;
        }
        fclose(fileStudentsID);
    }


    int student = atoi(studentID);
    for (int k = 0; k < jj; ++k) {
        if (lineID[k] == student) {
            strcpy(studentName, arrayStudentName[k]);
        }
    }
}


void result() {
    float total = 0;
    printf("%s - %s\n\n", studentName, studentID);
    printf("%s\n\n", moduleName[moduleSelected_int]);
    printf("   Weighting     Grade Item               Grade\n");

    for (int j = 0; j < numberLine; ++j) {
        printf("%d  %.0f/100", j + 1, valuesAssessements[j][0]);
        printf("            %s              ", gradeAssessements[j]);
        printf("%.2f/100\n", valuesAssessements[j][1]);
        total += (valuesAssessements[j][0] / 100) * valuesAssessements[j][1];
    }
    printf("                     TOTAL               %.2f/100\n\n", total);
    displayMessages();
}

void addRow() {
    if (testAdd == 2) {
        printf("\nWrite Assessements: \n");
        scanf("%s", assessements);
    } else {
        printf("\nassessements :    %s", assessements);
    }
    testAdd = 2;
    if (testAddGrade == 2) {
        printf("\nWrite Weighting: \n");
        scanf("%s", &weightingString);
    } else {
        printf("\nWeighting :    %s", weightingString);
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

    if (testAddGrade != 0 && testAdd == 1) {
        grade = atof(gradeString);
        FILE *f = NULL;
        f = fopen(fileModule, "a");
        fprintf(f, "\n%.0f-%.0f-%s-", weighting, grade, assessements);
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
    char assessementsModify[40];
    float weightingModify;
    float grade;
    printf("\nSelect the line for modify :\n");
    scanf("%d", &deleteLine);
    printf("\nWrite assessements: \n");
    scanf("%s", assessementsModify);
    printf("\nWrite weighting: \n");
    scanf("%f", &weightingModify);
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
            fprintf(f, "%.0f-%.0f-%s-\n", weightingModify, grade, assessementsModify);
        }
    }
    fclose(f);
}

int main() {
    system("cls");
    int testMenu = 1;
    moduleSelected_int = selectUpModule();
    numberLine = readModule();
    getStudentName();
    system("cls");
    result();
    switch (menu) {
        case 3:
            if (testAdd == 0 || testAddGrade == 0) {
                system("cls");
                result();
                addRow();
                return main();
            }
            break;
        case 4:
            if (testDelete == 0) {
                system("cls");
                result();
                deleteRow();
                return main();
            }
            break;

        default:;
    }
    printf("\n\n1 select an other UP number\n2 select an other module\n3 add a grade\n4 delete a grade\n5 modify a grade\n6 EXIT");
    printf("\n\nSELECT THE CORRESPONDING NUMBER");
    char menuString[1000];
    scanf("%s", menuString);
    for (int j = 0; j < strlen(menuString); ++j) {
        if (studentID[j] < 48 || studentID[j] > 57) {
            testMenu = 0;
        }
    }
    if (testMenu == 1) {
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
        case 3:    system("cls");
            result();
            addRow();
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
            modifyRow();
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

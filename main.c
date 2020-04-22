#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

int main() {


    char studentID[10];
    printf("ID \n");
    scanf("%s", studentID);

    char patchID[100];

    sprintf(patchID, "..\\grades\\%s", studentID);
    char variable[200];
    strcpy(variable, "./grades/");
    strcat(variable, studentID);

    //  printf("\n\n%s",variable);

    struct dirent *lecture;
    DIR *patch;
    patch = opendir(variable);
    int i = 1;
    char fileModule[240];
    char array[240][100];
    char moduleSelected[100];
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
    sprintf(fileModule, "grades\\%s\\%s",
            studentID, array[num]);
    FILE *file;
    file = fopen(fileModule, "r");
    char array2D[240][300];
    int arrayint2D[128][2];
    int ii = 0;
    char line[128][240];
  //  char array3d[240][230][230];
    if (file != NULL) {

        while (fgets(line[ii], sizeof line, file) != NULL) {


            int iii = 0;
            char separator[] = " ";
            char *sentence = strtok(line[ii], separator);
            while (sentence != NULL) {

                if (iii == 2) {
                    strcpy(array2D[ii], sentence);
                    printf("module %s\n", array2D[ii]);
                } else if (iii == 0) {
                    int number = atoi(sentence);
                    arrayint2D[ii][0] = number;
                    printf("tab  %d\n", arrayint2D[ii][0]);
                } else {
                    int number = atoi(sentence);
                    arrayint2D[ii][1] = number;
                    printf("tab2  %d\n", arrayint2D[ii][1]);
                }


                sentence = strtok(NULL, separator);
                iii++;
            }

        /*    strcpy(array3d[ii][0], "hello");
            strcpy(array3d[ii][1], " hello");
            strcpy(array3d[ii][2], "hello");

*/
            ii++;
        }


        fclose(file);


    }

    //   int lenght = strlen(line[ii]);
    //  printf("%d",lenght);


    printf("\n\n3D  ::   %s",array2D[2]);
    printf("\n\n3D  ::   %d",arrayint2D[0][1]);

    return 0;
}

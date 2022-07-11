#include "functions.c"
#include <stdio.h>
#include <stdlib.h>
#include "dataType.h"


int main() {


    int n;

    printf("***********************************\n");
    printf("*                                 *\n");
    printf("*        BOOK REPOSITORY          *\n");
    printf("*                                 *\n");
    printf("***********************************\n");

    do {
        printf("\n1) Add book \n");
        printf("2) Print all books \n");
        printf("3) Delete book \n");
        printf("4) Print author \n");
        printf("5) Print genre \n");
        printf("6) Book search \n");
        printf("7) Delete repository \n");
        printf("8) Search \n");
        printf("9) Save changes & Exit \n");

        do {
            printf("\nEnter number: ");
            scanf("%d", &n);
            getchar();
        } while (n < 1 || n>9);

        switchCase(n);

    } while (n != 9);

    return 0;
}


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"
#include <conio.h>
#include "dataType.h"

void switchCase(int n) {

    switch (n) {

    case 1:
        system("cls");
        addBook();
        break;

    case 2:
        system("cls");
        printBooks();
        break;

    case 3:
        system("cls");
        deleteBook();
        break;

    case 4:
        system("cls");
        authorPrint();
        break;

    case 5:
        system("cls");
        genrePrint();
        break;

    case 6:
        system("cls");
        bookSearch();
        break;

    case 7:
        system("cls");
        deleteFile();
        break;

    case 8:
        system("cls");
        searchInRepository();
        break;

    case 9:
        system("cls");
        exitProgram();
        break;
    }
}

void addBook() {
    FILE* fp = NULL;
    int n;
    BOOK* nBook = (BOOK*)malloc(sizeof(BOOK));
    if (nBook == NULL) {
        printf("Error");
        return 1;
    }

    printf("Enter name of author: ");
    scanf(" %29[^\n]", nBook->author);
    printf("Enter name of book: ");
    scanf(" %29[^\n]", nBook->book);
    printf("Enter name of genre: ");
    scanf(" %29[^\n]", nBook->genre);
    printf("Enter year: ");
    scanf(" %29[^\n]", nBook->year);


    fp = fopen("book.bin", "rb");
    if (fp == NULL) {
        fp = fopen("book.bin", "wb");
        n = 1;
        fwrite(&n, sizeof(int), 1, fp);
        fwrite(nBook, sizeof(BOOK), 1, fp);
        fclose(fp);
    }
    else {
        fclose(fp);
        fp = fopen("book.bin", "rb+");
        if (fp == NULL) {
            printf("Error");
        }
        else {
            fseek(fp, 0, SEEK_SET);
            fread(&n, sizeof(int), 1, fp);
            n++;
            fseek(fp, 0, SEEK_SET);
            fwrite(&n, sizeof(int), 1, fp);
            fseek(fp, 0, SEEK_END);
            fwrite(nBook, sizeof(BOOK), 1, fp);
            fclose(fp);
        }
    }


    fclose(fp);
    free(nBook);
    system("cls");

    return;
}



void authorPrint() {
    char author[30];
    int n, i, flag = 0, index = 0;

    FILE* fp = fopen("book.bin", "rb");
    if (fp == NULL) {
        printf("Repository is empty, might try option 1!");
        getch();
        system("cls");
        return;
    }

    fread(&n, sizeof(int), 1, fp);

    BOOK* sBook = (BOOK*)malloc(n * sizeof(BOOK));

    if (sBook == NULL) {
        printf("Error");
        return 1;
    }

    printf("Enter author's name: ");
    scanf(" %29[^\n]", author);
    printf("\n");
    fread(sBook, sizeof(BOOK), n, fp);
    for (int i = 0; i < n; i++) {
        if (strcmp((sBook + i)->author, author) == 0) {
            index++;
            if (index == 1) {
                printf("*Available %s books*\n", author);
            }
            printf("\nBook: %s", (sBook + i)->book);
            printf("\nGenre: %s", (sBook + i)->genre);
            printf("\nYear: %s\n", (sBook + i)->year);
            flag = 1;

        }
    }
    if (flag == 0) {
        printf("%s's books are not available in repository!", author);
    }
    fclose(fp);
    free(sBook);
    getch();
    system("cls");
}

void genrePrint() {
    char genre[30];
    int n, i, flag = 0, index = 0;

    FILE* fp = fopen("book.bin", "rb");
    if (fp == NULL) {
        printf("Repository is empty, might try option 1!");
        getch();
        system("cls");
        return;
    }

    fread(&n, sizeof(int), 1, fp);

    BOOK* sBook = (BOOK*)malloc(n * sizeof(BOOK));
    if (sBook == NULL) {
        printf("Error");
        return 1;
    }
    printf("Enter genre name: ");
    scanf(" %29[^\n]", genre);
    printf("\n");
    fread(sBook, sizeof(BOOK), n, fp);
    alphabeticalSort(sBook, n);

    for (int i = 0; i < n; i++) {
        if (strcmp((sBook + i)->genre, genre) == 0) {
            index++;
            if (index == 1) {
                printf("*Available %s books*\n", genre);
            }
            printf("\nAuthor: %s", (sBook + i)->author);
            printf("\nBook: %s", (sBook + i)->book);
            printf("\nYear: %s\n", (sBook + i)->year);
            flag = 1;

        }
    }
    if (flag == 0) {
        printf("%s's books are not available in repository!", genre);
    }
    fclose(fp);
    free(sBook);
    getch();
    system("cls");
}

void printBooks() {
    int n, i;
    FILE* fp = NULL;
    BOOK* pBook = NULL;
    fp = fopen("book.bin", "rb");
    if (fp == NULL) {
        printf("Repository is empty, might try option 1");
        getch();
        system("cls");
        return;
    }
    fread(&n, sizeof(int), 1, fp);
    if (n == 0) {
        printf("Repository is empty,might try option 1.\n\n");
        getch();
        system("cls");
        return;
    }
    pBook = (BOOK*)malloc(n * sizeof(BOOK));
    if (pBook == NULL) {
        printf("Error");
        return 1;
    }
    fread(pBook, sizeof(BOOK), n, fp);

    alphabeticalSort(pBook, n);


    printf("*You have %d books in repository*", n);

    for (i = 0; i < n; i++) {
        printf("\n\nAuthor:%s", (pBook + i)->author);
        printf("\nBook:%s", (pBook + i)->book);
        printf("\nGenre:%s", (pBook + i)->genre);
        printf("\nYear:%s", (pBook + i)->year);
    }
    fclose(fp);
    free(pBook);
    getch();
    system("cls");

    return;
}

void alphabeticalSort(BOOK* pBook, int n) {
    int k, j, i;
    BOOK* temp = (BOOK*)malloc(n * sizeof(BOOK));


    for (i = 0; i < n; ++i) {
        for (j = i + 1; j < n; j++) {
            if (strcmp(pBook[i].author, pBook[j].author) > 0) {
                strcpy(temp, pBook[i].author);
                strcpy(pBook[i].author, pBook[j].author);
                strcpy(pBook[j].author, temp);

                strcpy(temp, pBook[i].book);
                strcpy(pBook[i].book, pBook[j].book);
                strcpy(pBook[j].book, temp);

                strcpy(temp, pBook[i].genre);
                strcpy(pBook[i].genre, pBook[j].genre);
                strcpy(pBook[j].genre, temp);

                strcpy(temp, pBook[i].year);
                strcpy(pBook[i].year, pBook[j].year);
                strcpy(pBook[j].year, temp);
            }
        }
    }
    free(temp);

}

void bookSearch() {
    char searchedWord[30];
    int n, i, flag = 0;
    FILE* fp = fopen("book.bin", "rb");
    if (fp == NULL) {
        printf("Repository is empty, might try option 1!");
        getch();
        system("cls");
        return;

    }

    fread(&n, sizeof(int), 1, fp);

    BOOK* sBook = (BOOK*)malloc(n * sizeof(BOOK));
    if (sBook == NULL) {
        printf("Error");
        return 1;
    }
    printf("Enter book name: ");
    scanf(" %29[^\n]", searchedWord);
    fread(sBook, sizeof(BOOK), n, fp);

    for (int i = 0; i < n; i++) {
        if (strcmp((sBook + i)->book, searchedWord) == 0) {
            printf("\nAuthor %s", (sBook + i)->author);
            printf("\nBook: %s", (sBook + i)->book);
            printf("\nGenre: %s", (sBook + i)->genre);
            printf("\nYear: %s\n\n", (sBook + i)->year);
            flag = 1;
            printf("Book is available!\n");
        }
    }


    if (flag == 0) {
        printf("Searched book doesn't exist in repository!");
    }
    fclose(fp);
    free(sBook);
    getch();
    system("cls");

}

void deleteBook() {
    BOOK* dBook = NULL;
    int n, index, flag = 0;
    char s[30];
    FILE* fp = fopen("book.bin", "rb");
    if (fp == NULL) {
        printf("Repository is empty, might try option 1!");
        getch();
        system("cls");
        return;
    }
    else {
        fread(&n, sizeof(int), 1, fp);
        dBook = (BOOK*)malloc(n * sizeof(BOOK));
        if (dBook == NULL) {
            printf("Error");
            return 1;
        }
        else {
            fread(dBook, sizeof(BOOK), n, fp);
            fclose(fp);
            system("cls");
            printf("Enter name of book to be deleted: ");
            scanf(" %29[^\n]", s);
            for (int i = 0; i < n; i++) {
                if (strcmp((dBook + i)->book, s) == 0) {
                    index = i;
                    flag = 1;
                    break;
                }
            }
            if (flag == 0) {
                printf("\nBook is not available ");
            }
            else {
                fclose(fp);
                fp = fopen("book.bin", "wb");
                if (fp == NULL) {
                    perror("Error");
                    exit(EXIT_FAILURE);
                }
                else {
                    n--;
                    fwrite(&n, sizeof(int), 1, fp);
                    for (int i = 0; i < n + 1; i++) {
                        if (i == index) {
                            continue;
                        }
                        else {
                            fwrite((dBook + i), sizeof(BOOK), 1, fp);
                        }
                    }
                    printf("\nBook is deleted\n");
                    fclose(fp);
                    free(dBook);
                }
            }
        }
    }
}

void searchInRepository() {

    char searchedWord[30];
    int n, i, flag = 0;

    FILE* fp = fopen("book.bin", "rb");
    if (fp == NULL) {
        printf("Repository is empty, might try option 1");
        getch();
        system("cls");
        return;
    }

    fread(&n, sizeof(int), 1, fp);

    BOOK* sBook = (BOOK*)malloc(n * sizeof(BOOK));
    if (sBook == NULL) {
        printf("Error");
        return 1;
    }
    printf("Enter searched word: ");
    scanf(" %29[^\n]", searchedWord);
    fread(sBook, sizeof(BOOK), n, fp);
    alphabeticalSort(sBook, n);
    for (int i = 0; i < n; i++) {
        if (strcmp((sBook + i)->author, searchedWord) == 0) {
            printf("\nAuthor %s", (sBook + i)->author);
            printf("\nBook: %s", (sBook + i)->book);
            printf("\nGenre: %s", (sBook + i)->genre);
            printf("\nYear: %s\n", (sBook + i)->year);
            flag = 1;

        }
        else if (strcmp((sBook + i)->book, searchedWord) == 0) {
            printf("\nAuthor  %s", (sBook + i)->author);
            printf("\nBook: %s", (sBook + i)->book);
            printf("\nGenre: %s", (sBook + i)->genre);
            printf("\nYear: %s\n", (sBook + i)->year);
            flag = 1;

        }
        else if (strcmp((sBook + i)->genre, searchedWord) == 0) {
            printf("\nAuthor %s", (sBook + i)->author);
            printf("\nBook: %s", (sBook + i)->book);
            printf("\nGenre: %s", (sBook + i)->genre);
            printf("\nYear: %s\n", (sBook + i)->year);
            flag = 1;

        }
        else if (strcmp((sBook + i)->year, searchedWord) == 0) {
            printf("\nAuthor %s", (sBook + i)->author);
            printf("\nBook: %s", (sBook + i)->book);
            printf("\nGenre: %s", (sBook + i)->genre);
            printf("\nYear: %s\n", (sBook + i)->year);
            flag = 1;
        }
    }
    if (flag == 0) {
        printf("Searched word doesn't exist in repository!");
    }

    fclose(fp);
    free(sBook);
    getch();
    system("cls");
}

void exitProgram() {
    char verification;
    printf("\nAre you sure you want to end the program ?(Y/N): ");


    while (1) {
        scanf("%c", &verification);
        if ((verification == 'Y') || (verification == 'N')) {
            break;
        }
        printf("Wrong entry,try->Y/N: ");
        scanf("%c", &verification);
    }

    if (verification == 'Y') {
        exit(0);
    }

    else if (verification == 'N') {
        int n;

        do {
            system("cls");

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
    }

}

void deleteFile() {

    printf("Do you really want to delete repository?\n");
    printf("Enter Y/N: ");
    int x;
    char verification;
    char filename[] = "book.bin";

    while (1) {
        scanf("%c", &verification);
        if ((verification == 'Y') || (verification == 'N')) {
            break;
        }
        printf("Wrong entry,try->Y/N: ");
        scanf("%c", &verification);
    }
    if ('Y' == verification) {
        x = remove(filename);
        if (x == 0) {
            printf("Successfully deleted repository");
            getch();
            system("cls");
            return;
        }
        else {
            printf("Failed to delete repository");
            getch();
            system("cls");
            return;
        }
    }
    if ('N' == verification) {
        system("cls");
        return;
    }
}

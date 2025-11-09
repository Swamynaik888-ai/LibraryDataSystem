//This Is a Library Management  System Project Using C Language That uses Structures,File Handlings,Functions,Switch Casec To Perform various Operations::

// The System Allows Librarians or Users TO MAnage Books Like As--Add,Search,Delete,Display Books Store Available In Library..


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Book {          //using structure...to access an id,title,author,price,isiss
    int id;
    char title[50];
    char author[50];
    float price;
    int isIssued;  


} ;

// function declaration ::
void addBook();
void displayBooks();
void searchBook();
void deleteBook();
void issueBook();
void returnBook();



//Adding books from an ID  With (2201--------------2250)
void addBook() {
    struct Book b;
    FILE *fp = fopen("andros.txt", "ab");

    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    printf("\nEnter Book ID: ");
    scanf("%d", &b.id);
    getchar(); 
    printf("Enter Book Title: ");
    gets(b.title);
    printf("Enter Author Name: ");
    gets(b.author);
    printf("Enter Book Price: ");
    scanf("%f", &b.price);

    b.isIssued = 0;

    fwrite(&b, sizeof(b), 1, fp);
    fclose(fp);

    printf(" Book added successfully  \n");
}


void displayBooks() {
    struct Book b;
    FILE *fp = fopen("andros.txt", "rb");

    if (fp == NULL) {
        printf("No data found!\n");
        return;
    }

    printf("\n--------------------------------------------------------------------------------------------------------\n");
    printf("%-5s %-20s \t  %-20s  %-10s  %-10s\n", "ID", "Title ",      "   Author",  " Price", " Status");
    
    while (fread(&b, sizeof(b), 1, fp)) {
        printf("%-5d %-20s \t  %-20s  %-10.2f   %-10s\n",
               b.id, b.title, b.author, b.price,
               (b.isIssued == 1 ? "Issued" : "Available"));
    }

    fclose(fp);
}

void searchBook() {
    struct Book hello;
    FILE *fp = fopen("andros.txt", "rb");
    int id, found = 0;

    if (fp == NULL) {
        printf("No data found!\n");
        return;
    }

    printf("\nEnter Book ID to search: ");
    scanf("%d", &id);

    while (fread(&hello, sizeof(hello), 1, fp)) {
        if (hello.id == id) {
            printf("\nBook Found:\n");
            printf("ID: %d\nTitle: %s\nAuthor: %s\nPrice: %.2f\nStatus: %s\n",
                   hello.id, hello.title, hello.author, hello.price,
                   (hello.isIssued ? "Issued" : "Available"));
            found = 1;
            break;
        }
    }

    if (!found)
        printf("Book not found!\n");

    fclose(fp);
}

//
// Delete book by ID
void deleteBook() {
    struct Book b;
    FILE *fp, *temp;
    int id, found = 0;

    fp = fopen("andros.txt", "rb");
    if (fp == NULL) {
        printf("No data found!\n");
        return;
    }

    temp = fopen("temp.dat", "wb");
    printf("\nEnter Book ID to delete: ");
    scanf("%d", &id);

    while (fread(&b, sizeof(b), 1, fp)) {
        if (b.id != id)
            fwrite(&b, sizeof(b), 1, temp);
        else
            found = 1;
    }

    fclose(fp);
    fclose(temp);

    remove("andros.txt");
    rename("temp.dat", "andros.txt");

    if (found)
        printf("Book deleted successfully!\n");
    else
        printf("Book not found!\n");
}



void issueBook() {
    struct Book hello;
    FILE *fp = fopen("andros.txt", "rb+");
    int id, found = 0;

    if (fp == NULL) {
        printf("No data found!\n");
        return;
    }

    printf("\nEnter Book ID to issue: ");
    scanf("%d", &id);

    while (fread(&hello, sizeof(hello), 1, fp)) {
        if (hello.id == id) {
            found = 1;
            if (hello.isIssued == 1) {
                printf(" Book already issued!\n");
            } else {
                hello.isIssued = 1;
                fseek(fp, -sizeof(hello), SEEK_CUR);
                fwrite(&hello, sizeof(hello), 1, fp);
                printf(" Book Isissued Successfully \n");
            }
            break;
        }
    }

    if (!found)
        printf(" Book Not Found\n");

    fclose(fp);
}


void returnBook() {
    struct Book hello;
    FILE *fp = fopen("andros.txt", "rb+");
    int id, found = 0;

    if (fp == NULL) {
        printf("No data found!\n");
        return;
    }

    printf("\nEnter Book ID to return: ");
    scanf("%d", &id);

    while (fread(&hello, sizeof(hello), 1, fp)) {
        if (hello.id == id) {
            found = 1;
            if (hello.isIssued == 0) {
                printf(" Book is not issued!\n");
            } else {
                hello.isIssued = 0;
                fseek(fp, -sizeof(hello), SEEK_CUR);
                fwrite(&hello, sizeof(hello), 1, fp);
                printf("Book returned successfully!\n");
            }
            break;
        }
    }

    if (!found)
        printf(" Book not found!\n");

    fclose(fp);
}






//Displaying The  Options :
int main() {
    int choice;

    while (1) {
        printf("\n****** LIBRARY MANAGEMENT SYSTEM  ****** \n");
        printf("1. Add Book\n");
        printf("2. Display All Books\n");
        printf("3. Search Book by ID\n");
        printf("4. Delete Book by ID\n");
        printf("5. Issue Book\n");
        printf("6. Return Book\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

/// Using Switch case::
        switch (choice) {
            case 1:  
            addBook(); 
            break;
            case 2: 
            displayBooks(); 
            break;
            case 3:  
            searchBook();
             break;
            case 4: 
            deleteBook(); 
            break;
            case 5: 
            issueBook(); 
            break;
            case 6: 
             returnBook(); break;
            case 7:
                printf("Exit......\n");
                exit(0);
            default:
                printf("Enter Valid  Data \n");
        }
    }

    return 0;
}


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "menu.h"
#include "contacts.h"

void display_menu() {
    printf("*********** MENU ***********\n");
    printf("1. Display contacts\n");
    printf("2. Add contact\n");
    printf("3. Edit contact\n");
    printf("4. Delete contact\n");
    printf("5. Exit\n");
    printf("****************************\n");
    printf("Enter your choice: ");
}

void add_contact_from_user(Contacts **head) {
    char name[30], last_name[30], phone_number[11];
    char street[30], nr[5], post_code[6], town[30];

    getchar();
    printf("Enter name: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0';

    printf("Enter last name: ");
    fgets(last_name, sizeof(last_name), stdin);
    last_name[strcspn(last_name, "\n")] = '\0';

    printf("Enter phone number: ");
    fgets(phone_number, sizeof(phone_number), stdin);
    phone_number[strcspn(phone_number, "\n")] = '\0';

    printf("Enter street: ");
    fgets(street, sizeof(street), stdin);
    street[strcspn(street, "\n")] = '\0';

    printf("Enter house number: ");
    fgets(nr, sizeof(nr), stdin);
    nr[strcspn(nr, "\n")] = '\0';

    printf("Enter post code: ");
    fgets(post_code, sizeof(post_code), stdin);
    post_code[strcspn(post_code, "\n")] = '\0';
    
    printf("Enter town: ");
    fgets(town, sizeof(town), stdin);
    town[strcspn(town, "\n")] = '\0';

    printf("%s %s %s %s %s %s %s\n", name, last_name, phone_number, street, nr, post_code, town);

    add_contact(head, name, last_name, phone_number, street, nr, post_code, town);
    printf("Contact added successfully.\n");
}

void edit_contact_from_user(Contacts *head) {
    Contacts *current = head;
    int id;
    char name[30], last_name[30], phone_number[11];
    char street[30], nr[5], post_code[6], town[30];

    printf("Enter ID of contact to edit: ");
    scanf("%d", &id);
    getchar();

    while (current != NULL) {
        if (current->id == id) {
            // Znaleziono kontakt o podanym ID, aktualizacja danych
            printf("Enter new name: ");
            fgets(name, sizeof(name), stdin);
            name[strcspn(name, "\n")] = '\0';
            strcpy(current->name, name);

            printf("Enter new last name: ");
            fgets(last_name, sizeof(last_name), stdin);
            last_name[strcspn(last_name, "\n")] = '\0';
            strcpy(current->last_name, last_name);

            printf("Enter new phone number: ");
            fgets(phone_number, sizeof(phone_number), stdin);
            phone_number[strcspn(phone_number, "\n")] = '\0';
            strcpy(current->phone_number, phone_number);

            printf("Enter new street: ");
            fgets(street, sizeof(street), stdin);
            street[strcspn(street, "\n")] = '\0';
            strcpy(current->address.street, street);

            printf("Enter new house number: ");
            fgets(nr, sizeof(nr), stdin);
            nr[strcspn(nr, "\n")] = '\0';
            strcpy(current->address.nr, nr);

            printf("Enter new post code: ");
            fgets(post_code, sizeof(post_code), stdin);
            post_code[strcspn(post_code, "\n")] = '\0';
            strcpy(current->address.post_code, post_code);

            printf("Enter new town: ");
            fgets(town, sizeof(town), stdin);
            town[strcspn(town, "\n")] = '\0';

            save_contacts_to_file(head, "contacts.csv");
            printf("Contact edited successfully.\n");
            return;
        }
        current = current->next;
    }

    // Nie znaleziono kontaktu o podanym ID
    printf("Contact with ID %d not found.\n", id);

}

void delete_contact_from_user(Contacts **head) {
    int id;
    printf("Enter ID of contact to delete: ");
    scanf("%d", &id);

    Contacts *current = *head;
    Contacts *prev = NULL;

    // Przeszukiwanie listy w poszukiwaniu kontaktu o podanym indeksie
    while (current != NULL && current->id != id) {
        prev = current;
        current = current->next;
    }

    // Je�li kontakt o podanym indeksie zosta� znaleziony
    if (current != NULL) {
        // Je�li kontakt jest na pocz�tku listy
        if (prev == NULL) {
            *head = current->next;
        } else {
            prev->next = current->next;
        }
        free(current);
        printf("Contact deleted successfully.\n");
    } else {
        printf("Contact with ID %d not found.\n", id);
    }
}

void execute_option(Contacts **head, int option) {
    switch(option) {
        case 1:
            display_list(*head);
            break;
        case 2:
            add_contact_from_user(head);
            break;
        case 3:
            edit_contact_from_user(*head);
            break;
        case 4:
            delete_contact_from_user(head);
            break;
        case 5:
            printf("Exiting program.\n");
            break;
        default:
            printf("Invalid option.\n");
    }
}
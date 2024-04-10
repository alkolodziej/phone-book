#include <stdio.h>
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
    char name[50], last_name[50], phone_number[11];
    char street[30], nr[5], post_code[6], town[30];

    printf("Enter name: ");
    scanf("%s", name);
    printf("Enter last name: ");
    scanf("%s", last_name);
    printf("Enter phone number: ");
    scanf("%s", phone_number);
    printf("Enter street: ");
    scanf("%s", street);
    printf("Enter house number: ");
    scanf("%s", nr);
    printf("Enter post code: ");
    scanf("%s", post_code);
    printf("Enter town: ");
    scanf("%s", town);
    printf("%s %s %s %s %s %s %s\n", name, last_name, phone_number, street, nr, post_code, town);

    add_contact(head, name, last_name, phone_number, street, nr, post_code, town);
    printf("Contact added successfully.\n");
}

void edit_contact_from_user(Contacts *head) {
    int id;
    char name[50], last_name[50], phone_number[11];
    char street[30], nr[5], post_code[6], town[30];

    printf("Enter ID of contact to edit: ");
    scanf("%d", &id);

    printf("Enter new name: ");
    scanf("%s", name);
    printf("Enter new last name: ");
    scanf("%s", last_name);
    printf("Enter new phone number: ");
    scanf("%s", phone_number);
    printf("Enter new street: ");
    scanf("%s", street);
    printf("Enter new house number: ");
    scanf("%s", nr);
    printf("Enter new post code: ");
    scanf("%s", post_code);
    printf("Enter new town: ");
    scanf("%s", town);
    edit_contact(head, id, name, last_name, phone_number, street, nr, post_code, town);
    printf("Contact edited successfully.\n");
}

void delete_contact_from_user(Contacts **head) {
    int id;
    printf("Enter ID of contact to delete: ");
    scanf("%d", &id);
    delete_contact(head, id);
    printf("Contact deleted successfully.\n");
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
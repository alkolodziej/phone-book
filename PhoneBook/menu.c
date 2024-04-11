#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "menu.h"
#include "contacts.h"
#include "colors.h"

#ifdef _WIN32
#define CLEAR_SCREEN "cls"
#else
#define CLEAR_SCREEN "clear"
#endif



void clear_screen() {
    system(CLEAR_SCREEN);
}

int get_user_choice() {
    int choice;
    printf(COLOR_BOLD "Enter your choice: " COLOR_RESET);
    scanf("%d", &choice);
    getchar();
    return choice;
}

void display_menu() {
    printf(COLOR_BOLD "*********** MENU ***********\n" COLOR_RESET);
    printf(COLOR_YELLOW "1. Display contacts\n");
    printf("2. Add contact\n");
    printf("3. Edit contact\n");
    printf("4. Delete contact\n");
    printf(COLOR_BLUE "5. Exit\n" COLOR_RESET);
    printf(COLOR_BOLD "****************************\n" COLOR_RESET);
}

void get_line(char *line, long long unsigned length)
{
    fgets(line, sizeof(line), stdin);
    line[strcspn(line, "\n")] = '\0';
    if (strlen(line) > length) {
                // Ignoruj dodatkowe znaki w buforze wejściowym (czyści bufor)
                // Bez tego znaki w buforze wejściowym mogą wpłynąć na kolejne wczytywanie danych
                // https://stackoverflow.com/posts/28576329/revisions
                // Można teoretycznie do każdego fgets dodać takie coś
                int ch;
                while ((ch = getchar()) != '\n' && ch != EOF);
            }
}

void add_contact_from_user(Contacts **head) {
    char name[30], last_name[30], phone_number[11];
    char street[30], nr[5], post_code[8], town[30];

    printf(COLOR_BOLD "Adding new contact\n\n" COLOR_RESET);

    // getchar();
    // Imię
    printf(COLOR_BOLD "Enter name: " COLOR_RESET);
    get_line(name, 30);

    // Nazwisko
    printf(COLOR_BOLD "Enter last name: " COLOR_RESET);
    get_line(last_name, 30);

    // Numer telefonu
    printf(COLOR_BOLD "Enter phone number: " COLOR_RESET);
    get_line(phone_number, 10);

    // Ulica
    printf(COLOR_BOLD "Enter street: " COLOR_RESET);
    get_line(street, 30);

    // Numer domu
    printf(COLOR_BOLD "Enter house number: " COLOR_RESET);
    get_line(nr, 5);

    // Kod pocztowy
    printf(COLOR_BOLD "Enter post code: " COLOR_RESET);
    get_line(post_code, 6);
    
    // Miasto
    printf(COLOR_BOLD "Enter town: " COLOR_RESET);
    get_line(town, 30);

    // getchar();

    printf("%s %s \t %s \t %s %s \t %s %s\n", name, last_name, phone_number, street, nr, post_code, town);

    add_contact(head, name, last_name, phone_number, street, nr, post_code, town);
    printf(COLOR_GREEN "Contact added successfully.\n" COLOR_RESET);
}

void edit_contact_from_user(Contacts *head) {
    Contacts *current = head;
    int id;
    char name[30], last_name[30], phone_number[11];
    char street[30], nr[5], post_code[8], town[30];

    printf(COLOR_BOLD "Enter ID of contact to edit: " COLOR_RESET);
    scanf("%d", &id);
    getchar();

    while (current != NULL) {
        if (current->id == id) {
            // Znaleziono kontakt o podanym ID, aktualizacja danych

            // Imię
            printf(COLOR_YELLOW "Current name: %s\n" COLOR_RESET, current->name);
            printf(COLOR_BOLD "Enter new name (leave blank to keep current): " COLOR_RESET);
            get_line(name, 30);

            // Nazwisko
            printf(COLOR_YELLOW "Current last name: %s\n" COLOR_RESET, current->last_name);
            printf(COLOR_BOLD "Enter new last name (leave blank to keep current): " COLOR_RESET);
            get_line(last_name, 30);

            // Numer telefonu
            printf(COLOR_YELLOW "Current phone number: %s\n" COLOR_RESET, current->phone_number);
            printf(COLOR_BOLD "Enter new phone number (leave blank to keep current): " COLOR_RESET);
            get_line(phone_number, 10);

            // Ulica
            printf(COLOR_YELLOW "Current street: %s\n" COLOR_RESET, current->address.street);
            printf(COLOR_BOLD "Enter new street (leave blank to keep current): " COLOR_RESET);
            get_line(street, 30);

            // Numer domu
            printf(COLOR_YELLOW "Current house number: %s\n" COLOR_RESET, current->address.nr);
            printf(COLOR_BOLD "Enter new house number (leave blank to keep current): " COLOR_RESET);
            get_line(nr, 5);

            // Kod pocztowy
            printf(COLOR_YELLOW "Current post code: %s\n" COLOR_RESET, current->address.post_code);
            printf(COLOR_BOLD "Enter new post code (leave blank to keep current): " COLOR_RESET);
            get_line(post_code, 6);

            // Miasto
            printf(COLOR_YELLOW "Current town: %s\n" COLOR_RESET, current->address.town);
            printf(COLOR_BOLD "Enter new town (leave blank to keep current): " COLOR_RESET);
            get_line(town, 30);

            // Aktualizacja danych, jeśli zostały wprowadzone
            if (strlen(name) > 0) {
                strcpy(current->name, name);
            }
            if (strlen(last_name) > 0) {
                strcpy(current->last_name, last_name);
            }
            if (strlen(phone_number) > 0) {
                strcpy(current->phone_number, phone_number);
            }
            if (strlen(street) > 0) {
                strcpy(current->address.street, street);
            }
            if (strlen(nr) > 0) {
                strcpy(current->address.nr, nr);
            }
            if (strlen(post_code) > 0) {
                strcpy(current->address.post_code, post_code);
            }
            if (strlen(town) > 0) {
                strcpy(current->address.town, town);
            }

            //save_contacts_to_file(head, "contacts.csv");
            printf(COLOR_GREEN "Contact edited successfully.\n" COLOR_RESET);
            return;
        }
        current = current->next;
    }

    // Nie znaleziono kontaktu o podanym ID
    printf(COLOR_BLUE "Contact with ID %d not found.\n" COLOR_RESET, id);

}

void delete_contact_from_user(Contacts **head) {
    int id;
    printf(COLOR_BOLD "Enter ID of contact to delete: " COLOR_RESET);
    scanf("%d", &id);

    Contacts *current = *head;
    Contacts *prev = NULL;

    // Przeszukiwanie listy w poszukiwaniu kontaktu o podanym indeksie
    while (current != NULL && current->id != id) {
        prev = current;
        current = current->next;
    }

    // Jesli kontakt o podanym indeksie zostal znaleziony
    if (current != NULL) {
        // Jesli kontakt jest na poczatku listy
        if (prev == NULL) {
            *head = current->next;
        } else {
            prev->next = current->next;
        }
        free(current);
        printf(COLOR_GREEN "Contact deleted successfully.\n" COLOR_RESET);
    } else {
        printf(COLOR_BLUE "Contact with ID %d not found.\n" COLOR_RESET, id);
    }
    getchar();
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
            printf(COLOR_BOLD "Exiting program.\n" COLOR_RESET);
            exit(0);
            break;
        default:
            printf(COLOR_RED "Invalid option.\n" COLOR_RESET);
    }
}
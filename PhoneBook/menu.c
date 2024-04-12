#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "menu.h"
#include "contacts.h"
#include "colors.h"

// Definicja makra do czyszczenia ekranu w zależności od systemu operacyjnego
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
    printf("5. Search contact\n");
    printf(COLOR_BLUE "0. Exit\n" COLOR_RESET);
    printf(COLOR_BOLD "****************************\n" COLOR_RESET);
}

void get_line(char *line, size_t size) {
    fgets(line, (int)size, stdin);
    line[strcspn(line, "\n")] = '\0'; // Usunięcie znaku nowej linii

    // Sprawdzenie, czy długość wczytanej linii jest równa maksymalnemu rozmiarowi tablicy
    if (strlen(line) == size - 1) {
        // Czyszczenie bufora wejściowego
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF);
    }
}

void add_contact_from_user(Contacts **head) {
    char name[30], last_name[30], phone_number[10];
    char street[30], nr[6], post_code[7], town[30];
    Contacts *new_contact = (Contacts*)malloc(sizeof(Contacts));
    if (new_contact == NULL) {
        fprintf(stderr, COLOR_RED "Memory allocation failed\n" COLOR_RESET);
        exit(EXIT_FAILURE);
    }
    new_contact->next = NULL;

    printf(COLOR_BOLD "Adding new contact\n\n" COLOR_RESET);

    // getchar();
    // Imię
    printf(COLOR_BOLD "Enter name: " COLOR_RESET);
    get_line(name, sizeof(name));
    strcpy(new_contact->name, name);

    // Nazwisko
    printf(COLOR_BOLD "Enter last name: " COLOR_RESET);
    get_line(last_name, sizeof(last_name));
    strcpy(new_contact->last_name, last_name);

    // Numer telefonu
    printf(COLOR_BOLD "Enter phone number: " COLOR_RESET);
    get_line(phone_number, sizeof(phone_number));
    strcpy(new_contact->phone_number, phone_number);

    // Ulica
    printf(COLOR_BOLD "Enter street: " COLOR_RESET);
    get_line(street, sizeof(street));
    strcpy(new_contact->address.street, street);

    // Numer domu
    printf(COLOR_BOLD "Enter house number: " COLOR_RESET);
    get_line(nr, sizeof(nr));
    strcpy(new_contact->address.nr, nr);

    // Kod pocztowy
    printf(COLOR_BOLD "Enter post code: " COLOR_RESET);
    get_line(post_code, sizeof(post_code));
    strcpy(new_contact->address.post_code, post_code);
    
    // Miasto
    printf(COLOR_BOLD "Enter town: " COLOR_RESET);
    get_line(town, sizeof(town));
    strcpy(new_contact->address.town, town);

    
    // printf("\n%s %s \t %s \t %s %s \t %s %s\n", name, last_name, phone_number, street, nr, post_code, town);

    if (*head == NULL) {
        new_contact->id = 1; // Nadanie unikalnego ID dla pierwszego kontaktu
        *head = new_contact;
    } else {
        // W przeciwnym razie znajdź ostatni element listy i ustaw jego wskaźnik na następny na nowy kontakt
        Contacts *current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        new_contact->id = current->id + 1; // Nadanie unikalnego ID
        current->next = new_contact;
    }
    
    printf(COLOR_GREEN "Contact added successfully.\n" COLOR_RESET);
}

void check_to_change(char *first, char *second)
{
    if (strlen(second) > 0) {
        strcpy(first, second);
    }
}

void edit_contact_from_user(Contacts *head) {
    if(NULL != head){
        Contacts *current = head;
        int id;
        char name[30], last_name[30], phone_number[10];
        char street[30], nr[6], post_code[7], town[30];

        printf(COLOR_BOLD "Enter ID of contact to edit: " COLOR_RESET);
        scanf("%d", &id);
        getchar();

        while (current != NULL) {
                if (current->id == id) {
                // Znaleziono kontakt o podanym ID, aktualizacja danych

                // Imię
                printf(COLOR_YELLOW "Current name: %s\n" COLOR_RESET, current->name);
                printf(COLOR_BOLD "Enter new name (leave blank to keep current): " COLOR_RESET);
                get_line(name, sizeof(name));

                // Nazwisko
                printf(COLOR_YELLOW "Current last name: %s\n" COLOR_RESET, current->last_name);
                printf(COLOR_BOLD "Enter new last name (leave blank to keep current): " COLOR_RESET);
                get_line(last_name, sizeof(last_name));

                // Numer telefonu
                printf(COLOR_YELLOW "Current phone number: %s\n" COLOR_RESET, current->phone_number);
                printf(COLOR_BOLD "Enter new phone number (leave blank to keep current): " COLOR_RESET);
                get_line(phone_number, sizeof(phone_number));

                // Ulica
                printf(COLOR_YELLOW "Current street: %s\n" COLOR_RESET, current->address.street);
                printf(COLOR_BOLD "Enter new street (leave blank to keep current): " COLOR_RESET);
                get_line(street, sizeof(street));

                // Numer domu
                printf(COLOR_YELLOW "Current house number: %s\n" COLOR_RESET, current->address.nr);
                printf(COLOR_BOLD "Enter new house number (leave blank to keep current): " COLOR_RESET);
                get_line(nr, sizeof(nr));

                // Kod pocztowy
                printf(COLOR_YELLOW "Current post code: %s\n" COLOR_RESET, current->address.post_code);
                printf(COLOR_BOLD "Enter new post code (leave blank to keep current): " COLOR_RESET);
                get_line(post_code, sizeof(post_code));

                // Miasto
                printf(COLOR_YELLOW "Current town: %s\n" COLOR_RESET, current->address.town);
                printf(COLOR_BOLD "Enter new town (leave blank to keep current): " COLOR_RESET);
                get_line(town, sizeof(town));

                // Aktualizacja danych, jeśli zostały wprowadzone
                check_to_change(current->name, name);
                check_to_change(current->last_name, last_name);
                check_to_change(current->phone_number, phone_number);
                check_to_change(current->address.street, street);
                check_to_change(current->address.nr, nr);
                check_to_change(current->address.post_code, post_code);
                check_to_change(current->address.town, town);

                //save_contacts_to_file(head, "contacts.csv");
                printf(COLOR_GREEN "Contact edited successfully.\n" COLOR_RESET);
                return;
            }
            current = current->next;
        }

        // Nie znaleziono kontaktu o podanym ID
        printf(COLOR_BLUE "Contact with ID %d not found.\n" COLOR_RESET, id);  
    }   else
        // Lista jest pusta
        printf(COLOR_BLUE "List is empty.\n" COLOR_RESET);

}

void delete_contact_from_user(Contacts **head) {
    if(NULL != *head){
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
    } else
        // Lista jest pusta
        printf(COLOR_BLUE "List is empty.\n" COLOR_RESET);
}

void print_contact(const Contacts *contact) {
    printf("| %-*d| %-*s| %-*s| %-*s| %-*s| %-*s| %-*s| %-*s|\n",
               COLUMN_WIDTH_ID, contact->id, COLUMN_WIDTH_NAME, contact->name, COLUMN_WIDTH_LAST_NAME, contact->last_name,
               COLUMN_WIDTH_PHONE_NUMBER, contact->phone_number, COLUMN_WIDTH_STREET, contact->address.street,
               COLUMN_WIDTH_NR, contact->address.nr, COLUMN_WIDTH_POST_CODE, contact->address.post_code,
               COLUMN_WIDTH_TOWN, contact->address.town);
}

void print_header(int total_width)
{
    print_separator(total_width);

    printf(COLOR_BOLD "| %-*s| %-*s| %-*s| %-*s| %-*s| %-*s| %-*s| %-*s|\n" COLOR_RESET,
           COLUMN_WIDTH_ID, "ID", COLUMN_WIDTH_NAME, "Name", COLUMN_WIDTH_LAST_NAME, "Last Name",
           COLUMN_WIDTH_PHONE_NUMBER, "Phone Number", COLUMN_WIDTH_STREET, "Street", COLUMN_WIDTH_NR, "Nr",
           COLUMN_WIDTH_POST_CODE, "Post Code", COLUMN_WIDTH_TOWN, "Town");

    print_separator(total_width);
}

void search_contact_from_user(const Contacts *head) {
    if (head == NULL) {
        printf(COLOR_BLUE "List is empty.\n" COLOR_RESET);
        return;
    }

    int choice = 0;
    char search_value[30];
    printf(COLOR_BOLD "Choose the field to search:\n" COLOR_RESET);
    printf("1. Name \n");
    printf("2. Last Name\n");
    printf("3. Phone Number\n");
    printf("4. Street\n");
    printf("5. House Number\n");
    printf("6. City\n");
    printf("7. Post Code\n");
    printf("0. Return to menu\n");

    do{
        choice = get_user_choice();

    switch (choice) {
        case 1:
            printf(COLOR_BOLD "Enter name to search: " COLOR_RESET);
            break;
        case 2:
            printf(COLOR_BOLD "Enter last name to search: " COLOR_RESET);
            break;
        case 3:
            printf(COLOR_BOLD "Enter phone number to search: " COLOR_RESET);
            break;
        case 4:
            printf(COLOR_BOLD "Enter street to search: " COLOR_RESET);
            break;
        case 5:
            printf(COLOR_BOLD "Enter house number to search: " COLOR_RESET);
            break;
        case 6:
            printf(COLOR_BOLD "Enter city to search: " COLOR_RESET);
            break;
        case 7:
            printf(COLOR_BOLD "Enter post code to search: " COLOR_RESET);
            break;
        case 0:
            return; // Return to main menu
        default:
            printf(COLOR_RED "Invalid option.\n" COLOR_RESET);
    }
    }while(choice>7 || choice<0);

    get_line(search_value, sizeof(search_value));

    int total_width = COLUMN_WIDTH_ID + COLUMN_WIDTH_NAME + COLUMN_WIDTH_LAST_NAME +
                      COLUMN_WIDTH_PHONE_NUMBER + COLUMN_WIDTH_STREET + COLUMN_WIDTH_NR +
                      COLUMN_WIDTH_POST_CODE + COLUMN_WIDTH_TOWN + 8 * 2 - 1; // X * Y ; X - ilość kolumn, Y - szerokość kolumny z "| "

    print_header(total_width);

    const Contacts *current = head;
    int found = 0;
    while (current != NULL) {
        switch (choice) {
            case 1:
                if (strcasecmp(current->name, search_value) == 0){
                    print_contact(current);
                    found = 1;
                }
                break;
            case 2:
                if (strcasecmp(current->last_name, search_value) == 0){
                    print_contact(current);
                    found = 1;
                }
                break;
            case 3:
                if (strcasecmp(current->phone_number, search_value) == 0){
                    print_contact(current);
                    found = 1;
                }
                break;
            case 4:
                if (strcasecmp(current->address.street, search_value) == 0){
                    print_contact(current);
                    found = 1;
                }
                break;
            case 5:
                if (strcasecmp(current->address.nr, search_value) == 0){
                    print_contact(current);
                    found = 1;
                }
                break;
            case 6:
                if (strcasecmp(current->address.town, search_value) == 0){
                    print_contact(current);
                    found = 1;
                }
                break;
            case 7:
                if (strcasecmp(current->address.post_code, search_value) == 0){
                    print_contact(current);
                    found = 1;
                }
                break;
        }
        current = current->next;
    }
    print_separator(total_width);

    if (!found) {
        printf(COLOR_BLUE "No contact found.\n" COLOR_RESET);
    }
}

void execute_option(Contacts **head, int option) {
    switch(option) {
        case 0:
            printf(COLOR_BOLD "Exiting program.\n" COLOR_RESET);
            exit(0);
            break;
        case 1:
            display_list(head);
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
            search_contact_from_user(*head);
            break;
        default:
            printf(COLOR_RED "Invalid option.\n" COLOR_RESET);
    }
}
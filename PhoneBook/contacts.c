#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contacts.h"
#include "sort.h"
#include "colors.h"
#include "menu.h"

void save_contacts_to_file(Contacts *head, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        fprintf(stderr, COLOR_RED "Error opening file for writing.\n" COLOR_RESET);
        return;
    }

    const Contacts *current = head;
    while (current != NULL) {
        fprintf(file, "%d,%s,%s,%s,%s,%s,%s,%s\n",
                current->id, current->name, current->last_name,
                current->phone_number, current->address.street,
                current->address.nr, current->address.post_code,
                current->address.town);
                current = current->next;
    }

    fclose(file);
}

void load_contacts_from_file(Contacts **head, const char *filename) {
    FILE *file = fopen(filename, "a+");
    if (file == NULL) {
        fprintf(stderr, COLOR_RED "Error opening file for reading.\n" COLOR_RESET);
        return;
    }

    int id;
    char name[30], last_name[30], phone_number[10];
    char street[30], nr[6], post_code[7], town[30];
    Contacts *current_contact = NULL;
    
    while (fscanf(file, "%d,%29[^,],%29[^,],%9[^,],%29[^,],%5[^,],%6[^,],%29[^\n]",
               &id, name, last_name, phone_number, street, nr, post_code, town)==8) {
        Contacts *new_contact = (Contacts*)malloc(sizeof(Contacts));
        if (new_contact == NULL) {
            fprintf(stderr, COLOR_RED "Memory allocation failed\n" COLOR_RESET);
            exit(EXIT_FAILURE);
        }
        new_contact->next = NULL;
        
        new_contact->id = id;
        strcpy(new_contact->name, name);
        strcpy(new_contact->last_name, last_name);
        strcpy(new_contact->phone_number, phone_number);
        strcpy(new_contact->address.street, street);
        strcpy(new_contact->address.nr, nr);
        strcpy(new_contact->address.post_code, post_code);
        strcpy(new_contact->address.town, town);

        if (*head == NULL) {
            // Jeśli lista jest pusta, ustaw nowy kontakt jako głowę listy
            *head = new_contact;
            current_contact = new_contact; // Ustaw bieżący kontakt na nowy kontakt
        } else {
            // W przeciwnym razie dołącz nowy kontakt na koniec listy
            current_contact->next = new_contact;
            current_contact = new_contact; // Aktualizuj bieżący kontakt
        }
    }

    fclose(file);
}

void print_separator(int total_width) {
    putchar('+');
    for (int i = 0; i < total_width; i++) {
        putchar('-');
    }
    putchar('+');
    putchar('\n');
}

void display_sorting_menu() {
    printf(COLOR_BOLD "SORTING MENU:\n" COLOR_RESET);
    printf(COLOR_YELLOW "1. Sort by ID (default)\n");
    printf("2. Sort by name\n");
    printf("3. Sort by last name\n");
    printf("4. Sort by phone number\n");
    printf("5. Sort by town\n");
    printf("6. Sort by post code\n" COLOR_RESET);
    printf(COLOR_BLUE "0. Back to main menu\n" COLOR_RESET);
}

void display_ascending_descending_menu(){
    printf(COLOR_BOLD "SELECT SORTING ORDER:\n" COLOR_RESET);
    printf(COLOR_YELLOW "1. Ascending\n");
    printf("2. Descending\n" COLOR_RESET);
    printf(COLOR_BLUE "3. Cancel\n" COLOR_RESET);
}

void display_list(Contacts **headRef) {
    Contacts *head = *headRef;
    int sorting_mode = 1;
    int order = 1;

    do {
        clear_screen();
        puts("");
        if (head == NULL) {
            puts(COLOR_BLUE "There are no contacts in the list." COLOR_RESET);
            return;
        }

        // Sortowanie listy kontaktów
        if (sorting_mode > 0 && sorting_mode < 7)
            mergeSort(headRef, get_comparator(sorting_mode), order);
        else
            mergeSort(headRef, compareByID, 1);

        // Obliczanie całkowitej szerokości separatora
        int total_width = COLUMN_WIDTH_ID + COLUMN_WIDTH_NAME + COLUMN_WIDTH_LAST_NAME +
                          COLUMN_WIDTH_PHONE_NUMBER + COLUMN_WIDTH_STREET + COLUMN_WIDTH_NR +
                          COLUMN_WIDTH_POST_CODE + COLUMN_WIDTH_TOWN + 8 * 2 - 1; // X * Y ; X - ilość kolumn, Y - szerokość kolumny z "| "

        print_separator(total_width);

        // Wyświetlenie nagłówków kolumn
        printf(COLOR_BOLD "| %-*s| %-*s| %-*s| %-*s| %-*s| %-*s| %-*s| %-*s|\n" COLOR_RESET,
               COLUMN_WIDTH_ID, "ID", COLUMN_WIDTH_NAME, "Name", COLUMN_WIDTH_LAST_NAME, "Last Name",
               COLUMN_WIDTH_PHONE_NUMBER, "Phone Number", COLUMN_WIDTH_STREET, "Street", COLUMN_WIDTH_NR, "Nr",
               COLUMN_WIDTH_POST_CODE, "Post Code", COLUMN_WIDTH_TOWN, "Town");

        // Separator
        print_separator(total_width);

        // Wyświetlenie danych kontaktów w formie kolumn
        Contacts *current = *headRef;
        while (current != NULL) {
            printf("| %-*d| %-*s| %-*s| %-*s| %-*s| %-*s| %-*s| %-*s|\n",
                   COLUMN_WIDTH_ID, current->id, COLUMN_WIDTH_NAME, current->name, COLUMN_WIDTH_LAST_NAME, current->last_name,
                   COLUMN_WIDTH_PHONE_NUMBER, current->phone_number, COLUMN_WIDTH_STREET, current->address.street,
                   COLUMN_WIDTH_NR, current->address.nr, COLUMN_WIDTH_POST_CODE, current->address.post_code,
                   COLUMN_WIDTH_TOWN, current->address.town);

            current = current->next;
        }

        print_separator(total_width);

        display_sorting_menu();
        sorting_mode = get_user_choice(); // Update sorting mode for the next iteration
        if (sorting_mode >= 1 && sorting_mode <= 6) {
            display_ascending_descending_menu();
            do {
                int order_choice = get_user_choice();
                if (order_choice == 2) {
                    order = -1; // Set order to descending
                } else {
                    order = 1; // Default to ascending order
                }
                if(order_choice == 3){
                    break;
                }
            }while(order != 1 && order != -1);
        }
    } while (sorting_mode != 0);
    mergeSort(headRef, compareByID, 1);
}

void free_contacts_list(Contacts *head) {
    Contacts *current = head;
    while (current != NULL) {
        Contacts *temp = current;
        current = current->next;
        free(temp);
    }
}

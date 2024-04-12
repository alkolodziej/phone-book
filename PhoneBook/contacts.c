#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contacts.h"
#include "colors.h"
#include "menu.h"

#define COLUMN_WIDTH_ID 10
#define COLUMN_WIDTH_NAME 32
#define COLUMN_WIDTH_LAST_NAME 32
#define COLUMN_WIDTH_PHONE_NUMBER 15
#define COLUMN_WIDTH_STREET 32
#define COLUMN_WIDTH_NR 7
#define COLUMN_WIDTH_POST_CODE 10
#define COLUMN_WIDTH_TOWN 31

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
// Funkcja pomocnicza do zliczania liczby kontaktów w liście
size_t count_contacts(const Contacts *head) {
    int count = 0;
    const Contacts *current = head;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return (size_t)count;
}

// Funkcje porównujące dla sortowania

int compare_by_id(const void *a, const void *b) {
    const Contacts *contact1 = (const Contacts *)a;
    const Contacts *contact2 = (const Contacts *)b;
    return contact1->id - contact2->id;
}

int compare_by_name(const void *a, const void *b) {
    const Contacts *contact1 = (const Contacts *)a;
    const Contacts *contact2 = (const Contacts *)b;
    return strcmp(contact1->name, contact2->name);
}

int compare_by_last_name(const void *a, const void *b) {
    const Contacts *contact1 = (const Contacts *)a;
    const Contacts *contact2 = (const Contacts *)b;
    return strcmp(contact1->last_name, contact2->last_name);
}

int compare_by_phone_number(const void *a, const void *b) {
    const Contacts *contact1 = (const Contacts *)a;
    const Contacts *contact2 = (const Contacts *)b;
    return strcmp(contact1->phone_number, contact2->phone_number);
}

int compare_by_town(const void *a, const void *b) {
    const Contacts *contact1 = (const Contacts *)a;
    const Contacts *contact2 = (const Contacts *)b;
    return strcmp(contact1->address.town, contact2->address.town);
}

int compare_by_post_code(const void *a, const void *b) {
    const Contacts *contact1 = (const Contacts *)a;
    const Contacts *contact2 = (const Contacts *)b;
    return strcmp(contact1->address.post_code, contact2->address.post_code);
}

// Funkcja sortująca listę kontaktów

void sort_contacts(const Contacts *head, int sorting_mode) {
    switch (sorting_mode) {
        case 1:
            // Sortowanie po ID
            qsort((Contacts *)head, count_contacts(head), sizeof(Contacts), compare_by_id);
            break;
        case 2:
            // Sortowanie po imieniu
            qsort((Contacts *)head, count_contacts(head), sizeof(Contacts), compare_by_name);
            break;
        case 3:
            // Sortowanie po nazwisku
            qsort((Contacts *)head, count_contacts(head), sizeof(Contacts), compare_by_last_name);
            break;
        case 4:
            // Sortowanie po numerze telefonu
            qsort((Contacts *)head, count_contacts(head), sizeof(Contacts), compare_by_phone_number);
            break;
        case 5:
            // Sortowanie po mieście
            qsort((Contacts *)head, count_contacts(head), sizeof(Contacts), compare_by_town);
            break;
        case 6:
            // Sortowanie po kodzie pocztowym
            qsort((Contacts *)head, count_contacts(head), sizeof(Contacts), compare_by_post_code);
            break;
        default:
            // Domyślne sortowanie po ID
            qsort((Contacts *)head, count_contacts(head), sizeof(Contacts), compare_by_id);
            break;
    }
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

void display_list(const Contacts *head, int sorting_mode) {
    const Contacts *current = head;
    puts("");
    if(NULL==head)
    {
        puts(COLOR_BLUE "There are no contacts in the list." COLOR_RESET);
        return;
    }

    /*// Sortowanie listy kontaktów
    if(sorting_mode>0 && sorting_mode<7)
        sort_contacts(head, sorting_mode);
    else
        sort_contacts(head, 1);
*/
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
    while (current != NULL) {
        printf("| %-*d| %-*s| %-*s| %-*s| %-*s| %-*s| %-*s| %-*s|\n",
               COLUMN_WIDTH_ID, current->id, COLUMN_WIDTH_NAME, current->name, COLUMN_WIDTH_LAST_NAME, current->last_name,
               COLUMN_WIDTH_PHONE_NUMBER, current->phone_number, COLUMN_WIDTH_STREET, current->address.street,
               COLUMN_WIDTH_NR, current->address.nr, COLUMN_WIDTH_POST_CODE, current->address.post_code,
               COLUMN_WIDTH_TOWN, current->address.town);

        current = current->next;
    }

    print_separator(total_width);

/*
    display_sorting_menu();
    int sort_choice = get_user_choice();
    if(sort_choice>0 && sort_choice<7) {
        clear_screen();
        display_list(head, sort_choice);
    }
    else if(sort_choice==0) return;
    else {
        printf(COLOR_RED "Invalid choice.\n" COLOR_RESET);
        printf("Press enter to continue...\n");
        getchar();
        clear_screen();
        display_list(head, 1);
    }*/
}


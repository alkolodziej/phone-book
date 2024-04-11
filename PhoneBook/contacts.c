#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contacts.h"
#include "colors.h"

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


void add_contact(Contacts **head, char *name, char *last_name, char *phone_number, char *street, char *nr, char *post_code, char *town) {
    // Alokacja pamięci dla nowego kontaktu
    Contacts *new_contact = (Contacts*)malloc(sizeof(Contacts));
    if (new_contact == NULL) {
        fprintf(stderr, COLOR_RED "Memory allocation failed\n" COLOR_RESET);
        exit(EXIT_FAILURE);
    }

    // Inicjalizacja danych dla nowego kontaktu
    strcpy(new_contact->name, name);
    strcpy(new_contact->last_name, last_name);
    strcpy(new_contact->phone_number, phone_number);
    strcpy(new_contact->address.street, street);
    strcpy(new_contact->address.nr, nr);
    strcpy(new_contact->address.post_code, post_code);
    strcpy(new_contact->address.town, town);

    // Ustawienie wskaźnika na następny element na NULL
    new_contact->next = NULL;

    // Jeśli lista jest pusta, ustaw nowy kontakt jako głowę listy
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
    save_contacts_to_file(*head, "contacts.csv");
}

void load_contacts_from_file(Contacts **head, const char *filename) {
    FILE *file = fopen(filename, "a+");
    if (file == NULL) {
        fprintf(stderr, COLOR_RED "Error opening file for reading.\n" COLOR_RESET);
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        int id;
        char name[30], last_name[30], phone_number[11];
        char street[30], nr[5], post_code[8], town[30];

        sscanf(line, "%d,%29[^,],%29[^,],%10[^,],%29[^,],%4[^,],%6[^,],%29[^\n]",
               &id, name, last_name, phone_number, street, nr, post_code, town);

        add_contact(head, name, last_name, phone_number, street, nr, post_code, town);
    }

    fclose(file);
}

#define COLUMN_WIDTH_ID 7
#define COLUMN_WIDTH_NAME 32
#define COLUMN_WIDTH_LAST_NAME 32
#define COLUMN_WIDTH_PHONE_NUMBER 15
#define COLUMN_WIDTH_STREET 32
#define COLUMN_WIDTH_NR 6
#define COLUMN_WIDTH_POST_CODE 10
#define COLUMN_WIDTH_TOWN 31

void print_separator(int total_width) {
    for (int i = 0; i < total_width; i++) {
        putchar('-');
    }
    putchar('\n');
}

void display_list(const Contacts *head) {
    const Contacts *current = head;
    puts("");
    if(NULL==head)
    {
        puts(COLOR_BLUE "There are no contacts in the list." COLOR_RESET);
        return;
    }

    // Obliczanie całkowitej szerokości separatora
    int total_width = COLUMN_WIDTH_ID + COLUMN_WIDTH_NAME + COLUMN_WIDTH_LAST_NAME +
                      COLUMN_WIDTH_PHONE_NUMBER + COLUMN_WIDTH_STREET + COLUMN_WIDTH_NR +
                      COLUMN_WIDTH_POST_CODE + COLUMN_WIDTH_TOWN + 8 * 2; // X * Y ; X - ilość kolumn, Y - szerokość kolumny z "| "

    print_separator(total_width);

    // Wyświetlenie nagłówków kolumn
    printf(COLOR_BOLD " %-*s| %-*s| %-*s| %-*s| %-*s| %-*s| %-*s| %-*s|\n" COLOR_RESET,
           COLUMN_WIDTH_ID, "ID", COLUMN_WIDTH_NAME, "Name", COLUMN_WIDTH_LAST_NAME, "Last Name",
           COLUMN_WIDTH_PHONE_NUMBER, "Phone Number", COLUMN_WIDTH_STREET, "Street", COLUMN_WIDTH_NR, "Nr",
           COLUMN_WIDTH_POST_CODE, "Post Code", COLUMN_WIDTH_TOWN, "Town");

    // Separator
    print_separator(total_width);

    // Wyświetlenie danych kontaktów w formie kolumn
    while (current != NULL) {
        printf(" %-*d| %-*s| %-*s| %-*s| %-*s| %-*s| %-*s| %-*s|\n",
               COLUMN_WIDTH_ID, current->id, COLUMN_WIDTH_NAME, current->name, COLUMN_WIDTH_LAST_NAME, current->last_name,
               COLUMN_WIDTH_PHONE_NUMBER, current->phone_number, COLUMN_WIDTH_STREET, current->address.street,
               COLUMN_WIDTH_NR, current->address.nr, COLUMN_WIDTH_POST_CODE, current->address.post_code,
               COLUMN_WIDTH_TOWN, current->address.town);

        current = current->next;
    }
    print_separator(total_width);
    
}



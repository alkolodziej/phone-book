#include "contacts.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void save_contacts_to_file(Contacts *head, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        fprintf(stderr, "Error opening file for writing.\n");
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
        fprintf(stderr, "Memory allocation failed\n");
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
        fprintf(stderr, "Error opening file for reading.\n");
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        int id;
        char name[30], last_name[30], phone_number[11];
        char street[30], nr[5], post_code[6], town[30];

        sscanf(line, "%d,%29[^,],%29[^,],%10[^,],%29[^,],%4[^,],%5[^,],%29[^\n]",
               &id, name, last_name, phone_number, street, nr, post_code, town);

        add_contact(head, name, last_name, phone_number, street, nr, post_code, town);
    }

    fclose(file);
}


void display_list(const Contacts *head) {
    const Contacts *current = head;
    puts("");
    if(NULL==head)
    {
        puts("There are no contacts in the list.");
        return;
    }

    // Wyświetlenie nagłówków kolumn
    printf("%-7s|%-32s|%-32s|%-15s|%-32s|%-6s|%-10s|%-31s|\n", "ID", "Name", "Last Name", "Phone Number", "Street", "Nr", "Post Code", "Town");

    // Separator
    printf("-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");

    // Wyświetlenie danych kontaktów w formie kolumn
    while (current != NULL) {
        printf("%-7d|%-32s|%-32s|%-15s|%-32s|%-6s|%-10s|%-31s|\n", current->id, current->name, current->last_name, current->phone_number,
               current->address.street, current->address.nr, current->address.post_code, current->address.town);

        current = current->next;
    }
    printf("-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    puts("");
}



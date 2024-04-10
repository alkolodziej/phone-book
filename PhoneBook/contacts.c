#include "contacts.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
}

void edit_contact(Contacts *head, int id, char *name, char *last_name, char *phone_number, char *street, char *nr, char *post_code, char *town)
{
    Contacts *current = head;

    while (current != NULL) {
        if (current->id == id) {
            // Znaleziono kontakt o podanym ID, aktualizacja danych
            strcpy(current->name, name);
            strcpy(current->last_name, last_name);
            strcpy(current->phone_number, phone_number);
            strcpy(current->address.street, street);
            strcpy(current->address.nr, nr);
            strcpy(current->address.post_code, post_code);
            strcpy(current->address.town, town);
            return;
        }
        current = current->next;
    }

    // Nie znaleziono kontaktu o podanym ID
    printf("Contact with ID %d not found.\n", id);
}

void delete_contact(Contacts **head, int index)
{
    Contacts *current = *head;
    Contacts *prev = NULL;

    // Przeszukiwanie listy w poszukiwaniu kontaktu o podanym indeksie
    while (current != NULL && current->id != index) {
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
    } else {
        printf("Contact with ID %d not found.\n", index);
    }
}

void display_list(const Contacts *head) {
    const Contacts *current = head;

    printf("Contact List:\n");
    printf("--------------------------------------------\n");
    while (current != NULL) {
        printf("ID: %d\n", current->id);
        printf("Name: %s %s\n", current->name, current->last_name);
        printf("Phone Number: %s\n", current->phone_number);
        printf("Address: %s %s, %s, %s\n", current->address.street, current->address.nr, current->address.post_code, current->address.town);
        printf("--------------------------------------------\n");

        current = current->next;
    }
}



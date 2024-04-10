#include "contacts.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void add_contact(Contacts **head, char *name, char *last_name, char *phone_number, char *street, char *nr, char *post_code, char *town)
{
    // Alokacja pami�ci dla nowego kontaktu
    Contacts *new_contact = (Contacts*)malloc(sizeof(Contacts));
    if (new_contact == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    // Inicjalizacja danych dla nowego kontaktu
    new_contact->id = (*head == NULL) ? 1 : (*head)->id + 1; // Nadanie unikalnego ID
    strcpy(new_contact->name, name);
    strcpy(new_contact->last_name, last_name);
    strcpy(new_contact->phone_number, phone_number);
    strcpy(new_contact->address.street, street);
    strcpy(new_contact->address.nr, nr);
    strcpy(new_contact->address.post_code, post_code);
    strcpy(new_contact->address.town, town);

    // Dodanie nowego kontaktu na pocz�tek listy kontakt�w
    new_contact->next = *head;
    *head = new_contact;
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

void display_list(const Contacts *head)
{
     if (head == NULL) {
        return;
    }

    display_list(head->next);

    printf("--------------------------------------------\n");
    printf("ID: %d\n", head->id);
    printf("Name: %s %s\n", head->name, head->last_name);
    printf("Phone Number: %s\n", head->phone_number);
    printf("Address: %s %s, %s, %s\n", head->address.street, head->address.nr, head->address.post_code, head->address.town);
    printf("--------------------------------------------\n");
}



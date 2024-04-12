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

typedef int (*Comparator)(const Contacts *, const Contacts *);

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

// Merges two sorted lists into one
Contacts *merge(Contacts *a, Contacts *b, Comparator comp) {
    Contacts *result = NULL;

    // Base cases: if either list is empty, return the other list
    if (a == NULL) {
        return b;
    } else if (b == NULL) {
        return a;
    }

    // Compare the elements of the two lists and merge them accordingly
    if (comp(a, b) <= 0) {
        result = a;
        result->next = merge(a->next, b, comp);
    } else {
        result = b;
        result->next = merge(a, b->next, comp);
    }

    return result;
}

// Splits the list into two sublists
void split(Contacts *source, Contacts **frontRef, Contacts **backRef) {
    Contacts *fast;
    Contacts *slow;

    if (source == NULL || source->next == NULL) {
        *frontRef = source;
        *backRef = NULL;
    } else {
        slow = source;
        fast = source->next;

        // Advance 'fast' two nodes and advance 'slow' one node
        while (fast != NULL) {
            fast = fast->next;
            if (fast != NULL) {
                slow = slow->next;
                fast = fast->next;
            }
        }

        // 'slow' is before the midpoint, split the list in two at that point
        *frontRef = source;
        *backRef = slow->next;
        slow->next = NULL;
    }
}

// Sorts the linked list using Merge Sort
void mergeSort(Contacts **headRef, Comparator comp) {
    Contacts *head = *headRef;
    Contacts *a;
    Contacts *b;

    // Base case: empty or single element list, no need to sort
    if (head == NULL || head->next == NULL) {
        return;
    }

    // Split head into 'a' and 'b' sublists
    split(head, &a, &b);

    // Recursively sort the sublists
    mergeSort(&a, comp);
    mergeSort(&b, comp);

    // Merge the sorted sublists
    *headRef = merge(a, b, comp);
}

// Comparison function for sorting by ID
int compareByID(const Contacts *a, const Contacts *b) {
    return a->id - b->id;
}

// Comparison function for sorting by name
int compareByName(const Contacts *a, const Contacts *b) {
    return strcasecmp(a->name, b->name);
}

// Comparison function for sorting by last name
int compareByLastName(const Contacts *a, const Contacts *b) {
    return strcasecmp(a->last_name, b->last_name);
}

// Comparison function for sorting by phone number
int compareByPhoneNumber(const Contacts *a, const Contacts *b) {
    return strcasecmp(a->phone_number, b->phone_number);
}

// Comparison function for sorting by street
int compareByStreet(const Contacts *a, const Contacts *b) {
    return strcasecmp(a->address.street, b->address.street);
}

// Comparison function for sorting by house number
int compareByNr(const Contacts *a, const Contacts *b) {
    return strcasecmp(a->address.nr, b->address.nr);
}

// Comparison function for sorting by post code
int compareByPostCode(const Contacts *a, const Contacts *b) {
    return strcasecmp(a->address.post_code, b->address.post_code);
}

// Comparison function for sorting by town
int compareByTown(const Contacts *a, const Contacts *b) {
    return strcasecmp(a->address.town, b->address.town);
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

// Funkcja zwracająca odpowiednią funkcję porównującą na podstawie wyboru użytkownika
Comparator get_comparator(int sorting_mode) {
    switch (sorting_mode) {
        case 1:
            return compareByID;
        case 2:
            return compareByName;
        case 3:
            return compareByLastName;
        case 4:
            return compareByPhoneNumber;
        case 5:
            return compareByTown;
        case 6:
            return compareByPostCode;
        default:
            return compareByID; // Default sorting mode
    }
}

void display_list(Contacts **headRef) {
    Contacts *head = *headRef;
    int sorting_mode = 1;

    do {
        clear_screen();
        puts("");
        if (head == NULL) {
            puts(COLOR_BLUE "There are no contacts in the list." COLOR_RESET);
            return;
        }

        // Sortowanie listy kontaktów
        if (sorting_mode > 0 && sorting_mode < 7)
            mergeSort(headRef, get_comparator(sorting_mode));
        else
            mergeSort(headRef, compareByID);

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
    } while (sorting_mode != 0);
    mergeSort(headRef, compareByID);
}

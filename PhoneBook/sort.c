#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contacts.h"
#include "menu.h"
#include "colors.h"

typedef int (*Comparator)(const Contacts *, const Contacts *); // Add sorting order parameter

// Merges two sorted lists into one
Contacts *merge(Contacts *a, Contacts *b, Comparator comp, int order) {
    Contacts *result = NULL;

    // Base cases: if either list is empty, return the other list
    if (a == NULL) {
        return b;
    } else if (b == NULL) {
        return a;
    }

    // Compare the elements of the two lists and merge them accordingly
    if ((order == 1 && comp(a, b) <= 0) || (order == -1 && comp(a, b) >= 0)) {
        result = a;
        result->next = merge(a->next, b, comp, order);
    } else {
        result = b;
        result->next = merge(a, b->next, comp, order);
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
void mergeSort(Contacts **headRef, Comparator comp, int order) {
    Contacts *head = *headRef;
    Contacts *a;
    Contacts *b;

    // Base case: empty or single element list, no need to sort
    if (head == NULL || head->next == NULL) {
        //printf(COLOR_BLUE "Lista jest pusta lub ma 1 element." COLOR_RESET);
        return;
    }

    // Split head into 'a' and 'b' sublists
    split(head, &a, &b);

    // Recursively sort the sublists
    mergeSort(&a, comp, order);
    mergeSort(&b, comp, order);

    // Merge the sorted sublists
    *headRef = merge(a, b, comp, order);
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

// Function to get the comparator based on user choice
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
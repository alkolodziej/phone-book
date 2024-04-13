/**
 * @file sort.c
 * @brief Implementation of functions related to sorting contacts.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contacts.h"
#include "sort.h"
#include "colors.h"

/**
 * @brief Merges two sorted lists into one.
 * 
 * This function merges two sorted linked lists into a single sorted linked list.
 * 
 * @param a Pointer to the head of the first sorted list.
 * @param b Pointer to the head of the second sorted list.
 * @param comp Comparator function for comparing contacts.
 * @param order Sorting order parameter (1 for ascending, -1 for descending).
 * @return Pointer to the merged sorted list.
 */
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

/**
 * @brief Splits the list into two sublists.
 * 
 * This function divides a linked list into two separate linked lists. It uses a slow and a fast pointer to find the midpoint of the list and then splits it at that point.
 * 
 * @param source Pointer to the head of the list to split.
 * @param frontRef Pointer to the pointer to store the head of the first sublist.
 * @param backRef Pointer to the pointer to store the head of the second sublist.
 */
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

/**
 * @brief Sorts the linked list using Merge Sort.
 * 
 * This function sorts a linked list using the Merge Sort algorithm. It recursively divides the list into smaller sublists, sorts them individually, and then merges them back together in the correct order.
 * 
 * @param headRef Pointer to the pointer to the head of the contacts list.
 * @param comp Comparator function for comparing contacts.
 * @param order Sorting order parameter (1 for ascending, -1 for descending).
 */
void mergeSort(Contacts **headRef, Comparator comp, int order) {
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
    mergeSort(&a, comp, order);
    mergeSort(&b, comp, order);

    // Merge the sorted sublists
    *headRef = merge(a, b, comp, order);
}

/**
 * @brief Comparison function for sorting by ID.
 * 
 * This function compares two contacts based on their ID numbers.
 * 
 * @param a Pointer to the first contact.
 * @param b Pointer to the second contact.
 * @return Negative if a should precede b, positive if b should precede a, zero if equal.
 */
int compareByID(const Contacts *a, const Contacts *b) {
    return a->id - b->id;
}

/**
 * @brief Comparison function for sorting by name.
 * 
 * This function compares two contacts based on their names.
 * 
 * @param a Pointer to the first contact.
 * @param b Pointer to the second contact.
 * @return Negative if a should precede b, positive if b should precede a, zero if equal.
 */
int compareByName(const Contacts *a, const Contacts *b) {
    return strcasecmp(a->name, b->name);
}

/**
 * @brief Comparison function for sorting by last name.
 * 
 * This function compares two contacts based on their last names.
 * 
 * @param a Pointer to the first contact.
 * @param b Pointer to the second contact.
 * @return Negative if a should precede b, positive if b should precede a, zero if equal.
 */
int compareByLastName(const Contacts *a, const Contacts *b) {
    return strcasecmp(a->last_name, b->last_name);
}

/**
 * @brief Comparison function for sorting by phone number.
 * 
 * This function compares two contacts based on their phone numbers.
 * 
 * @param a Pointer to the first contact.
 * @param b Pointer to the second contact.
 * @return Negative if a should precede b, positive if b should precede a, zero if equal.
 */
int compareByPhoneNumber(const Contacts *a, const Contacts *b) {
    return strcasecmp(a->phone_number, b->phone_number);
}

/**
 * @brief Comparison function for sorting by street.
 * 
 * This function compares two contacts based on their street addresses.
 * 
 * @param a Pointer to the first contact.
 * @param b Pointer to the second contact.
 * @return Negative if a should precede b, positive if b should precede a, zero if equal.
 */
int compareByStreet(const Contacts *a, const Contacts *b) {
    return strcasecmp(a->address.street, b->address.street);
}

/**
 * @brief Comparison function for sorting by house number.
 * 
 * This function compares two contacts based on their house numbers.
 * 
 * @param a Pointer to the first contact.
 * @param b Pointer to the second contact.
 * @return Negative if a should precede b, positive if b should precede a, zero if equal.
 */
int compareByNr(const Contacts *a, const Contacts *b) {
    return strcasecmp(a->address.nr, b->address.nr);
}

/**
 * @brief Comparison function for sorting by post code.
 * 
 * This function compares two contacts based on their post codes.
 * 
 * @param a Pointer to the first contact.
 * @param b Pointer to the second contact.
 * @return Negative if a should precede b, positive if b should precede a, zero if equal.
 */
int compareByPostCode(const Contacts *a, const Contacts *b) {
    return strcasecmp(a->address.post_code, b->address.post_code);
}

/**
 * @brief Comparison function for sorting by town.
 * 
 * This function compares two contacts based on their towns.
 * 
 * @param a Pointer to the first contact.
 * @param b Pointer to the second contact.
 * @return Negative if a should precede b, positive if b should precede a, zero if equal.
 */
int compareByTown(const Contacts *a, const Contacts *b) {
    return strcasecmp(a->address.town, b->address.town);
}

/**
 * @brief Gets the comparator function based on user choice.
 * 
 * This function returns the appropriate comparator function based on the user's choice for sorting mode.
 * 
 * @param sorting_mode User choice for sorting mode.
 * @return Comparator function.
 */
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
#ifndef SORT_H_INCLUDED
#define SORT_H_INCLUDED

#include "contacts.h"

// Define a function pointer type for comparators
typedef int (*Comparator)(const Contacts *, const Contacts *);

// Function declarations for sorting contacts

// Merge two sorted lists
Contacts *merge(Contacts *a, Contacts *b, Comparator comp, int order);

// Split a list into two sublists
void split(Contacts *source, Contacts **frontRef, Contacts **backRef);

// Sort the list using Merge Sort
void mergeSort(Contacts **headRef, Comparator comp, int order);

// Comparison functions for sorting contacts by different fields
int compareByID(const Contacts *a, const Contacts *b);
int compareByName(const Contacts *a, const Contacts *b);
int compareByLastName(const Contacts *a, const Contacts *b);
int compareByPhoneNumber(const Contacts *a, const Contacts *b);
int compareByStreet(const Contacts *a, const Contacts *b);
int compareByNr(const Contacts *a, const Contacts *b);
int compareByPostCode(const Contacts *a, const Contacts *b);
int compareByTown(const Contacts *a, const Contacts *b);

// Function to get the appropriate comparator based on user choice
Comparator get_comparator(int sorting_mode);

#endif // SORT_H_INCLUDED
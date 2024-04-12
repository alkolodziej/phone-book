#ifndef SORT_H_INCLUDED
#define SORT_H_INCLUDED
#include "contacts.h"

typedef int (*Comparator)(const Contacts *, const Contacts *); // Add sorting order parameter

Contacts *merge(Contacts *a, Contacts *b, Comparator comp, int order);
void split(Contacts *source, Contacts **frontRef, Contacts **backRef);
void mergeSort(Contacts **headRef, Comparator comp, int order);
int compareByID(const Contacts *a, const Contacts *b);
int compareByName(const Contacts *a, const Contacts *b);
int compareByLastName(const Contacts *a, const Contacts *b);
int compareByPhoneNumber(const Contacts *a, const Contacts *b);
int compareByStreet(const Contacts *a, const Contacts *b);
int compareByNr(const Contacts *a, const Contacts *b);
int compareByPostCode(const Contacts *a, const Contacts *b);
int compareByTown(const Contacts *a, const Contacts *b);
Comparator get_comparator(int sorting_mode);

#endif // SORT_H_INCLUDED
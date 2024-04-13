#ifndef CONTACTS_H_INCLUDED
#define CONTACTS_H_INCLUDED

// Define column widths for displaying contact details
#define COLUMN_WIDTH_ID 10
#define COLUMN_WIDTH_NAME 32
#define COLUMN_WIDTH_LAST_NAME 32
#define COLUMN_WIDTH_PHONE_NUMBER 15
#define COLUMN_WIDTH_STREET 32
#define COLUMN_WIDTH_NR 7
#define COLUMN_WIDTH_POST_CODE 10
#define COLUMN_WIDTH_TOWN 31

// Define the structure for an address
typedef struct Address {
    char street[30];
    char nr[6];
    char post_code[7];
    char town[30];
} Address;

// Define the structure for a contact
typedef struct Contacts {
    int id;
    char name[30];
    char last_name[30];
    char phone_number[10];
    Address address;
    struct Contacts *next;
} Contacts;

// Function declarations for managing contacts

// Save contacts to a file
void save_contacts_to_file(Contacts *head, const char *filename);

// Load contacts from a file
void load_contacts_from_file(Contacts **head, const char *filename);

// Print a separator line in the contact list display
void print_separator(int total_width);

// Display the sorting menu for contacts
void display_sorting_menu();

// Display the menu for selecting ascending or descending order
void display_ascending_descending_menu();

// Display the list of contacts
void display_list(Contacts **headRef);

// Free memory allocated for the contacts list
void free_contacts_list(Contacts *head);

#endif // CONTACTS_H_INCLUDED
#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include "contacts.h"

// Function declarations for menu operations

// Clears the screen
void clear_screen();

// Gets user choice from the menu
int get_user_choice();

// Displays the main menu
void display_menu();

// Gets a line of input from the user
void get_line(char *line, size_t size);

// Checks if a given string is blank
void check_if_blank(char *line);

// Adds a new contact from user input
void add_contact_from_user(Contacts **head);

// Checks and updates the value of a field if a new value is provided
void check_to_change(char *first, char *second);

// Edits an existing contact based on user input
void edit_contact_from_user(Contacts *head);

// Deletes a contact based on user input
void delete_contact_from_user(Contacts **head);

// Prints details of a single contact
void print_contact(const Contacts *contact);

// Prints the header of the contact details table
void print_header(int total_width);

// Prints the menu for search options
void print_search_menu();

// Compares two strings case-insensitively up to the length of str2
int strcasecmp_partial(const char *str1, const char *str2);

// Searches for a contact based on user input and displays the results
void search_contact_from_user(const Contacts *head);

// Executes the selected option from the menu
void execute_option(Contacts **head, int option);

#endif // MENU_H_INCLUDED
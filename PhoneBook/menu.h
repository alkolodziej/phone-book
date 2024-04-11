#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED
#include "contacts.h"

void display_menu();
void execute_option(Contacts **head, int option);
int get_user_choice();
void clear_screen();
void add_contact_from_user(Contacts **head);
void edit_contact_from_user(Contacts *head);
void delete_contact_from_user(Contacts **head);
void get_line(char *line, long long unsigned length);

#endif // MENU_H_INCLUDED

#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED
#include "contacts.h"

void clear_screen();
int get_user_choice();
void display_menu();
void get_line(char *line, size_t size);
void add_contact_from_user(Contacts **head);
void check_to_change(char *first, char *second);
void check_if_blank(char *line);
void edit_contact_from_user(Contacts *head);
void delete_contact_from_user(Contacts **head);
void execute_option(Contacts **head, int option);
void search_contact_from_user(const Contacts *head);
void print_contact(const Contacts *contact);
void print_header(int total_width);

#endif // MENU_H_INCLUDED

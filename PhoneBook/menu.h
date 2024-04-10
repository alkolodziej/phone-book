#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED
#include "contacts.h"

void display_menu();
void execute_option(Contacts **head, int option);
int get_user_choice();
void clear_screen();

#endif // MENU_H_INCLUDED

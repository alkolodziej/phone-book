#include <stdio.h>
#include "contacts.h"
#include "menu.h"

int main() {
    Contacts *head = NULL;
    load_contacts_from_file(&head, "contacts.csv");
    int option;
    clear_screen();
    do {
        display_menu();
        option = get_user_choice();
        clear_screen();
        execute_option(&head, option);
        if(option!=0) printf("\nPress enter to continue...\n");
        getchar();
        save_contacts_to_file(head, "contacts.csv");
        clear_screen();
    } while(option != 0);
    free_contacts_list(head);
    return 0;
}

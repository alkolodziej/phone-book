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
        if(option!=5) printf("\nPress enter to continue...\n");
        getchar();
        clear_screen();
    } while(option != 5);

    // debug

    // printf("Debug\n");
    // add_contact(&head, "John", "Doe", "123456789", "Main St", "123", "12345", "City1");
    // add_contact(&head, "Jane", "Doe", "987654321", "Second St", "456", "67890", "City2");
    // display_list(head);
    // edit_contact(head, 1, "New Name", "New Last Name", "987654321", "New St", "456", "67890", "New City");
    // edit_contact(head, 3, "New Name", "New Last Name", "987654321", "New St", "456", "67890", "New City");
    // display_list(head);
    // delete_contact(&head, 1);
    // display_list(head);
    // delete_contact(&head, 3);
    return 0;
}

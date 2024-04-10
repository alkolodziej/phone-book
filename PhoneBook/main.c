#include <stdio.h>
#include "contacts.h"

int main() {
    Contacts *head = NULL;
    add_contact(&head, "John", "Doe", "123456789", "Main St", "123", "12345", "City1");
    add_contact(&head, "Jane", "Doe", "987654321", "Second St", "456", "67890", "City2");
    display_list(head);
    edit_contact(head, 1, "New Name", "New Last Name", "987654321", "New St", "456", "67890", "New City");
    edit_contact(head, 3, "New Name", "New Last Name", "987654321", "New St", "456", "67890", "New City");
    display_list(head);
    delete_contact(&head, 1);
    display_list(head);
    delete_contact(&head, 3);
    return 0;
}

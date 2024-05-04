/**
 * @file menu.c
 * @brief Implementation of functions related to the menu and contacts management.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "menu.h"
#include "contacts.h"
#include "colors.h"

// Macro definition to clear the screen depending on the operating system
#ifdef _WIN32
#define CLEAR_SCREEN "cls"
#else
#define CLEAR_SCREEN "clear"
#endif

/**
 * @brief Clear the terminal screen.
 * 
 * This function clears the terminal screen.
 */
void clear_screen() {
    system(CLEAR_SCREEN);
}

/**
 * @brief Get user's choice from the menu.
 * 
 * @return User's choice.
 */
int get_user_choice() {
    int choice;
    printf(COLOR_BOLD "Enter your choice: " COLOR_RESET);
    scanf("%d", &choice);
    getchar(); // Clear input buffer
    return choice;
}

/**
 * @brief Display the main menu.
 * 
 * This function displays the main menu options.
 */
void display_menu() {
    printf(COLOR_BOLD "*********** MENU ***********\n" COLOR_RESET);
    printf(COLOR_YELLOW "1. Display contacts\n");
    printf("2. Add contact\n");
    printf("3. Edit contact\n");
    printf("4. Delete contact\n");
    printf("5. Search contact\n");
    printf(COLOR_BLUE "0. Exit\n" COLOR_RESET);
    printf(COLOR_BOLD "****************************\n" COLOR_RESET);
}

/**
 * @brief Get input line from the user.
 * 
 * @param line Buffer to store the input line.
 * @param size Size of the buffer.
 */
void get_line(char *line, size_t size) {
    fgets(line, (int)size, stdin);
    line[strcspn(line, "\n")] = '\0'; // Remove newline character

    // Check if the length of the input line equals the maximum buffer size
    if (strlen(line) == size - 1) {
        // Clear the input buffer
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF);
    }
}

/**
 * @brief Check if the input line is blank and replace it with a single space if so.
 * 
 * @param line Input line to check.
 */
void check_if_blank(char *line) {
    if (strlen(line) == 0)
        strcpy(line, " ");
}

/**
 * @brief Add a new contact based on user input.
 * 
 * This function prompts the user to input contact details such as name, last name,
 * phone number, address, and adds the new contact to the linked list.
 * 
 * @param head Pointer to the pointer to the head of the contacts linked list.
 */
void add_contact_from_user(Contacts **head) {
    char name[30], last_name[30], phone_number[10];
    char street[30], nr[6], post_code[7], town[30];
    Contacts *new_contact = (Contacts*)malloc(sizeof(Contacts));
    if (new_contact == NULL) {
        fprintf(stderr, COLOR_RED "Memory allocation failed\n" COLOR_RESET);
        exit(EXIT_FAILURE);
    }
    new_contact->next = NULL;

    printf(COLOR_BOLD "Adding new contact\n\n" COLOR_RESET);

    // First name
    printf(COLOR_BOLD "Enter name: " COLOR_RESET);
    get_line(name, sizeof(name));
    check_if_blank(name);
    strcpy(new_contact->name, name);

    // Last name
    printf(COLOR_BOLD "Enter last name: " COLOR_RESET);
    get_line(last_name, sizeof(last_name));
    check_if_blank(last_name);
    strcpy(new_contact->last_name, last_name);

    // Phone number
    printf(COLOR_BOLD "Enter phone number: " COLOR_RESET);
    get_line(phone_number, sizeof(phone_number));
    check_if_blank(phone_number);
    strcpy(new_contact->phone_number, phone_number);

    // Street
    printf(COLOR_BOLD "Enter street: " COLOR_RESET);
    get_line(street, sizeof(street));
    check_if_blank(street);
    strcpy(new_contact->address.street, street);

    // House number
    printf(COLOR_BOLD "Enter house number: " COLOR_RESET);
    get_line(nr, sizeof(nr));
    check_if_blank(nr);
    strcpy(new_contact->address.nr, nr);

    // Post code
    printf(COLOR_BOLD "Enter post code: " COLOR_RESET);
    get_line(post_code, sizeof(post_code));
    check_if_blank(post_code);
    strcpy(new_contact->address.post_code, post_code);
    
    // Town
    printf(COLOR_BOLD "Enter town: " COLOR_RESET);
    get_line(town, sizeof(town));
    check_if_blank(town);
    strcpy(new_contact->address.town, town);

    
    // printf("\n%s %s \t %s \t %s %s \t %s %s\n", name, last_name, phone_number, street, nr, post_code, town);

    if (*head == NULL) {
        new_contact->id = 1; // Assign a unique ID for the first contact
        *head = new_contact;
    } else {
        // Otherwise, find the last element in the list and set its pointer to the next to the new contact
        Contacts *current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        new_contact->id = current->id + 1; // Assign a unique ID
        current->next = new_contact;
    }
    
    printf(COLOR_GREEN "Contact added successfully.\n" COLOR_RESET);
}

/**
 * @brief Check if the second string is not empty and update the first string.
 * 
 * This function checks if the second string is not empty, and if so, it updates the first string with the value of the second string.
 * 
 * @param first Pointer to the first string.
 * @param second Pointer to the second string.
 */
void check_to_change(char *first, char *second)
{
    if (strlen(second) > 0) {
        strcpy(first, second);
    }
}

/**
 * @brief Edit an existing contact based on user input.
 * 
 * This function prompts the user to input the ID of the contact to edit,
 * then allows the user to modify the contact's details.
 * 
 * @param head Pointer to the head of the contacts linked list.
 */
void edit_contact_from_user(Contacts *head) {
    if(NULL != head){
        Contacts *current = head;
        int id;
        char name[30], last_name[30], phone_number[10];
        char street[30], nr[6], post_code[7], town[30];

        printf(COLOR_BOLD "Enter ID of contact to edit: " COLOR_RESET);
        scanf("%d", &id);
        getchar();

        while (current != NULL) {
                if (current->id == id) {
                // Contact with the given ID found, updating data

                // First name
                printf(COLOR_YELLOW "Current name: %s\n" COLOR_RESET, current->name);
                printf(COLOR_BOLD "Enter new name (leave blank to keep current): " COLOR_RESET);
                get_line(name, sizeof(name));

                // Last name
                printf(COLOR_YELLOW "Current last name: %s\n" COLOR_RESET, current->last_name);
                printf(COLOR_BOLD "Enter new last name (leave blank to keep current): " COLOR_RESET);
                get_line(last_name, sizeof(last_name));


                // Phone number
                printf(COLOR_YELLOW "Current phone number: %s\n" COLOR_RESET, current->phone_number);
                printf(COLOR_BOLD "Enter new phone number (leave blank to keep current): " COLOR_RESET);
                get_line(phone_number, sizeof(phone_number));

                // Street
                printf(COLOR_YELLOW "Current street: %s\n" COLOR_RESET, current->address.street);
                printf(COLOR_BOLD "Enter new street (leave blank to keep current): " COLOR_RESET);
                get_line(street, sizeof(street));

                // House number
                printf(COLOR_YELLOW "Current house number: %s\n" COLOR_RESET, current->address.nr);
                printf(COLOR_BOLD "Enter new house number (leave blank to keep current): " COLOR_RESET);
                get_line(nr, sizeof(nr));

                // Post code
                printf(COLOR_YELLOW "Current post code: %s\n" COLOR_RESET, current->address.post_code);
                printf(COLOR_BOLD "Enter new post code (leave blank to keep current): " COLOR_RESET);
                get_line(post_code, sizeof(post_code));

                // Town
                printf(COLOR_YELLOW "Current town: %s\n" COLOR_RESET, current->address.town);
                printf(COLOR_BOLD "Enter new town (leave blank to keep current): " COLOR_RESET);
                get_line(town, sizeof(town));

                // Update data if entered
                check_to_change(current->name, name);
                check_to_change(current->last_name, last_name);
                check_to_change(current->phone_number, phone_number);
                check_to_change(current->address.street, street);
                check_to_change(current->address.nr, nr);
                check_to_change(current->address.post_code, post_code);
                check_to_change(current->address.town, town);

                //save_contacts_to_file(head, "contacts.csv");
                printf(COLOR_GREEN "Contact edited successfully.\n" COLOR_RESET);
                return;
            }
            current = current->next;
        }

        // Contact with the provided ID not found
        printf(COLOR_BLUE "Contact with ID %d not found.\n" COLOR_RESET, id);  
    }   else
        // The list is empty
        printf(COLOR_BLUE "List is empty.\n" COLOR_RESET);

}

/**
 * @brief Delete an existing contact based on user input.
 * 
 * This function prompts the user to input the ID of the contact to delete,
 * then removes the contact from the linked list.
 * 
 * @param head Pointer to the pointer to the head of the contacts linked list.
 */
void delete_contact_from_user(Contacts **head) {
    if(NULL != *head){
        int id;
        printf(COLOR_BOLD "Enter ID of contact to delete: " COLOR_RESET);
        scanf("%d", &id);

        Contacts *current = *head;
        Contacts *prev = NULL;

        // Search the list for the contact with the given ID
        while (current != NULL && current->id != id) {
            prev = current;
            current = current->next;
        }

        // If the contact with the given ID has been found
        if (current != NULL) {
            // If the contact is at the beginning of the list
            if (prev == NULL) {
                *head = current->next;
            } else {
                prev->next = current->next;
            }
            free(current);
            printf(COLOR_GREEN "Contact deleted successfully.\n" COLOR_RESET);
        } else {
            printf(COLOR_BLUE "Contact with ID %d not found.\n" COLOR_RESET, id);
        }
        getchar();
    } else
        // List is empty.
        printf(COLOR_BLUE "List is empty.\n" COLOR_RESET);
}

/**
 * @brief Print the details of a contact.
 * 
 * This function prints the details (ID, name, last name, phone number, address) of a given contact.
 * 
 * @param contact Pointer to the contact whose details are to be printed.
 */
void print_contact(const Contacts *contact) {
    printf("| %-*d| %-*s| %-*s| %-*s| %-*s| %-*s| %-*s| %-*s|\n",
               COLUMN_WIDTH_ID, contact->id, COLUMN_WIDTH_NAME, contact->name, COLUMN_WIDTH_LAST_NAME, contact->last_name,
               COLUMN_WIDTH_PHONE_NUMBER, contact->phone_number, COLUMN_WIDTH_STREET, contact->address.street,
               COLUMN_WIDTH_NR, contact->address.nr, COLUMN_WIDTH_POST_CODE, contact->address.post_code,
               COLUMN_WIDTH_TOWN, contact->address.town);
}

/**
 * @brief Print the header for displaying contact details.
 * 
 * This function prints the header row for displaying contact details in a formatted table.
 * 
 * @param total_width Total width of the table.
 */
void print_header(int total_width)
{
    print_separator(total_width);

    printf(COLOR_BOLD "| %-*s| %-*s| %-*s| %-*s| %-*s| %-*s| %-*s| %-*s|\n" COLOR_RESET,
           COLUMN_WIDTH_ID, "ID", COLUMN_WIDTH_NAME, "Name", COLUMN_WIDTH_LAST_NAME, "Last Name",
           COLUMN_WIDTH_PHONE_NUMBER, "Phone Number", COLUMN_WIDTH_STREET, "Street", COLUMN_WIDTH_NR, "Nr",
           COLUMN_WIDTH_POST_CODE, "Post Code", COLUMN_WIDTH_TOWN, "Town");

    print_separator(total_width);
}

// Function definition for print_search_menu
/**
 * @brief Print the menu for selecting the field to search.
 */
void print_search_menu()
{
    printf(COLOR_BOLD "Choose the field to search:\n" COLOR_RESET);
    printf(COLOR_YELLOW "1. Name \n");
    printf("2. Last Name\n");
    printf("3. Phone Number\n");
    printf("4. Street\n");
    printf("5. House Number\n");
    printf("6. City\n");
    printf("7. Post Code\n" COLOR_RESET);
    printf(COLOR_BLUE "0. Return to menu\n" COLOR_RESET);
}


/**
 * @brief Compare two strings partially, ignoring case.
 * 
 * This function compares two strings partially, character by character, ignoring case sensitivity.
 * It returns 1 if str1 contains str2 as a substring, otherwise returns 0.
 * 
 * @param str1 Pointer to the first string.
 * @param str2 Pointer to the second string.
 * @return int Returns 1 if str1 contains str2 as a substring, otherwise returns 0.
 */
int strcasecmp_partial(const char *str1, const char *str2) {
    // Loop through both strings until one of them reaches the end
    while (*str1 && *str2) {
        // Compare characters of both strings, ignoring case
        if (tolower((unsigned char)*str1) != tolower((unsigned char)*str2))
            return 0; // Return 0 if characters are not equal
        str1++; // Move to the next character in str1
        str2++; // Move to the next character in str2
    }

    // Check if str2 has been fully read
    if (*str2 == '\0')
        return 1; // Return true if str2 has been fully read, indicating str1 contains str2 as a substring
    else
        return 0; // Return false if str2 has not been fully read
}

/**
 * @brief Search for a contact based on user input.
 * 
 * This function allows the user to search for a contact by various fields such as name, last name, phone number, etc.
 * It displays the contacts matching the search criteria.
 * 
 * @param head Pointer to the head of the contacts linked list.
 */
void search_contact_from_user(const Contacts *head) {
    if (head == NULL) {
        printf(COLOR_BLUE "List is empty.\n" COLOR_RESET);
        return;
    }

    int choice = 0;
    char search_value[30];

    print_search_menu();

    do{
        choice = get_user_choice();

    switch (choice) {
        case 1:
            printf(COLOR_BOLD "Enter name to search: " COLOR_RESET);
            break;
        case 2:
            printf(COLOR_BOLD "Enter last name to search: " COLOR_RESET);
            break;
        case 3:
            printf(COLOR_BOLD "Enter phone number to search: " COLOR_RESET);
            break;
        case 4:
            printf(COLOR_BOLD "Enter street to search: " COLOR_RESET);
            break;
        case 5:
            printf(COLOR_BOLD "Enter house number to search: " COLOR_RESET);
            break;
        case 6:
            printf(COLOR_BOLD "Enter city to search: " COLOR_RESET);
            break;
        case 7:
            printf(COLOR_BOLD "Enter post code to search: " COLOR_RESET);
            break;
        case 0:
            return; // Return to main menu
        default:
            printf(COLOR_RED "Invalid option.\n" COLOR_RESET);
    }
    }while(choice>7 || choice<0);

    get_line(search_value, sizeof(search_value));
    check_if_blank(search_value);

    int total_width = COLUMN_WIDTH_ID + COLUMN_WIDTH_NAME + COLUMN_WIDTH_LAST_NAME +
                      COLUMN_WIDTH_PHONE_NUMBER + COLUMN_WIDTH_STREET + COLUMN_WIDTH_NR +
                      COLUMN_WIDTH_POST_CODE + COLUMN_WIDTH_TOWN + 8 * 2 - 1; // X * Y ; X - ilość kolumn, Y - szerokość kolumny z "| "
    
    const Contacts *current = head;
    int found = 0;
    while (current != NULL) {
        switch (choice) {
            case 1:
                if (strcasecmp_partial(current->name, search_value)){
                    found++;
                    if(found == 1)
                        print_header(total_width);
                    print_contact(current);
                }
                break;
            case 2:
                if (strcasecmp_partial(current->last_name, search_value)){
                    found++;
                    if(found == 1)
                        print_header(total_width);
                    print_contact(current);
                }
                break;
            case 3:
                if (strcasecmp_partial(current->phone_number, search_value)){
                    found++;
                    if(found == 1)
                        print_header(total_width);
                    print_contact(current);
                }
                break;
            case 4:
                if (strcasecmp_partial(current->address.street, search_value)){
                    found++;
                    if(found == 1)
                        print_header(total_width);
                    print_contact(current);
                }
                break;
            case 5:
                if (strcasecmp_partial(current->address.nr, search_value)){
                    found++;
                    if(found == 1)
                        print_header(total_width);
                    print_contact(current);
                }
                break;
            case 6:
                if (strcasecmp_partial(current->address.town, search_value)){
                    found++;
                    if(found == 1)
                        print_header(total_width);
                    print_contact(current);
                }
                break;
            case 7:
                if (strcasecmp_partial(current->address.post_code, search_value)){
                    found++;
                    if(found == 1)
                        print_header(total_width);
                    print_contact(current);
                }
                break;
        }
        current = current->next;
    }

    if (!found) {
        printf(COLOR_BLUE "No contact found.\n" COLOR_RESET);
    }else{
        print_separator(total_width);
    }
}

/**
 * @brief Execute the selected option from the menu.
 * 
 * This function executes the appropriate action based on the user's menu choice.
 * 
 * @param head Pointer to the pointer to the head of the contacts linked list.
 * @param option The option selected by the user.
 */
void execute_option(Contacts **head, int option) {
    switch(option) {
        case 0:
            printf(COLOR_BOLD "Exiting program.\n" COLOR_RESET);
            exit(0);
            break;
        case 1:
            display_list(head);
            break;
        case 2:
            add_contact_from_user(head);
            break;
        case 3:
            edit_contact_from_user(*head);
            break;
        case 4:
            delete_contact_from_user(head);
            break;
        case 5:
            search_contact_from_user(*head);
            break;
        default:
            printf(COLOR_RED "Invalid option.\n" COLOR_RESET);
    }
}
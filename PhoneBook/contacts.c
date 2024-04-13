/**
 * @file contacts.c
 * @brief Implementation of functions related to the menu and contacts management.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contacts.h"
#include "sort.h"
#include "colors.h"
#include "menu.h"

/**
 * @brief Saves contacts to a file.
 * 
 * @param head Pointer to the head of the contacts list.
 * @param filename Name of the file to save contacts to.
 */
void save_contacts_to_file(Contacts *head, const char *filename) {
    FILE *file = fopen(filename, "w"); // Open the file for writing
    if (file == NULL) {
        fprintf(stderr, COLOR_RED "Error opening file for writing.\n" COLOR_RESET); // Print error message if file opening fails
        return;
    }

    const Contacts *current = head;
    while (current != NULL) {
        // Write contact information to the file
        fprintf(file, "%d,%s,%s,%s,%s,%s,%s,%s\n",
                current->id, current->name, current->last_name,
                current->phone_number, current->address.street,
                current->address.nr, current->address.post_code,
                current->address.town);
        current = current->next;
    }

    fclose(file); // Close the file
}

/**
 * @brief Loads contacts from a file.
 * 
 * This function reads contact information from a file and creates a linked list
 * of contacts based on the data read from the file.
 * 
 * @param head Pointer to the pointer to the head of the contacts list.
 * @param filename Name of the file to load contacts from.
 */
void load_contacts_from_file(Contacts **head, const char *filename) {
    FILE *file = fopen(filename, "a+"); // Open the file for reading and appending
    if (file == NULL) {
        fprintf(stderr, COLOR_RED "Error opening file for reading.\n" COLOR_RESET); // Print error message if file opening fails
        return;
    }

    int id;
    char name[30], last_name[30], phone_number[10];
    char street[30], nr[6], post_code[7], town[30];
    Contacts *current_contact = NULL;
    
    // Read contact information from the file
    while (fscanf(file, "%d,%29[^,],%29[^,],%9[^,],%29[^,],%5[^,],%6[^,],%29[^\n]",
               &id, name, last_name, phone_number, street, nr, post_code, town)==8) {
        // Allocate memory for a new contact
        Contacts *new_contact = (Contacts*)malloc(sizeof(Contacts));
        if (new_contact == NULL) {
            fprintf(stderr, COLOR_RED "Memory allocation failed\n" COLOR_RESET); // Print error message if memory allocation fails
            exit(EXIT_FAILURE); // Terminate the program if memory allocation fails
        }
        new_contact->next = NULL;
        
        // Initialize the new contact with the read data
        new_contact->id = id;
        strcpy(new_contact->name, name);
        strcpy(new_contact->last_name, last_name);
        strcpy(new_contact->phone_number, phone_number);
        strcpy(new_contact->address.street, street);
        strcpy(new_contact->address.nr, nr);
        strcpy(new_contact->address.post_code, post_code);
        strcpy(new_contact->address.town, town);

        if (*head == NULL) {
            // If the list is empty, set the new contact as the head of the list
            *head = new_contact;
            current_contact = new_contact; // Set the current contact to the new contact
        } else {
            // Otherwise, append the new contact to the end of the list
            current_contact->next = new_contact;
            current_contact = new_contact; // Update the current contact
        }
    }

    fclose(file); // Close the file
}

/**
 * @brief Prints a separator line.
 * 
 * This function prints a horizontal separator line composed of '-' characters
 * enclosed by '+' characters at the beginning and end.
 * 
 * @param total_width Total width of the separator line.
 */
void print_separator(int total_width) {
    putchar('+'); // Print the starting '+' character
    for (int i = 0; i < total_width; i++) {
        putchar('-'); // Print '-' characters to create the separator line
    }
    putchar('+'); // Print the ending '+' character
    putchar('\n'); // Move to the next line after printing the separator
}

/**
 * @brief Displays the sorting menu.
 * 
 * This function prints the sorting menu options to the console, allowing the user
 * to choose the sorting criteria.
 */
void display_sorting_menu() {
    printf(COLOR_BOLD "SORTING MENU:\n" COLOR_RESET);
    printf(COLOR_YELLOW "1. Sort by ID (default)\n");
    printf("2. Sort by name\n");
    printf("3. Sort by last name\n");
    printf("4. Sort by phone number\n");
    printf("5. Sort by town\n");
    printf("6. Sort by post code\n" COLOR_RESET);
    printf(COLOR_BLUE "0. Back to main menu\n" COLOR_RESET);
}

/**
 * @brief Displays the ascending/descending sorting menu.
 * 
 * This function prints the ascending/descending sorting options to the console,
 * allowing the user to choose the sorting order.
 */
void display_ascending_descending_menu(){
    printf(COLOR_BOLD "SELECT SORTING ORDER:\n" COLOR_RESET);
    printf(COLOR_YELLOW "1. Ascending\n");
    printf("2. Descending\n" COLOR_RESET);
    printf(COLOR_BLUE "3. Cancel\n" COLOR_RESET);
}

/**
 * @brief Displays the contacts list.
 * 
 * This function displays the contacts list in a formatted table.
 * 
 * @param headRef Pointer to the pointer to the head of the contacts list.
 */
void display_list(Contacts **headRef) {
    Contacts *head = *headRef;
    int sorting_mode = 1;
    int order = 1;

    do {
        clear_screen(); // Clear the screen for better readability
        puts(""); // Print an empty line

        if (head == NULL) {
            puts(COLOR_BLUE "There are no contacts in the list." COLOR_RESET);
            return;
        }

        // Sorting the contacts list
        if (sorting_mode > 0 && sorting_mode < 7)
            mergeSort(headRef, get_comparator(sorting_mode), order);
        else
            mergeSort(headRef, compareByID, 1);

        // Calculating the total width of the separator
        int total_width = COLUMN_WIDTH_ID + COLUMN_WIDTH_NAME + COLUMN_WIDTH_LAST_NAME +
                          COLUMN_WIDTH_PHONE_NUMBER + COLUMN_WIDTH_STREET + COLUMN_WIDTH_NR +
                          COLUMN_WIDTH_POST_CODE + COLUMN_WIDTH_TOWN + 8 * 2 - 1; // X * Y ; X - number of columns, Y - width of column with "| "

        print_separator(total_width); // Print the separator line

        // Printing column headers
        printf(COLOR_BOLD "| %-*s| %-*s| %-*s| %-*s| %-*s| %-*s| %-*s| %-*s|\n" COLOR_RESET,
               COLUMN_WIDTH_ID, "ID", COLUMN_WIDTH_NAME, "Name", COLUMN_WIDTH_LAST_NAME, "Last Name",
               COLUMN_WIDTH_PHONE_NUMBER, "Phone Number", COLUMN_WIDTH_STREET, "Street", COLUMN_WIDTH_NR, "Nr",
               COLUMN_WIDTH_POST_CODE, "Post Code", COLUMN_WIDTH_TOWN, "Town");

        print_separator(total_width); // Print the separator line

        // Printing contact data in column format
        Contacts *current = *headRef;
        while (current != NULL) {
            printf("| %-*d| %-*s| %-*s| %-*s| %-*s| %-*s| %-*s| %-*s|\n",
                   COLUMN_WIDTH_ID, current->id, COLUMN_WIDTH_NAME, current->name, COLUMN_WIDTH_LAST_NAME, current->last_name,
                   COLUMN_WIDTH_PHONE_NUMBER, current->phone_number, COLUMN_WIDTH_STREET, current->address.street,
                   COLUMN_WIDTH_NR, current->address.nr, COLUMN_WIDTH_POST_CODE, current->address.post_code,
                   COLUMN_WIDTH_TOWN, current->address.town);

            current = current->next;
        }

        print_separator(total_width); // Print the separator line

        display_sorting_menu(); // Display the sorting menu
        sorting_mode = get_user_choice(); // Update sorting mode for the next iteration
        if (sorting_mode >= 1 && sorting_mode <= 6) {
            display_ascending_descending_menu(); // Display the ascending/descending menu
            do {
                int order_choice = get_user_choice();
                if (order_choice == 2) {
                    order = -1; // Set order to descending
                } 
                else if(order_choice == 1) {
                    order = 1; // Default to ascending order
                }
                else if(order_choice == 3){
                    break;
                } else {
                    printf(COLOR_RED "WRONG OPTION!" COLOR_RESET);
                }
            } while(order != 1 && order != -1);
        }
    } while (sorting_mode != 0); // Repeat until the user chooses to exit
    mergeSort(headRef, compareByID, 1); // Sort the list by ID before exiting
}

/**
 * @brief Frees the memory allocated for the contacts list.
 * 
 * This function iterates through the contacts list and frees the memory allocated
 * for each contact node, including the memory for the contact's data structure.
 * 
 * @param head Pointer to the head of the contacts list.
 */
void free_contacts_list(Contacts *head) {
    Contacts *current = head;
    while (current != NULL) {
        Contacts *temp = current; // Store the current node temporarily
        current = current->next; // Move to the next node
        free(temp); // Free the memory for the current node
    }
}
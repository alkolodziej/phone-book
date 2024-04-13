/**
 * @file main.c
 * @brief The main entry point for the phone book application.
 */

#include <stdio.h>
#include "contacts.h"
#include "menu.h"

/**
 * @brief The main function.
 * 
 * This function serves as the entry point for the phone book application.
 * It loads contacts from a file, displays the main menu, and executes user-selected options
 * until the user chooses to exit the program.
 * 
 * @return 0 upon successful execution.
 */
int main() {
    Contacts *head = NULL; ///< Pointer to the head of the contacts linked list.

    // Load contacts from file
    load_contacts_from_file(&head, "contacts.csv");

    int option; ///< Variable to store user's menu choice.

    clear_screen(); // Clear the screen before displaying the menu

    // Main loop to display menu, get user choice, and execute selected option
    do {
        display_menu(); // Display the main menu
        option = get_user_choice(); // Get user's menu choice
        clear_screen(); // Clear the screen before executing the option
        execute_option(&head, option); // Execute the user-selected option

        // Prompt the user to press enter to continue, except when exiting the program
        if (option != 0) 
            printf("\nPress enter to continue...\n");
        getchar(); // Wait for user to press enter

        save_contacts_to_file(head, "contacts.csv"); // Save contacts to file after each operation

        clear_screen(); // Clear the screen before displaying the menu again

    } while(option != 0); // Continue until the user chooses to exit the program

    free_contacts_list(head); // Free dynamically allocated memory for the contacts linked list

    return 0; // Return 0 to indicate successful execution
}
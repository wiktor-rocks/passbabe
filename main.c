/*

Resources:

- How to read from csv files
    - Read CSV File Data Into An Array Of Structs | C Programming Example - YouTube
      [Online video]. Available at: https://www.youtube.com/watch?v=rbVt5v8NNe8&t=2s

- How to use multiple files in C
    - Multiple Files in C (Header and Source Files) - YouTube
      [Online video]. Available at: https://www.youtube.com/watch?v=bHA_pavoVG8

- Kernighan, B. W., & Ritchie, D. M. (1988). The C Programming Language.

- Abelson, H., Sussman, G. J., & Sussman, J. (1996). Structure and Interpretation of Computer Programs.

- CS50 DUCK ai

- CS50 notes related to C.

*/



#include "helpers.h"
#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>

// Menu options
#define QUIT_PROGRAM 0
#define ADD_ENTRY 1
#define LIST_ENTRIES 2
#define DELETE_ENTRY 3
#define ADD_DATABASE 4

int main(void)
{
    // Create db directory
    struct stat st = {0};

    if (stat("~/.config/passbabe", &st) == -1)
    {
        mkdir("~/.config/passbabe", 0700);
    }


    // Define menu options.
    const char *menu[] = {
    "0. Quit",
    "1. Add New Entry",
    "2. List Entries",
    "3. Delete Entry",
    "4. Add New Database"
    };

    // Clear the screen
    printf("\033[2J");

    // Print menu options to user.
    printf("-----------------------------------------------\n   PassBabe Password Manager (For The Chads)   "
           "\n-----------------------------------------------\n");

    printf("\n");

    while (1)
    {

        for (int i = 0, n = sizeof(menu) / sizeof(menu[0]); i < n; i++)
        {
            printf("%s\n", menu[i]);
        }

        printf("\n");

        // Get option from user.
        int user_menu_option = 0;

        printf(">>: ");
        if (scanf("%d", &user_menu_option) == -1)
        {
            user_menu_option = -1;
        }

        printf("\n");

        printf("\033[2J");
        switch (user_menu_option)
        {
            case QUIT_PROGRAM:
                return 0;

            case ADD_ENTRY:
                add_entry();
                printf("\033[2J");
                break;

            case LIST_ENTRIES:
                list_entries();
                printf("\033[2J");
                break;

            case DELETE_ENTRY:
                break;

            case ADD_DATABASE:
                add_database();
                printf("\033[2J");
                break;

            default:
                printf("Invalid input.\n");
                break;
        }
    }

    return 0;
}
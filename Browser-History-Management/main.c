
/*
 * main.c -- Main Module
 * Browser History Management System
 * DSA Lab Project
 */

#include "browser.h"

/* Global variables */
HistoryNode *head = NULL;
HistoryNode *tail = NULL;
HistoryNode *current = NULL;

Stack backStack;
Stack forwardStack;

BookmarkNode *bookmarkHead = NULL;

/* Read input safely */
int readLine(char *buffer, int size)
{
    size_t length;
    int ch;

    if (fgets(buffer, size, stdin) == NULL)
        return 0;

    length = strlen(buffer);

    if (length > 0 && buffer[length - 1] == '\n')
    {
        buffer[length - 1] = '\0';
    }
    else
    {
        while ((ch = getchar()) != '\n' && ch != EOF)
        {
            /* Clear extra input */
        }
    }

    return 1;
}

/* Display main menu */
void displayMenu(void)
{
    printf("\n");
    printf("============================================\n");
    printf("       BROWSER HISTORY MANAGEMENT SYSTEM\n");
    printf("============================================\n");

    printf("1.  Visit New Website\n");
    printf("2.  Go Back\n");
    printf("3.  Go Forward\n");
    printf("4.  Display Current Page\n");
    printf("5.  Display Browsing History\n");
    printf("6.  Search History\n");
    printf("7.  Delete History by Position\n");
    printf("8.  Delete History by URL\n");
    printf("9.  Clear Complete History\n");
    printf("10. Bookmark Manager\n");
    printf("11. Save History to File\n");
    printf("12. Load History from File\n");
    printf("0.  Exit\n");

    printf("============================================\n");
    printf("Enter your choice: ");
}

/* Main function */
int main(void)
{
    char choice[INPUT_SIZE];

    /* Initialize navigation stacks */
    initStack(&backStack);
    initStack(&forwardStack);

    printf("\nWelcome to Browser History Management System!\n");

    while (1)
    {
        displayMenu();

        if (!readLine(choice, sizeof(choice)))
        {
            printf("\nInput ended. Exiting program.\n");
            break;
        }

        if (strcmp(choice, "1") == 0)
        {
            visitPage();
        }
        else if (strcmp(choice, "2") == 0)
        {
            goBack();
        }
        else if (strcmp(choice, "3") == 0)
        {
            goForward();
        }
        else if (strcmp(choice, "4") == 0)
        {
            displayCurrentPage();
        }
        else if (strcmp(choice, "5") == 0)
        {
            displayHistory();
        }
        else if (strcmp(choice, "6") == 0)
        {
            searchHistory();
        }
        else if (strcmp(choice, "7") == 0)
        {
            deletePage();
        }
        else if (strcmp(choice, "8") == 0)
        {
            deleteByURL();
        }
        else if (strcmp(choice, "9") == 0)
        {
            clearHistory();
        }
        else if (strcmp(choice, "10") == 0)
        {
            bookmarkMenu();
        }
        else if (strcmp(choice, "11") == 0)
        {
            saveHistory();
        }
        else if (strcmp(choice, "12") == 0)
        {
            loadHistory();
        }
        else if (strcmp(choice, "0") == 0)
        {
            printf("\nThank you for using Browser History Management System!\n");
            break;
        }
        else
        {
            printf("\n[!] Invalid choice. Please enter 0-12.\n");
        }
    }

    /* Release dynamically allocated memory */
    freeAllMemory();

    return 0;
}

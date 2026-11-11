
/*
 * bookmarks.c -- Module 5: Bookmark Management
 * DSA Concepts: Singly Linked List, Insertion,
 * Traversal, Linear Search and Deletion.
 */

#include "browser.h"

/* Validate bookmark URL */
static int isValidBookmarkURL(const char *url)
{
    int i;
    int length = strlen(url);
    int hasDot = 0;

    if (length < 3)
        return 0;

    for (i = 0; i < length; i++)
    {
        if (isspace((unsigned char)url[i]))
            return 0;

        if (url[i] == '.')
            hasDot = 1;
    }

    return hasDot;
}

/* Add a new bookmark */
void addBookmark(void)
{
    char url[MAX_URL];
    char title[MAX_TITLE];

    BookmarkNode *newNode;
    BookmarkNode *temp;

    printf("\nEnter website URL: ");

    if (!readLine(url, sizeof(url)))
        return;

    if (!isValidBookmarkURL(url))
    {
        printf("[!] Invalid URL. Please enter a valid URL.\n");
        return;
    }

    /* Check duplicate bookmark */
    for (temp = bookmarkHead; temp != NULL; temp = temp->next)
    {
        if (equalsIgnoreCase(temp->url, url))
        {
            printf("[!] This website is already bookmarked.\n");
            return;
        }
    }

    printf("Enter website title: ");

    if (!readLine(title, sizeof(title)))
        return;

    if (title[0] == '\0')
    {
        printf("[!] Website title cannot be empty.\n");
        return;
    }

    newNode = (BookmarkNode *)malloc(sizeof(BookmarkNode));

    if (newNode == NULL)
    {
        printf("[!] Memory allocation failed.\n");
        return;
    }

    strcpy(newNode->url, url);
    strcpy(newNode->title, title);
    newNode->next = NULL;

    /* Insert at the end of bookmark list */
    if (bookmarkHead == NULL)
    {
        bookmarkHead = newNode;
    }
    else
    {
        temp = bookmarkHead;

        while (temp->next != NULL)
        {
            temp = temp->next;
        }

        temp->next = newNode;
    }

    printf("\n[OK] Bookmark added successfully!\n");
    printf("Website: %s\n", newNode->title);
    printf("URL: %s\n", newNode->url);
}

/* Display all bookmarks */
void displayBookmarks(void)
{
    BookmarkNode *temp;
    int position = 1;

    if (bookmarkHead == NULL)
    {
        printf("\n[i] No bookmarks available.\n");
        return;
    }

    printf("\n========== SAVED BOOKMARKS ==========\n");

    for (temp = bookmarkHead; temp != NULL; temp = temp->next)
    {
        printf("\n%d. Website: %s\n", position, temp->title);
        printf("   URL: %s\n", temp->url);

        position++;
    }

    printf("\n=====================================\n");
    printf("Total bookmarks: %d\n", position - 1);
}

/* Search bookmark by title or URL */
void searchBookmark(void)
{
    char key[INPUT_SIZE];
    BookmarkNode *temp;
    int found = 0;

    if (bookmarkHead == NULL)
    {
        printf("\n[i] No bookmarks available to search.\n");
        return;
    }

    printf("\nEnter website title or URL to search: ");

    if (!readLine(key, sizeof(key)))
        return;

    if (key[0] == '\0')
    {
        printf("[!] Search text cannot be empty.\n");
        return;
    }

    printf("\nSearch Results:\n");

    for (temp = bookmarkHead; temp != NULL; temp = temp->next)
    {
        if (containsIgnoreCase(temp->title, key) ||
            containsIgnoreCase(temp->url, key))
        {
            printf("\nWebsite: %s\n", temp->title);
            printf("URL: %s\n", temp->url);
            found++;
        }
    }

    if (found == 0)
    {
        printf("\n[x] Bookmark not found.\n");
    }
    else
    {
        printf("\n[OK] %d bookmark(s) found.\n", found);
    }
}

/* Delete bookmark by URL */
void deleteBookmark(void)
{
    char url[MAX_URL];

    BookmarkNode *temp;
    BookmarkNode *previous = NULL;

    if (bookmarkHead == NULL)
    {
        printf("\n[i] No bookmarks available to delete.\n");
        return;
    }

    printf("\nEnter URL of bookmark to delete: ");

    if (!readLine(url, sizeof(url)))
        return;

    if (url[0] == '\0')
    {
        printf("[!] URL cannot be empty.\n");
        return;
    }

    temp = bookmarkHead;

    while (temp != NULL)
    {
        if (equalsIgnoreCase(temp->url, url))
        {
            if (previous == NULL)
            {
                bookmarkHead = temp->next;
            }
            else
            {
                previous->next = temp->next;
            }

            free(temp);

            printf("\n[-] Bookmark deleted successfully.\n");
            return;
        }

        previous = temp;
        temp = temp->next;
    }

    printf("\n[x] Bookmark not found.\n");
}

/* Bookmark management menu */
void bookmarkMenu(void)
{
    char choice[INPUT_SIZE];

    while (1)
    {
        printf("\n========== BOOKMARK MANAGER ==========\n");
        printf("1. Add Bookmark\n");
        printf("2. Display Bookmarks\n");
        printf("3. Search Bookmark\n");
        printf("4. Delete Bookmark\n");
        printf("0. Back to Main Menu\n");
        printf("======================================\n");

        printf("Enter your choice: ");

        if (!readLine(choice, sizeof(choice)))
            return;

        if (strcmp(choice, "1") == 0)
        {
            addBookmark();
        }
        else if (strcmp(choice, "2") == 0)
        {
            displayBookmarks();
        }
        else if (strcmp(choice, "3") == 0)
        {
            searchBookmark();
        }
        else if (strcmp(choice, "4") == 0)
        {
            deleteBookmark();
        }
        else if (strcmp(choice, "0") == 0)
        {
            printf("\nReturning to Main Menu...\n");
            return;
        }
        else
        {
            printf("\n[!] Invalid choice. Try again.\n");
        }
    }
}

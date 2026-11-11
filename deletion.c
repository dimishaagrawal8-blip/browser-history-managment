
/*
 * deletion.c -- Module 4: History Deletion
 * DSA Concepts: Doubly Linked List Deletion,
 * Dynamic Memory Management.
 */

#include "browser.h"

/* Free all history nodes and navigation stacks */
void freeAllMemory(void)
{
    HistoryNode *temp;

    while (head != NULL)
    {
        temp = head;
        head = head->next;
        free(temp);
    }

    head = NULL;
    tail = NULL;
    current = NULL;

    clearStack(&backStack);
    clearStack(&forwardStack);

    /* Free bookmark nodes */
    while (bookmarkHead != NULL)
    {
        BookmarkNode *bookmarkTemp = bookmarkHead;
        bookmarkHead = bookmarkHead->next;
        free(bookmarkTemp);
    }

    bookmarkHead = NULL;
}

/* Delete a history node safely */
static int removeHistoryNode(HistoryNode *target)
{
    char deletedUrl[MAX_URL];

    if (target == NULL)
        return 0;

    strcpy(deletedUrl, target->url);

    /* Update current page if target is current */
    if (target == current)
    {
        if (target->prev != NULL)
            current = target->prev;
        else
            current = target->next;
    }

    /* Update previous node */
    if (target->prev != NULL)
        target->prev->next = target->next;
    else
        head = target->next;

    /* Update next node */
    if (target->next != NULL)
        target->next->prev = target->prev;
    else
        tail = target->prev;

    free(target);

    /* Rebuild navigation stacks */
    if (!rebuildStacks())
    {
        printf("[!] Navigation update failed. Clearing history.\n");
        freeAllMemory();
        return -1;
    }

    printf("\n[-] Deleted website: %s\n", deletedUrl);

    if (current != NULL)
        printf("[i] Current page: %s\n", current->url);
    else
        printf("[i] History is now empty.\n");

    return 1;
}

/* Delete history page by position */
void deletePage(void)
{
    char input[INPUT_SIZE];
    char *endPtr;
    long number;
    int total, i;
    HistoryNode *target;

    if (head == NULL)
    {
        printf("\n[i] History is empty. Nothing to delete.\n");
        return;
    }

    displayHistory();
    total = countHistory();

    printf("\nEnter position number to delete (1-%d): ", total);

    if (!readLine(input, sizeof(input)))
        return;

    number = strtol(input, &endPtr, 10);

    if (input[0] == '\0' || *endPtr != '\0')
    {
        printf("[!] Please enter a valid number.\n");
        return;
    }

    if (number < 1 || number > total)
    {
        printf("[!] Invalid position.\n");
        return;
    }

    target = head;

    for (i = 1; i < number; i++)
        target = target->next;

    removeHistoryNode(target);
}

/* Delete history entries by URL */
void deleteByURL(void)
{
    char url[MAX_URL];
    HistoryNode *temp;
    HistoryNode *next;
    int deleted = 0;

    if (head == NULL)
    {
        printf("\n[i] History is empty.\n");
        return;
    }

    printf("\nEnter URL to delete: ");

    if (!readLine(url, sizeof(url)))
        return;

    if (url[0] == '\0')
    {
        printf("[!] URL cannot be empty.\n");
        return;
    }

    temp = head;

    while (temp != NULL)
    {
        next = temp->next;

        if (equalsIgnoreCase(temp->url, url))
        {
            /* Update current before removing */
            int result = removeHistoryNode(temp);

            if (result == -1)
                return;

            deleted++;
        }

        temp = next;
    }

    if (deleted == 0)
        printf("\n[x] URL not found in history.\n");
    else
        printf("\n[OK] %d matching history record(s) deleted.\n", deleted);
}

/* Clear complete browsing history */
void clearHistory(void)
{
    char answer[INPUT_SIZE];
    int total;

    if (head == NULL)
    {
        printf("\n[i] History is already empty.\n");
        return;
    }

    total = countHistory();

    printf("\nThis will delete all %d history records.\n", total);
    printf("Are you sure? (y/n): ");

    if (!readLine(answer, sizeof(answer)))
        return;

    if (answer[0] != 'y' && answer[0] != 'Y')
    {
        printf("[i] Clear history cancelled.\n");
        return;
    }

    /* Clear history and navigation stacks */
    HistoryNode *temp;

    while (head != NULL)
    {
        temp = head;
        head = head->next;
        free(temp);
    }

    head = NULL;
    tail = NULL;
    current = NULL;

    clearStack(&backStack);
    clearStack(&forwardStack);

    printf("\n[-] All %d history records deleted.\n", total);
    printf("[i] Back and Forward navigation stacks cleared.\n");
}

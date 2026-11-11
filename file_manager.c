
/*
 * file_manager.c -- Module 6: File Management
 * DSA Concepts: Linked List Traversal and File Handling.
 */

#include "browser.h"

/* File used to store browsing history */
#define HISTORY_FILE "browser_history.txt"

/* Save browsing history into a file */
int saveHistory(void)
{
    FILE *fp;
    HistoryNode *temp;
    int count = 0;

    fp = fopen(HISTORY_FILE, "w");

    if (fp == NULL)
    {
        printf("\n[!] Unable to open history file for saving.\n");
        return 0;
    }

    fprintf(fp, "URL\tTITLE\tTIME\tCOUNT\n");

    for (temp = head; temp != NULL; temp = temp->next)
    {
        fprintf(fp, "%s\t%s\t%s\t%d\n",
                temp->url,
                temp->title,
                temp->visitTime,
                temp->visitCount);

        count++;
    }

    if (fclose(fp) != 0)
    {
        printf("\n[!] Error while closing history file.\n");
        return 0;
    }

    printf("\n[OK] History saved successfully!\n");
    printf("Total records saved: %d\n", count);

    return 1;
}

/* Load browsing history from a file */
int loadHistory(void)
{
    FILE *fp;
    char line[INPUT_SIZE + MAX_TITLE + MAX_TIME];
    char *url, *title, *visitTime, *visitCountText;
    char *endPtr;
    long visitCount;

    HistoryNode *newNode;
    HistoryNode *temp;
    int loaded = 0;

    fp = fopen(HISTORY_FILE, "r");

    if (fp == NULL)
    {
        printf("\n[!] History file not found.\n");
        return 0;
    }

    /* Remove old history records */
    while (head != NULL)
    {
        temp = head;
        head = head->next;
        free(temp);
    }

    head = NULL;
    tail = NULL;
    current = NULL;

    /* Clear old navigation stacks */
    clearStack(&backStack);
    clearStack(&forwardStack);

    /* Skip the header line */
    if (fgets(line, sizeof(line), fp) == NULL)
    {
        fclose(fp);
        printf("\n[!] History file is empty.\n");
        return 0;
    }

    /* Read saved records */
    while (fgets(line, sizeof(line), fp) != NULL)
    {
        line[strcspn(line, "\r\n")] = '\0';

        url = strtok(line, "\t");
        title = strtok(NULL, "\t");
        visitTime = strtok(NULL, "\t");
        visitCountText = strtok(NULL, "\t");

        if (url == NULL || title == NULL ||
            visitTime == NULL || visitCountText == NULL)
        {
            continue;
        }

        if (strlen(url) >= MAX_URL ||
            strlen(title) >= MAX_TITLE ||
            strlen(visitTime) >= MAX_TIME)
        {
            continue;
        }

        visitCount = strtol(visitCountText, &endPtr, 10);

        if (*visitCountText == '\0' || *endPtr != '\0' ||
            visitCount < 1 || visitCount > 2147483647L)
        {
            continue;
        }

        newNode = (HistoryNode *)malloc(sizeof(HistoryNode));

        if (newNode == NULL)
        {
            printf("\n[!] Memory allocation failed.\n");
            break;
        }

        strcpy(newNode->url, url);
        strcpy(newNode->title, title);
        strcpy(newNode->visitTime, visitTime);
        newNode->visitCount = (int)visitCount;

        newNode->prev = tail;
        newNode->next = NULL;

        if (head == NULL)
        {
            head = newNode;
        }
        else
        {
            tail->next = newNode;
        }

        tail = newNode;
        loaded++;
    }

    fclose(fp);

    /* Set latest loaded page as current */
    current = tail;

    if (!rebuildStacks())
    {
        printf("\n[!] Navigation stack update failed.\n");

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

        return 0;
    }

    printf("\n[OK] History loaded successfully!\n");
    printf("Total records loaded: %d\n", loaded);

    return 1;
}

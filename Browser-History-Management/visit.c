
/*
 * visit.c -- Module 1: Visit Page
 * DSA Concepts:
 * 1. Doubly Linked List
 * 2. Dynamic Memory Allocation
 * 3. Searching and Updating Records
 */

#include "browser.h"
#include <time.h>

/* ---------- URL Validation ---------- */

static int isValidUrl(const char *url)
{
    size_t i, len = strlen(url);
    int hasDot = 0;

    if (len < 3)
        return 0;

    for (i = 0; i < len; i++)
    {
        if (isspace((unsigned char)url[i]))
            return 0;

        if (url[i] == '.')
            hasDot = 1;
    }

    return hasDot;
}

/* ---------- Generate Current Date and Time ---------- */

static void getCurrentTime(char *buffer, size_t size)
{
    time_t now;
    struct tm *timeInfo;

    now = time(NULL);
    timeInfo = localtime(&now);

    if (timeInfo == NULL)
    {
        snprintf(buffer, size, "Time unavailable");
        return;
    }

    strftime(buffer, size, "%d-%m-%Y %I:%M:%S %p", timeInfo);
}

/* ---------- Generate Website Title ---------- */

static void generateTitle(const char *url, char *title, size_t size)
{
    const char *start = url;
    const char *www = "www.";

    if (strncmp(start, "https://", 8) == 0)
        start += 8;
    else if (strncmp(start, "http://", 7) == 0)
        start += 7;

    if (strncmp(start, www, 4) == 0)
        start += 4;

    snprintf(title, size, "%s", start);
}

/* ---------- Visit New Website ---------- */

void visitPage(void)
{
    char url[INPUT_SIZE];

    HistoryNode *newNode;
    HistoryNode *temp;
    HistoryNode *next;

    int removed = 0;

    printf("\n========== VISIT NEW WEBSITE ==========\n");

    printf("Enter website URL: ");

    if (!readLine(url, sizeof(url)))
        return;

    if (url[0] == '\0')
    {
        printf("[!] URL cannot be empty.\n");
        return;
    }

    if (strlen(url) >= MAX_URL)
    {
        printf("[!] URL is too long.\n");
        return;
    }

    if (!isValidUrl(url))
    {
        printf("[!] Invalid URL. Please enter a valid URL.\n");
        return;
    }

    /* Check if current website is the same */

    if (current != NULL && equalsIgnoreCase(current->url, url))
    {
        printf("[!] You are already on this page.\n");
        return;
    }

    /* Check whether URL already exists in history */

    temp = head;

    while (temp != NULL)
    {
        if (equalsIgnoreCase(temp->url, url))
        {
            temp->visitCount++;

            getCurrentTime(temp->visitTime, sizeof(temp->visitTime));

            printf("\n[i] Previously visited website found.\n");
            printf("[+] Visit count updated: %d\n", temp->visitCount);

            /* Continue navigation to this existing page */
            break;
        }

        temp = temp->next;
    }

    /* Create a new node only if URL does not exist */

    if (temp == NULL)
    {
        newNode = (HistoryNode *)malloc(sizeof(HistoryNode));

        if (newNode == NULL)
        {
            printf("[!] Memory allocation failed.\n");
            return;
        }

        strcpy(newNode->url, url);

        generateTitle(url, newNode->title, sizeof(newNode->title));

        getCurrentTime(newNode->visitTime, sizeof(newNode->visitTime));

        newNode->visitCount = 1;

        newNode->prev = NULL;
        newNode->next = NULL;
    }
    else
    {
        newNode = temp;
    }

    /* First website visit */

    if (current == NULL)
    {
        if (newNode->prev == NULL && newNode->next == NULL)
        {
            head = tail = current = newNode;
        }
    }
    else
    {
        /* Push current page into Back stack */

        if (!push(&backStack, current))
        {
            printf("[!] Unable to update navigation stack.\n");

            if (temp == NULL)
                free(newNode);

            return;
        }

        /* Remove forward history after current page */

        temp = current->next;

        while (temp != NULL)
        {
            next = temp->next;

            /* Do not free an existing history node */
            if (temp != newNode)
            {
                free(temp);
                removed++;
            }

            temp = next;
        }

        current->next = NULL;
        tail = current;

        clearStack(&forwardStack);

        /* Link the selected page after current */

        if (newNode != current)
        {
            newNode->prev = current;
            newNode->next = NULL;

            current->next = newNode;

            tail = newNode;
            current = newNode;
        }
    }

    printf("\n========== WEBSITE DETAILS ==========\n");

    printf("Website URL   : %s\n", current->url);
    printf("Website Title : %s\n", current->title);
    printf("Visit Time    : %s\n", current->visitTime);
    printf("Visit Count   : %d\n", current->visitCount);

    if (removed > 0)
    {
        printf("[i] Forward history cleared: %d page(s).\n", removed);
    }

    printf("[+] Website opened successfully.\n");
}

/* ---------- Display Current Page ---------- */

void displayCurrentPage(void)
{
    printf("\n========== CURRENT PAGE ==========\n");

    if (current == NULL)
    {
        printf("[i] No page is currently open.\n");
        return;
    }

    printf("Website Title : %s\n", current->title);
    printf("Website URL   : %s\n", current->url);
    printf("Last Visit    : %s\n", current->visitTime);
    printf("Visit Count   : %d\n", current->visitCount);

    printf("----------------------------------\n");

    printf("Back Pages    : %d\n", backStack.size);
    printf("Forward Pages : %d\n", forwardStack.size);

    printf("==================================\n");
}

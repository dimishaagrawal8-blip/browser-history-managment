
/*
 * history.c -- Module 3: History Display and Search
 * DSA Concepts: Doubly Linked List Traversal, Linear Search.
 */

#include "browser.h"

/* Count total history records */
int countHistory(void)
{
    int count = 0;
    HistoryNode *n;

    for (n = head; n != NULL; n = n->next)
    {
        count++;
    }

    return count;
}

/* Count unique URLs (case-insensitive) */
int countUniqueURLs(void)
{
    HistoryNode *n, *temp;
    int uniqueCount = 0;
    int alreadyExists;

    for (n = head; n != NULL; n = n->next)
    {
        alreadyExists = 0;

        for (temp = head; temp != n; temp = temp->next)
        {
            if (equalsIgnoreCase(temp->url, n->url))
            {
                alreadyExists = 1;
                break;
            }
        }

        if (!alreadyExists)
        {
            uniqueCount++;
        }
    }

    return uniqueCount;
}

/* Compare two strings ignoring case */
int equalsIgnoreCase(const char *a, const char *b)
{
    while (*a != '\0' && *b != '\0')
    {
        if (tolower((unsigned char)*a) !=
            tolower((unsigned char)*b))
        {
            return 0;
        }

        a++;
        b++;
    }

    return *a == *b;
}

/* Search substring ignoring case */
int containsIgnoreCase(const char *text, const char *pattern)
{
    size_t i, j;
    size_t textLength = strlen(text);
    size_t patternLength = strlen(pattern);

    if (patternLength == 0)
        return 1;

    if (patternLength > textLength)
        return 0;

    for (i = 0; i + patternLength <= textLength; i++)
    {
        for (j = 0; j < patternLength; j++)
        {
            if (tolower((unsigned char)text[i + j]) !=
                tolower((unsigned char)pattern[j]))
            {
                break;
            }
        }

        if (j == patternLength)
            return 1;
    }

    return 0;
}

/* Display complete browsing history */
void displayHistory(void)
{
    HistoryNode *n;
    int position = 1;

    if (head == NULL)
    {
        printf("\n[i] Browsing history is empty.\n");
        return;
    }

    printf("\n========== BROWSING HISTORY ==========\n");

    for (n = head; n != NULL; n = n->next)
    {
        printf("\n%d. Website: %s\n", position, n->title);
        printf("   URL: %s\n", n->url);
        printf("   Visit Time: %s\n", n->visitTime);
        printf("   Visit Count: %d\n", n->visitCount);

        if (n == current)
        {
            printf("   <-- CURRENT PAGE\n");
        }

        position++;
    }

    printf("\n======================================\n");
    printf("Total history records : %d\n", countHistory());
    printf("Unique websites       : %d\n", countUniqueURLs());

    if (current != NULL)
    {
        printf("Current page          : %s\n", current->title);
    }
    else
    {
        printf("Current page          : None\n");
    }
}

/* Search browsing history */
void searchHistory(void)
{
    char key[INPUT_SIZE];
    HistoryNode *n;
    int position = 1;
    int found = 0;

    if (head == NULL)
    {
        printf("\n[i] History is empty. Nothing to search.\n");
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

    printf("\nSearch results for \"%s\":\n", key);

    for (n = head; n != NULL; n = n->next)
    {
        if (containsIgnoreCase(n->url, key) ||
            containsIgnoreCase(n->title, key))
        {
            printf("\nFound at position %d\n", position);
            printf("Website: %s\n", n->title);
            printf("URL: %s\n", n->url);
            printf("Visit Time: %s\n", n->visitTime);
            printf("Visit Count: %d\n", n->visitCount);

            if (n == current)
            {
                printf("<-- CURRENT PAGE\n");
            }

            found++;
        }

        position++;
    }

    if (found == 0)
    {
        printf("\n[x] Website not found in history.\n");
    }
    else
    {
        printf("\n[OK] %d matching record(s) found.\n", found);
    }
}

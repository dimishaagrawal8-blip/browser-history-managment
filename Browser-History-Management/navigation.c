
/*
 * navigation.c -- Module 2: Back and Forward Navigation
 *
 * DSA Concepts:
 * 1. Stack (LIFO)
 * 2. Linked List
 * 3. Dynamic Memory Allocation
 */

#include "browser.h"

/* ---------- Initialize Stack ---------- */

void initStack(Stack *s)
{
    s->top = NULL;
    s->size = 0;
}

/* ---------- Check Whether Stack Is Empty ---------- */

int isStackEmpty(const Stack *s)
{
    return s->top == NULL;
}

/* ---------- Push Page into Stack ---------- */

int push(Stack *s, HistoryNode *page)
{
    StackNode *node;

    node = (StackNode *)malloc(sizeof(StackNode));

    if (node == NULL)
    {
        return 0;
    }

    node->page = page;
    node->below = s->top;

    s->top = node;
    s->size++;

    return 1;
}

/* ---------- Pop Page from Stack ---------- */

HistoryNode *pop(Stack *s)
{
    StackNode *node;
    HistoryNode *page;

    if (isStackEmpty(s))
    {
        return NULL;
    }

    node = s->top;
    page = node->page;

    s->top = node->below;
    s->size--;

    free(node);

    return page;
}

/* ---------- Clear Stack ---------- */

void clearStack(Stack *s)
{
    while (!isStackEmpty(s))
    {
        pop(s);
    }
}

/* ---------- Display Navigation Page Details ---------- */

static void displayNavigationPage(HistoryNode *page)
{
    if (page == NULL)
    {
        printf("[!] Page information unavailable.\n");
        return;
    }

    printf("\n========== PAGE DETAILS ==========\n");
    printf("Website Title : %s\n", page->title);
    printf("Website URL   : %s\n", page->url);
    printf("Last Visit    : %s\n", page->visitTime);
    printf("Visit Count   : %d\n", page->visitCount);
    printf("==================================\n");
}

/* ---------- Rebuild Stacks After Deletion ---------- */

int rebuildStacks(void)
{
    HistoryNode *n;

    clearStack(&backStack);
    clearStack(&forwardStack);

    if (current == NULL)
    {
        return 1;
    }

    /* Rebuild Back Stack */

    for (n = head; n != NULL && n != current; n = n->next)
    {
        if (!push(&backStack, n))
        {
            clearStack(&backStack);
            clearStack(&forwardStack);
            return 0;
        }
    }

    /* Rebuild Forward Stack */

    for (n = tail; n != NULL && n != current; n = n->prev)
    {
        if (!push(&forwardStack, n))
        {
            clearStack(&backStack);
            clearStack(&forwardStack);
            return 0;
        }
    }

    return 1;
}

/* ---------- Go Back ---------- */

void goBack(void)
{
    HistoryNode *previousPage;

    if (current == NULL)
    {
        printf("\n[!] History is empty. Nothing to go back to.\n");
        return;
    }

    if (isStackEmpty(&backStack))
    {
        printf("\n[!] No previous page available.\n");
        printf("[i] You are at the oldest page: %s\n", current->url);
        return;
    }

    /* Push current page into Forward Stack */

    if (!push(&forwardStack, current))
    {
        printf("\n[!] Memory allocation failed. Cannot go back.\n");
        return;
    }

    /* Pop previous page from Back Stack */

    previousPage = pop(&backStack);

    if (previousPage == NULL)
    {
        printf("\n[!] Navigation failed.\n");
        return;
    }

    current = previousPage;

    printf("\n[<] Successfully moved BACK.\n");

    displayNavigationPage(current);

    printf("Back Stack Size    : %d\n", backStack.size);
    printf("Forward Stack Size : %d\n", forwardStack.size);
}

/* ---------- Go Forward ---------- */

void goForward(void)
{
    HistoryNode *nextPage;

    if (current == NULL)
    {
        printf("\n[!] History is empty. Nothing to go forward to.\n");
        return;
    }

    if (isStackEmpty(&forwardStack))
    {
        printf("\n[!] No next page available.\n");
        printf("[i] You are at the newest page: %s\n", current->url);
        return;
    }

    /* Push current page into Back Stack */

    if (!push(&backStack, current))
    {
        printf("\n[!] Memory allocation failed. Cannot go forward.\n");
        return;
    }

    /* Pop next page from Forward Stack */

    nextPage = pop(&forwardStack);

    if (nextPage == NULL)
    {
        printf("\n[!] Navigation failed.\n");
        return;
    }

    current = nextPage;

    printf("\n[>] Successfully moved FORWARD.\n");

    displayNavigationPage(current);

    printf("Back Stack Size    : %d\n", backStack.size);
    printf("Forward Stack Size : %d\n", forwardStack.size);
}

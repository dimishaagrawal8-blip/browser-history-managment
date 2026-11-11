
/*
 * browser.h
 * Common header file for the Advanced Browser History Management System.
 * Contains structures, shared variables and function prototypes.
 */

#ifndef BROWSER_H
#define BROWSER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_URL 256
#define MAX_TITLE 100
#define MAX_TIME 30
#define INPUT_SIZE 300

/* ---------- Doubly Linked List Node ---------- */
/* Stores information about each visited website */

typedef struct HistoryNode {
    char url[MAX_URL];
    char title[MAX_TITLE];
    char visitTime[MAX_TIME];
    int visitCount;

    struct HistoryNode *prev;
    struct HistoryNode *next;
} HistoryNode;


/* ---------- Bookmark Node ---------- */
/* Stores bookmarked websites separately */

typedef struct BookmarkNode {
    char url[MAX_URL];
    char title[MAX_TITLE];

    struct BookmarkNode *next;
} BookmarkNode;


/* ---------- Stack Node ---------- */
/* Used for Back and Forward navigation */

typedef struct StackNode {
    HistoryNode *page;
    struct StackNode *below;
} StackNode;

typedef struct {
    StackNode *top;
    int size;
} Stack;


/* ---------- Shared Global Variables ---------- */

extern HistoryNode *head;
extern HistoryNode *tail;
extern HistoryNode *current;

extern Stack backStack;
extern Stack forwardStack;

extern BookmarkNode *bookmarkHead;


/* ---------- Input Helper Functions ---------- */

int readLine(char *buffer, int size);


/* ---------- Stack Operations and Navigation ---------- */

void initStack(Stack *s);
int isStackEmpty(const Stack *s);

int push(Stack *s, HistoryNode *page);
HistoryNode *pop(Stack *s);

void clearStack(Stack *s);
int rebuildStacks(void);

void goBack(void);
void goForward(void);


/* ---------- Visit Module ---------- */

void visitPage(void);
void displayCurrentPage(void);


/* ---------- History Module ---------- */

int countHistory(void);
int countUniqueURLs(void);

int equalsIgnoreCase(const char *a, const char *b);
int containsIgnoreCase(const char *text, const char *pattern);

void displayHistory(void);
void searchHistory(void);


/* ---------- Deletion Module ---------- */

void deletePage(void);
void deleteByURL(void);
void clearHistory(void);
void freeAllMemory(void);


/* ---------- Bookmark Module (New) ---------- */

void bookmarkMenu(void);
void addBookmark(void);
void displayBookmarks(void);
void searchBookmark(void);
void deleteBookmark(void);


/* ---------- File Management Module (New) ---------- */

int saveHistory(void);
int loadHistory(void);


#endif /* BROWSER_H */

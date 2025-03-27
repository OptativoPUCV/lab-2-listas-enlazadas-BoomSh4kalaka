#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List * createList() {
    List *newList = (List *) malloc (sizeof(List));
    newList->head = NULL;
    newList->tail = NULL;
    newList->current = NULL;
    return newList;
}

void * firstList(List * list) {
    list->current = list->head;
    if (list->current != NULL) {
        return list->current->data;
    }
    return NULL;
}

void * nextList(List * list) {
    if (list->current != NULL) 
    {
        list->current = list->current->next;
    }
    if (list->current != NULL) 
    {
        return list->current->data;
    }
    else return NULL;
}

void * lastList(List * list) {
    list->current = list->tail;
    if (list->current != NULL) {
        return list->current->data;
    }
    return NULL;
}

void * prevList(List * list) {
    if (list->current != NULL) 
    {
        list->current = list->current->prev;
    }
    if (list->current != NULL) 
    {
        return list->current->data;
    }
    else return NULL;
}

void pushFront(List * list, void * data) {
    Node * newNode = createNode(data);
    newNode->next = list->head;
    if(list->head != NULL) {
        list->head->prev = newNode;
    }
    else 
    {
        list->tail = newNode;
    }
    list->head = newNode;
}

void pushBack(List * list, void * data) {
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List * list, void * data) {
    Node * newNode = createNode(data);
    if (list->current == NULL) {
        pushFront(list,data);
    }
    else {
        newNode->prev = list->current;
        newNode->next = list->current->next;
        newNode->prev->next = newNode;
        if (newNode->next != NULL) newNode->next->prev = newNode;
        else list->tail = newNode;
    }
}

void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

void * popCurrent(List * list) {
    if (list->current == NULL) {
        return NULL;
    }
    Node *izq = list->current->prev;
    Node *der = list->current->next;

    if (izq != NULL) {
        izq->next = der;
    }
    else {
        list->head = der;
    }

    if (der != NULL) {
        der->prev = izq;
    }
    else {
        list->tail = izq;
    }

    void *aux = list->current->data;
    free(list->current);

    return aux;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}
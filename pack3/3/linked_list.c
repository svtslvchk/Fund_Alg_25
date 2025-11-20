#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"

// Базовые операции
LinkedList create_list(void) {
    LinkedList list;
    list.head = NULL;
    list.tail = NULL;
    list.size = 0;
    return list;
}

void erase_list(LinkedList *list) {
    if (!list) {
        return;
    }

    Node *current = list->head;
    while (current) {
        Node *next = current->next;
        free(current);
        current = next;
    }

    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
}

void delete_list(LinkedList *list) {
    if (!list) {
        return;
    }

    erase_list(list);
    free(list);
}

void push_back_list(LinkedList *list, LIST_TYPE value) {
    if (!list) {
        return;
    }

    Node *node = (Node *)malloc(sizeof(Node));
    if (!node) {
        return;
    }

    node->data = value;
    node->next = NULL;
    node->prev = list->tail;
    if (list->tail) {
        list->tail->next = node;
    } else {
        list->head = node;
    }

    list->tail = node;
    list->size++;
}

void push_front_list(LinkedList *list, LIST_TYPE value) {
    if (!list) {
        return;
    }

    Node *node = (Node *)malloc(sizeof(Node));
    if (!node) {
        return;
    }

    node->data = value;
    node->next = list->head;
    node->prev = NULL;
    if (list->head) {
        list->head->prev = node;
    } else {
        list->tail = node;
    }

    list->head = node;
    list->size++;
}

LIST_TYPE pop_back_list(LinkedList *list) {
    if (!list || !list->tail) {
        return (LIST_TYPE)0;
    }

    Node *last = list->tail;
    LIST_TYPE res = last->data;
    if (list->head == last) {
        list->head = NULL;
        list->tail = NULL;
    } else {
        list->tail = last->prev;
        list->tail->next = NULL;
    }

    free(last);
    list->size--;
    return res;
}

LIST_TYPE pop_front_list(LinkedList *list) {
    if (!list || !list->head) {
        return (LIST_TYPE)0;
    }

    Node *first = list->head;
    LIST_TYPE res = first->data;
    if (list->tail == first) {
        list->head = NULL;
        list->tail = NULL;
    } else {
        list->head = first->next;
        list->head->prev = NULL;
    }

    free(first);
    list->size--;
    return res;
}

void insert_at_list(LinkedList *list, size_t index, LIST_TYPE value) {
    if (!list || index > list->size) {
        return;
    }

    if (!index) {
        push_front_list(list, value);
        return;
    }

    if (index == list->size) {
        push_back_list(list, value);
        return;
    }

    Node *current = list->head;
    for (size_t i = 0; i < index; i++) {
        current = current->next;
    }

    Node *node = (Node *)malloc(sizeof(Node));
    if (!node) {
        return;
    }

    node->data = value;
    node->next = current;
    node->prev = current->prev;
    current->prev->next = node;
    current->prev = node;
    list->size++;
}

void delete_at_list(LinkedList *list, size_t index) {
    if (!list || index >= list->size) {
        return;
    }

    if (!index) {
        pop_front_list(list);
        return;
    }

    if (index == list->size - 1) {
        pop_back_list(list);
        return;
    }

    Node *current = list->head;
    for (size_t i = 0; i < index; i++) {
        current = current->next;
    }

    current->next->prev = current->prev;
    current->prev->next = current->next;
    free(current);
    list->size--;
}

LIST_TYPE get_at_list(const LinkedList *list, size_t index) {
    if (!list || index >= list->size) {
        return (LIST_TYPE)0;
    }

    Node *current = list->head;
    for (size_t i = 0; i < index; i++) {
        if (!current) {
            return (LIST_TYPE)0;
        }
        
        current = current->next;
    }

    return current->data;
}

int is_equal_list(const LinkedList *l1, const LinkedList *l2) {
    if (!l1 || !l2 || l1->size != l2->size) {
        return 0;
    }

    Node *cur1 = l1->head;
    Node *cur2 = l2->head;
    while (cur1 && cur2) {
        if (cur1->data != cur2->data) {
            return 0;
        }

        cur1 = cur1->next;
        cur2 = cur2->next;
    }

    return 1;
}

// Стек
void push_stack(LinkedList *stack, LIST_TYPE value) {
    push_back_list(stack, value);
}

LIST_TYPE pop_stack(LinkedList *stack) {
    return pop_back_list(stack);
}

LIST_TYPE peek_stack(const LinkedList *stack) {
    return get_at_list(stack, stack->size - 1);
}

// Очередь
void enqueue(LinkedList *queue, LIST_TYPE value) {
    push_back_list(queue, value);
}

LIST_TYPE dequeue(LinkedList *queue) {
    return pop_front_list(queue);
}

LIST_TYPE peek_queue(const LinkedList *queue) {
    return get_at_list(queue, 0);
}
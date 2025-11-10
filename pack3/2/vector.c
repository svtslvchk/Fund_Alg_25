#include "vector.h"
#include <stdio.h>

Vector create_vector(size_t initial_capacity, VECTOR_TYPE(*CopyFunc)(VECTOR_TYPE), void (*DeleteFunc)(VECTOR_TYPE)) {
    Vector v;
    v.capacity = initial_capacity;
    v.size = 0;
    v.CopyVoidPtr = CopyFunc;
    v.DeleteVoidPtr = DeleteFunc;
    v.data = (VECTOR_TYPE *)malloc(sizeof(VECTOR_TYPE) * v.capacity);
    if (!v.data) {
        v.capacity = 2;
    }

    return v;
}

void erase_vector(Vector *v) {
    if (!v) {
        return;
    }

    for (size_t i = 0; i < v->size; i++) {
        v->DeleteVoidPtr(v->data[i]);
    }

    free(v->data);
    v->data = NULL;
    v->capacity = 0;
    v->size = 0;
}

int is_equal_vector(const Vector *v1, const Vector *v2) {
    if (!v1 || !v2) {
        return 0;
    }

    if (v1->size != v2->size) {
        return 0;
    }

    for (size_t i = 0; i < v1->size; i++) {
        if (v1->data[i] != v2->data[i]) {
            return 0;
        }
    }

    return 1;
}

void copy_vector(Vector *dest, const Vector *src) {
    if (!dest || !src) {
        return;
    }

    erase_vector(dest);
    dest->capacity = src->capacity;
    dest->CopyVoidPtr = src->CopyVoidPtr;
    dest->DeleteVoidPtr = src->DeleteVoidPtr;
    dest->size = src->size;
    dest->data = (VECTOR_TYPE *)realloc(dest->data, sizeof(VECTOR_TYPE) * dest->capacity);
    if (!dest->data) {
        dest->capacity = 0;
        dest->size = 0;
        return;
    }

    for (size_t i = 0; i < src->size; i++) {
        dest->data[i] = src->CopyVoidPtr(src->data[i]);
    }
}

Vector *copy_vector_new(const Vector *src) {
    if (!src) {
        return NULL;
    }

    Vector *v = (Vector *)malloc(sizeof(Vector));
    if (!v) {
        return NULL;
    }

    v->capacity = 0;
    v->CopyVoidPtr = NULL;
    v->data = NULL;
    v->DeleteVoidPtr = NULL;
    v->size = 0;
    copy_vector(v, src);

    if (!v->data) {
        free(v);
        return NULL;
    }

    return v;
}

void push_back_vector(Vector *v, VECTOR_TYPE value) {
    if (!v) {
        return;
    }

    if (v->size >= v->capacity) {
        v->capacity *= 2;
        VECTOR_TYPE *temp = (VECTOR_TYPE *)realloc(v->data, sizeof(VECTOR_TYPE) * v->capacity);
        if (!temp) {
            return;
        }

        v->data = temp;
    }

    v->data[v->size] = v->CopyVoidPtr(value);
    v->size++;
}

void delete_at_vector(Vector *v, size_t index) {
    if (!v || v->size <= index) {
        return;
    }

    v->DeleteVoidPtr(v->data[index]);

    for (size_t i = index; i < v->size; i++) {
        v->data[i] = v->data[i + 1];
    }

    v->size--;
}

VECTOR_TYPE get_at_vector(const Vector *v, size_t index) {
    if (!v || v->size <= index) {
        return (VECTOR_TYPE)0;
    }

    return v->data[index];
}

void delete_vector(Vector *v) {
    if (!v) {
        return;
    }

    erase_vector(v);
    free(v);
}
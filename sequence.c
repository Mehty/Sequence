#include "sequence.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


struct sequence {
    int len;
    struct llist *data;
};

struct llnode {
    int item;
    struct llnode *next;
};

struct llist {
    struct llnode *front;
};

struct llist *list_create(void) {
    struct llist *lst = malloc(sizeof(struct llist));
    lst->front = NULL;
    return lst;
}

/////////////////////////////////////////////////


struct sequence *sequence_create(void) {
    struct sequence *seq = malloc(sizeof(struct sequence));
    seq->len = 0;
    seq->data = list_create();
    return seq;
}

// node_destroy frees all the nodes in a llnode
// effects: the memory at seq is invalid (freed)
// time: O(n)
void node_destroy(struct llnode *node) {
    if (node) {
        if (node->next) node_destroy(node->next);
        free(node);
    }
}

void sequence_destroy(struct sequence *seq) {
    assert(seq);
    struct llnode *node = seq->data->front;
    node_destroy(node);
    free(seq->data);
    free(seq);
}

int sequence_length(const struct sequence *seq) {
    assert(seq);
    return seq->len;
}

int sequence_item_at(const struct sequence *seq, int pos) {
    assert(seq);
    assert(pos >= 0);
    assert(pos < seq->len);
    int index = pos;
    struct llnode *current = seq->data->front;
    while(index) {
        current = current->next;
        index--;
    }
    return current->item;
}

void sequence_insert_at(struct sequence *seq, int pos, int val) {
    assert(seq);
    assert(pos >= 0);
    assert(pos <= seq->len);
    if (pos == 0) {
        struct llnode *node = malloc(sizeof(struct llnode));
        node->item = val;
        node->next = seq->data->front;
        seq->data->front = node;
        seq->len += 1;
    } else {
        int index = pos - 1;
        struct llnode *current = seq->data->front;
        while (index) {
            current = current->next;
            index--;
        }
        struct llnode *node = malloc(sizeof(struct llnode));
        node->item = val;
        node->next = current->next;
        current->next = node;
        seq->len += 1;
    }
}

int sequence_remove_at(struct sequence *seq, int pos) {
    assert(seq);
    assert(pos >= 0);
    assert(pos < seq->len);
    if (pos == 0) {
        assert(seq->data->front);
        int item = seq->data->front->item;
        struct llnode *backup = seq->data->front;
        seq->data->front = seq->data->front->next;
        free(backup);
        seq->len -= 1;
        return item;
    }
    int index = pos - 1;
    struct llnode *current = seq->data->front;
    while (index) {
        current = current->next;
        index--;
    }
    int item = current->next->item;
    struct llnode *backup = current->next;
    current->next = current->next->next;
    free(backup);
    seq->len -= 1;
    return item;
}

void sequence_print(const struct sequence *seq) {
    struct llnode *current = seq->data->front;
    int len = seq->len;
    if (len == 0) printf("[empty]\n");
    else {
        printf("[");
        while (len>1) {
            printf("%d,", current->item);
            current = current->next;
            len--;
        }
        printf("%d]\n", current->item);
    }
}

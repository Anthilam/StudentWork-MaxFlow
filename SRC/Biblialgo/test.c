#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

struct list {
        struct list_node *first;
        // struct list_node *last;
};

struct list_node {
        int value;
        struct list_node *next;
        // struct list_node *prev;
};

void list_create(struct list *self) {
        self->first = NULL;
}

void list_destroy(struct list *self) {
        free(self->first);
}

void dump(struct list_node *self) {
        if (self != NULL)
        {
                printf("%d", self->value);
                if (self->next != NULL)
                {
                        printf(" , ");
                        dump(self->next);
                }
        }
}

void list_dump(const struct list *self) {
        printf("( ");
        dump(self->first);
        printf(" )\n");
}

void add_back(struct list_node *self, int value) {
        if (self->next == NULL) {
                struct list_node *l = malloc(sizeof(struct list_node));
                l->value = value;
                l->next = NULL;
                self->next = l;
        }
        else
        {
                add_back(self->next, value);
        }

}

void list_add_back(struct list *self, int value) {
        if (self->first == NULL)
        {
                self->first = malloc(sizeof(struct list_node));
                self->first->value = value;
                self->first->next = NULL;
        }
        else
        {
                add_back(self->first, value);
        }
}

int *list_get(const struct list *self, size_t index) {
        struct list_node *l = self->first;

        for (size_t i = 0; i < index; ++i)
        {
              l = l->next;
        }

        return &l->value;
}

bool list_is_empty(const struct list *self) {
        if (self->first != NULL)
        {
            return false;
        }

        return true;
}

size_t list_size(const struct list *self) {
        size_t i = 0;
        if (self->first != NULL)
        {
            struct list_node *l = self->first;
            while(l != NULL)
            {
              ++i;
              l = l->next;
            }
        }

        return i;
}

int main(int argc, char *argv[])
{
        struct list a;
        list_create(&a);
        list_dump(&a);
        list_add_back(&a, 1);
        list_dump(&a);
        list_add_back(&a, 2);
        list_dump(&a);
        list_add_back(&a, 3);
        list_dump(&a);
        list_add_back(&a, 4);
        list_dump(&a);
        list_add_back(&a, 5);
        list_dump(&a);
        list_destroy(&a);

        return 0;
}

#include <stdio.h>
#include <stdlib.h>

struct node {
    int pow;
    int coeff;
    struct node *next;
} *start = NULL;

typedef struct node NODE;

void create_poly() {
    NODE *temp, *temp1;
    temp = (NODE *)malloc(sizeof(NODE));
    temp->next = NULL;
    printf("Enter the power and coefficient of polynomial term: ");
    scanf("%d%d", &(temp->pow), &(temp->coeff));

    if (start == NULL) {
        start = temp;
    } else {
        temp1 = start;
        while (temp1->next != NULL) {
            temp1 = temp1->next;
        }
        temp1->next = temp;
    }
}

void display_poly() {
    NODE *temp;
    temp = start;

    if (temp == NULL) {
        printf("No node in this linked list\n");
    } else {
        printf("Polynomial list is:\n");
        while (temp != NULL) {
            if (temp->next != NULL)
                printf("%dx^%d + ", temp->coeff, temp->pow);
            else
                printf("%dx^%d", temp->coeff, temp->pow);
            temp = temp->next;
        }
        printf("\n");
    }
}

void add_poly() {
    NODE *poly1 = start, *poly2 = NULL, *result = NULL, *tail = NULL;

    printf("Enter second polynomial:\n");
    int n;
    printf("How many terms? ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        NODE *new = (NODE *)malloc(sizeof(NODE));
        new->next = NULL;
        printf("Enter power and coefficient: ");
        scanf("%d%d", &new->pow, &new->coeff);

        if (poly2 == NULL)
            poly2 = new;
        else {
            NODE *t = poly2;
            while (t->next != NULL)
                t = t->next;
            t->next = new;
        }
    }

    NODE *p1 = poly1, *p2 = poly2;
    while (p1 != NULL && p2 != NULL) {
        NODE *temp = (NODE *)malloc(sizeof(NODE));
        temp->next = NULL;

        if (p1->pow > p2->pow) {
            temp->pow = p1->pow;
            temp->coeff = p1->coeff;
            p1 = p1->next;
        } else if (p2->pow > p1->pow) {
            temp->pow = p2->pow;
            temp->coeff = p2->coeff;
            p2 = p2->next;
        } else {
            temp->pow = p1->pow;
            temp->coeff = p1->coeff + p2->coeff;
            p1 = p1->next;
            p2 = p2->next;
        }

        if (result == NULL)
            result = tail = temp;
        else {
            tail->next = temp;
            tail = temp;
        }
    }

    while (p1 != NULL) {
        NODE *temp = (NODE *)malloc(sizeof(NODE));
        temp->pow = p1->pow;
        temp->coeff = p1->coeff;
        temp->next = NULL;
        tail->next = temp;
        tail = temp;
        p1 = p1->next;
    }

    while (p2 != NULL) {
        NODE *temp = (NODE *)malloc(sizeof(NODE));
        temp->pow = p2->pow;
        temp->coeff = p2->coeff;
        temp->next = NULL;
        tail->next = temp;
        tail = temp;
        p2 = p2->next;
    }

    printf("Result of addition:\n");
    NODE *t = result;
    while (t != NULL) {
        if (t->next != NULL)
            printf("%dx^%d + ", t->coeff, t->pow);
        else
            printf("%dx^%d", t->coeff, t->pow);
        t = t->next;
    }
    printf("\n");
}

void multiply_poly() {
    NODE *p1 = start, *result = NULL;

    printf("Enter second polynomial:\n");
    int n;
    NODE *poly2 = NULL;
    printf("How many terms? ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        NODE *new = (NODE *)malloc(sizeof(NODE));
        new->next = NULL;
        printf("Enter power and coefficient: ");
        scanf("%d%d", &new->pow, &new->coeff);

        if (poly2 == NULL)
            poly2 = new;
        else {
            NODE *t = poly2;
            while (t->next != NULL)
                t = t->next;
            t->next = new;
        }
    }

    while (p1 != NULL) {
        NODE *p2 = poly2;
        while (p2 != NULL) {
            int coeff = p1->coeff * p2->coeff;
            int pow = p1->pow + p2->pow;

            NODE *temp = result, *prev = NULL;
            while (temp != NULL && temp->pow > pow) {
                prev = temp;
                temp = temp->next;
            }

            if (temp != NULL && temp->pow == pow) {
                temp->coeff += coeff;
            } else {
                NODE *new = (NODE *)malloc(sizeof(NODE));
                new->coeff = coeff;
                new->pow = pow;
                new->next = temp;

                if (prev == NULL)
                    result = new;
                else
                    prev->next = new;
            }

            p2 = p2->next;
        }
        p1 = p1->next;
    }

    printf("Result of multiplication:\n");
    NODE *t = result;
    while (t != NULL) {
        if (t->next != NULL)
            printf("%dx^%d + ", t->coeff, t->pow);
        else
            printf("%dx^%d", t->coeff, t->pow);
        t = t->next;
    }
    printf("\n");
}

int main() {
    int choice;
    while (1) {
        printf("\n1. Create Polynomial\n2. Display Polynomial\n3. Add Polynomial\n4. Multiply Polynomial\n5. Exit\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: create_poly(); break;
            case 2: display_poly(); break;
            case 3: add_poly(); break;
            case 4: multiply_poly(); break;
            case 5: exit(0);
            default: printf("Invalid choice\n");
        }
    }
    return 0;
}

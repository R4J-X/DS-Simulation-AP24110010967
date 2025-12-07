#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 50

/* ========================= ARRAY SIMULATOR ========================= */

typedef struct
{
    int data[MAX_SIZE];
    int size;
} ArraySim;

void initArray(ArraySim *a)
{
    a->size = 0;
}

void displayArray(ArraySim *a)
{
    int i;
    if (a->size == 0)
    {
        printf("Array is empty.\n");
        return;
    }
    printf("Array elements (index : value):\n");
    for (i = 0; i < a->size; i++)
    {
        printf("[%d] : %d\n", i, a->data[i]);
    }
}

void insertArray(ArraySim *a, int pos, int value)
{
    int i;
    if (a->size == MAX_SIZE)
    {
        printf("Array is full, cannot insert.\n");
        return;
    }
    if (pos < 0 || pos > a->size)
    {
        printf("Invalid position.\n");
        return;
    }

    printf("Inserting %d at position %d\n", value, pos);
    /* Shift elements right */
    for (i = a->size; i > pos; i--)
    {
        printf("Shifting element from index %d to %d (value %d)\n",
               i - 1, i, a->data[i - 1]);
        a->data[i] = a->data[i - 1];
    }
    a->data[pos] = value;
    a->size++;
}

void deleteArray(ArraySim *a, int pos)
{
    int i;
    if (a->size == 0)
    {
        printf("Array is empty, nothing to delete.\n");
        return;
    }
    if (pos < 0 || pos >= a->size)
    {
        printf("Invalid position.\n");
        return;
    }
    printf("Deleting element %d at position %d\n", a->data[pos], pos);
    for (i = pos; i < a->size - 1; i++)
    {
        printf("Shifting element from index %d to %d (value %d)\n",
               i + 1, i, a->data[i + 1]);
        a->data[i] = a->data[i + 1];
    }
    a->size--;
}

/* ========================= LINKED LIST SIMULATOR ========================= */

typedef struct Node
{
    int data;
    struct Node *next;
} Node;

Node *createNode(int value)
{
    Node *n = (Node *)malloc(sizeof(Node));
    if (!n)
    {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    n->data = value;
    n->next = NULL;
    return n;
}

void displayList(Node *head)
{
    Node *temp = head;
    int index = 0;
    if (!head)
    {
        printf("List is empty.\n");
        return;
    }
    printf("Linked list nodes (address[data|next]):\n");
    while (temp)
    {
        printf("Node %d at %p : data=%d, next=%p\n",
               index, (void *)temp, temp->data, (void *)temp->next);
        temp = temp->next;
        index++;
    }
}

Node *insertAtBeginning(Node *head, int value)
{
    Node *n = createNode(value);
    printf("Creating new node at %p with data=%d\n", (void *)n, value);
    n->next = head;
    printf("New node next points to old head %p\n", (void *)head);
    head = n;
    return head;
}

Node *insertAtEnd(Node *head, int value)
{
    Node *n = createNode(value);
    printf("Creating new node at %p with data=%d\n", (void *)n, value);
    if (!head)
    {
        printf("List was empty, new node becomes head.\n");
        return n;
    }
    Node *temp = head;
    while (temp->next)
    {
        printf("Traversing node at %p with data=%d\n", (void *)temp, temp->data);
        temp = temp->next;
    }
    printf("Last node found at %p, linking its next to new node %p\n",
           (void *)temp, (void *)n);
    temp->next = n;
    return head;
}

Node *deleteByValue(Node *head, int value)
{
    Node *temp = head, *prev = NULL;
    while (temp && temp->data != value)
    {
        printf("Visiting node at %p with data=%d (looking for %d)\n",
               (void *)temp, temp->data, value);
        prev = temp;
        temp = temp->next;
    }
    if (!temp)
    {
        printf("Value %d not found in list.\n", value);
        return head;
    }
    if (!prev)
    {
        printf("Deleting head node at %p with data=%d\n", (void *)temp, temp->data);
        head = temp->next;
    }
    else
    {
        printf("Deleting node at %p with data=%d, linking %p->next to %p\n",
               (void *)temp, temp->data, (void *)prev, (void *)temp->next);
        prev->next = temp->next;
    }
    free(temp);
    return head;
}

void freeList(Node *head)
{
    Node *temp;
    while (head)
    {
        temp = head;
        head = head->next;
        free(temp);
    }
}

/* ========================= STACK SIMULATOR (ARRAY) ========================= */

typedef struct
{
    int data[MAX_SIZE];
    int top;
} Stack;

void initStack(Stack *s)
{
    s->top = -1;
}

int isStackEmpty(Stack *s)
{
    return s->top == -1;
}

int isStackFull(Stack *s)
{
    return s->top == MAX_SIZE - 1;
}

void push(Stack *s, int value)
{
    if (isStackFull(s))
    {
        printf("Stack overflow, cannot push.\n");
        return;
    }
    printf("Pushing %d on stack at position %d\n", value, s->top + 1);
    s->top++;
    s->data[s->top] = value;
}

int pop(Stack *s)
{
    if (isStackEmpty(s))
    {
        printf("Stack underflow, cannot pop.\n");
        return -1;
    }
    printf("Popping value %d from position %d\n", s->data[s->top], s->top);
    return s->data[s->top--];
}

void displayStack(Stack *s)
{
    int i;
    if (isStackEmpty(s))
    {
        printf("Stack is empty.\n");
        return;
    }
    printf("Stack contents (top to bottom):\n");
    for (i = s->top; i >= 0; i--)
    {
        printf("Index %d : %d\n", i, s->data[i]);
    }
}

/* ========================= QUEUE SIMULATOR (CIRCULAR ARRAY) ========================= */

typedef struct
{
    int data[MAX_SIZE];
    int front;
    int rear;
    int count;
} Queue;

void initQueue(Queue *q)
{
    q->front = 0;
    q->rear = -1;
    q->count = 0;
}

int isQueueEmpty(Queue *q)
{
    return q->count == 0;
}

int isQueueFull(Queue *q)
{
    return q->count == MAX_SIZE;
}

void enqueue(Queue *q, int value)
{
    if (isQueueFull(q))
    {
        printf("Queue is full, cannot enqueue.\n");
        return;
    }
    q->rear = (q->rear + 1) % MAX_SIZE;
    q->data[q->rear] = value;
    q->count++;
    printf("Enqueued %d at index %d (front=%d, count=%d)\n",
           value, q->rear, q->front, q->count);
}

int dequeue(Queue *q)
{
    int value;
    if (isQueueEmpty(q))
    {
        printf("Queue is empty, cannot dequeue.\n");
        return -1;
    }
    value = q->data[q->front];
    printf("Dequeuing %d from index %d\n", value, q->front);
    q->front = (q->front + 1) % MAX_SIZE;
    q->count--;
    return value;
}

void displayQueue(Queue *q)
{
    int i, idx;
    if (isQueueEmpty(q))
    {
        printf("Queue is empty.\n");
        return;
    }
    printf("Queue contents (front to rear):\n");
    idx = q->front;
    for (i = 0; i < q->count; i++)
    {
        printf("Index %d : %d\n", idx, q->data[idx]);
        idx = (idx + 1) % MAX_SIZE;
    }
}

/* ========================= RECURSION DEMO ========================= */

long long factorialTrace(int n, int depth)
{
    int i;
    for (i = 0; i < depth; i++)
        printf("  ");
    printf("factorial(%d) called\n", n);

    if (n == 0 || n == 1)
    {
        for (i = 0; i < depth; i++)
            printf("  ");
        printf("Return 1\n");
        return 1;
    }

    long long result = n * factorialTrace(n - 1, depth + 1);

    for (i = 0; i < depth; i++)
        printf("  ");
    printf("Return %lld (because %d * factorial(%d))\n", result, n, n - 1);
    return result;
}

/* ========================= MENUS ========================= */

void arrayMenu(ArraySim *a)
{
    int choice, pos, value;
    while (1)
    {
        printf("\n--- ARRAY SIMULATOR ---\n");
        printf("1. Display array\n");
        printf("2. Insert element\n");
        printf("3. Delete element\n");
        printf("0. Back to main menu\n");
        printf("Enter choice: ");
        if (scanf("%d", &choice) != 1)
            return;
        switch (choice)
        {
        case 1:
            displayArray(a);
            break;
        case 2:
            printf("Enter position (0 to %d): ", a->size);
            scanf("%d", &pos);
            printf("Enter value: ");
            scanf("%d", &value);
            insertArray(a, pos, value);
            break;
        case 3:
            printf("Enter position (0 to %d): ", a->size - 1);
            scanf("%d", &pos);
            deleteArray(a, pos);
            break;
        case 0:
            return;
        default:
            printf("Invalid choice.\n");
        }
    }
}

void listMenu(Node **headRef)
{
    int choice, value;
    while (1)
    {
        printf("\n--- LINKED LIST SIMULATOR ---\n");
        printf("1. Display list\n");
        printf("2. Insert at beginning\n");
        printf("3. Insert at end\n");
        printf("4. Delete by value\n");
        printf("0. Back to main menu\n");
        printf("Enter choice: ");
        if (scanf("%d", &choice) != 1)
            return;
        switch (choice)
        {
        case 1:
            displayList(*headRef);
            break;
        case 2:
            printf("Enter value: ");
            scanf("%d", &value);
            *headRef = insertAtBeginning(*headRef, value);
            break;
        case 3:
            printf("Enter value: ");
            scanf("%d", &value);
            *headRef = insertAtEnd(*headRef, value);
            break;
        case 4:
            printf("Enter value to delete: ");
            scanf("%d", &value);
            *headRef = deleteByValue(*headRef, value);
            break;
        case 0:
            return;
        default:
            printf("Invalid choice.\n");
        }
    }
}

void stackMenu(Stack *s)
{
    int choice, value, popped;
    while (1)
    {
        printf("\n--- STACK SIMULATOR ---\n");
        printf("1. Display stack\n");
        printf("2. Push\n");
        printf("3. Pop\n");
        printf("0. Back to main menu\n");
        printf("Enter choice: ");
        if (scanf("%d", &choice) != 1)
            return;
        switch (choice)
        {
        case 1:
            displayStack(s);
            break;
        case 2:
            printf("Enter value: ");
            scanf("%d", &value);
            push(s, value);
            break;
        case 3:
            popped = pop(s);
            if (popped != -1)
                printf("Popped value: %d\n", popped);
            break;
        case 0:
            return;
        default:
            printf("Invalid choice.\n");
        }
    }
}

void queueMenu(Queue *q)
{
    int choice, value, deq;
    while (1)
    {
        printf("\n--- QUEUE SIMULATOR ---\n");
        printf("1. Display queue\n");
        printf("2. Enqueue\n");
        printf("3. Dequeue\n");
        printf("0. Back to main menu\n");
        printf("Enter choice: ");
        if (scanf("%d", &choice) != 1)
            return;
        switch (choice)
        {
        case 1:
            displayQueue(q);
            break;
        case 2:
            printf("Enter value: ");
            scanf("%d", &value);
            enqueue(q, value);
            break;
        case 3:
            deq = dequeue(q);
            if (deq != -1)
                printf("Dequeued value: %d\n", deq);
            break;
        case 0:
            return;
        default:
            printf("Invalid choice.\n");
        }
    }
}

void recursionMenu()
{
    int n;
    long long ans;
    printf("\n--- RECURSION DEMO (FACTORIAL) ---\n");
    printf("Enter n (0-20): ");
    if (scanf("%d", &n) != 1)
        return;
    if (n < 0 || n > 20)
    {
        printf("Out of range.\n");
        return;
    }
    ans = factorialTrace(n, 0);
    printf("Final result: %d! = %lld\n", n, ans);
}

/* ========================= MAIN ========================= */

int main(void)
{
    ArraySim arr;
    Node *head = NULL;
    Stack stack;
    Queue queue;
    int choice;

    initArray(&arr);
    initStack(&stack);
    initQueue(&queue);

    while (1)
    {
        printf("\n===== DATA STRUCTURE SIMULATOR =====\n");
        printf("1. Array\n");
        printf("2. Linked List\n");
        printf("3. Stack\n");
        printf("4. Queue\n");
        printf("5. Recursion (factorial)\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1)
            break;

        switch (choice)
        {
        case 1:
            arrayMenu(&arr);
            break;
        case 2:
            listMenu(&head);
            break;
        case 3:
            stackMenu(&stack);
            break;
        case 4:
            queueMenu(&queue);
            break;
        case 5:
            recursionMenu();
            break;
        case 0:
            printf("Exiting...\n");
            freeList(head);
            return 0;
        default:
            printf("Invalid choice.\n");
        }
    }

    freeList(head);
    return 0;
}

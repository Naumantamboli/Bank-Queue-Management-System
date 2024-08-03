#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100
#define MAX_NAME_LENGTH 50

struct Queue {
    int front, rear;
    int numCustomers;
    char names[MAX_SIZE][MAX_NAME_LENGTH];
};

// Function to initialize the queue
void initializeQueue(struct Queue *q) {
    q->front = -1;
    q->rear = -1;
    q->numCustomers = 0;
}

// Function to check if the queue is empty
int isQueueEmpty(struct Queue *q) {
    return (q->front == -1 && q->rear == -1);
}

// Function to check if the queue is full
int isQueueFull(struct Queue *q) {
    return (q->rear == MAX_SIZE - 1);
}

// Function to add a specified number of customers to the queue
void CustEnqueue(struct Queue *q) {
    if (isQueueFull(q)) {
        printf("Queue is full. Cannot add more customers.\n");
        return;
    }

    int numCustomers;
    printf("Enter the number of customers to add: ");
    scanf("%d", &numCustomers);
    getchar(); // Clearing the newline character from the input buffer

    if (numCustomers <= 0) {
        printf("Invalid number of customers. Please enter a positive integer.\n");
        return;
    }

    if (numCustomers > MAX_SIZE - q->numCustomers) {
        printf("Not enough space in the queue to add %d customers.\n", numCustomers);
        return;
    }

    for (int i = 0; i < numCustomers; i++) {
        printf("Enter customer name: ");
        fgets(q->names[++q->rear], sizeof(q->names[q->rear]), stdin);
        q->names[q->rear][strcspn(q->names[q->rear], "\n")] = '\0'; // Removing the trailing newline character
        q->numCustomers++;
        printf("Customer %s added to the queue.\n", q->names[q->rear]);
    }
}

// Function to remove a customer from the front of the queue
void CustDequeue(struct Queue *q) {
    if (isQueueEmpty(q)) {
        printf("Queue is empty. No customers to remove.\n");
        return;
    } else if (q->front == q->rear) {
        printf("Customer %s served and removed from the queue.\n", q->names[q->front]);
        q->front = q->rear = -1;
    } else {
        printf("Customer %s served and removed from the queue.\n", q->names[q->front]);
        q->front++;
    }

    q->numCustomers--;
}

// Function to display the queue
void DispQueue(struct Queue *q) {
    if (isQueueEmpty(q)) {
        printf("Queue is empty.\n");
        return;
    }

    printf("Customers in the queue: ");
    for (int i = q->front; i <= q->rear; i++) {
        printf("%s ", q->names[i]);
    }
    printf("\n");
}

// Function to get the number of customers in the queue
int NumQueue(struct Queue *q) {
    return q->numCustomers;
}

int main() {
    struct Queue bankQueue;
    initializeQueue(&bankQueue);

    int choice;

    do {
        printf("1. Add customer(s) to the queue\n");
        printf("2. Serve a customer\n");
        printf("3. Display queue\n");
        printf("4. Number of customers in the queue\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Clearing the newline character from the input buffer

        switch (choice) {
            case 1:
                CustEnqueue(&bankQueue);
                break;
            case 2:
                CustDequeue(&bankQueue);
                break;
            case 3:
                DispQueue(&bankQueue);
                break;
            case 4:
                printf("Number of customers in the queue: %d\n", NumQueue(&bankQueue));
                break;
            case 5:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
        printf("\n");
    } while (choice != 5);

    return 0;
}

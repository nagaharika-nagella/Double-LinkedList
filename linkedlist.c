#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Task {
    char description[100];
    int completed;
    struct Task *prev;
    struct Task *next;
};

struct TaskList {
    struct Task *head;
    struct Task *tail;
};

void add_task(struct TaskList *list, char *description) {
    struct Task *new_task = (struct Task *) malloc(sizeof(struct Task));
    strncpy(new_task->description, description, sizeof(new_task->description) - 1);
    new_task->completed = 0;
    new_task->prev = NULL;
    new_task->next = NULL;
    if (list->head == NULL) {
        list->head = new_task;
        list->tail = new_task;
    }
 else {
        list->tail->next = new_task;
        new_task->prev = list->tail;
        list->tail = new_task;
    }
}

void complete_task(struct TaskList *list, int index) 
{   int i;
    struct Task *current_task = list->head;
    for ( i = 1; i < index; i++)
	{
        if (current_task == NULL) {
            printf("Task index out of range.\n");
            return;
        }
        current_task = current_task->next;
    }
    current_task->completed = 1;
}

void show_tasks(struct TaskList *list) {
    struct Task *current_task = list->head;
    int i = 1;
    while (current_task != NULL) {
        char *completed_text = current_task->completed ? "[X]" : "[ ]";
        printf("%d. %s %s\n", i, completed_text, current_task->description);
        current_task = current_task->next;
        i++;
    }
}

void save_tasks(struct TaskList *list, char *filename) {
    FILE *f = fopen(filename, "w");
    struct Task *current_task = list->head;
    while (current_task != NULL) {
        fprintf(f, "%s,%d\n", current_task->description, current_task->completed);
        current_task = current_task->next;
    }
    fclose(f);
}
int main() {
    struct TaskList list = { NULL, NULL };
    int choice, index;
    char description[100], filename[100];
    printf("\n-------------------ONLINE COURSE PLATFORM-----------------------\n");
    printf("\n'Complete the tasks to complete online course and claim certificate'\n");
    while (1) {
    	printf("\n---------------MAIN MENU--------------\n");
        printf("1. Add task\n");
        printf("2. Complete task\n");
        printf("3. Show tasks\n");
        printf("4. Save tasks\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("Enter task description: ");
                scanf("%s", description);
                add_task(&list, description);
                break;
            case 2:
                printf("Enter task index: ");
                scanf("%d", &index);
                complete_task(&list, index);
                break;
            case 3:
                show_tasks(&list);
                break;
            case 4:
                printf("Enter filename: ");
                scanf("%s", filename);
                save_tasks(&list, filename);
                break;
            case 5:
                exit(0);
            default:
                printf("Invalid choice.\n");
        }
    }
    return 0;
}
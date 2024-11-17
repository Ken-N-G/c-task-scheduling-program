#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "functions.h"

int main() {
    bool menuLoop = true;
    bool continueProgram;
    struct task * taskHead;
    programInitializer();
    taskHead = fileReader();
    taskHead = checkDueDate(taskHead);
    do {
        taskHead = mainMenu(taskHead);
        if (taskHead == NULL) {
            printf("No tasks are loaded. The program will end if you don't add or load a task.\n");
            continueProgram = inputContinueChoice();
            if (continueProgram == true) {
                taskHead = fileReader();
                continue;
            }
            else
                menuLoop = false;
        }
    } while(menuLoop == true);
    return 0;
}

struct task * mainMenu(struct task * taskHead) {
    printf("Hello user! Welcome to the Personal Task Management System.\n1) View Tasks\n2) Update Task\n3) Add Task\n4) Delete Task\n5) Exit Program\nPlease enter an option: ");
    int choice = 0;
    fflush(stdin);
    scanf("%d", &choice);
    switch(choice) {
        case 1:
        taskHead = viewTask(taskHead);
        return taskHead;
        break;

        case 2:
        taskHead = updateTask(taskHead);
        return taskHead;
        break;

        case 3:
        taskHead = addTask(taskHead);
        return taskHead;
        break;

        case 4:
        taskHead = deleteTask(taskHead);
        return taskHead;
        break;

        case 5:
        printf("You will exit the program. Your tasks will be automatically saved and all current data will be erased.\n");
        fileWriter(taskHead);
        taskHead = deleteLinkedList(taskHead);
        return taskHead;
        break;

        default:
        printf("Invalid input!. Try again.\n");
        return taskHead;
        break;
    }
}

bool inputContinueChoice() {
    bool subMenuLoop = true;
    char continueChoice = ' ';
    do {
        printf("Do you wish to continue? (y/n): ");
        while (getchar() != '\n');
        scanf("%c", &continueChoice);
        if (continueChoice == 'y') {
            return true;
        }
        else if (continueChoice == 'n') {
            return false;
        }
        else {
            printf("Invalid input! Try again.\n");
        }
    } while (subMenuLoop == true);
}

struct task * deleteTask(struct task * taskHead) {
    if (taskHead == NULL) {
        printf("There are no tasks to delete! Add a task first.\n");
        return taskHead;
    }
    else {
        char targetTask[100];
        bool deleteChoice;
        inputTaskName(targetTask);
        struct task * previousTask = NULL;
        struct task * currentTask = NULL;
        currentTask = taskHead;
        if (strcmp(currentTask->taskName, targetTask) == 0) {
            printf("'%s' will be deleted.\n", targetTask);
            deleteChoice = inputContinueChoice();
            switch (deleteChoice) {
                case true:
                taskHead = currentTask->next;
                printf("The task '%s' has been deleted. You will return to the main menu.\n", targetTask);
                return taskHead;
                break;

                case false:
                printf("Task deletion has been canceled. You will return to the main menu.\n");
                return taskHead;
                break;
            }
        }
        else {
            do {
                previousTask = currentTask;
                currentTask = currentTask->next;
                if (strcmp(currentTask->taskName, targetTask) == 0) {
                    printf("'%s' will be deleted.\n", targetTask);
                    deleteChoice = inputContinueChoice();
                    switch (deleteChoice) {
                        case true:
                        previousTask->next = currentTask->next;
                        free(currentTask);
                        printf("The task '%s' has been deleted. You will return to the main menu.\n", targetTask);
                        return taskHead;
                        break;

                        case false:
                        printf("Task deletion has been canceled. You will return to the main menu.\n");
                        return taskHead;
                        break;
                    }
                    break;
                }
            } while (currentTask->next != NULL);
            if (strcmp(currentTask->taskName, targetTask) == 0) {
                printf("'%s' will be deleted.\n", targetTask);
                deleteChoice = inputContinueChoice();
                switch (deleteChoice) {
                    case true:
                    free(currentTask);
                    printf("The task '%s' has been deleted. You will return to the main menu.\n", targetTask);
                    return taskHead;
                    break;

                    case false:
                    printf("Task deletion has been canceled. You will return to the main menu.\n");
                    return taskHead;
                    break;
                }
            }
            else {
                printf("There is no task named '%s'! You will be returned to the main menu.\n", targetTask);
                return taskHead;
            }
        }
    }
}

struct task * addTask(struct task * taskHead) {
    struct task * addTask = (struct task *)malloc(sizeof(struct task));
    addTask->next = NULL;
    strcpy(addTask->status, "Ongoing");
    inputTaskName(addTask->taskName);
    inputTaskCategory(addTask->category);
    inputTaskDueDate(addTask->dueDate);
    if (taskHead == NULL) {
        taskHead = addTask;
    }
    else {
        bool sameTask;
        sameTask = addTaskValidator(taskHead, addTask);
        if (sameTask == true) {
            printf("You cannot have a task with the same name! Try again.\n");
            free(addTask);
            return taskHead;
        }
        struct task * taskPointer = taskHead;
        while (taskPointer->next != NULL)
            taskPointer = taskPointer->next;
        taskPointer->next = addTask;
    }
    printf("Task '%s' has been successfully created!\n", addTask->taskName);
    return taskHead;
}

void inputTaskStatus(char * status) {
    int choice = 0;
    bool subMenuLoop = true;
    do {
        printf("Please enter a status for the task.\n1) Completed\n2) Ongoing\n3) Postponed\n");
        while (getchar() != '\n');
        scanf("%i", &choice);
        switch(choice) {
            case 1:
            strcpy(status, "Completed");
            subMenuLoop = false;
            break;

            case 2:
            strcpy(status, "Ongoing");
            subMenuLoop = false;
            break;

            case 3:
            strcpy(status, "Postponed");
            subMenuLoop = false;
            break;

            default:
            printf("Invalid input! Try again.\n");
            continue;
        }
    } while(subMenuLoop == true);
}

void inputTaskCategory(char * category) {
    int choice = 0;
    bool subMenuLoop = true;
    do {
        printf("Please enter a category.\n1) Entertainment\n2) Family\n3) Finances\n4) Health\n5) Personal\n6) Religion\n7) School\n8) Social\n9) Work\n");
        while (getchar() != '\n');
        scanf("%i", &choice);
        switch(choice) {
            case 1:
            strcpy(category, "Entertainment");
            subMenuLoop = false;
            break;

            case 2:
            strcpy(category, "Family");
            subMenuLoop = false;
            break;

            case 3:
            strcpy(category, "Finances");
            subMenuLoop = false;
            break;

            case 4:
            strcpy(category, "Health");
            subMenuLoop = false;
            break;

            case 5:
            strcpy(category, "Personal");
            subMenuLoop = false;
            break;

            case 6:
            strcpy(category, "Religion");
            subMenuLoop = false;
            break;

            case 7:
            strcpy(category, "School");
            subMenuLoop = false;
            break;

            case 8:
            strcpy(category, "Social");
            subMenuLoop = false;
            break;

            case 9:
            strcpy(category, "Work");
            subMenuLoop = false;
            break;

            default:
            printf("Invalid input! Try again.\n");
            continue;
        }
    } while(subMenuLoop == true);
}

void inputTaskName(char * outputName) {
    char taskName[100] = "";
    bool subMenuLoop = true;
    while (subMenuLoop = true) {
        bool invalidCharacter = false;
        printf("Enter the name for this task (maximum 99 characters & no '#'): ");
        while (getchar() != '\n');
        scanf("%99[^\n]s", taskName);
        for (int count = 0; count < strlen(taskName); count++) {
            if (taskName[count] == '#') {
                printf("You cannot have '#' in the task name! Try again.\n");
                invalidCharacter = true;
            }
        }
        if (invalidCharacter == true)
            continue;
        else
            break;
    }
    strcpy(outputName, taskName);
}

void inputTaskDueDate(char * dueDate) {
    char day[10], month[10], year[10];
    char date[20] = "";
    int intDay, intMonth, intYear;
    time_t rawTime;
    time(&rawTime);
    struct tm * currentTime = localtime(&rawTime);
    int daysInAMonth[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    bool submMenuLoop = true;
    while (submMenuLoop == true) {
        printf("Please input a year (YYYY).\n");
        fflush(stdin);
        gets(year);
        intYear = atoi(year);
        if (intYear > 9999 || intYear <= 0) {
            printf("Invalid input! Try again.\n");
            continue;
        }
        printf("Please input a month (MM).\n");
        fflush(stdin);
        gets(month);
        intMonth = atoi(month);
        if (intMonth <= 0 || intMonth > 12) {
            printf("Invalid input! Try again.\n");
            continue;
        }
        printf("Please input a day (DD).\n");
        fflush(stdin);
        gets(day);
        intDay = atoi(day);
        if (intDay <= 0 || intDay > daysInAMonth[intMonth - 1]) {
            printf("Invalid input! Try again.\n");
            continue;
        }
        if (intYear < (currentTime->tm_year + 1900) || (intYear  == (currentTime->tm_year + 1900) && intMonth < (currentTime->tm_mon + 1)) || (intYear  == (currentTime->tm_year + 1900) && intMonth == (currentTime->tm_mon + 1) && intDay < currentTime->tm_mday)) {
            printf("The due date cannot be less than today's date! Try again.\n");
            continue;
        }
        break;
    }
    strcat(date, year);
    strcat(date, "/");
    strcat(date, month);
    strcat(date, "/");
    strcat(date, day);
    strcpy(dueDate, date);
}


struct task * formatStringToFile(struct task * taskHead) {
    struct task * taskPointer = NULL;
    taskPointer = taskHead;
    while (taskPointer->next != NULL) {
        for (int stringPos = 0;stringPos < strlen(taskPointer->taskName);stringPos++) {
            if (taskPointer->taskName[stringPos] == ' ')
                taskPointer->taskName[stringPos] = '-';
        }
        taskPointer = taskPointer->next;
    }
    for (int stringPos = 0;stringPos < strlen(taskPointer->taskName);stringPos++) {
        if (taskPointer->taskName[stringPos] == ' ')
            taskPointer->taskName[stringPos] = '-';
    }
    return taskHead;
}

void formatStringFromFile(char * string) {
    char line[100];
    strcpy(line, string);
    for (int stringPos = 0;stringPos < strlen(line);stringPos++) {
        if (line[stringPos] == '-')
            line[stringPos] = ' ';
    }
    strcpy(string, line);
}

void fileWriter(struct task * taskHead) {
    if (taskHead != NULL) {
        FILE * filePointer;
        struct task * taskPointer = NULL;
        filePointer = fopen("userdata.txt", "w");
        taskPointer = formatStringToFile(taskHead);
        while (taskPointer->next != NULL) {
            fprintf(filePointer, "%s#%s#%s#%s\n", taskPointer->taskName, taskPointer->category, taskPointer->dueDate, taskPointer->status);
            taskPointer = taskPointer->next;
        }
        fprintf(filePointer, "%s#%s#%s#%s\n", taskPointer->taskName, taskPointer->category, taskPointer->dueDate, taskPointer->status);
        fclose(filePointer);
    }
}

void programInitializer() {
    if (access("userdata.txt", F_OK) != 0) {
        printf("A file for saved task data does not exist. A new file will be created.\n");
        FILE * filePointer;
        filePointer = fopen("userdata.txt", "w");
        fclose(filePointer);
    }
}

struct task * fileReader() {
    FILE * filePointer;
    filePointer = fopen("userdata.txt", "r");
    char line[255];
    struct task * taskHead = (struct task *)malloc(sizeof(struct task));
    struct task * taskPointer = NULL;
    taskHead->next = NULL;
    taskPointer = taskHead;
    char * token;
    if (fscanf(filePointer, "%s\n", line) > 0) {
        token = strtok(line, "#");
        formatStringFromFile(token);
        strcpy(taskPointer->taskName, token);
        token = strtok(NULL, "#");
        strcpy(taskPointer->category, token);
        token = strtok(NULL, "#");
        strcpy(taskPointer->dueDate, token);
        token = strtok(NULL, "#");
        formatStringFromFile(token);
        strcpy(taskPointer->status, token);

    }
    else {
        printf("The file is empty! No tasks were loaded in.\n");
        taskHead = NULL;
        fclose(filePointer);
        return taskHead;
    }
    while (fscanf(filePointer, "%s\n", line) > 0) {
        struct task * newTask = (struct task *)malloc(sizeof(struct task));
        token = strtok(line, "#");
        formatStringFromFile(token);
        strcpy(newTask->taskName, token);
        token = strtok(NULL, "#");
        strcpy(newTask->category, token);
        token = strtok(NULL, "#");
        strcpy(newTask->dueDate, token);
        token = strtok(NULL, "#");
        formatStringFromFile(token);
        strcpy(newTask->status, token);
        newTask->next = NULL;
        taskPointer->next = newTask;
        taskPointer = taskPointer->next;
    }
    fclose(filePointer);
    return taskHead;
}

struct task * deleteLinkedList(struct task * taskHead) {
    struct task * taskPointer = NULL;
    struct task * nodeToDelete = NULL;
    taskPointer = taskHead;
    while (taskPointer != NULL) {
        nodeToDelete = taskPointer;
        taskPointer = taskPointer->next;
        free(nodeToDelete);
    }
    return taskPointer;
}

struct task * updateTask(struct task * taskHead) {
    if (taskHead == NULL) {
        printf("There are no tasks to view! Add a task first and try again.\n");
        return taskHead;
    }
    else {
        char targetTask[100];
        bool updateChoice;
        bool sameTask;
        struct task * taskPointer = NULL;
        taskPointer = taskHead;
        inputTaskName(targetTask);
        while (taskPointer->next != NULL) {
            if (strcmp(taskPointer->taskName, targetTask) == 0) {
                struct task * updatedTask = (struct task *)malloc(sizeof(struct task));
                printf("Task '%s' has been found!. Please enter the new task details.\n", taskPointer->taskName);
                inputTaskName(updatedTask->taskName);
                inputTaskCategory(updatedTask->category);
                inputTaskDueDate(updatedTask->dueDate);
                inputTaskStatus(updatedTask->status);
                sameTask = addTaskValidator(taskHead, updatedTask);
                if (sameTask == true) {
                    printf("You cannot have one or more tasks with the same name! Try again.\n");
                    return taskHead;
                }
                printf("Here are the details of the new task:\nTask name: %s\nCategory: %s\nDue Date: %s\nStatus: %s\n", updatedTask->taskName, updatedTask->category, updatedTask->dueDate, updatedTask->status);
                updateChoice = inputContinueChoice();
                switch(updateChoice) {
                    case true:
                    strcpy(taskPointer->taskName, updatedTask->taskName);
                    strcpy(taskPointer->category, updatedTask->category);
                    strcpy(taskPointer->dueDate, updatedTask->dueDate);
                    strcpy(taskPointer->status, updatedTask->status);
                    free(updatedTask);
                    printf("'%s' has been successfully updated!\n", taskPointer->taskName);
                    return taskHead;
                    break;

                    case false:
                    free(updatedTask);
                    printf("Task has not been updated. You will return to the main menu.\n");
                    return taskHead;
                    break;
                }
            }
            taskPointer = taskPointer->next;
        }
        if (strcmp(taskPointer->taskName, targetTask) == 0) {
            struct task * updatedTask = (struct task *)malloc(sizeof(struct task));
            printf("Task '%s' has been found!. Please enter the new task details.\n", taskPointer->taskName);
            inputTaskName(updatedTask->taskName);
            inputTaskCategory(updatedTask->category);
            inputTaskDueDate(updatedTask->dueDate);
            inputTaskStatus(updatedTask->status);
            sameTask = addTaskValidator(taskHead, updatedTask);
            if (sameTask == true) {
                printf("You cannot have one or more tasks with the same name! Try again.\n");
                return taskHead;
            }
            printf("Here are the details of the new task:\nTask name: %s\nCategory: %s\nDue Date: %s\nStatus: %s\n", updatedTask->taskName, updatedTask->category, updatedTask->dueDate, updatedTask->status);
            updateChoice = inputContinueChoice();
            switch(updateChoice) {
                case true:
                strcpy(taskPointer->taskName, updatedTask->taskName);
                strcpy(taskPointer->category, updatedTask->category);
                strcpy(taskPointer->dueDate, updatedTask->dueDate);
                strcpy(taskPointer->status, updatedTask->status);
                free(updatedTask);
                printf("'%s' has been successfully updated!\n", taskPointer->taskName);
                return taskHead;
                break;

                case false:
                free(updatedTask);
                printf("Task has not been updated. You will return to the main menu\n");
                return taskHead;
                break;
            }
        }
        printf("There is no task named '%s'! Try again.\n", targetTask);
        return taskHead;
    }
}

void switchTaskData(char * detailOne, char * detailTwo) {
    char temp[100];
    strcpy(temp, detailOne);
    strcpy(detailOne, detailTwo);
    strcpy(detailTwo, temp);
}

void switchTasks(struct task * taskOne, struct task * taskTwo) {
    switchTaskData(taskOne->taskName, taskTwo->taskName);
    switchTaskData(taskOne->category, taskTwo->category);
    switchTaskData(taskOne->dueDate, taskTwo->dueDate);
    switchTaskData(taskOne->status, taskTwo->status);

}

struct task * sortByCategory(struct task * taskHead) {
    int choice = 0;
    bool subMenuLoop = true;
    struct task * currentNode;
    struct task * switchNode;
    struct task * comparisonNode;
    do {
        printf("Select an order.\n1) Ascending\n2) Descending\n");
        while (getchar() != '\n');
        scanf("%i", &choice);
        switch (choice) {
            case 1:
            for (currentNode = taskHead;currentNode->next != NULL;currentNode = currentNode->next) {
                switchNode = currentNode;
                for (comparisonNode = currentNode->next;comparisonNode != NULL;comparisonNode = comparisonNode->next) {
                    if (strcmp(switchNode->category, comparisonNode->category) > 0)
                        switchNode = comparisonNode;
                }
                switchTasks(currentNode, switchNode);
            }
            subMenuLoop = false;
            break;

            case 2:
            for (currentNode = taskHead;currentNode->next != NULL;currentNode = currentNode->next) {
                switchNode = currentNode;
                for (comparisonNode = currentNode->next;comparisonNode != NULL;comparisonNode = comparisonNode->next) {
                    if (strcmp(switchNode->category, comparisonNode->category) < 0)
                        switchNode = comparisonNode;
                }
                switchTasks(currentNode, switchNode);
            }
            subMenuLoop = false;
            break;

            default:
            printf("Invalid input!. Try again.\n");
            continue;
        }
    } while (subMenuLoop == true);
    return taskHead;
}

struct task * sortByName(struct task * taskHead) {
    int choice = 0;
    bool subMenuLoop = true;
    struct task * currentNode;
    struct task * switchNode;
    struct task * comparisonNode;
    do {
        printf("Select an order.\n1) Ascending\n2) Descending\n");
        while (getchar() != '\n');
        scanf("%i", &choice);
        switch (choice) {
            case 1:
            for (currentNode = taskHead;currentNode->next != NULL;currentNode = currentNode->next) {
                switchNode = currentNode;
                for (comparisonNode = currentNode->next;comparisonNode != NULL;comparisonNode = comparisonNode->next) {
                    if (strcmp(switchNode->taskName, comparisonNode->taskName) > 0)
                        switchNode = comparisonNode;
                }
                switchTasks(currentNode, switchNode);
            }
            subMenuLoop = false;
            break;

            case 2:
            for (currentNode = taskHead;currentNode->next != NULL;currentNode = currentNode->next) {
                switchNode = currentNode;
                for (comparisonNode = currentNode->next;comparisonNode != NULL;comparisonNode = comparisonNode->next) {
                    if (strcmp(switchNode->taskName, comparisonNode->taskName) < 0)
                        switchNode = comparisonNode;
                }
                switchTasks(currentNode, switchNode);
            }
            subMenuLoop = false;
            break;

            default:
            printf("Invalid input!. Try again.\n");
            continue;
        }
    } while (subMenuLoop == true);
    return taskHead;
}

struct task * sortByDueDate(struct task * taskHead) {
    int choice = 0;
    bool subMenuLoop = true;
    struct task * currentNode;
    struct task * switchNode;
    struct task * comparisonNode;
    do {
        printf("Select an order.\n1) Ascending\n2) Descending\n");
        while (getchar() != '\n');
        scanf("%i", &choice);
        switch (choice) {
            case 1:
            for (currentNode = taskHead;currentNode->next != NULL;currentNode = currentNode->next) {
                switchNode = currentNode;
                for (comparisonNode = currentNode->next;comparisonNode != NULL;comparisonNode = comparisonNode->next) {
                    if (strcmp(switchNode->dueDate, comparisonNode->dueDate) > 0)
                        switchNode = comparisonNode;
                }
                switchTasks(currentNode, switchNode);
            }
            subMenuLoop = false;
            break;

            case 2:
            for (currentNode = taskHead;currentNode->next != NULL;currentNode = currentNode->next) {
                switchNode = currentNode;
                for (comparisonNode = currentNode->next;comparisonNode != NULL;comparisonNode = comparisonNode->next) {
                    if (strcmp(switchNode->dueDate, comparisonNode->dueDate) < 0)
                        switchNode = comparisonNode;
                }
                switchTasks(currentNode, switchNode);
            }
            subMenuLoop = false;
            break;

            default:
            printf("Invalid input!. Try again.\n");
            continue;
        }
    } while (subMenuLoop == true);
    return taskHead;
}

struct task * sortByStatus(struct task * taskHead) {
    int choice = 0;
    bool subMenuLoop = true;
    struct task * currentNode;
    struct task * switchNode;
    struct task * comparisonNode;
    do {
        printf("Select an order.\n1) Ascending\n2) Descending\n");
        while (getchar() != '\n');
        scanf("%i", &choice);
        switch (choice) {
            case 1:
            for (currentNode = taskHead;currentNode->next != NULL;currentNode = currentNode->next) {
                switchNode = currentNode;
                for (comparisonNode = currentNode->next;comparisonNode != NULL;comparisonNode = comparisonNode->next) {
                    if (strcmp(switchNode->status, comparisonNode->status) > 0)
                        switchNode = comparisonNode;
                }
                switchTasks(currentNode, switchNode);
            }
            subMenuLoop = false;
            break;

            case 2:
            for (currentNode = taskHead;currentNode->next != NULL;currentNode = currentNode->next) {
                switchNode = currentNode;
                for (comparisonNode = currentNode->next;comparisonNode != NULL;comparisonNode = comparisonNode->next) {
                    if (strcmp(switchNode->status, comparisonNode->status) < 0)
                        switchNode = comparisonNode;
                }
                switchTasks(currentNode, switchNode);
            }
            subMenuLoop = false;
            break;

            default:
            printf("Invalid input!. Try again.\n");
            continue;
        }
    } while (subMenuLoop == true);
    return taskHead;
}

struct task * viewTaskDetails(struct task * taskHead) {
        struct task * taskPointer;
        char targetTask[100] = "";
        printf("Here are your saved tasks:\n");
        for (taskPointer = taskHead; taskPointer->next != NULL;taskPointer = taskPointer->next)
            printf("%s\n", taskPointer->taskName);
        printf("%s\n", taskPointer->taskName);
        printf("Input a task name to view the task's details.\n");
        inputTaskName(targetTask);
        for (taskPointer = taskHead; taskPointer->next != NULL;taskPointer = taskPointer->next)
            if (strcmp(taskPointer->taskName, targetTask) == 0) {
                printf("Here the details that task.\nTask name: %s\nCategory: %s\nStatus: %s\nDue date: %s\n", taskPointer->taskName, taskPointer->category, taskPointer->status, taskPointer->dueDate);
                return taskHead;
            }
        if (strcmp(taskPointer->taskName, targetTask) == 0) {
            printf("Here the details that task.\nTask name: %s\nCategory: %s\nStatus: %s\nDue date: %s\n", taskPointer->taskName, taskPointer->category, taskPointer->status, taskPointer->dueDate);
            return taskHead;
        }
        printf("'%s' does not exist! Try again.\n", targetTask);
        return taskHead;
}

struct task * viewTask(struct task * taskHead) {
    if (taskHead == NULL)
        printf("There are no tasks to view! Add or load a task first and try again.\n");
    else {
        int choice = 0;
        bool subMenuLoop = true;
        do {
            printf("Select a task detail to sort by.\n1) Category\n2) Due date\n3) Name\n4) Status\n");
            while (getchar() != '\n');
            scanf("%i", &choice);
            switch (choice) {
                case 1:
                taskHead = sortByCategory(taskHead);
                subMenuLoop = false;
                break;

                case 2:
                taskHead = sortByDueDate(taskHead);
                subMenuLoop = false;
                break;

                case 3:
                taskHead = sortByName(taskHead);
                subMenuLoop = false;
                break;

                case 4:
                taskHead = sortByStatus(taskHead);
                subMenuLoop = false;
                break;

                default:
                printf("Invalid input! Try again.\n");
                continue;
            }
        } while (subMenuLoop == true);
        taskHead = viewTaskDetails(taskHead);
    }
    return taskHead;
}

struct task * checkDueDate(struct task * taskHead) {
    if (taskHead == NULL)
        return taskHead;
    struct task * taskPointer = NULL;
    taskPointer = taskHead;
    char day[10], month[10], year[10];
    char * token;
    int intDay, intMonth, intYear;
    char dueDate[30];
    time_t rawTime;
    time(&rawTime);
    struct tm * currentTime = localtime(&rawTime);
    while (taskPointer->next != NULL) {
        strcpy(dueDate, taskPointer->dueDate);
        token = strtok(dueDate, "/");
        strcpy(year, token);
        token = strtok(NULL, "/");
        strcpy(month, token);
        token = strtok(NULL, "/");
        strcpy(day, token);
        intDay = atoi(day);
        intMonth = atoi(month);
        intYear = atoi(year);
        if (intYear < (currentTime->tm_year + 1900) || (intYear  == (currentTime->tm_year + 1900) && intMonth < (currentTime->tm_mon + 1)) || (intYear  == (currentTime->tm_year + 1900) && intMonth == (currentTime->tm_mon + 1) && intDay < currentTime->tm_mday)) {
            printf("'%s' is past due!.\n", taskPointer->taskName);
            strcpy(taskPointer->status, "Late");
        }
        taskPointer = taskPointer->next;
    }
    strcpy(dueDate, taskPointer->dueDate);
    token = strtok(dueDate, "/");
    strcpy(year, token);
    token = strtok(NULL, "/");
    strcpy(month, token);
    token = strtok(NULL, "/");
    strcpy(day, token);
    intDay = atoi(day);
    intMonth = atoi(month);
    intYear = atoi(year);
    if (intYear < (currentTime->tm_year + 1900) || (intYear  == (currentTime->tm_year + 1900) && intMonth < (currentTime->tm_mon + 1)) || (intYear  == (currentTime->tm_year + 1900) && intMonth == (currentTime->tm_mon + 1) && intDay < currentTime->tm_mday)) {
        printf("'%s' is past due!.\n", taskPointer->taskName);
        strcpy(taskPointer->status, "Late");
    }
    return taskHead;
}

bool addTaskValidator(struct task * taskHead, struct task * addTask) {
    struct task * taskPointer = NULL;
    taskPointer = taskHead;
    while (taskPointer->next != NULL) {
        if (strcmp(taskPointer->taskName, addTask->taskName) == 0) {
            return true;
        }
        taskPointer = taskPointer->next;
    }
    if (strcmp(taskPointer->taskName, addTask->taskName) == 0) {
        return true;
    }
    return false;
}

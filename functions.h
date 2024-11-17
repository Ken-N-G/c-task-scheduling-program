#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

struct task {
    char taskName[100];
    char category[20];
    char dueDate[20];
    char status[10];
    struct task * next;
};

struct task * mainMenu(struct task *);

struct task * viewTask(struct task *);

struct task * sortByCategory(struct task *);

struct task * sortByDueDate(struct task *);

struct task * sortByName(struct task *);

struct task * sortByStatus(struct task *);

struct task * updateTask(struct task *);

struct task * viewTaskDetails(struct task *);

void switchTasks(struct task *, struct task *);

void switchTaskData(char *, char *);

void inputTaskCategory(char *);

void inputTaskName(char *);

void inputTaskStatus(char *);

void inputTaskDueDate(char *);

struct task * addTask(struct task *);

struct task * fileReader();

void programInitializer();

void fileWriter(struct task *);

struct task * deleteTask(struct task *);

bool inputContinueChoice();

struct task * formatStringToFile(struct task *);

void formatStringFromFile(char *);

struct task * deleteLinkedList(struct task *);

bool addTaskValidator(struct task *, struct task *);

struct task * checkDueDate(struct task *);

#endif // FUNCTIONS_H_INCLUDED

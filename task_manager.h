#ifndef TASK_MANAGER_H
#define TASK_MANAGER_H

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Node {
public:
    string data;
    Node* next;

    Node(string d);
};

class TaskManager {
private:
    Node* head;

public:
    TaskManager();
    ~TaskManager();
    void addTask(string task);
    void displayTasks();
    void deleteTask(string task);
    void saveTasks(string filename);
    void loadTasks(string filename);
    void addTaskFromInput(); // New function to add a task from user input
};

#endif
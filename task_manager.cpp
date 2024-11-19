#include "task_manager.h"
#include <limits>

Node::Node(string d) {
    data = d;
    next = NULL;
}

TaskManager::TaskManager() {
    head = NULL;
}

TaskManager::~TaskManager() {
    while (head != NULL) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

void TaskManager::addTask(string task) {
    Node* newTask = new Node(task);
    if (head == NULL) {
        head = newTask;
    } else {
        Node* current = head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newTask;
    }
}

void TaskManager::addTaskFromInput() {
    string task;
    cout << "Enter task: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore previous new line character
    getline(cin, task);
    addTask(task);
}

void TaskManager::displayTasks() {
    Node* current = head;
    while (current != NULL) {
        cout << current->data << endl;
        current = current->next;
    }
}

void TaskManager::deleteTask(string task) {
    if (head == NULL) {
        return;
    }

    if (head->data == task) {
        Node* temp = head;
        head = head->next;
        delete temp;
        return;
    }

    Node* current = head;
    while (current->next != NULL) {
        if (current->next->data == task) {
            Node* temp = current->next;
            current->next = current->next->next;
            delete temp;
            return;
        }
        current = current->next;
    }
}

void TaskManager::saveTasks(string filename) {
    ofstream file(filename);
    Node* current = head;
    while (current != NULL) {
        file << current->data << endl;
        current = current->next;
    }
    file.close();
}

void TaskManager::loadTasks(string filename) {
    ifstream file(filename);
    string task;
    while (getline(file, task)) {
        addTask(task);
    }
    file.close();
}

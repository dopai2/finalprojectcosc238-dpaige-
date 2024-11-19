#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Task {
private:
    string taskName;
    string deadline;
public:
    Task(string name, string date) : taskName(name), deadline(date) {}
    string getName() const { return taskName; }
    string getDeadline() const { return deadline; }
    void setName(string name) { taskName = name; }
    void setDeadline(string date) { deadline = date; }
};

class Node {
public:
    Task task;
    Node* next;
    Node(Task t) : task(t), next(nullptr) {}
    ~Node() {
        delete next;
    }
};

class TaskList {
private:
    Node* head;
public:
    TaskList() : head(nullptr) {}
    ~TaskList() {
        delete head;
    }
    void addTask(Task t) {
        Node* newNode = new Node(t);
        newNode->next = head;
        head = newNode;
    }
    void displayTasks() const {
        Node* current = head;
        while (current != nullptr) {
            cout << "Task: " << current->task.getName() << "\tDeadline: " << current->task.getDeadline() << endl;
            current = current->next;
        }
    }
    void saveTasksToFile(string filename) const {
        ofstream outFile(filename);
        if (!outFile) {
            cout << "Unable to open file: " << filename << endl;
            return;
        }
        Node* current = head;
        while (current != nullptr) {
            outFile << current->task.getName() << "," << current->task.getDeadline() << endl;
            current = current->next;
        }
        outFile.close();
    }
    void loadTasksFromFile(string filename) {
        ifstream inFile(filename);
        if (!inFile) {
            cout << "Unable to open file: " << filename << endl;
            return;
        }
        string name, deadline;
        while (getline(inFile, name, ',')) {
            getline(inFile, deadline);
            Task t(name, deadline);
            addTask(t);
        }
        inFile.close();
    }
    void deleteTask(string name) {
        Node* current = head;
        Node* previous = nullptr;

        while (current != nullptr) {
            if (current->task.getName() == name) {
                if (previous == nullptr) {
                    head = current->next;
                } else {
                    previous->next = current->next;
                }
                current->next = nullptr;
                delete current;
                return;
            }
            previous = current;
            current = current->next;
        }
        cout << "Task not found." << endl;
    }
    void updateTask(string name, string newName, string newDeadline) {
        Node* current = head;

        while (current != nullptr) {
            if (current->task.getName() == name) {
                current->task.setName(newName);
                current->task.setDeadline(newDeadline);
                return;
            }
            current = current->next;
        }
        cout << "Task not found." << endl;
    }
};
int main() {
    TaskList tasks;
    tasks.addTask(Task("Complete project proposal for COSC238 Final Project", "2024-04-23"));
    tasks.addTask(Task("Prepare Code for COSC238 Final project", "2024-05-07"));
    tasks.addTask(Task("Write a txt file for COSC238 Final Project", "2024-05-16"));
    cout << "Tasks before file is saved:" << endl;
    tasks.displayTasks();
    tasks.saveTasksToFile("tasks.txt");
    tasks = TaskList();
    tasks.loadTasksFromFile("tasks.txt");
    cout << "\nTasks after loading from file:" << endl;
    tasks.displayTasks();
    // Deleting a task
    cout << "\nDeleting task: Prepare Code for COSC238 Final project" << endl;
    tasks.deleteTask("Prepare Code for COSC238 Final project");
    tasks.displayTasks();
    // Updating a task
    cout << "\nUpdating task: Complete project proposal for COSC238 Final Project" << endl;
    tasks.updateTask("Complete project proposal for COSC238 Final Project", "Complete project proposal", "2024-05-10");
    tasks.displayTasks();
    return 0;
}

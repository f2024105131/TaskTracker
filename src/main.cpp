#include <iostream>
#include <limits>
#include <string>

#include "TaskManager.h"

namespace {

void printMenu() {
    std::cout << "\n==== Task & Habit Tracker ====\n"
                  << "1. View tasks\n"
                  << "2. Add task\n"
                  << "3. Edit task\n"
                  << "4. Delete task\n"
                  << "5. Toggle complete\n"
                  << "6. Sort by priority\n"
                  << "7. Sort by due date\n"
                  << "0. Exit\n"
                  << "Choose an option: ";
}

// Reads a full line of input, tolerating a leftover '\n' from prior >> reads.
std::string readLine(const std::string& prompt) {
    std::cout << prompt;
    std::string line;
    std::getline(std::cin, line);
    return line;
}

int readInt(const std::string& prompt) {
    std::cout << prompt;
    int value;
    while (!(std::cin >> value)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Please enter a valid number: ";
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return value;
}

Priority readPriority() {
    std::string input = readLine("Priority (Low/Medium/High) [Medium]: ");
    if (input.empty()) return Priority::Medium;
    return stringToPriority(input);
}

void handleAdd(TaskManager& manager) {
    std::string title = readLine("Title: ");
    std::string description = readLine("Description: ");
    Priority priority = readPriority();
    std::string dueDate = readLine("Due date (YYYY-MM-DD, blank for none): ");

    int id = manager.addTask(title, description, priority, dueDate);
    std::cout << "Added task #" << id << ".\n";
}

void handleEdit(TaskManager& manager) {
    int id = readInt("Task ID to edit: ");
    std::cout << "Leave a field blank to keep its current value.\n";
    std::string title = readLine("New title: ");
    std::string description = readLine("New description: ");
    Priority priority = readPriority();
    std::string dueDate = readLine("New due date (YYYY-MM-DD): ");

    if (manager.editTask(id, title, description, priority, dueDate)) {
        std::cout << "Task #" << id << " updated.\n";
    } else {
        std::cout << "No task with ID " << id << ".\n";
    }
}

void handleDelete(TaskManager& manager) {
    int id = readInt("Task ID to delete: ");
    if (manager.removeTask(id)) {
        std::cout << "Task #" << id << " deleted.\n";
    } else {
        std::cout << "No task with ID " << id << ".\n";
    }
}

void handleToggle(TaskManager& manager) {
    int id = readInt("Task ID to toggle complete: ");
    if (manager.toggleComplete(id)) {
        std::cout << "Task #" << id << " updated.\n";
    } else {
        std::cout << "No task with ID " << id << ".\n";
    }
}

} // namespace

int main() {
    TaskManager manager("data/tasks.txt");

    std::cout << "Loaded " << manager.taskCount() << " task(s) from disk.\n";

    bool running = true;
    while (running) {
        printMenu();
        int choice = readInt("");

        switch (choice) {
            case 1: manager.listTasks(SortMode::None); break;
            case 2: handleAdd(manager); break;
            case 3: handleEdit(manager); break;
            case 4: handleDelete(manager); break;
            case 5: handleToggle(manager); break;
            case 6: manager.listTasks(SortMode::Priority); break;
            case 7: manager.listTasks(SortMode::DueDate); break;
            case 0: running = false; break;
            default: std::cout << "Invalid option, try again.\n"; break;
        }
    }

    std::cout << "Goodbye!\n";
    return 0;
}
#include "TaskManager.h"

#include <algorithm>
#include <iomanip>
#include <iostream>

TaskManager::TaskManager(const std::string& storageFile)
    : fileHandler_(storageFile) {
    load();
}

std::vector<Task>::iterator TaskManager::findTaskById(int id) {
    return std::find_if(tasks_.begin(), tasks_.end(),
                         [id](const Task& t) { return t.getId() == id; });
}

int TaskManager::addTask(const std::string& title,
                          const std::string& description,
                          Priority priority,
                          const std::string& dueDate) {
    int id = nextId_++;
    tasks_.emplace_back(id, title, description, priority, dueDate);
    save();
    return id;
}

bool TaskManager::removeTask(int id) {
    auto it = findTaskById(id);
    if (it == tasks_.end()) return false;
    tasks_.erase(it);
    save();
    return true;
}

bool TaskManager::editTask(int id,
                            const std::string& title,
                            const std::string& description,
                            Priority priority,
                            const std::string& dueDate) {
    auto it = findTaskById(id);
    if (it == tasks_.end()) return false;

    if (!title.empty())       it->setTitle(title);
    if (!description.empty()) it->setDescription(description);
    it->setPriority(priority);
    if (!dueDate.empty())     it->setDueDate(dueDate);

    save();
    return true;
}

bool TaskManager::toggleComplete(int id) {
    auto it = findTaskById(id);
    if (it == tasks_.end()) return false;
    it->setCompleted(!it->isCompleted());
    save();
    return true;
}

void TaskManager::listTasks(SortMode mode) const {
    if (tasks_.empty()) {
        std::cout << "No tasks yet. Add one from the main menu.\n";
        return;
    }

    std::vector<Task> view = tasks_; // sort a copy; storage order stays stable

    switch (mode) {
        case SortMode::Priority:
            std::stable_sort(view.begin(), view.end(), [](const Task& a, const Task& b) {
                return static_cast<int>(a.getPriority()) > static_cast<int>(b.getPriority());
            });
            break;
        case SortMode::DueDate:
            // Empty due dates ("-") sort after any real ISO date.
            std::stable_sort(view.begin(), view.end(), [](const Task& a, const Task& b) {
                const auto& da = a.getDueDate();
                const auto& db = b.getDueDate();
                if (da.empty()) return false;
                if (db.empty()) return true;
                return da < db;
            });
            break;
        case SortMode::None:
        default:
            break;
    }

    std::cout << std::left
               << "     " << std::setw(4) << "ID"
               << std::setw(22) << "Title"
               << std::setw(9) << "Priority"
               << std::setw(12) << "Due Date" << "\n";
    std::cout << std::string(50, '-') << "\n";
    for (const auto& t : view) t.display();
}

void TaskManager::load() {
    tasks_ = fileHandler_.loadTasks();
    nextId_ = 1;
    for (const auto& t : tasks_) {
        nextId_ = std::max(nextId_, t.getId() + 1);
    }
}

void TaskManager::save() const {
    fileHandler_.saveTasks(tasks_);
}
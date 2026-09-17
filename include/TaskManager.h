#pragma once

#include <string>
#include <vector>

#include "FileHandler.h"
#include "Task.h"

enum class SortMode {
    None,
    Priority,
    DueDate
};

class TaskManager {
public:
    explicit TaskManager(const std::string& storageFile);

    
    int addTask(const std::string& title,
                const std::string& description,
                Priority priority,
                const std::string& dueDate);

    bool removeTask(int id);

    bool editTask(int id,
                  const std::string& title,
                  const std::string& description,
                  Priority priority,
                  const std::string& dueDate);

    bool toggleComplete(int id);

    void listTasks(SortMode mode = SortMode::None) const;
    std::size_t taskCount() const noexcept { return tasks_.size(); }

    void load();
    void save() const;

private:
    std::vector<Task> tasks_;
    int nextId_ = 1;
    FileHandler fileHandler_;

    std::vector<Task>::iterator findTaskById(int id);
};
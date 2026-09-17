#pragma once

#include <string>
#include <vector>

#include "Task.h"

class FileHandler {
public:
    explicit FileHandler(std::string filePath);

    std::vector<Task> loadTasks() const;
    bool saveTasks(const std::vector<Task>& tasks) const;

private:
    std::string filePath_;

  
    static std::string escape(const std::string& field);
    static std::string unescape(const std::string& field);
};
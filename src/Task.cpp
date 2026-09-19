#include "Task.h"

#include <iomanip>
#include <iostream>

std::string priorityToString(Priority p) {
    switch (p) {
        case Priority::Low:    return "Low";
        case Priority::Medium: return "Medium";
        case Priority::High:   return "High";
    }
    return "Medium";
}

Priority stringToPriority(const std::string& s) {
    if (s == "Low" || s == "low" || s == "1")    return Priority::Low;
    if (s == "High" || s == "high" || s == "3")  return Priority::High;
    return Priority::Medium; // default / "Medium" / "2"
}

Task::Task(int id,
           std::string title,
           std::string description,
           Priority priority,
           std::string dueDate,
           bool completed)
    : id_(id),
      title_(std::move(title)),
      description_(std::move(description)),
      priority_(priority),
      dueDate_(std::move(dueDate)),
      completed_(completed) {}

void Task::setTitle(std::string title) { title_ = std::move(title); }
void Task::setDescription(std::string description) { description_ = std::move(description); }
void Task::setPriority(Priority priority) { priority_ = priority; }
void Task::setDueDate(std::string dueDate) { dueDate_ = std::move(dueDate); }
void Task::setCompleted(bool completed) { completed_ = completed; }

void Task::display() const {
    std::cout << std::left
               << "[" << (completed_ ? "x" : " ") << "] "
               << std::setw(4)  << id_
               << std::setw(22) << (title_.size() > 20 ? title_.substr(0, 17) + "..." : title_)
               << std::setw(9)  << priorityToString(priority_)
               << std::setw(12) << (dueDate_.empty() ? "-" : dueDate_)
               << "\n";
}
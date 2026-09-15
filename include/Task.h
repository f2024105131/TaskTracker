#pragma once

#include <string>

enum class Priority {
    Low,
    Medium,
    High
};

std::string priorityToString(Priority p);
Priority stringToPriority(const std::string& s);


class Task {
public:
    Task() = default;
    Task(int id,
         std::string title,
         std::string description,
         Priority priority,
         std::string dueDate,   // ISO format "YYYY-MM-DD", empty = no due date
         bool completed = false);

    // --- Accessors ---
    int getId() const noexcept { return id_; }
    const std::string& getTitle() const noexcept { return title_; }
    const std::string& getDescription() const noexcept { return description_; }
    Priority getPriority() const noexcept { return priority_; }
    const std::string& getDueDate() const noexcept { return dueDate_; }
    bool isCompleted() const noexcept { return completed_; }

    // --- Mutators ---
    void setTitle(std::string title);
    void setDescription(std::string description);
    void setPriority(Priority priority);
    void setDueDate(std::string dueDate);
    void setCompleted(bool completed);

    
    void display() const;

private:
    int id_ = 0;
    std::string title_;
    std::string description_;
    Priority priority_ = Priority::Medium;
    std::string dueDate_;
    bool completed_ = false;
};
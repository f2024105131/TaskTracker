#include "FileHandler.h"

#include <fstream>
#include <iostream>
#include <sstream>

namespace {
constexpr char kDelimiter = '|';

std::string replaceAll(std::string s, const std::string& from, const std::string& to) {
    size_t pos = 0;
    while ((pos = s.find(from, pos)) != std::string::npos) {
        s.replace(pos, from.size(), to);
        pos += to.size();
    }
    return s;
}
} // namespace

FileHandler::FileHandler(std::string filePath) : filePath_(std::move(filePath)) {}

std::string FileHandler::escape(const std::string& field) {
    std::string out = replaceAll(field, "|", "%7C");
    out = replaceAll(out, "\n", "%0A");
    return out;
}

std::string FileHandler::unescape(const std::string& field) {
    std::string out = replaceAll(field, "%7C", "|");
    out = replaceAll(out, "%0A", "\n");
    return out;
}

bool FileHandler::saveTasks(const std::vector<Task>& tasks) const {
    std::ofstream out(filePath_, std::ios::trunc);
    if (!out.is_open()) {
        std::cerr << "Error: could not open '" << filePath_ << "' for writing.\n";
        return false;
    }

    for (const auto& t : tasks) {
        out << t.getId() << kDelimiter
            << escape(t.getTitle()) << kDelimiter
            << escape(t.getDescription()) << kDelimiter
            << priorityToString(t.getPriority()) << kDelimiter
            << t.getDueDate() << kDelimiter
            << (t.isCompleted() ? 1 : 0) << '\n';
    }
    return true;
}

std::vector<Task> FileHandler::loadTasks() const {
    std::vector<Task> tasks;
    std::ifstream in(filePath_);
    if (!in.is_open()) {
        // No file yet is not an error — first run starts empty.
        return tasks;
    }

    std::string line;
    while (std::getline(in, line)) {
        if (line.empty()) continue;

        std::vector<std::string> fields;
        std::stringstream ss(line);
        std::string field;
        while (std::getline(ss, field, kDelimiter)) {
            fields.push_back(field);
        }
        if (fields.size() != 6) {
            std::cerr << "Warning: skipping malformed line in " << filePath_ << "\n";
            continue;
        }

        try {
            int id = std::stoi(fields[0]);
            std::string title = unescape(fields[1]);
            std::string description = unescape(fields[2]);
            Priority priority = stringToPriority(fields[3]);
            std::string dueDate = fields[4];
            bool completed = fields[5] == "1";

            tasks.emplace_back(id, title, description, priority, dueDate, completed);
        } catch (const std::exception& e) {
            std::cerr << "Warning: skipping bad record (" << e.what() << ")\n";
        }
    }
    return tasks;
}
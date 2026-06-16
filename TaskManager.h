#pragma once
#include "Task.h"
#include <vector>

class TaskManager {
private:
    std::vector<Task> tasks;

public:
    void addTask(std::string title);
    void viewTasks();
    void loadTasks();
    void saveTasks();
    void taskCompletion(int completedTaskNum);
    void taskDeletion(int deleteTaskNum);
    void taskSearch(std::string keyword);
    void markFavorite(int favoriteTaskNum);
    void editTask(int index, const std::string& args);
    void sortTasks(std::string criteria, std::string order);
    void customSortTasks();
    void createTaskFolder(std::string folderName);
};
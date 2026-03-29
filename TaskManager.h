#pragma once
#include "Task.h"
#include <vector>

class TaskManager {
private:
    std::vector<Task> tasks;

public:
    void addTask();
    void viewTasks();
    void LoadTasks();
    void saveTasks();
    void taskCompletion(int completedTaskNum);
    void taskDeletion(int deleteTaskNum);
    void taskSearch(std::string keyword);
    void markFavorite(int favoriteTaskNum);
};
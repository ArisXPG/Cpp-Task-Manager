#include "Task.h"
#include "TaskManager.h"
#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <sstream>

using namespace std;

// Function for task addition
void TaskManager::addTask(){
    Task newTask;
    string title;

    cout << "Enter task title: ";
    getline(cin, title);
    newTask.setTitle(title);
    newTask.isCompleted(false);
    newTask.isFavorited(false);
    tasks.push_back(newTask);
}

// Function for viewing tasks
void TaskManager::viewTasks(){
    cout << "[=————REGISTERED TASKS————=]" << endl;
    cout << "Tasks: " << endl;
    for(int i = 0; i < tasks.size(); i++){
        tasks[i].display(i);
    }
    cout << "[——————————————————————————] " << endl;
    cout << endl;
}

// Function for loading tasks from file
void TaskManager::loadTasks(){
    ifstream inTasks("tasks.txt");
    if(inTasks.is_open()){
        string line;
        while(getline(inTasks, line)){
            size_t position = line.find("|");
        
            if(position != string::npos){
                string status = line.substr(0, position);
                string title = line.substr(position + 1).substr(0, line.substr(position + 1).find("|"));
                size_t secondPosition = line.find(title) + title.size() + 1;
                string favorited = line.substr(secondPosition);

                Task loadedTask;
                loadedTask.isCompleted((status == "1"));
                loadedTask.setTitle(title);
                loadedTask.isFavorited((favorited == "1"));
                tasks.push_back(loadedTask);
            }
        }
    }
    
    else {
        cout << "Error loading tasks from file!" << endl;
    }

inTasks.close();
}


// Function for saving tasks to file
void TaskManager::saveTasks(){
    ofstream outTasks("tasks.txt");
    if(outTasks.is_open()){
        for(int i = 0; i < tasks.size(); i++){
            outTasks << tasks[i].isCompleted() << "|" << tasks[i].getTitle() << "|" << tasks[i].isFavorited() << endl;
        }
    }

    else {
        cout << "Error saving tasks to file!" << endl;
    }

    outTasks.close();
}

// Function for task completion/pending status update
void TaskManager::taskCompletion(int completedTaskNum){
                
    int indexCompleted = completedTaskNum - 1;
                
    if(completedTaskNum > 0 && completedTaskNum <= tasks.size()){
        if(tasks[indexCompleted].isCompleted() == true){
            char response;
            cout << "Task is already marked as completed! Do you wish to mark it as pending? (Y/N)" << endl << endl;
            cin >> response;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            // Check user response for marking as pending or left unchanged
            if((response == 'Y' || response == 'y')){
                tasks[indexCompleted].markPending();
                cout << "Task No. " << completedTaskNum <<  " status updated to 'pending' successfully!" << endl << endl;
            } 
            else if (response == 'N' || response == 'n') {
                cout << "Task No. " << completedTaskNum << " was not updated." << endl << endl;
                }
                else {
                    cout << "Invalid response! No changes made to task status." << endl << endl;
                }
        } 
                    
        else {                    
            tasks[indexCompleted].markCompleted();
            cout << "Task No. " << completedTaskNum << " status updated to 'completed' successfully!" << endl << endl;
            }
        }
    
    else {
        cout << "A task with that number does not exist!" << endl << endl;
    }
}

// Function for task deletion
void TaskManager::taskDeletion(int deleteTaskNum){
    int indexDelete = deleteTaskNum - 1;

    if(deleteTaskNum > 0 && deleteTaskNum <= tasks.size()){
        char response;
        cout << "Are you sure you wish to delete task No. " << deleteTaskNum << "? (Y/N)\n";
        cin >> response;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        // Check user response for deletion confirmation
        if((response == 'Y' || response =='y')){
            tasks.erase(tasks.begin() + indexDelete);
            cout << "Task No. " << deleteTaskNum << " deleted successfully! Index of tasks changed accordingly!" << endl << endl;
        }
                    
        else if (response == 'N' || response == 'n') {
            cout << "Task No. " << deleteTaskNum << " was not deleted." << endl << endl;
        }
                    
        else {
            cout << "Invalid response! Task No. " << deleteTaskNum << " was not deleted." << endl << endl;
        }
    }
                
    else {
        cout << "A task with that number does not exist!" << endl << endl;
    }
}

// Function for task searching
void TaskManager::taskSearch(string keyword){
    cout << "Search results for '" << keyword << "': " << endl;
    bool found = false;

    for(int i = 0; i < tasks.size(); i++){
        if(tasks[i].matches(keyword)){
            tasks[i].display(i);
            found = true;
        }
    }

    if(!found){
        cout << "No tasks found containing '" << keyword << "'." << endl;
    }
    cout << "[——————————————————————] " << endl;
    cout << endl;
}

// Function for marking/unmarking tasks as favorite
void TaskManager::markFavorite(int favoriteTaskNum){
    int indexFavorite = favoriteTaskNum - 1;

    if(favoriteTaskNum > 0 && favoriteTaskNum <= tasks.size()){
        if(tasks[indexFavorite].isFavorited() == true){
            char response;
            cout << "Task is already marked as favorited! Do you wish to unmark it as favorite? (Y/N)" << endl << endl;
            cin >> response;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            // Check user response for unmarking as favorite or left unchanged
            if((response == 'Y' || response == 'y')){
                tasks[indexFavorite].isFavorited(false);
                cout << "Task No. " << favoriteTaskNum <<  " is no longer marked as favorite!" << endl << endl;
            } 
            else if (response == 'N' || response == 'n') {
                cout << "Task No. " << favoriteTaskNum << " was not updated." << endl << endl;
                }
                else {
                    cout << "Invalid response! No changes made to task's favorite status." << endl << endl;
                }
        } 
                    
        else {                    
            tasks[indexFavorite].isFavorited(true);
            cout << "Task No. " << favoriteTaskNum << " is now marked as favorite!" << endl << endl;
            }
        }
    
    else {
        cout << "A task with that number does not exist!" << endl << endl;
    }
}

void TaskManager::editTask(int index){
    int indexEdit = index - 1;

    if(indexEdit >= 0 && indexEdit < tasks.size()){
        string newTitle;
        cout << "Enter a new title for the selected task: ";
        getline(cin, newTitle);
        tasks[indexEdit].setTitle(newTitle);

        cout << "Task No. " << index << " title updated successfully!" << endl << endl;
    }
    else {
        cout << "Invalid task number!" << endl << endl;
    }
}

void TaskManager::sortTasks(string criteria, string order){
    if(criteria == "title"){
        if(order == "asc"){
            sort(tasks.begin(), tasks.end(), [](const Task& a, const Task& b){
                return a.getTitle() < b.getTitle();
            });
            cout << "Tasks sorted by title in ascending order successfully!" << endl << endl;
            viewTasks();
        }
        else if(order == "desc"){
            sort(tasks.begin(), tasks.end(), [](const Task& a, const Task& b){
                return a.getTitle() > b.getTitle();
            });
            cout << "Tasks sorted by title in descending order successfully!" << endl << endl;
            viewTasks();
        }
        else if(order == ""){
            sort(tasks.begin(), tasks.end(), [](const Task& a, const Task& b){
                return a.getTitle() > b.getTitle();
            });
            cout << "Tasks sorted by title in descending order successfully!" << endl << endl;
            viewTasks();
        }
        else {
            cout << "Invalid sort order! Please use 'asc' for ascending or 'desc' for descending." << endl << endl;
        }
    }
    
    else if(criteria == "completed"){
        if(order == "desc"){
            sort(tasks.begin(), tasks.end(), [](const Task& a, const Task& b){
                return a.isCompleted() > b.isCompleted();
            });
            cout << "Tasks sorted by status in ascending order successfully!" << endl << endl;
            viewTasks();
        }
        else if(order == "asc"){
            sort(tasks.begin(), tasks.end(), [](const Task& a, const Task& b){
                return a.isCompleted() < b.isCompleted();
            });
            cout << "Tasks sorted by status in descending order successfully!" << endl << endl;
            viewTasks();
        }
        else if(order == ""){
            sort(tasks.begin(), tasks.end(), [](const Task& a, const Task& b){
                return a.isCompleted() > b.isCompleted();
            });
            cout << "Tasks sorted by status in descending order successfully!" << endl << endl;
            viewTasks();
        }
        else {
            cout << "Invalid sort order! Please use 'asc' for ascending or 'desc' for descending." << endl << endl;
        }
    }

    else if(criteria == "favorite"){
        if(order == "desc"){
            sort(tasks.begin(), tasks.end(), [](const Task& a, const Task& b){
                return a.isFavorited() > b.isFavorited();
            });
            cout << "Tasks sorted by favorited first successfully!" << endl << endl;
            viewTasks();
        }
        else if(order == "asc"){
            sort(tasks.begin(), tasks.end(), [](const Task& a, const Task& b){
                    return a.isFavorited() < b.isFavorited();
            });
            cout << "Tasks sorted by favorited last successfully!" << endl << endl;
            viewTasks();
        }
        else if(order == ""){
            sort(tasks.begin(), tasks.end(), [](const Task& a, const Task& b){
                    return a.isFavorited() > b.isFavorited();
            });
            cout << "Tasks sorted by favorited first successfully!" << endl << endl;
            viewTasks();
        }
        else {
            cout << "Invalid sort order! Please use 'asc' for ascending or 'desc' for descending." << endl << endl;
        }
    }

    else {
        cout << "Invalid sort criteria! Please use 'title', 'completed', or 'favorite'." << endl << endl;
    }
}

void TaskManager::customSortTasks(){
        struct SortCriterion {
            string criteria;
            bool ascending;
        };
        
        vector<SortCriterion> criteriaList;
        vector<string> criterions;

        cout << "Please enter what criteria to sort with and the order for each criteria:\n> ";
        string input;
        getline(cin, input);
        cout << "Sorting tasks by: " << input << endl << endl;

        stringstream ss(input);
        string criterion;
        while(getline(ss, criterion, ',')) {
            criterions.push_back(criterion);
        }

        for (string& crit : criterions){
            stringstream critStream(crit);
            string critName, critOrder;
            critStream >> critName >> critOrder;

            SortCriterion c;

            c.criteria = critName;
            c.ascending = (critOrder == "asc");

            criteriaList.push_back(c);
        }

        sort(tasks.begin(), tasks.end(), [&criteriaList](const Task& a, const Task& b){
            for(const SortCriterion& c : criteriaList){
                if(c.criteria == "favorite"){
                    if(a.isFavorited() != b.isFavorited()){
                        return c.ascending ? 
                            a.isFavorited() < b.isFavorited() : a.isFavorited() > b.isFavorited();
                    }
                }

                else if(c.criteria == "completed"){
                    if(a.isCompleted() != b.isCompleted()){
                        return c.ascending ? 
                            a.isCompleted() < b.isCompleted() : a.isCompleted() > b.isCompleted();
                    }
                }

                else if(c.criteria == "title"){
                    if(a.getTitle() != b.getTitle()){
                        return c.ascending ? 
                            a.getTitle() < b.getTitle() : a.getTitle() > b.getTitle();
                    }
                }              
            }
            return false;
        });

        cout << "Tasks sorted by custom criteria successfully!" << endl << endl;
        viewTasks();

}
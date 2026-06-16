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
#include <typeinfo>

using namespace std;

int TASK_ID_COUNTER = 1;


namespace {
    bool tryParseInt(const string& text, int& value){
        try {
            size_t parsedChars = 0;
            value = stoi(text, &parsedChars);
            return parsedChars == text.size();
        }
        catch(...) {
            return false;
        }
    }
}

// Function for task addition
void TaskManager::addTask(string title){
    Task newTask;

    newTask.setTitle(title);
    newTask.isCompleted(false);
    newTask.isFavorited(false);
    newTask.setId(TASK_ID_COUNTER);
    newTask.setPriority(5);
    newTask.setDateCreated(newTask.getDateCreated());
    tasks.push_back(newTask);
    TASK_ID_COUNTER++;
}

// Function for viewing tasks
void TaskManager::viewTasks(){
    cout << "[=----REGISTERED TASKS----=]" << endl;
    cout << "Tasks: " << endl;
    for(size_t i = 0; i < tasks.size(); i++){
        tasks[i].display(static_cast<int>(i));
    }
    cout << "[--------------------------] " << endl;
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
                size_t secondPosition = line.find("|", position + 1);
                size_t thirdPosition = line.find("|", secondPosition + 1);
                size_t fourthPosition = line.find("|", thirdPosition + 1);
                size_t fifthPosition = line.find("|", fourthPosition + 1);

                if(secondPosition == string::npos || thirdPosition == string::npos || fourthPosition == string::npos || fifthPosition == string::npos){
                    cout << "Skipping malformed task line: " << line << endl;
                    continue;
                }

                string status = line.substr(0, position);
                string title = line.substr(position + 1, secondPosition - position - 1);
                string favorited = line.substr(secondPosition + 1, thirdPosition - secondPosition - 1);
                string idStr = line.substr(thirdPosition + 1, fourthPosition - thirdPosition - 1);
                string priorityStr = line.substr(fourthPosition + 1, fifthPosition - fourthPosition - 1);
                string dateStr = line.substr(fifthPosition + 1);

                int loadedId;
                int loadedPriority;
                if(!tryParseInt(idStr, loadedId) || !tryParseInt(priorityStr, loadedPriority)){
                    cout << "Skipping task line with invalid number: " << line << endl;
                    continue;
                }

                Task loadedTask;
                loadedTask.isCompleted((status == "1"));
                loadedTask.setTitle(title);
                loadedTask.isFavorited((favorited == "1"));
                loadedTask.setId(loadedId);
                loadedTask.setPriority(loadedPriority);
                loadedTask.setDateCreated(dateStr);
                tasks.push_back(loadedTask);

                TASK_ID_COUNTER = max(TASK_ID_COUNTER, loadedId + 1);
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
        for(size_t i = 0; i < tasks.size(); i++){
            outTasks << tasks[i].isCompleted() << "|" << tasks[i].getTitle() << "|" << tasks[i].isFavorited() << "|" << tasks[i].getId() << "|" << tasks[i].getPriority() << "|" << tasks[i].getDateCreated() << endl;
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
                
    if(completedTaskNum > 0 && completedTaskNum <= static_cast<int>(tasks.size())){
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

    if(deleteTaskNum > 0 && deleteTaskNum <= static_cast<int>(tasks.size())){
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

    for(size_t i = 0; i < tasks.size(); i++){
        if(tasks[i].matches(keyword)){
            tasks[i].display(static_cast<int>(i));
            found = true;
        }
    }

    if(!found){
        cout << "No tasks found containing '" << keyword << "'." << endl;
    }
    cout << "[----------------------] " << endl;
    cout << endl;
}

// Function for marking/unmarking tasks as favorite
void TaskManager::markFavorite(int favoriteTaskNum){
    int indexFavorite = favoriteTaskNum - 1;

    if(favoriteTaskNum > 0 && favoriteTaskNum <= static_cast<int>(tasks.size())){
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

void TaskManager::editTask(int index, const string& args){
    int indexEdit = index - 1;
    string titleValue, priorityValue;

    size_t titlePosition = args.find("title:");
    size_t priorityPosition = args.find("priority:"); 
    
    if(titlePosition != string::npos){
        size_t end = (priorityPosition != string::npos && priorityPosition > titlePosition)
                    ? priorityPosition
                    : args.size();

        titleValue = args.substr(titlePosition + 6, end - (titlePosition + 6));
        }
        
    if(priorityPosition != string::npos){
        priorityValue = args.substr(priorityPosition + 9);
    }

    if(indexEdit >= 0 && indexEdit < static_cast<int>(tasks.size())){
        if(!titleValue.empty()){
            tasks[indexEdit].setTitle(titleValue);
            cout << "Task No. " << index << " title updated successfully!" << endl;
        }

        if(!priorityValue.empty())
        {
            int p;
            if(tryParseInt(priorityValue, p))
                tasks[indexEdit].setPriority(p);
            cout << "Task No. " << index << " priority updated successfully!" << endl;
        }
    }
    else {
        cout << "Invalid task number!" << endl << endl;
    }
    cout << endl;
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

    else if(criteria == "favorited"){
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

    else if(criteria == "priority"){
        if(order == "desc"){
            sort(tasks.begin(), tasks.end(), [](const Task& a, const Task& b){
                return a.getPriority() > b.getPriority();
            });
            cout << "Tasks sorted by priority in descending order successfully!" << endl << endl;
            viewTasks();
        }
        else if(order == "asc"){
            sort(tasks.begin(), tasks.end(), [](const Task& a, const Task& b){
                return a.getPriority() < b.getPriority();
            });
            cout << "Tasks sorted by priority in ascending order successfully!" << endl << endl;
            viewTasks();
        }
        else if(order == ""){
            sort(tasks.begin(), tasks.end(), [](const Task& a, const Task& b){
                return a.getPriority() > b.getPriority();
            });
            cout << "Tasks sorted by priority in descending order successfully!" << endl << endl;
            viewTasks();
        }
        else {
            cout << "Invalid sort order! Please use 'asc' for ascending or 'desc' for descending." << endl << endl;
        }
    }

    else if(criteria == "id"){
        if(order == "desc"){
            sort(tasks.begin(), tasks.end(), [](const Task& a, const Task& b){
                return a.getId() > b.getId();
            });
            cout << "Tasks sorted by ID in descending order successfully!" << endl << endl;
            viewTasks();
        }
        else if(order == "asc"){
            sort(tasks.begin(), tasks.end(), [](const Task& a, const Task& b){
                return a.getId() < b.getId();
            });
            cout << "Tasks sorted by ID in ascending order successfully!" << endl << endl;
            viewTasks();
        }
        else if(order == ""){
            sort(tasks.begin(), tasks.end(), [](const Task& a, const Task& b){
                return a.getId() > b.getId();
            });
            cout << "Tasks sorted by ID in descending order successfully!" << endl << endl;
            viewTasks();
        }
        else {
            cout << "Invalid sort order! Please use 'asc' for ascending or 'desc' for descending." << endl << endl;
        }
    }

    else {
        cout << "Invalid sort criteria! Please use 'id', 'title', 'priority', 'completed', or 'favorited'." << endl << endl;
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
                
                else if(c.criteria == "priority"){
                    if(a.getPriority() != b.getPriority()){
                        return c.ascending ? 
                            a.getPriority() < b.getPriority() : a.getPriority() > b.getPriority();
                    }
                }

                else if(c.criteria == "id"){
                    if(a.getId() != b.getId()){
                        return c.ascending ? 
                            a.getId() < b.getId() : a.getId() > b.getId();
                    }
                }

                else {
                    cout << "Invalid sort criteria '" << c.criteria << "'! Skipping this criteria." << endl;
                }
            }
            return false;
        });

        cout << "Tasks sorted by custom criteria successfully!" << endl << endl;
        viewTasks();

}

void TaskManager::createTaskFolder(string folderName){
    (void)folderName;
}
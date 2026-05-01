#include "TaskManager.h"
#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <fstream>
#include <iomanip>
#include <algorithm>

using namespace std;

// MAIN FUNCTION
int main(){
    string user, password;
    TaskManager manager;
    manager.loadTasks();

// Unnecessary login system for fun
    cout << "User: ";
    cin >> user;
    cout << "Password: ";
    cin >> password;

    cout << "Welcome " << user << " to the Task Manager!" << endl << endl;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer for getline in addTask function


    while(true){
        string input;
        cout << "> ";
        getline(cin, input);

        if(input == "add"){
            manager.addTask();
            cout << "Task added successfully!" << endl << endl;
        }

        else if(input == "view"){
            manager.viewTasks();
        }

        else if(input.find("complete") == 0){
            size_t position = input.find(" ");
            if(position != string::npos){
                string taskNumStr = input.substr(position + 1);
                int completedTaskNum = stoi(taskNumStr);
                manager.taskCompletion(completedTaskNum);
            }
            else {
                cout << "Invalid command format! Please use 'complete [task number]'." << endl << endl;
            }
        }

        else if(input.find("delete") == 0){
            size_t position = input.find(" ");
            if(position != string::npos){
                string taskNumStr = input.substr(position + 1);
                int deleteTaskNum = stoi(taskNumStr);
                manager.taskDeletion(deleteTaskNum);
            }
            else {
                cout << "Invalid command format! Please use 'delete [task number]'." << endl << endl;
            }
        }

        else if(input.find("search") == 0){
            size_t position = input.find(" ");
            if(position != string::npos){
                string keyword = input.substr(position + 1);
                manager.taskSearch(keyword);
            }
            else {
                cout << "Invalid command format! Please use 'search [keyword]'." << endl << endl;
            }
        }

        else if(input.find("favorite") == 0){
            size_t position = input.find(" ");
            if(position != string::npos){
                string taskNumStr = input.substr(position + 1);
                int favoriteTaskNum = stoi(taskNumStr);
                manager.markFavorite(favoriteTaskNum);
            }
            else {
                cout << "Invalid command format! Please use 'favorite [task number]'." << endl << endl;
            }
        }

        else if(input.find("edit") == 0){
            size_t position = input.find(" ");
            if(position != string::npos){
                string taskNumStr = input.substr(position + 1);
                int editTaskNum = stoi(taskNumStr);
                manager.editTask(editTaskNum);
            }
            else {
                cout << "Invalid command format! Please use 'edit [task number]'." << endl << endl;
            }
        }

        else if(input.find("sort") == 0){

            if(input == "sort custom"){
                manager.customSortTasks();
            }
            else{
                size_t firstPosition = input.find(" ");
                size_t secondPosition = input.find(" ", firstPosition + 1);
                if(firstPosition != string::npos && secondPosition != string::npos){
                    string criteria = input.substr(firstPosition + 1, secondPosition - firstPosition - 1);
                    string order = input.substr(secondPosition + 1);
                    manager.sortTasks(criteria, order);
                }
                else {
                    cout << "Invalid command format! Please use 'sort [criteria] [order]'." << endl << endl;
                }
            }    
        }

        else if(input == "exit"){
            manager.saveTasks();
            cout << "Saving tasks to file and exiting. Have a good day " << user << "!" << endl;
            return 0;
        }

        else if(input == "help"){
            cout << "Available commands (Brackets are required parameters of type INT or STRING):" << endl;
            cout << "add — Add a new task" << endl;
            cout << "view — View all tasks" << endl;
            cout << "complete [task number] — Mark a task as completed or pending" << endl;
            cout << "delete [task number] — Delete a task" << endl;
            cout << "search [keyword] — Search for tasks containing a keyword" << endl;
            cout << "edit [task number] — Edit the title of a task" << endl;
            cout << "sort [criteria] [order] — Sort tasks by criteria and order" << endl;
            cout << "favorite [task number] — Mark/unmark a task as favorite" << endl;
            cout << "exit — Save tasks and exit the program" << endl;
            cout << endl;
        }

        else {
            cout << "Invalid command! Please enter a valid command! For help type 'help'." << endl << endl;
        }
    }

return 0;
}
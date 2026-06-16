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

// MAIN FUNCTION
int main(){
    string user, password;
    TaskManager manager;
    manager.loadTasks();
    
// Unnecessary login system for fun
    cout << "Please enter credentials:" << endl;
    cout << "User: ";
    cin >> user;
    cout << "Password: ";
    cin >> password;

    cout << "Welcome " << user << " to the Task Manager!" << endl << endl;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer for getline in addTask function


    while(true){
        string input="", command="";
        cout << "> ";
        getline(cin, input);

        stringstream ss(input);
        ss >> command;

        if(command == "add"){
            string title;
            ss >> title;

            int titleStartingWithNumber;
            if(tryParseInt(title, titleStartingWithNumber)){
                cout << "Task title cannot start with a number! Please enter a valid title." << endl << endl;
                continue;
            }

            manager.addTask(title);
            
            cout << "Task added successfully!" << endl << endl;
        }

        else if(command == "view"){
            manager.viewTasks();
        }

        else if(command == "complete"){            
            string taskNumStr;

            if(!(ss >> taskNumStr))
            {
                cout << "Invalid command format! Please use 'complete [task number]'." << endl;
                continue;
            }

            int completedTaskNum;

            if(!tryParseInt(taskNumStr, completedTaskNum))
            {
                cout << "Invalid task number! Please enter a whole positive number." << endl;
                continue;
            }

            manager.taskCompletion(completedTaskNum);
        }

        else if(command == "delete"){
            string taskNumStr;

            if(!(ss >> taskNumStr))
            {
                cout << "Invalid command format! Please use 'delete [task number]'." << endl;
                continue;
            }

            int deleteTaskNum;

            if(!tryParseInt(taskNumStr, deleteTaskNum))
            {
                cout << "Invalid task number! Please enter a whole positive number." << endl;
                continue;
            }

            manager.taskDeletion(deleteTaskNum);
        }

        else if(command == "search"){
            string keyword;

            if(!(ss >> keyword))
            {
                cout << "Invalid command format! Please use 'search [keyword]'." << endl;
                continue;
            }

            manager.taskSearch(keyword);
        }

        else if(command == "favorite"){
            string taskNumStr;

            if(!(ss >> taskNumStr))
            {
                cout << "Invalid command format! Please use 'favorite [task number]'." << endl;
                continue;
            }

            int favoriteTaskNum;

            if(!tryParseInt(taskNumStr, favoriteTaskNum))
            {
                cout << "Invalid task number! Please enter a whole positive number." << endl;
                continue;
            }

            manager.markFavorite(favoriteTaskNum);
        }

        else if(command == "sort"){

            if(input == "sort custom"){
                manager.customSortTasks();
            }
            else{
                string criteria;
                string order;

                if(!(ss >> criteria >> order))
                {
                    cout << "Invalid command format! Please use 'sort [criteria] [order]'." << endl;
                    continue;
                }

                manager.sortTasks(criteria, order);
            }
        }

        else if(command == "edit"){
            string taskNumStr, args;
            ss >> taskNumStr;
            
            int editTaskNum;
            if(!tryParseInt(taskNumStr, editTaskNum))
            {
                cout << "Invalid task number! Please enter a whole positive number." << endl;
                continue;
            }

            getline(ss, args);
            if(!args.empty() && args[0] == ' ')
                args.erase(0, 1);
            manager.editTask(editTaskNum, args);
        }

        else if(input == "folder"){
            /*size_t folderNamePosition = input.find(" ");
            if(folderNamePosition != string::npos){
                string folderName = input.substr(folderNamePosition + 1);
                manager.createTaskFolder(folderName);
            }
            else {
                cout << "Invalid command format! Please use 'folder [folder name]'." << endl << endl;
            }*/
            cout << "This feature is currently under development and will be available in a future update!" << endl << endl;
        }

        else if(input == "exit"){
            manager.saveTasks();
            cout << "Saving tasks to file and exiting. Have a good day " << user << "!" << endl;
            return 0;
        }

        else if(input == "help"){
            cout << "Available commands (Brackets are required parameters of type INT or STRING):" << endl;
            cout << "add [task title] -- Add a new task" << endl;
            cout << "view -- View all tasks" << endl;
            cout << "complete [task number] -- Mark a task as completed or pending" << endl;
            cout << "delete [task number] -- Delete a task" << endl;
            cout << "search [keyword] -- Search for tasks containing a keyword" << endl;
            cout << "edit [task number] [title/priority]:[new value] ([priority/title]:[new value]) -- Edit a task" << endl;
            cout << "sort [criteria] [order] -- Sort tasks by criteria and order" << endl;
            cout << "favorite [task number] -- Mark/unmark a task as favorite" << endl;
            cout << "exit -- Save tasks and exit the program" << endl;
            cout << endl;
        }

        else {
            cout << "Invalid command! Please enter a valid command! For help type 'help'." << endl << endl;
        }
    }

return 0;
}

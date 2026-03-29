#include "Task.h"
#include <iostream>
#include <iomanip>

using namespace std;

Task::Task() { title = "", completed = false; }

string Task::getTitle() const {return title;}
bool Task::isCompleted() const {return completed;}
bool Task::isFavorited() const {return favorited;}

void Task::setTitle(const string& t) {title = t;}
void Task::isCompleted(bool c) {completed = c;}
void Task::isFavorited(bool f) {favorited = f;}

void Task::markCompleted(){completed = true;};
void Task::markPending(){completed = false;};

void Task::display(int index) const {
    cout << left << index + 1 << "} ";
    cout << setw(25) << left << title;
    cout << setw(15) << left << (completed ? "—— [Completed]" : "—— [Pending]");
    if(completed){
        cout << "  "<< (favorited ? "| [Favorited]" : "") << endl;;
    }
    else {
        cout << "    "<< (favorited ? "| [Favorited]" : "") << endl;;
    }
};

bool Task::matches(string keyword) const {
    string taskLower = title;
    string keywordLower = keyword;

    for(int i = 0; i < taskLower.size(); i++){
        taskLower[i] = tolower(taskLower[i]);
    }
    for(int i = 0; i < keywordLower.size(); i++){
        keywordLower[i] = tolower(keywordLower[i]);
    }
    return taskLower.find(keywordLower) != string::npos;

};
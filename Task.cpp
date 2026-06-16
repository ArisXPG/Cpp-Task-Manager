#include "Task.h"
#include <iostream>
#include <iomanip>
#include <cctype>
#include <ctime>

using namespace std;

string getCurrentDate(){
    time_t now = time(nullptr);
    tm* localTime = localtime(&now);

    size_t day = localTime->tm_mday;
    size_t month = localTime->tm_mon + 1;
    size_t year = localTime->tm_year + 1900;

    string taskDate = to_string(year) + "-" + to_string(month) + "-" + to_string(day);

    return
    {
        taskDate
    };
}

Task::Task() {
    title = "";
    completed = false;
    favorited = false;
    id = 0;
    priority = 5;
    date = getCurrentDate();
}

string Task::getTitle() const {return title;}
bool Task::isCompleted() const {return completed;}
bool Task::isFavorited() const {return favorited;}
int Task::getId() const {return id;}
int Task::getPriority() const {return priority;}
string Task::getDateCreated() const {return date;}

void Task::setTitle(const string& t) {title = t;}
void Task::isCompleted(bool c) {completed = c;}
void Task::isFavorited(bool f) {favorited = f;}
void Task::setId(int i) {id = i;}
void Task::setPriority(int p) {priority = p;}
void Task::setDateCreated(const string& d) {date = d;}

void Task::markCompleted(){completed = true;};
void Task::markPending(){completed = false;};

void Task::display(int index) const {
    cout << left << index + 1 << "} ";
    cout << setw(7) << left << "[ID:" + to_string(id) + "]";
    cout << setw(4) << left << "<" + to_string(priority) + ">";
    cout << setw(25) << left << title;
    cout << setw(15) << left << (completed ? "-- [Completed]" : "-- [Pending]");
    if(completed){
        cout << "  "<< (favorited ? "| [Favorited]" : "             ") << "  Creation Date: " << date << endl;;
    }
    else {
        cout << "  "<< (favorited ? "| [Favorited]" : "             ") << "  Creation Date: " << date << endl;;
    }
};

bool Task::matches(string keyword) const {
    string taskLower = title;
    string keywordLower = keyword;

    for(size_t i = 0; i < taskLower.size(); i++){
        taskLower[i] = static_cast<char>(tolower(static_cast<unsigned char>(taskLower[i])));
    }
    for(size_t i = 0; i < keywordLower.size(); i++){
        keywordLower[i] = static_cast<char>(tolower(static_cast<unsigned char>(keywordLower[i])));
    }
    return taskLower.find(keywordLower) != string::npos;

};
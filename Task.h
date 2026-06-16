#pragma once
#include <string>

class Task {
private:
    std::string title;
    bool completed;
    bool favorited;
    int id;
    int priority;
    std::string date;

public:
    Task();

    std::string getTitle() const;
    bool isCompleted() const;
    bool isFavorited() const;
    int getId() const;
    int getPriority() const;
    std::string getDateCreated() const;


    void setTitle(const std::string& t);
    void isCompleted(bool c);
    void isFavorited(bool f);
    void setId(int i);
    void setPriority(int p);
    void setDateCreated(const std::string& d);

    void markCompleted();
    void markPending();


    void display(int index) const;

    bool matches(std::string keyword) const;
};
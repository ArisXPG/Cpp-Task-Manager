#pragma once
#include <string>

class Task {
private:
    std::string title;
    bool completed;
    bool favorited;

public:
    Task();

    std::string getTitle() const;
    bool isCompleted() const;
    bool isFavorited() const;

    void setTitle(const std::string& t);
    void isCompleted(bool c);
    void isFavorited(bool f);

    void markCompleted();
    void markPending();

    void display(int index) const;

    bool matches(std::string keyword) const;
};
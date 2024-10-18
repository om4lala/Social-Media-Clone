#ifndef DYNAMIC_LIST_HPP
#define DYNAMIC_LIST_HPP

#include <string>

class DynamicList {
private:
    std::string* data;
    size_t capacity;
    size_t size;

public:
    DynamicList();
    ~DynamicList();
    void push_back(const std::string& value);
    int getSize() const;
    std::string& operator[](int index);
};

#endif


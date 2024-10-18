#include <iostream>
#include "DynamicList.hpp"


DynamicList::DynamicList() : data(nullptr), capacity(0), size(0) {}

DynamicList::~DynamicList() {
    delete[] data;
}

void DynamicList::push_back(const std::string& value) {
    if (size >= capacity) {
        if (capacity == 0) capacity = 1;
        else capacity *= 2;

        std::string* newData = new std::string[capacity];
        for (size_t i = 0; i < size; ++i) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
    }
    data[size++] = value;
}

int DynamicList::getSize() const {
    return size;
}

std::string& DynamicList::operator[](int index) {
    if (index < size) {
        return data[index];
    } else {
        throw std::out_of_range("Index out of range");
    }
}



#ifndef USER_HPP
#define USER_HPP

#include <string>
#include "DynamicList.hpp"

class User {
private:
    std::string name, userName, password;
    std::string newName, newUsername, newPassword;
    DynamicList followRequests;

public:
    void signUp();
    bool login();
    void editProfile();
    void viewFollowedUsers();
    void followUser();
    void viewNotifications();
    void makePost();
    void viewPosts();
};

#endif

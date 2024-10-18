#include "User.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include "DynamicList.hpp"

void User::signUp() {
    std::cout << "Enter Name: ";
    std::cin >> name;

    std::string tempName;
    bool found = false;

    do {
        std::cout << "Enter your Username: ";
        std::cin >> userName;

        std::ifstream inFile("initial_users.txt");
        if (!inFile.is_open()) {
            std::cerr << "File cannot be opened!" << std::endl;
            return;
        }

        found = false;
        while (getline(inFile, tempName, ',')) {
            getline(inFile, tempName, ',');
            if (tempName == userName) {
                std::cout << "Username already exists. Try again!." << std::endl;
                found = true;
                break;
            }
            getline(inFile, tempName);
        }

        inFile.close();
    } while (found);

    std::cout << "Enter your Password: ";
    std::cin >> password;

    std::ofstream updateFile("initial_users.txt", std::ios::app);
    if (!updateFile.is_open()) {
        std::cerr << "File cannot be opened!" << std::endl;
        return;
    }
    updateFile << name << ',' << userName << ',' << password << std::endl; // Write user info to the next line
    updateFile.close();
}
bool User::login() {
    int attempts = 0;
    int maxAttempts = 5;
    bool loggedIn = false;

    while (attempts < maxAttempts) {
        std::ifstream readFile("initial_users.txt");

        std::cout << "Enter your username: ";
        std::cin >> userName;
        std::cout << "Enter your password: ";
        std::cin >> password;

        std::string line;
        bool found = false;

        while (getline(readFile, line)) {
            std::stringstream ss(line);
            std::string tempName, tempUsername, tempPassword;
            getline(ss, tempName, ',');
            getline(ss, tempUsername, ',');
            getline(ss, tempPassword, ',');

            if (tempUsername == userName && tempPassword == password) {
                std::cout << "Welcome back! " << userName << std::endl;
                loggedIn = true;
                found = true;
                break;
            }
        }

        readFile.close();
        if (found) {
            break;
        } else {
            std::cout << "\nUsername or password is incorrect!\n" << std::endl;
            attempts++;
            if (attempts == maxAttempts) {
                std::cout << "Maximum login attempts reached. Exiting.\n";
                break;
            }

            
            int choice;
            std::cout << "Do you want to:\n1. Sign up\n2. Login again\n3. Exit\nType: ";
            std::cin >> choice;
            if (choice == 1) {
                signUp();  
            } else if (choice == 3) {
                std::cout << "Exiting the program...\n";
                break;
            }
        }
    }

    return loggedIn;
}

void User::editProfile() {
    int userInput;
    std::cout << "\n1. Change Name\n2. Change Username\n3. Change Password\n4. Exit\nType: ";
    std::cin >> userInput;

    if (userInput == 1) {
        std::cout << "Enter new name: ";
        std::cin >> newName;

        DynamicList userInformation;
        std::ifstream readFile("initial_users.txt");
        std::string line;
        while (getline(readFile, line)) {
            std::stringstream ss(line);
            std::string tempName, tempUsername, tempPassword;
            getline(ss, tempName, ',');
            getline(ss, tempUsername, ',');
            getline(ss, tempPassword, ',');

            if (tempUsername == userName && tempPassword == password) {
                tempName = newName; // Update the name
            }

            userInformation.push_back(tempName + "," + tempUsername + "," + tempPassword);
        }
        readFile.close();

        std::ofstream updateFile("initial_users.txt");
        if (!updateFile.is_open()) {
            std::cerr << "File cannot be opened!" << std::endl;
            return;
        }
        for (size_t i = 0; i < userInformation.getSize(); i++) {
            updateFile << userInformation[i] << std::endl;
        }
        updateFile.close();

        std::cout << "Name updated successfully!" << std::endl;
        return;
    } else if (userInput == 2) {
        std::cout << "Enter new username: ";
        std::cin >> newUsername;

        std::ifstream checkFile("initial_users.txt");
        std::string line;
        bool usernameExists = false;
        while (getline(checkFile, line)) {
            std::stringstream ss(line);
            std::string tempName, tempUsername, tempPassword;
            getline(ss, tempName, ',');
            getline(ss, tempUsername, ',');
            getline(ss, tempPassword, ',');
            if (tempUsername == newUsername) {
                std::cout << "Username already exists." << std::endl;
                usernameExists = true;
                break;
            }
        }
        checkFile.close();

        if (!usernameExists) {
            DynamicList userInformation;
            std::ifstream readFile("initial_users.txt");
            while (getline(readFile, line)) {
                std::stringstream ss(line);
                std::string tempName, tempUsername, tempPassword;
                getline(ss, tempName, ',');
                getline(ss, tempUsername, ',');
                getline(ss, tempPassword, ',');
                if (tempUsername == userName && tempPassword == password) {
                    if (!newName.empty()) {
                        userInformation.push_back(newName + "," + newUsername + "," + tempPassword);
                    } else {
                        userInformation.push_back(tempName + "," + newUsername + "," + tempPassword);
                    }
                } else {
                    userInformation.push_back(line);
                }
            }
            readFile.close();

            std::ofstream updateFile("initial_users.txt");
            if (!updateFile.is_open()) {
                std::cerr << "File cannot be opened!" << std::endl;
                return;
            }

            for (size_t i = 0; i < userInformation.getSize(); i++) {
                updateFile << userInformation[i] << std::endl;
            }
            updateFile.close();

            std::cout << "Username updated successfully!" << std::endl;
            userName = newUsername; 
        }
    } else if (userInput == 3) {
        std::cout << "Enter new password: ";
        std::cin >> newPassword;

        DynamicList userInformation;
        std::ifstream readFile("initial_users.txt");
        std::string line;
        while (getline(readFile, line)) {
            std::stringstream ss(line);
            std::string tempName, tempUsername, tempPassword;
            getline(ss, tempName, ',');
            getline(ss, tempUsername, ',');
            getline(ss, tempPassword, ',');

            if (tempUsername == userName && tempPassword == password) {
                tempPassword = newPassword; 
            }

            userInformation.push_back(tempName + "," + tempUsername + "," + tempPassword);
        }
        readFile.close();

        std::ofstream updateFile("initial_users.txt");
        if (!updateFile.is_open()) {
            std::cerr << "File cannot be opened!" << std::endl;
            return;
        }
        for (size_t i = 0; i < userInformation.getSize(); i++) {
            updateFile << userInformation[i] << std::endl;
        }
        updateFile.close();

        std::cout << "Password updated successfully!" << std::endl;
        password = newPassword; 
    } else if (userInput == 4) {
        std::cout << "Exiting edit profile..." << std::endl;
        return;
    } else {
        std::cout << "Invalid option!" << std::endl;
    }
}
void User::viewFollowedUsers() {
    std::ifstream followedFile("followed_users.txt");
    if (!followedFile.is_open()) {
        std::cout << "You are not following anyone." << std::endl;
        return;
    }

    std::string line;
    std::cout << "Followed Users = " << std::endl;
    bool found = false;
    while (getline(followedFile, line)) {
        std::stringstream ss(line);
        std::string currentUser, followedUser;
        getline(ss, currentUser, ',');
        getline(ss, followedUser, ',');
        if (currentUser == userName) {
            std::cout << " - " << followedUser << std::endl;
            found = true; 
        }
    }

    followedFile.close();

    if (!found) { 
        std::cout << "You are not following anyone." << std::endl;
    }
}

void User::followUser() {
    std::string username;
    std::cout << "Enter the username of the user you want to follow: ";
    std::cin >> username;

    std::ifstream userFile("initial_users.txt");
    if (!userFile.is_open()) {
        std::cerr << "User database cannot be accessed!" << std::endl;
        return;
    }

    bool userExists = false;
    std::string line;
    while (getline(userFile, line)) {
        std::stringstream ss(line);
        std::string tempName, tempUsername, tempPassword;
        getline(ss, tempName, ',');
        getline(ss, tempUsername, ',');
        getline(ss, tempPassword, ',');

        if (tempUsername == username) {
            userExists = true;
            break;
        }
    }
    userFile.close();

    if (!userExists) {
        std::cout << "User '" << username << "' does not exist." << std::endl;
        return;
    }

    std::ifstream followedFile("followed_users.txt");
    if (!followedFile.is_open()) {
        std::cerr << "File cannot be opened!" << std::endl;
        return;
    }

    while (getline(followedFile, line)) {
        std::stringstream ss(line);
        std::string currentUser, followedUser;
        getline(ss, currentUser, ',');
        getline(ss, followedUser, ',');
        if (currentUser == userName && followedUser == username) {
            std::cout << "You are already following this user." << std::endl;
            followedFile.close();
            return;
        }
    }
    followedFile.close();

    std::ofstream followedFileAppend("followed_users.txt", std::ios::app); 
    if (!followedFileAppend.is_open()) {
        std::cerr << "File cannot be opened!" << std::endl;
        return;
    }
    followedFileAppend << userName << "," << username << std::endl; 
    followedFileAppend.close();
    std::cout << "User '" << username << "' followed successfully!" << std::endl;

    viewFollowedUsers();
}

void User::viewNotifications() {
    std::ifstream followedFile("followed_users.txt");
    if (!followedFile.is_open()) {
        std::cout << "No notifications." << std::endl;
        return;
    }

    std::string line;
    std::cout << "Notifications:" << std::endl;
    while (getline(followedFile, line)) {
        std::stringstream ss(line);
        std::string currentUser, followedUser;
        getline(ss, currentUser, ',');
        getline(ss, followedUser, ',');
        if (followedUser == userName) {
            std::cout << "- You have a new follower: " << currentUser << std::endl;
        }
    }

   
}

void User::makePost() {
    std::string post;
    std::cout << "Enter your post: ";
    std::cin.ignore(); 
    getline(std::cin, post); 

    std::ofstream postFile("userposts.txt", std::ios::app);
    if (!postFile.is_open()) {
        std::cerr << "Error: Unable to open file for writing!" << std::endl;
        return;
    }

    postFile << userName << ": " << post << std::endl;
    postFile.close();
    std::cout << "Post added successfully!" << std::endl;
}

void User::viewPosts() {
    std::ifstream postFile("userposts.txt");
    if (!postFile.is_open()) {
        std::cout << "No posts available." << std::endl;
        return;
    }

    std::cout << "Posts:" << std::endl;
    std::string line;
    while (getline(postFile, line)) {
        std::cout << line << std::endl;
    }
    postFile.close();
}

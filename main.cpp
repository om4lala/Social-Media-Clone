#include "User.hpp"
#include <iostream>
#include <fstream>

int main() {
    User currentUser;
    std::ofstream followedFile("followed_users.txt", std::ios::app);
    if (!followedFile.is_open()) {
        std::cerr << "Error: Could not open followed_users.txt file!" << std::endl;
        return 1; 
    }
    
    int choice;
    do {
        std::cout << "Welcome to social media! Choose one of the following options\n1. Sign Up\n2. Login\n3. Close App\nType: ";
        std::cin >> choice;

        if (choice == 1) {
            currentUser.signUp();
        } else if (choice == 2) {
            if (currentUser.login()) {
                int loggedInChoice;
                while (true) {
                    std::cout << "\nLogged in successfully! Choose one of the following options\n";
                    std::cout << "1. Edit Profile\n2. Send Request\n3. View Followed Users\n4. Make a Post\n5. View Posts\n6. Logout\nType: ";
                    std::cin >> loggedInChoice;

                    if (loggedInChoice == 1) {
                        currentUser.editProfile();
                    } else if (loggedInChoice == 2) {
                        currentUser.followUser();
                    } else if (loggedInChoice == 3) {
                        currentUser.viewFollowedUsers();
                    } else if (loggedInChoice == 4) {
                        currentUser.makePost();
                    } else if (loggedInChoice == 5) {
                        currentUser.viewPosts();
                    } else if (loggedInChoice == 6) {
                        std::cout << "Going Back to Main Menu\n";
                        break;
                    } else {
                        std::cout << "Invalid choice! Try again." << std::endl;
                    }
                }
            } else {
                std::cout << "Login failed!\n";
            }
        } else if (choice == 3) {
            std::cout << "Closing App...\n";
            break;
        } else {
            std::cout << "Invalid choice! Try again." << std::endl;
        }
    } while (true);
}


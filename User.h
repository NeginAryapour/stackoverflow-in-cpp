//
// Created by spsina on 11/8/18.
//

#ifndef STACKOVERFLOW_IN_CPP1_USER_H
#define STACKOVERFLOW_IN_CPP1_USER_H

#include <iostream>
#include "AbstractUser.h"
#include "Content.h"
#include <time.h>

//const std::string currentDateTime() {
//    time_t     now = time(0);
//    struct tm  tstruct;
//    char       buf[80];
//    tstruct = *localtime(&now);
//    // Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
//    // for more information about date/time format
//    strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);
//
//    return buf;
//}

class User : public AbstractUser {
public:
    User(string username, string password, UserType type);

    static void init(const string &salt);

public:
    void set_password(string password);
    bool check_password(string password);

public:
    bool authenticate(string username, string password);
    void deleteAccount();

public:
    static User& login(string username, string password);
    static User& signup(string username, string password);
//    void add_to_log(string file_name);
    friend ostream& operator<<(ostream& ostream1,const User& user){
        time_t     now = time(0);
        struct tm  tstruct;
        char       buf[80];
        tstruct = *localtime(&now);
        // Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
        // for more information about date/time format
        strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);
        ostream1<<buf<<" username : "<<user.username<<" password : "<<user.password;
        return ostream1;
    }

    void AddContent(Content& c);
    void EditContent(int nc,ContentType t,EditType et);
    void DeleteContent(Content c);
    void SeeContents(ContentType type1,int number);
    void MakeContent(ContentType type1,Content * destination);




private:
    static string salt;
    static vector<User> users;
    vector<Content> contents;
    

};

#endif //STACKOVERFLOW_IN_CPP1_USER_H

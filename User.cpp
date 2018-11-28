#include <utility>

//
// Created by spsina on 11/8/18.
//

#include <sstream>
#include "User.h"
#include "Exceptions.h"
#include <iostream>
#include <fstream>
#include <ios>
vector<User> User::users;
string User::salt;


User::User(string username, string password, UserType type){
    lower(username);
    this->username = username;
    set_password(std::move(password));
    this->type = type;
}

void User::set_password(string password){
    size_t ps = pass_hash(password + salt);
    stringstream out;
    out << ps;
    this->password = out.str();
}

bool User::check_password(string password){
    size_t check = pass_hash(password + salt);
    stringstream out;
    out << check;
    return (this->password == out.str());
}

bool User::authenticate(string username, string password){
    lower(username);
    return this->username == username and check_password(password);
}
void User::deleteAccount(){
    if (this->type == UserType::ADMIN) {
        throw DeleteAdminException();
    }

    for (auto user = users.begin(); user != users.end();user++){
        if ( user->username == this->username  ) {
            users.erase(user);
            break;
        }
    }
}

User& User::login(string username, string password){
    for (auto &user : users) {
        if(user.authenticate(username, password)) {
            return user;
        }
    }
    throw WrongUsernameOrPasswordException();
}

User& User::signup(string username, string password){
    for (auto &user : users) {
        if (user.username == username) {
            throw UserAlreadyExistsException();
        }
    }
    //Create user
    users.emplace_back(username, password, UserType::MEMBER);
    return users[users.size() - 1];
}

void User::init(const string &salt) {
    User::salt = salt;
    users.reserve(20);
    users.emplace_back("admin", "admin", UserType::ADMIN);
}

void User::AddContent(Content &c) {
    this->contents.push_back(c);
}

void User::MakeContent(ContentType type1,Content*destination){
    string ContentBody;
    int nt; //number of tags
    cout<<"enter the number of tags of your Content"<<endl;
    cin>>nt;
    string t;
    vector<string>tag;
    vector<ContentRelation> ContentRelations;
//    if(type1 == ContentType ::ANSWER){
//        ContentRelation cr (*destination,ANSWER_TO);
//        ContentRelations.push_back(cr);
//    } else{
//        //search in file
//        //if destination
//            ContentRelation cr (*destination,DUPLECATE_OF);
//            ContentRelations.push_back(cr);
////            ContentRelation rc(DUPLECATE_OF); ?????? mishe un destination ham duplicate beshe
//
////            *destination->Add_to_contentRelations(this);
//
//    }
    for(int i = 0;i<nt;i++)
    {
        cout<<"write the tag of your Question"<<endl;
        cin>>t;
        tag.push_back(t);
    }
    cout<<"write your Question"<<endl;
//    cin>>ContentBody;
    getline(std::cin,ContentBody);
//    cin>>ContentBody;
    getline(std::cin,ContentBody);
    Content cn (ContentBody,type1,tag,0,ContentRelations);
    AddContent(cn);
    cout<<"Your Question is sent "<<endl;

}

void User::SeeContents(ContentType type1, int number) {
    if (contents.size() == 0){
        cout<<"there is no question"<<endl;
        return;
    }
    int i =0;
    for(auto iter = contents.begin();iter!=contents.end() && i<number;iter++,i++){
        cout<<*iter<<endl;
        (*iter).visit++;
    }
}

void User::EditContent(int nc,ContentType t,EditType et) {
    if(et == EDIT) {
        if(t == QUESTION) {
            if (nc < 0 || nc >= contents.size()) {
                cout << "Invalid Content Number" << endl;
                return;
            } else {
                string new_content_body;
                getline(std::cin, new_content_body);
//            cin >> new_content_body;
                contents[nc].set_body(new_content_body);
            }
        } else if(t == ANSWER) {
            cout<<"not managed yet"<<endl;
        }

    } else{
        if(t == QUESTION) {
            cout<<"not managed yet"<<endl;
            if (nc < 0 || nc > contents.size()) {
                cout << "Invalid Content Number" << endl;
                return;
            }
//            string new_content_body;
//            cin >> new_content_body;
            auto iter = contents.begin();
//            for (;(iter) != contents[nc] && iter != contents.end();iter++);
            contents.erase(iter);
        } else if(t == ANSWER) {
            cout<<"not managed yet"<<endl;
        }

    }
}





//void User::add_to_log(string file_name){
//
//    logs.close();
//}
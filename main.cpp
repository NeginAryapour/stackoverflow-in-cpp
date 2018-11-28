#include <iostream>
#include <string>
#include "AbstractUser.h"
#include "Exceptions.h"
#include "User.h"
#include <fstream>

#ifdef _WIN32
#define CLEAR "cls"
#else //In any other OS
#define CLEAR "clear"
#endif

using namespace std;


enum MenuState {
    START,
    LOGGED_IN,
    POST,
    END
};


int main() {
    User::init("SECRET_KEY");
    User * loggedInUser = nullptr;
    MenuState menuState = MenuState::START;
    string last_message;
//    ofstream logs("logs.txt");

    char choice;
    while(menuState != MenuState::END) {
        system(CLEAR);
        if (!last_message.empty())
            cout << last_message << endl;
        last_message = "";
        switch (menuState) {
            case MenuState::START: {
                cout << "1. login\n2. signup\ne. exit\n";
                cin >> choice;
                switch (choice) {
                    case '1': { // login
                        try {
                            string username, password;
                            cout << "Enter Username: ";
                            cin >> username;
                            cout << "Enter Password: ";
                            cin >> password;
                            loggedInUser = &User::login(username,password);
                            std::ofstream logs("logs.txt",ios::app |ios::out);
                            logs<<*loggedInUser<<endl;
                            logs.close();
                            menuState = MenuState::LOGGED_IN;
                        } catch (WrongUsernameOrPasswordException &e) {
                            last_message = e.what();
                        }
                        break;
                    }
                    case '2': { // signup
                        try {
                            string username, password;
                            cout << "Enter Username: ";
                            cin >> username;
                            cout << "Enter Password: ";
                            cin >> password;
                            loggedInUser = &User::signup(username, password);
                            menuState = MenuState::LOGGED_IN;
                            last_message = "User signed up!\n";
                        } catch (UserAlreadyExistsException &e) {
                            last_message = e.what();
                        }
                        break;
                    }
                    case 'e': { // exit
                        menuState = MenuState::END;
                        break;
                    }
                    default: { // unknown input
                        last_message = "Unknown Input\n";
                        break;
                    }
                }
                break;
            }
            case MenuState::LOGGED_IN: {

                system(CLEAR);
                cout <<"q. Qustions\nd. delete account\nl. logout\ne. exit\n";
                cin >> choice;
                switch (choice) {
                    case 'd': {
                        try {
                            loggedInUser->deleteAccount();
                            cout << "Account successfully deleted\n";
                            loggedInUser = nullptr;
                            menuState = MenuState::START;
                        }
                        catch (DeleteAdminException &e) {
                            last_message = e.what();
                        }
                        break;
                    }
                    case 'l': { // logout
                        loggedInUser = nullptr;
                        menuState = MenuState::START;
                        last_message = "GOOD BYE\n";
                        break;
                    }
                    case 'e': { // exit
                        menuState = MenuState::END;
                        break;
                    }
                    case 'q': {//
                        menuState = MenuState :: POST;
                        break;

                    }
                    default: { // unknown input
                        last_message = "Unknown Input\n";
                        break;
                    }

                }
                break;
            }
            case MenuState ::POST:{
                system(CLEAR);
                cout << "1.Ask a new question or send an answer\n2.See your questions\n3.Edit your question\n4.See your Answers\n";
                cin >> choice;
                switch(choice){
                    case '1':{
                        cout<<"1.Ask a new question\n2.Answer to a question"<<endl;
                        char askOrAnswer;
                        cin>>askOrAnswer;
                        switch (askOrAnswer){
                            case '1':{ //ask q
                                loggedInUser->MakeContent(QUESTION, nullptr);
                                break;
                            }
                            case '2':{ //answer to q
                                cout<<"Enter the Content you want to answer"<<endl;
                                cout<<"not managed yet"<<endl;

                                //get content
                                //search for contetn
                                //if autration
                                //destination  = content
//                                loggedInUser->MakeContent(ANSWER,);
                                break;

                            }
                        }
                        break;

                    }
                    case '2': {//see q
                        cout<<"Inter the number of your Questions you want to see"<<endl;
                        int numberOfQuestions;
                        cin>>numberOfQuestions;
                        loggedInUser->SeeContents(QUESTION,numberOfQuestions);
                        break;


                    }
                    case '3':{//edit q
                        cout<<"q. edit your questions\na. edit your answer"<<endl;
                        char editType;
                        cin>>editType;
                        switch (editType){
                            case 'q': {
                                int nq;
                                cout << "please enter the number of your Question" << endl;
                                cin >> nq;
                                loggedInUser->EditContent(nq, QUESTION,EDIT);
                                break;
                            }
                            case 'a': {
                                int na;
                                cout << "please enter the number of your Answer" << endl;
                                cin >> na;
                                loggedInUser->EditContent(na, ANSWER,EDIT);
                                break;
                            }
                        }
                        break;
                    }
                    case '4':{//see answer
                        cout<<"Inter the number of your answers you want to see"<<endl;
                        int numberOfAnswers;
                        cin>>numberOfAnswers;
                        loggedInUser->SeeContents(ANSWER,numberOfAnswers);
                        break;
                    }
                    default:{
                        last_message = "Unknown Input\n";
                        break;
                    }
                }
            }
        }
    }
    system(CLEAR);
    cout << "GOODBYE" << endl;
    return 0;
}

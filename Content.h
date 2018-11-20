//
// Created by spsina on 11/8/18.
//

#ifndef STACKOVERFLOW_IN_CPP1_CONTENT_H
#define STACKOVERFLOW_IN_CPP1_CONTENT_H
#include <vector>
#include <iostream>
#include "AbstractUser.h"

enum ContentType{
    QUESTION,
    ANSWER
};

enum ContentRelationType{
    DUPLECATE_OF,
    ANSWER_TO
};
class ContentRelation ;
class Content {
   string body;
   ContentType type;
   vector<string> tag; 
   int visit;
   vector<ContentRelation> relations;
public:

    void set_body(string str){
        body = str;
    }

    string get_body(){
        return body;
    }

    ContentType get_ContentType(){
        return type;
    }


    void set_tag(string str) {
        tag.push_back(str);
    }

    // void remove_tag(string str){
    //     tag.insert(str);
    // }

    bool search_tag(string str){
        for(auto iter = tag.begin();iter != tag.end();iter++){
            if(*iter ==  str)
                return true;
        }
        return false;
    }

};

class ContentRelation {
    Content destination;
    ContentRelationType type;

};

#endif //STACKOVERFLOW_IN_CPP1_CONTENT

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
enum EditType{
    DELETE,
    EDIT
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

public:
    int visit;
    vector<ContentRelation> relations;
    Content(string ContentBody ,ContentType type1,vector<string> tags,int ContentVisit,vector<ContentRelation> ContetntRelations):
    body(ContentBody),type(type1),tag(tags),visit(ContentVisit = 0),relations(ContetntRelations) {}

    void set_body(string str){
        body = str;
    }

    string get_body(){
        return body;
    }

    ContentType get_ContentType(){
        return type;
    }

    void setContentType(ContentType type){
        this->type = type;
    }



    void set_tag(string str) {
        tag.push_back(str);
    }

    // void remove_tag(string str){
    //     tag.insert(str);
    // }

    bool search_tag(string str) {
        for(auto iter = tag.begin();iter != tag.end();iter++) {
            if(*iter ==  str)
                return true;
        }
        return false;
    }
    friend ostream&operator <<(ostream&out,Content & c) {
        out<<c.body<<endl;
        return out;
    }


//    void Add_to_contentRelations(ContentRelation & c){
//        relations.push_back(c);
//    }

};

class ContentRelation {
    Content destination;
    ContentRelationType type;
public:
    ContentRelation(Content dest,ContentRelationType type1):destination(dest),type(type1) {};
    void setDestination(Content dest){
        destination = move(dest);
    }
    void setContenRelationType(ContentRelationType type1){
        type = type1;
    }

};

//ContentRelation::ContentRelation(Content dest, ContentRelationType type1)}

#endif //STACKOVERFLOW_IN_CPP1_CONTENT

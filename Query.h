//
// Created by jakob on 2/14/2022.
//

#ifndef UNTITLED_QUERY_H
#define UNTITLED_QUERY_H

#include <vector>
#include <string>
#include "Predicate.h"

using namespace std;

class Query{
private:
    Predicate predicate;
public:
    Query(Predicate predicate): predicate(predicate){}

    Predicate getPredicate(){
        return predicate;
    }
    vector<string> getParameters(){
        return predicate.getNames();
    }
    string toString(){
        stringstream ss;
        ss<<predicate.toString()<<"?";
        return ss.str();    }
};
#endif //UNTITLED_QUERY_H

//
// Created by jakob on 2/8/2022.
//

#ifndef UNTITLED_RULE_H
#define UNTITLED_RULE_H

#include <string>
#include "Predicate.h"

using namespace std;
class Rule {
private:
    Predicate head;
    vector<Predicate> predicates;
public:
    Rule(Predicate head, vector<Predicate> predicates): head(head), predicates(predicates){}
    string toString(){
        stringstream ss;
        ss<<head.toString()<<" :- ";
        for(int i = 0; i<(int)(predicates.size()); i++){
            ss<<predicates.at(i).toString();
            if(i!=(int)(predicates.size()-1)){
                ss<<",";
            }
        }
        ss<<".";
        return ss.str();
    }
};
#endif //UNTITLED_RULE_H

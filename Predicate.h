//
// Created by jakob on 2/8/2022.
//

#ifndef UNTITLED_PREDICATE_H
#define UNTITLED_PREDICATE_H

#include "Parameter.h"
#include <string>
#include <vector>

using namespace  std;
class Predicate {
private:
    string name;
    //for predicate
    vector<Parameter> parameters;
    //for head predicate
    vector<string> idList;
    bool headPredicate=false;
public:
    //Head predicate
    Predicate(string name, vector<string> idList): name(name), idList(idList){
        headPredicate=true;
    }
    //Predicate
    Predicate(string name, vector<Parameter> parameters): name(name), parameters(parameters){}

    string getName(){
        return name;
    }

    vector<string> getNames(){
        vector<string> params;
        for(int i = 0; i< (int(parameters.size())); i++){
            params.push_back(parameters.at(i).toString());
        }
        return params;
    }

    string toString(){
        //if(idList.size()==2)
            //cout << "predicate: " <<idList.size() <<endl;
        stringstream  ss;
        ss<<name<<"(";
        if(headPredicate){
            for(int i = 0; i<(int)(idList.size()); i++){
                //cout <<idList.size()<<endl;
                ss<<idList.at(i);
                if(i!=(int)(idList.size()-1)){
                    ss<<",";
                }
            }
        }else{
            for(int j = 0; j<(int)(parameters.size()); j++){
                ss<<parameters.at(j).toString();
                if(j!=(int)(parameters.size()-1)){
                    ss<<",";
                }
            }
        }
        ss<<")";
        return ss.str();
    }
};
#endif //UNTITLED_PREDICATE_H

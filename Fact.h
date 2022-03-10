//
// Created by jakob on 2/14/2022.
//

#ifndef UNTITLED_FACT_H
#define UNTITLED_FACT_H

#include <vector>
#include <string>

using namespace std;
class Fact{
private:
    string name;
    vector<string> strings;
public:
    Fact(string name, vector<string> strings): name(name), strings(strings){}
    string toString(){
        stringstream ss;
        ss<<name<<"(";
        for(int i = 0; i<(int)(strings.size()); i++){
            ss<<strings.at(i);
            if(i!=(int)(strings.size()-1)){
                ss<<",";
            }
        }
        ss<<").";
        return ss.str();
    }
    string getName(){
        return name;
    }
    vector<string> getStrings(){
        return strings;
    }
};
#endif //UNTITLED_FACT_H

//
// Created by jakob on 2/28/2022.
//

#ifndef UNTITLED_SCHEME_H
#define UNTITLED_SCHEME_H

#include <string>
#include<vector>

using namespace std;

class Scheme : public vector<string> {

private:
    string name;
    vector<string> names;

public:

    Scheme(vector<string> names, string name) : names(names), name(name) {}


    unsigned size() const {
        return names.size();
    }

    const string& at(int index) const {
        return names.at(index);
    }

    string getName(){
        return name;
    }
    vector<string> getNames(){
        return names;
    }
    string toString(){
        stringstream ss;
        ss<<name<<"(";
        for(int i = 0; i<(int)(names.size()); i++){
            ss<<names.at(i);
            if(i!=(int)(names.size()-1)){
                ss<<",";
            }
        }
        ss<<")";
        return ss.str();
    }
    /*
    void rename(string original, string change){
        for(int i = 0; i<(int)(names.size()); i++){
            if(names.at(i) == original){
                names.at(i)=change;
                break;
            }
        }
    }*/

    // TODO: add more delegation functions as needed

};
#endif //UNTITLED_SCHEME_H

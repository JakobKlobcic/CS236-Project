//
// Created by jakob on 2/8/2022.
//

#ifndef UNTITLED_PARAMETER_H
#define UNTITLED_PARAMETER_H

#include <string>
#include <iostream>
#include "Token.h"

using namespace std;
class Parameter {
private:
    string value;
public:
    Parameter(string value) : value(value){
        //cout<<this->toString()<<endl;
    }
    string toString(){
        return value;
    }
};
#endif //UNTITLED_PARAMETER_H

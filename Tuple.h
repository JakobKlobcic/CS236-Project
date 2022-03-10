//
// Created by jakob on 2/28/2022.
//

#ifndef UNTITLED_TUPLE_H
#define UNTITLED_TUPLE_H

#include <string>
#include<vector>
#include <sstream>
#include "Scheme.h"

using namespace std;

class Tuple : public vector<string> {
//TODO: return
private:

    vector<string> values;

public:

    Tuple(vector<string> values) : values(values) { }

    unsigned size() const {
        return values.size();
    }

    const string& at(int index) const {
        return values.at(index);
    }

    bool operator<(const Tuple t) const {
        return values < t.values;
    }

    string toString(const Scheme& scheme) const {
        stringstream out;
        for (unsigned i = 0; i < size(); i++) {
            if (i > 0)
                out << ", ";
            const string& name = scheme.at(i);
            const string& value = at(i);
            out << name << "=" << value;
        }
        return out.str();
    }

    vector<string> getValues(){
        return values;
    }

    // TODO: add more delegation functions as needed

};
#endif //UNTITLED_TUPLE_H

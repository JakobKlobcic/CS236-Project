//
// Created by jakob on 2/28/2022.
//

#ifndef UNTITLED_RELATION_H
#define UNTITLED_RELATION_H


#include <string>
#include<vector>
#include <sstream>
#include "Scheme.h"
#include "Tuple.h"

using namespace std;
class Relation{
//TODO: select, project rename
private:
    Scheme scheme;
    vector<Tuple> tuples;
    string name;

public:
    Relation(string name, Scheme scheme): scheme(scheme), name(name){}

    //Relation(){}

    Relation selectType1(int index, const string& value) const {
        Relation result(name, scheme);
        for (auto& tuple : tuples)
            if (tuple.at(index) == value)
                result.addTuple(tuple);
        return result;
    }

    Relation selectType2(int position1, int position2){
        Relation result(name, scheme);
        for (auto& tuple : tuples)
            if (tuple.at(position1) == tuple.at(position2))
                result.addTuple(tuple);
        return result;
    }
    /*
    Relation project(vector<string> positions) {
        vector<string> originalSchemeNames = scheme.getNames();
        vector<string> newSchemeNames;
        for (int i = 0; i < (int) (originalSchemeNames.size()); i++)
            if (find(positions.begin(), positions.end(), i) != positions.end())
                newSchemeNames.push_back(originalSchemeNames.at(i));

        Scheme a = Scheme(newSchemeNames, scheme.getName());

        Relation result(name, a);

        for (int i = 0; i < (int) (tuples.size()); i++) {
            vector<string> oldTupleValues = tuples.at(i);
            vector<string> newTupleValues;
            for (int j = 0; j < (int) (originalSchemeNames.size()); j++) {
                if (find(positions.begin(), positions.end(), i) != positions.end()) {
                    newTupleValues.push_back(oldTupleValues.at(j));
                }
            }
            result.addTuple(Tuple(newTupleValues));
        }
        return result;
    }
    */
    Relation rename(int position, string change){
        //Only changes the scheme
        vector<string> names = scheme.getNames();
        names.at(position)=change;
        return {name,Scheme(names, scheme.getName())};

    }

    void addTuple(Tuple tuple){
        tuples.push_back(tuple);
    }

    string getName(){
        return name;
    }

    string toString(){
        stringstream ss;
        ss<<"Scheme: ";
        for(int i = 0; i<(int)(scheme.getNames().size()); i++){
            ss<<scheme.getNames().at(i);
            if(i!=(int)(scheme.getNames().size())-1)
                ss<<", ";
        }
        ss<<endl;
        for(int i = 0; i<(int)(tuples.size()); i++){
            ss<<"Tuple: ";
            for(int j = 0; j< tuples.at(i).getValues().size(); j++){
                if (j > 0)
                    ss << ", ";
                ss << tuples.at(i).getValues().at(j) ;
            }
            ss << endl;
        }
        ss<<endl;
        return ss.str();
    }

};
#endif //UNTITLED_RELATION_H

/*

    SK(X,'c')?
  SK('b','c')?
  SK(X,X)?
  SK(X,Y)?
  SK('c','c')?


  position - index of column


 * */
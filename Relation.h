//
// Created by jakob on 2/28/2022.
//

#ifndef UNTITLED_RELATION_H
#define UNTITLED_RELATION_H


#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
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
        for (auto& tuple : tuples) {
            if (tuple.at(position1) == tuple.at(position2)) {
                result.addTuple(tuple);
            }
        }
        return result;
    }

    Relation project(vector<int> positions) {
        vector<string> originalSchemeNames = scheme.getNames();
        vector<string> newSchemeNames={};
        for (int i = 0; i < (int) (originalSchemeNames.size()); i++) {
            if ( find(positions.begin(), positions.end(), i) != positions.end() ) {
                newSchemeNames.push_back(originalSchemeNames.at(i));
            }
        }

        Scheme a = Scheme(newSchemeNames, scheme.getName());

        Relation result(name, a);

        for (int i = 0; i < (int)(tuples.size()); i++) {
            vector<string> oldTupleValues = tuples.at(i).getValues();
            vector<string> newTupleValues;

            for (int j = 0; j < (int)(originalSchemeNames.size()); j++) {
                if (find(positions.begin(), positions.end(), j) != positions.end()) {
                    newTupleValues.push_back(oldTupleValues.at(j));
                }
            }
            result.addTuple(Tuple(newTupleValues));
        }

        return result;
    }

    Relation rename(int position, string change){
        vector<string> names = scheme.getNames();
        names.at(position)=change;
        Relation result = {name,Scheme(names, scheme.getName())};
        for(int i = 0; i<(int)(tuples.size());i++){
            result.addTuple(tuples.at(i));
        }
        return result;

    }

    Relation removeDuplicates(){
        Relation result = {name,Scheme(scheme.getNames(), scheme.getName())};
        //go through all tuples
        for (int i = 0; i < (int)(tuples.size()); ++i) {
            Tuple check = tuples.at(i);
            //go through them again comparing to i-th tuple
            for (int j = i; j < (int)(tuples.size()); ++j) {
                //go through parameters
                if(j!=i)
                    if(tuples.at(j).compareTuple(tuples.at(i))){
                        tuples.erase(tuples.begin()+j);
                        j--;
                    }
                //cout<<tuples.size()<<endl;
            }
        }
        for (int i = 0; i <(int)(tuples.size()) ; ++i) {
            result.addTuple(tuples.at(i));
        }
        return result;
    }

    Relation sortTuples(){
        Relation result = {name,Scheme(scheme.getNames(), scheme.getName())};
        vector<Tuple> tups = tuples;
        for (int i = 0; i < (int)(tuples.size()); ++i) {
            for (int j = i; j < (int)(tuples.size()); ++j) {
                if(tups.at(j)<tups.at(i)){
                    iter_swap(tups.begin() + i, tups.begin() + j);
                }
            }
        }
        for (int i = 0; i < (int)(tups.size()); ++i) {
            result.addTuple(tups.at(i));
        }
        return result;
    }

    void addTuple(Tuple tuple){
        tuples.push_back(tuple);
    }

    int getSize(){
        return (int)(tuples.size());
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
            for(int j = 0; j< (int)(tuples.at(i).getValues().size()); j++){
                if (j > 0)
                    ss << ", ";
                ss << tuples.at(i).getValues().at(j) ;
            }
            ss << endl;
        }
        ss<<endl;
        return ss.str();
    }

    string toStringP3(){
        stringstream  ss;
        //cout<<"printing: "<<tuples.size()<<endl;

        if (!tuples.empty()){
            vector<int> duplicates={};

            for (int i = 0; i < (int)(tuples.size()); ++i) {
                if((int)(scheme.getNames().size())>0)
                    ss<<"  ";
                vector<string> usedParams={};
                for (int j = 0; j < (int)(scheme.getNames().size()); ++j) {
                    if(find(usedParams.begin(),usedParams.end(),scheme.getNames().at(j))==usedParams.end()){
                        usedParams.push_back(scheme.getNames().at(j));
                        ss << scheme.getNames().at(j) << "=" << tuples.at(i).getValues().at(j);
                        if (j != (int)(scheme.getNames().size())-1 && (find(usedParams.begin(),usedParams.end(),scheme.getNames().at(j+1))==usedParams.end()))
                            ss << ", ";
                        usedParams.push_back(scheme.getNames().at(j));
                    }
                }
                if((int)(scheme.getNames().size())>0)
                    ss<<endl;
            }
        }
        return ss.str();
    }

    static bool joinable(const Scheme& leftScheme, const Scheme& rightScheme,
                         const Tuple& leftTuple, const Tuple& rightTuple) {

        for (unsigned leftIndex = 0; leftIndex < leftScheme.size(); leftIndex++) {
            const string& leftName = leftScheme.at(leftIndex);
            const string& leftValue = leftTuple.at(leftIndex);
            cout << "left name: " << leftName << " value: " << leftValue << endl;
        }
        for (unsigned rightIndex = 0; rightIndex < rightScheme.size(); rightIndex++) {
            const string& rightName = rightScheme.at(rightIndex);
            const string& rightValue = rightTuple.at(rightIndex);
            cout << "right name: " << rightName << " value: " << rightValue << endl;
        }
        return true;
    }

};
#endif //UNTITLED_RELATION_H
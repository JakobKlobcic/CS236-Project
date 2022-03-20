//
// Created by jakob on 3/5/2022.
//

#ifndef UNTITLED_DATABASE_H
#define UNTITLED_DATABASE_H

#include "Relation.h"

class Database{
private:
    vector<Relation> relations;
public:
    void addRelation(Relation relation){
        relations.push_back(relation);
    }
    Database(){}

    vector<Relation> getRelations(){
        return relations;
    }
    void addTuples(string name, Tuple tuple){
        for(int i = 0; i<(int)(relations.size()); i++){
            if(name==relations.at(i).getName()){
                relations.at(i).addTuple(tuple);
            }
        }
    }

};
#endif //UNTITLED_DATABASE_H

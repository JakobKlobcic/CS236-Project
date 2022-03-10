//
// Created by jakob on 3/7/2022.
//

#ifndef UNTITLED_INTERPRETER_H
#define UNTITLED_INTERPRETER_H

#include "DatalogProgram.h"

class Interpreter{
private:
    DatalogProgram program;
public:
    Interpreter(DatalogProgram program): program(program) {
        //TODO: Make a Relation for each scheme-Predicate, and put that Relation in the Database data member
        createRelations();
        //TODO: Make a Tuple for each fact-Predicate, and put that Tuple in the appropriate Relation in the Database
        insertTuples();
        //TODO: Loop through queries
        evaluateQueries();
        /*for (int i = 0; i < (int) (program.getQueries().size()); i++) {
            vector<Relation> relations = program.getDatabase().getRelations();
            vector<Relation> queryRelations;
            while ((int) (relations.size()) > 0) {
                if (q.getPredicate().getName() == relations.at(0).getName()) {
                    queryRelations.push_back(relations.at(0));
                }
                cout << "relation: " << relations.at(0).getName() << endl;
                relations.erase(relations.begin());
                //TODO check type of query
            }
        }*/
    }

    void createRelations(){
        string relationName="";
        for(int i = 0; i<(int)(program.getSchemes().size()); i++){
            //this assumes all scheme names are different
            if(relationName!=program.getSchemes().at(i).getName())
                program.getDatabase().addRelation(Relation(program.getSchemes().at(i).getName(),program.getSchemes().at(i)));
        }
    }

    void insertTuples(){
        for(int i = 0; i<(int)(program.getFacts().size()); i++){
            string name = program.getFacts().at(i).getName();
            program.getDatabase().addTuple(name, Tuple(program.getFacts().at(i).getStrings()));
        }
    }

    void evaluateQueries(){
        vector<Relation> currentRelations = program.getDatabase().getRelations();
        vector<Relation> newRealtions;
        vector<Query> queries = program.getQueries();
        for (int i = 0; i < (int) (queries.size()); i++) {
            cout<< queries.at(1).toString();
            vector<string> queryParameters = queries.at(1).getParameters();
            vector<string> parameterType={};
            for (int k = 0; k < (int) (queryParameters.size()); k++){
                if((int)(queryParameters.at(k).size())==1){
                    parameterType.push_back("VARIABLE");
                }else{
                    parameterType.push_back("CONSTANT");
                }
            }

            //for(){}

            //1. Check name and find relation with the same name.
            string queryName = queries.at(i).getPredicate().getName();
            Relation queryRelation;
            for(int k = 0; k < (int)(currentRelations.size()); k++){
                if(queryName==currentRelations.at(k).getName()){
                    queryRelation = currentRelations.at(k);
                    break;
                }
            }

            //2. Check the type of query and choose the appropriate process
            vector<string> predicates = queries.at(i).getPredicate().getNames();
            for (int k = 0; k < (int)(queries.at(i).getPredicate().getNames().size()); k++){

            }
            //Query relations returns the relations that queries require

        }
    }
};
#endif //UNTITLED_INTERPRETER_H

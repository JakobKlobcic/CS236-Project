//
// Created by jakob on 3/7/2022.
//

#ifndef UNTITLED_INTERPRETER_H
#define UNTITLED_INTERPRETER_H

#include "DatalogProgram.h"

class Interpreter{
private:
    DatalogProgram program;
    Database database=Database();
public:
    Interpreter(DatalogProgram program): program(program) {

        createRelations();

        insertTuples();

        evaluateQueries();
    }

    void createRelations(){
        string relationName="";
        for(int i = 0; i<(int)(program.getSchemes().size()); i++){
            //this assumes all scheme names are different
            //if(relationName!=program.getSchemes().at(i).getName())
            Relation r = Relation(program.getSchemes().at(i).getName(),program.getSchemes().at(i));
            database.addRelation(r);
        }
    }

    void insertTuples(){
        for(int i = 0; i<(int)(program.getFacts().size()); i++){
            string name = program.getFacts().at(i).getName();
            database.addTuples(name, Tuple(program.getFacts().at(i).getStrings()));
        }
    }

    void evaluateQueries(){
        vector<Relation> currentRelations = database.getRelations();
        vector<Relation> newRealtions;
        vector<Query> queries = program.getQueries();
        for (int i = 0; i < (int) (queries.size()); i++) {
            vector<string> queryParameters = queries.at(i).getPredicate().getNames();
            vector<string> parameterType={};
            vector<int> variablePositions={};
            for (int k = 0; k < (int) (queryParameters.size()); k++){
                if(isVariable(queryParameters.at(k))){
                    parameterType.push_back("VARIABLE");
                    variablePositions.push_back(k);
                }else{
                    parameterType.push_back("CONSTANT");
                }
            }

            //for(){}

            //1. Check name and find relation with the same name.
            string queryName = queries.at(i).getPredicate().getName();
            int a = -1;
            //this loop finds the relation matching the query and stores the index in a
            for(int k = 0; k < (int)(currentRelations.size()); k++){
                //cout << currentRelations.at(k).getName() << endl;
                if(queryName==currentRelations.at(k).getName()){
                    //cout << currentRelations.at(k).getName()<<endl;
                    a=k;
                    break;
                }
            }
            //If there is q relation with the query name
            Relation result = currentRelations.at(a);
            if(a!=-1){

                //2. Check the type of query and choose the appropriate process

                vector<vector<int>> sameVariableIndexes;
                vector<int> constants;
                for (int k = 0; k < (int)(queryParameters.size()); k++){
                    if(parameterType.at(k) == "VARIABLE") {
                        vector <int> sameVariable={k};
                        for(int j = k; j<(int)(queryParameters.size()); j++){
                            if(j>k){//Todo
                                if(queryParameters.at(k)==queryParameters.at(j)){
                                    sameVariable.push_back(j);
                                }
                            }
                        }
                        sameVariableIndexes.push_back(sameVariable);
                    }
                    else{
                        constants.push_back(k);
                    }
                }

                cout << queries.at(i).toString();
                result=result.removeDuplicates();
                result=result.sortTuples();
                for(int k = 0; k < (int)(sameVariableIndexes.size()); k++){
                    if(sameVariableIndexes.at(k).size()>1) {
                        for (int j = 0; j < (int) (sameVariableIndexes.at(k).size()) - 1; j++) {
                            result = result.selectType2(j, j + 1);
                            result = result.rename(j,queryParameters.at(j));
                            result = result.rename(j+1,queryParameters.at(j+1));
                        }
                        //cout << result.toString()<<endl;
                    }else{
                        result = result.rename(sameVariableIndexes.at(k).at(0),queryParameters.at(sameVariableIndexes.at(k).at(0)));
                        //cout<<"No duplicates"<<endl;
                    }
                    //cout<<k<<endl;
                }

                for(int k = 0; k<(int)(constants.size());k++){
                    int index=constants.at(k);
                    result=result.selectType1(index, queryParameters.at(index));
                }
                if(result.getSize()!=0){
                    cout << " Yes("<<result.getSize()<<")"<<endl;
                }else{
                    cout<<" No"<<endl;
                }
                //cout << result.toString()<<endl;


            }else{
                cout<<" No"<<endl;
            }
            /*
            for (int j = 0; j < (int)(parameterType.size()); ++j) {
                if(parameterType.at(j)== "CONSTANT"){
                    result = result.selectType1(j,queryParameters.at(j));
                }
            }*/
            result=result.project(variablePositions);
            cout << result.toStringP3();

            //Query relations returns the relations that queries require

        }
    }

    bool isVariable(string a){
        if(a.at(0)=='\'' && a.at((int)(a.size())-1)=='\''){
            return false;
        }else{
            return true;
        }
    }

};
#endif //UNTITLED_INTERPRETER_H

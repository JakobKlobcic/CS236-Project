//
// Created by jakob on 2/8/2022.
//

#ifndef UNTITLED_DATALOGPROGRAM_H
#define UNTITLED_DATALOGPROGRAM_H
#include<string>
#include "Query.h"
#include "Scheme.h"
#include "Rule.h"
#include "Fact.h"
#include "Database.h"

using namespace std;
class DatalogProgram{
private:
    vector<Scheme> schemes;
    vector<Fact> facts;
    vector<Rule> rules;
    vector<Query> queries;
    vector<string> domain;
    bool success = true;
    vector<Token> errorTokens;
    Database database;
public:
    void addScheme(Scheme s){
        schemes.push_back(s);
    }
    void addFact(Fact f){
        facts.push_back(f);
    }
    void addRule(Rule r){
        rules.push_back(r);
    }
    void addQuery(Query q){
        queries.push_back(q);
        //ONLY ELEMENT LEFT IS THE RELATION WITH THE SAME NAME AS THE QUERY PREDICATE
    }

    void programSuccess (bool s, Token e){
        success=s;
        if(errorTokens.size()==0)
            errorTokens.push_back(e);
    }

    void setDomain(vector<string> s){
        domain=s;
        sort( domain.begin(), domain.end() );
        domain.erase( unique( domain.begin(), domain.end() ), domain.end() );
    }

    //GETTERS
    Database getDatabase(){
        return database;
    }
    vector<Scheme> getSchemes(){
        return schemes;
    }
    vector<Fact> getFacts(){
        return facts;
    }
    vector<Rule> getRules(){
        return rules;
    }
    vector<Query> getQueries(){
        return queries;
    }


    string toString(){
        stringstream  ss;
        if(success){
            ss<<"Success!"<<endl;
            ss <<"Schemes("<<(int)(schemes.size())<<"):"<<endl;
            for(int i = 0; i<(int)(schemes.size()); i++){
                ss << "  " <<schemes.at(i).toString()<<endl;
            }
            ss <<"Facts("<<(int)(facts.size())<<"):"<<endl;
            for(int i = 0; i<(int)(facts.size()); i++){
                ss << "  " <<facts.at(i).toString()<<endl;
            }
            ss <<"Rules("<<(int)(rules.size())<<"):"<<endl;
            for(int i = 0; i<(int)(rules.size()); i++){
                ss << "  " <<rules.at(i).toString()<<endl;
            }
            ss <<"Queries("<<(int)(queries.size())<<"):"<<endl;
            for(int i = 0; i<(int)(queries.size()); i++){
                ss << "  " <<queries.at(i).toString()<<endl;
            }
            ss <<"Domain("<<(int)(domain.size())<<"):"<<endl;
            for(int i = 0; i<(int)(domain.size()); i++){
                ss << "  " <<domain.at(i)<<endl;
            }

        }else{
            ss<<"Failure!"<<endl;
            ss<< "  " << errorTokens.at(0).toString();
        }
        return ss.str();
    }
};
#endif //UNTITLED_DATALOGPROGRAM_H

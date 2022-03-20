//
// Created by jakob on 2/8/2022.
//

#ifndef UNTITLED_PARSER_H
#define UNTITLED_PARSER_H
#include <vector>
#include <iostream>
#include "Token.h"
#include "Parameter.h"
#include "DatalogProgram.h"
#include "Interpreter.h"

using namespace std;
class Parser {
    private:
        DatalogProgram program;
        vector<Token> tokens;
        vector<Parameter> parameters;
        vector<Parameter> currentParametersList;
        vector<string> currentStringList;
        vector<string> currentIdList;
        vector<Predicate> currentPredicateList;
        vector<string> domain;
    public:
        Parser(const vector<Token>& tokens) : tokens(tokens) {
            for(int i = 0; i<(int)(this->tokens.size()); i++){
                //cout << this->tokens.at(i).toString()<<endl;
                if(tokens.at(i).getType()==COMMENT){
                    this->tokens.erase(this->tokens.begin()+i);
                    //cout <<i<<endl;
                }
            }
            //cout << tokens.size()<<endl;
            datalogProgram();
            Interpreter interpreter = Interpreter(program);
        }

        TokenType tokenType() const {
            return tokens.at(0).getType();
        }

        void advanceToken() {
            tokens.erase(tokens.begin());
        }

        void throwError() {
            //std::cout << "Failure!\n\t" << tokens.at(0).toString()<< endl;
            program.programSuccess(false, tokens.at(0));
        }

        void match(TokenType t) {
            //cout << "match: " << Token::typeName(t) << endl;
            //cout << "match: " << t << endl;

            if (tokenType() == t)
                advanceToken();
            else
                throwError();
        }


        void datalogProgram() {
            /*
             SCHEMES COLON scheme schemeList
		        FACTS COLON factList
		        RULES COLON ruleList
		        QUERIES COLON query queryList
			    EOF
            */
            if (tokenType() == SCHEMES) {
                match(SCHEMES);
                match(COLON);
                scheme();
                schemeList();
                match(FACTS);
                match(COLON);
                factList();
                match(RULES);
                match(COLON);
                ruleList();
                match(QUERIES);
                match(COLON);
                query();
                queryList();
                match(EOFF);
                currentParametersList.clear();
                currentStringList.clear();
                currentIdList.clear();
                currentPredicateList.clear();
                program.setDomain(domain);
                domain.clear();

            } else {
                //lambda
            }
            //TODO: datalog to string
            //cout<< program.toString();
        }


        void schemeList() {
            if (tokenType() == ID) {
                scheme();
                schemeList();
            } else {
                //lambda
            }
        }

        void factList() {
            if (tokenType() == ID) {
                fact();
                factList();
            } else {
                //lambda
            }
        }

        void ruleList() {
            if (tokenType() == ID) {
                rule();
                ruleList();
            } else {
                //lambda
            }
        }

        void queryList() {
            if (tokenType() == ID) {
                query();
                queryList();
            } else {
                //lambda
            }
        }


        void scheme() {
            string name;
            vector<string> ids;
            if (tokenType() == ID) {
                name=tokens.at(0).getValue();
                match(ID);
                match(LEFT_PAREN);
                ids.push_back(tokens.at(0).getValue());
                match(ID);
                idList();
                ids.insert(ids.end(), currentIdList.begin(), currentIdList.end());
                match(RIGHT_PAREN);
                program.addScheme(Scheme(ids, name));
                currentIdList.clear();
            } else {
                throwError();
            }

        }

        void fact() {
            string name;
            vector<string> strings;
            if (tokenType() == ID) {
                name=tokens.at(0).getValue();
                match(ID);
                match(LEFT_PAREN);
                strings.push_back(tokens.at(0).getValue());
                domain.push_back(tokens.at(0).getValue());
                match(STRING);
                stringList();
                strings.insert(strings.end(), currentStringList.begin(), currentStringList.end());
                domain.insert(domain.end(), currentStringList.begin(), currentStringList.end());
                match(RIGHT_PAREN);
                match(PERIOD);
                program.addFact(Fact(name, strings));
                currentStringList.clear();
            } else {
                throwError();
            }
        }

        void rule() {
            //headPredicate COLON_DASH predicate predicateList PERIOD
            //cout << "head predicate"<<endl;
            vector<Predicate> predicates;
            if (tokenType() == ID) {
                currentPredicateList.clear();
                headPredicate();
                Predicate head = currentPredicateList.at(0);
                currentPredicateList.clear();
                match(COLON_DASH);
                predicate();
                predicateList();
                //copy(currentPredicateList.begin()+1, currentPredicateList.end(), back_inserter(predicates));
                predicates.insert(predicates.end(), currentPredicateList.begin(), currentPredicateList.end());

                match(PERIOD);
                program.addRule(Rule(head, predicates));
                //program.addRule(Rule(currentPredicateList.at(0), predicates));
            } else {
                throwError();
            }
        }

        void query() {
            //predicate Q_MARK
            if (tokenType() == ID) {
                currentPredicateList.clear();
                predicate();
                program.addQuery(Query(currentPredicateList.at(0)));
                currentPredicateList.clear();
                match(Q_MARK);
            } else {
                throwError();
            }
        }


        void headPredicate() {
            //ID LEFT_PAREN ID idList RIGHT_PAREN
            string name;
            vector<string> ids;
            if (tokenType() == ID) {
                name=tokens.at(0).getValue();
                match(ID);
                match(LEFT_PAREN);
                ids.push_back(tokens.at(0).getValue());
                match(ID);
                idList();
                ids.insert(ids.end(), currentIdList.begin(), currentIdList.end());
                //cout << "predicate: " <<ids.at(0) << " " << ids.at(1)<<endl;
                match(RIGHT_PAREN);
                currentPredicateList.push_back(Predicate(name,ids));
                currentIdList.clear();
            } else {
                throwError();
            }
        }

        void predicate() {
            //predicate	->	ID LEFT_PAREN parameter parameterList RIGHT_PAREN
            string name;
            vector<Parameter> params;
            if (tokenType() == ID) {
                name=tokens.at(0).getValue();
                match(ID);
                match(LEFT_PAREN);
                parameter();
                parameterList();
                params.insert(params.end(), currentParametersList.begin(), currentParametersList.end());
                match(RIGHT_PAREN);
                currentPredicateList.push_back(Predicate(name, params));
                currentParametersList.clear();
            } else {
                throwError();
            }
        }


        void predicateList() {
            //COMMA STRING stringList | lambda
            if (tokenType() == COMMA) {
                match(COMMA);
                predicate();
                predicateList();
            } else {
                //lambda
            }
        }

        void parameterList() {
            if (tokenType() == COMMA) {
                match(COMMA);
                parameter();
                parameterList();
            } else {
                // lambda
            }
        }

        void stringList() {
            //COMMA STRING stringList | lambda
            if (tokenType() == COMMA) {
                match(COMMA);
                currentStringList.push_back(tokens.at(0).getValue());
                match(STRING);
                stringList();
            } else {
                //lambda
            }
        }

        void idList() {
            if (tokenType() == COMMA) {
                match(COMMA);
                currentIdList.push_back(tokens.at(0).getValue());
                match(ID);
                idList();
            } else {
                // lambda
            }
        }


        void parameter() {
            //parameter	->	STRING | ID
            if (tokenType() == STRING) {
                parameters.emplace_back(tokens.at(0).getValue());
                currentParametersList.emplace_back(tokens.at(0).getValue());
                match(STRING);
            } else if (tokenType() == ID) {
                parameters.emplace_back(tokens.at(0).getValue());
                currentParametersList.emplace_back(tokens.at(0).getValue());
                match(ID);
            }else{
                throwError();
            }
        }












        //predicateList	->	COMMA predicate predicateList | lambda


        /*

schemeList	->	scheme schemeList | lambda
factList	->	fact factList | lambda
ruleList	->	rule ruleList | lambda
queryList	->	query queryList | lambda
         */
};
#endif //UNTITLED_PARSER_H

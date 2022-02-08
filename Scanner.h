//
// Created by jakob on 1/26/2022.
//

#ifndef UNTITLED_SCANNER_H
#define UNTITLED_SCANNER_H
#pragma once
#include <string>
#include <cctype>
#include <vector>
#include <algorithm>
#include "Token.h"

class Scanner {
private:
    string input;
    vector<Token> inputTokens;
    vector<Token> tokens;
    vector <char> multiCharTokens = {':','\'','#'};
    vector<char> brakeTokens={' ',',','.','?','(',')','*','+', '\n'};
public:
    Scanner(const string& input) : input(input) {}
    void scannAllTokens(){
        int line =1;
        int i = 0;
        while(i<(int)(input.size())){
            cout << input.at(i)<<";<--input.at("<<i<<")"<<endl;
            if(input.at(i)=='\n'){
                //cout<<"newline"<<endl;
                line++;
                //cout<<"input:" << input.substr(0,i)<< endl;
                if(i!=0 && (int)(input.size())!=0){
                    inputTokens.push_back(correctIdentity(input.substr(0,i), line));
                    input.erase(0,i);
                    i=0;
                }else if((int)(input.size())!=0){
                    input.erase(0,1);
                }
                //cout<<input.size()<<" input after newline:"<<input<<endl;
                continue;
            }

            //single char
            if(std::count(brakeTokens.begin(), brakeTokens.end(), input.at(i))){
                //cout<<"single char token"<<endl;
                //cout<<"val at i = "<< i <<":"<< input.at(i) << endl;
                //cout<<"token:" <<input.substr(0,i)<<endl;
                if(isspace(input.at(i))){
                    //cout<<"space seperation"<<endl;
                    if(i!=0){
                        inputTokens.push_back(correctIdentity(input.substr(0,i), line));
                        //input = input.substr(i);
                        //input.erase(input.begin()+i);
                    }
                    //cout<<"token:" <<input.substr(0,i)<<endl;
                    //cout<<"space stuff: " << input.at(i) <<endl ;
                    input = input.substr(i+1);
                    i = 0;
                    continue;
                }
                //cout << "--------" << input.substr(i,1) << "----" <<endl;
                if(i!=0) {
                    inputTokens.push_back(correctIdentity(input.substr(0,i), line));
                }
                switch(tolower(input.at(i))){
                    case ',':
                        inputTokens.emplace_back(COMMA, input.substr(i,1), line);
                        break;
                    case '.':
                        inputTokens.emplace_back(PERIOD, input.substr(i,1), line);
                        break;
                    case '?':
                        inputTokens.emplace_back(Q_MARK, input.substr(i,1), line);
                        break;
                    case '(':
                        inputTokens.emplace_back(LEFT_PAREN, input.substr(i,1), line);
                        break;
                    case ')':
                        inputTokens.emplace_back(RIGHT_PAREN, input.substr(i,1), line);
                        break;
                    case '*':
                        inputTokens.emplace_back(MULTIPLY, input.substr(i,1), line);
                        break;
                    case '+':
                        inputTokens.emplace_back(ADD, input.substr(i,1), line);
                        break;
                }
                //inputTokens.emplace_back(UNKNOWN, input.substr(i,1), line);

                input = input.substr(i+1);
                i=0;
                continue;
            }

            //multi char
            if(std::count(multiCharTokens.begin(), multiCharTokens.end(), input.at(i))){
                //cout<<"multi char"<< input.at(i)<<endl;
                //cout<<"input at i = "<< i <<":"<< input.at(i) << endl;
                //bool readyToSubmit = false;

                if(input.at(i)=='\''){
                    //cout << "first dash ....................." <<endl;
                    //input.erase(input.begin()+i);
                    int t = 0;
                    while(i+t+1<(int)(input.size()-1) && input.at(i+t+1) !='\''){
                        //cout << input.at(t+i+1) << "--" <<i+t+1 << "--" << (int)(input.size())<<endl;
                        if(input.at(i+t+1)=='\n')
                            line++;
                        t++;
                    }
                    if(input.at(i+t+1) !='\''){
                        inputTokens.emplace_back(UNDEFINED, input.substr(i,i+t+2), line);
                        input.erase(i,i+t+2);
                        continue;
                    }
                    inputTokens.emplace_back(STRING, input.substr(i,i+t+2), line);
                    input.erase(i,i+t+2);
                    continue;
                }
                else if(input.at(i)==':'){
                    //cout<<"colon"<<endl;
                    if(input.at(i+1)=='-'){
                        if(i!=0)
                            inputTokens.push_back(correctIdentity(input.substr(0,i), line));
                        inputTokens.emplace_back(COLON_DASH, ":-", line);
                        input=input.substr(i+2);

                        i=0;
                        continue;
                    }else{
                        if(i!=0)
                            inputTokens.push_back(correctIdentity(input.substr(0,i), line));
                        inputTokens.emplace_back(COLON, ":", line);
                        input=input.substr(i+1);
                        i=0;
                        continue;
                    }

                }
                else if(input.at(i)=='#'){
                    //cout<<"#"<<endl;
                    if(input.at(i+1)=='|'){
                        //cout<<"#|"<<endl;
                        int k = 0;
                        while(i+k+3<(int)(input.size()-1) && (input.at(i+k+2) !='|' || input.at(i+k+3)!='#')){
                            if(input.at(i+k+2)=='\n')
                                line++;
                            k++;
                        }
                        if(input.at(i+k+2) !='|' && input.at(i+k+3)!='#'){
                            inputTokens.emplace_back(UNDEFINED, input.substr(i,k+4), line);
                            input.erase(i,i+k+4);
                            continue;
                        }
                        //cout << input.substr(i,k+4) <<"--" << endl;
                        //if endo of file undefined token
                        inputTokens.emplace_back(COMMENT, input.substr(i,k+4), line);
                        input.erase(i,i+k+4);
                        //cout << "--" << input <<"--" << endl;

                        continue;
                    }
                    else {
                        //cout<<"|#"<<endl;
                        int j =0;
                        while(input.at(i+j)!='\n'&& i+j<(int)(input.size())){
                            j++;
                        }
                        inputTokens.emplace_back(COMMENT, input.substr(i,j), line);
                        line++;
                        input.erase(i,i+j);
                    }

                }
                continue;
            }

            i++;

        }

        inputTokens.emplace_back(EOFF, input.substr(i,1), line+1);

        for(int j = 0; j < (int)(inputTokens.size()); j++){
            cout<<inputTokens[j].toString()<<endl;
        }

        cout << "Total Tokens = "<<inputTokens.size()<<endl;

        /*while(input.size()>0){
            Token t = scanToken();
            cout << t.toString() << endl;
            tokens.push_back(t);
        }*/
    }

    Token correctIdentity(string value, int line){
        //cout<<"identity:" << value<<endl;
       if(value == "Schemes")
            return {SCHEMES, value, line};
       else if( value == "Rules")
           return {RULES, value, line};
       else if( value == "Facts")
           return {FACTS, value, line};
       else if( value == "Queries")
           return {QUERIES, value, line};
       else
           return {ID, value, line};
    }
    void scanToken() {

    }
    //GET THE LINE NUMBER TO WORK
    Token multiCharToken(){
        cout << input.at(0) <<endl;
        //Token t = new Token();
        switch (tolower(input.at(0))){
            case 's':
                if(tolower(input.at(1))=='c'
                   && tolower(input.at(2))=='h'
                   && tolower(input.at(3))=='e'
                   && tolower(input.at(4))=='m'
                   && tolower(input.at(5))=='e'
                   && tolower(input.at(6))=='s'){
                    string result = input.substr(0,6);
                    input=input.substr(6);
                    return {SCHEMES, result, 1};
                }
                else
                    return {UNDEFINED, "", 1};
                break;
            case 'f':
                if(tolower(input.at(1))=='a'
                   && tolower(input.at(2))=='c'
                   && tolower(input.at(3))=='t'
                   && tolower(input.at(4))=='s'){
                    string result = input.substr(0,4);
                    input=input.substr(4);
                    return {FACTS, result, 1};
                }else
                    return {UNDEFINED, "", 1};
                break;
            case 'r':
                if(tolower(input.at(1))=='u'
                   && tolower(input.at(2))=='l'
                   && tolower(input.at(3))=='e'
                   && tolower(input.at(4))=='s'){
                    string result = input.substr(0,4);
                    input=input.substr(4);
                    return {RULES, result, 1};
                }
                else{

                    return {UNDEFINED, input.substr(0,4), 1};
                }
                break;
            case 'q':
                cout << input.substr(0,7)<< endl;
                if(tolower(input.at(1))=='u'
                   && tolower(input.at(2))=='e'
                   && tolower(input.at(3))=='r'
                   && tolower(input.at(4))=='i'
                   && tolower(input.at(5))=='e'
                   && tolower(input.at(6))=='s'){
                    string result = input.substr(0,7);
                    input=input.substr(7);
                    return {QUERIES, result, 1};
                }else{
                    //TODO: remove input
                    //string result = input.substr(0,7);
                    //input=input.substr(7);
                    return {UNDEFINED, "", 1};
                }
                break;
            case ':': //check for :- COLON_DASH
                if(input.at(1)=='-'){
                    string result = input.substr(0,2);
                    input=input.substr(2);
                    return {COLON_DASH, result, 1};
                }else{
                    string result = input.substr(0,1);
                    input=input.substr(1);
                    return {COLON, result, 1};
                }
                break;
            case '\'':{ // STRING that doesnt end is UNDEFINED
                int i = 0;
                bool endOfFile = false;
                while(input.at(i)!= '\'' ){
                    i++;
                    if(i >= static_cast<int>(input.size()-1)){
                        endOfFile = true;
                        break;
                    }
                }
                if (endOfFile){
                    cout<<"\' --"<<endl;
                    return {UNDEFINED, "", 1};
                }
                else {
                    string result = input.substr(0, i);
                    input=input.substr(i+1);
                    return {STRING, result, 1};
                }
                break;}
            case '#':{
                if(input.at(1)=='|'){
                    int i = 0;
                    bool endOfFile = false;
                    while(input.at(i)!= '|' && input.at(i+1)=='#' ){
                        i++;
                        if(i >= static_cast<int>(input.size()-1)){
                            endOfFile = true;
                            break;
                        }
                    }
                    if (endOfFile){
                        cout<<"#; --"<<endl;
                        return {UNDEFINED, "", 1};
                    }
                    else //if end of file is reached
                        return {COMMENT, input.substr(0, i+2), 1};
                }
                break;
            }
        }
        return {UNDEFINED, "", 1};
    }

    /*string toString(){
        stringstream out;
        for(int i = 0; i<static_cast<int>(tokens.size()); i++){
            out << tokens[i].toString() << endl;
        }
        return out.str();
    }*/
};
#endif //UNTITLED_SCANNER_H

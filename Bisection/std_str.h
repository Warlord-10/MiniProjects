#ifndef std_str
#define std_str

#include <iostream>
#include <string>
using namespace std;

/// @brief Checks if the character is an operator
/// @param op Char to evaluate
/// @return True if the given character is an operator
bool isoperator(char op){
    if(op == '+' || op == '*' || op == '-' || op == '/' || op == '^' || op == '(' || op == ')'){
        return true;        
    }
    else{
        return false;
    }
}

/// @brief Checks if the string has a maths function
/// @param w String to evaluate
/// @return True if the given string has a math function
bool is_mathop(string w){
    // True if the word is a math function
    if(w=="cos" || w=="sin" || w=="tan" || w=="log" || w=="ln"){
        return true;
    }
    else{
        return false;
    }
}

/// @brief Checks if the given string is pure integer
/// @param w String to evaluate
/// @return True if the string contains only integers
bool word_integer(string w){
    // True if the word is integer only
    for(int i=0;i<w.length();i++){
        if(isdigit(w[i]) == 0){
            return false;
        }
    }
    return true;
}


/// @brief Generates tokens.
class Tokens{
    public:
        string type;
        string value;
        Tokens(){}
        Tokens(string x, string y){
            type = x;
            value = y;
        }
        void GiveData(){
            cout << "[" << type << "," << value << "]" << endl;
        }
};

#endif
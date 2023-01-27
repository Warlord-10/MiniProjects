#include <iostream>
#include <string>
#include "std_str.h"
using namespace std;


/// @brief Generates lexical tokens.
class Lexer{
    private:
        int stack_counter = -1;   // Elements in token array
        int pointer = -1;   // iterate over the equation
        Tokens TOKENS[50];
        string current_word;
        string eq = "(";

        void Advance(){
            // Generate next pointer in equation
            pointer++;
        }
        void AddToken(string type,string val){
            if(val.empty() == false){
                stack_counter++;
                TOKENS[stack_counter] = Tokens(type,val);
            }
        }
        void Check(){
            // Tokenizer logic
            if(eq[pointer] == ' '){
                cout << "space";
            } 
            else if(eq[pointer] == 'x'){
                // Add token of variable
                AddToken("var","x");
            }
            else if(eq[pointer] == 'e'){
                AddToken("int","2.718281");
            }
            else if(isdigit(eq[pointer]) || isalpha(eq[pointer]) || eq[pointer] == '.'){
                // append to current_word
                current_word += eq[pointer];
            }
            else if(isoperator(eq[pointer])){
                // Add token of integer
                AddToken("int",current_word);
                current_word.clear();

                // Add token of operator
                current_word += eq[pointer];
                AddToken("operator",current_word);
                current_word.clear();
            }
            if(is_mathop(current_word)){
                // Add token of math
                AddToken("math",current_word);
                current_word.clear();
            }
        }

    public:
        /// @brief Input method for the string equation.
        /// @param temp_eq Equation to be evaluated.
        void Write(string temp_eq){
            // Input Method
            eq.append(temp_eq);
            eq.append(")");
        }

        /// @brief Build lexical tokens.
        /// @return Tokens* Tokens array.
        Tokens * Build(){
            cout << "Lexing...\n";
            Advance();
            
            while(pointer < eq.length()){
                Check();
                Advance();
            }
            if(word_integer(current_word) == true){
                AddToken("int",current_word);
                current_word.clear();
            }
            else{
                cout << "ERROR: Ivalid Expression" << endl;
                return nullptr;
            }
            if(TOKENS[stack_counter].type == "math" || TOKENS[stack_counter].type == "operator"){
                if(TOKENS[stack_counter].value != ")"){
                    cout << "ERROR: Ivalid Expression" << endl;
                    return nullptr;
                }
            }
            return TOKENS;
        }
        void Show(){
            // Show tokens
            for(int i=0;i<stack_counter+1;i++){
                cout << i;
                TOKENS[i].GiveData();
            }
        }
        ~Lexer(){}
};
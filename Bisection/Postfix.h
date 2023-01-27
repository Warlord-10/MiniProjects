#include <iostream>
#include <string>
#include "std_str.h"
using namespace std;


/// @brief Converts the lexical tokens into postfix notation.
class Postfix{
    private:
        Tokens *PTR;
        Tokens STACK[50];
        Tokens ANSWER[50];
        Tokens CURR;

        int stack_pointer = -1;
        int answer_pointer = -1;
        int curr_power = -1;

        void advance(){
            // Generates the next token for processing
            CURR = *PTR;
            PTR++;
        }
        int adjust(Tokens t){
            // Generates the current power in the stack
            if(t.type == "math"){
                return 3;
            }
            else{
                if(t.value == "^"){
                    return 2;
                }
                else if(t.value == "*" || t.value == "/"){
                    return 1;
                }
                else if(t.value == "+" || t.value == "-"){
                    return 0;
                }
                else if(t.value == "(" || t.value == ")"){
                    return -1;
                }
            }
            return 0;
        }

        void Push(Tokens t){
            int pow = adjust(t);
            if(t.value == ")"){
                while(STACK[stack_pointer].value != "("){
                    Pop();
                }
                stack_pointer--;
            }
            else if(t.value == "("){
                stack_pointer++;
                STACK[stack_pointer] = t;
            }
            else{
                if(pow > curr_power){
                    stack_pointer++;
                    STACK[stack_pointer] = t;
                }
                else{
                    while(pow <= curr_power){
                        Pop();
                    }
                    stack_pointer++;
                    STACK[stack_pointer] = t;
                }
            }
            curr_power = pow;
        }
        void Pop(){
            answer_pointer++;
            ANSWER[answer_pointer] = STACK[stack_pointer];
            stack_pointer--;
            curr_power = adjust(STACK[stack_pointer]);
        }

    public:
        /// @brief Generates the postfix notation 
        /// @param start Pointer to the lexical token array.
        /// @return Tokens* Token array.
        Tokens * Run(Tokens *start){
            cout << "Running...." << endl;
            PTR = start;
            advance();
            while(CURR.value > ""){
                if(CURR.type=="int" || CURR.type=="var"){
                    answer_pointer++;
                    ANSWER[answer_pointer] = CURR;
                }
                else{
                    Push(CURR);
                }
                advance();
            }
            return ANSWER;
        }
        void Show(){
            // Show tokens
            for(int i=0;i<answer_pointer+1;i++){
                cout << i;
                ANSWER[i].GiveData();
            }
        }
        ~Postfix(){}
           
};
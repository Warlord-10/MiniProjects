#include <iostream>
#include <string>
#include <math.h>
#include "std_str.h"
using namespace std;

/// @brief Evaluates the postfix notation.
class Evaluation{
    private:
        float ANSWER;
        Tokens *PTR;
        Tokens STACK[50];
        Tokens CURR;
        int stack_counter = -1;

        void Advance(){
            CURR = *PTR;
            PTR++;
        }

        void Solve(Tokens a, Tokens b){
            float ans = 0;
            if(CURR.value == "+"){
                ans = stof(a.value) + stof(b.value);
            }
            else if(CURR.value == "-"){
                ans = stof(b.value) - stof(a.value);
            }
            else if(CURR.value == "*"){
                ans = stof(a.value) * stof(b.value);
            }
            else if(CURR.value == "/"){
                ans = stof(b.value) / stof(a.value);
            }
            else if(CURR.value == "^"){
                ans = powf(stof(b.value),stof(a.value));
            }
            Pop();
            STACK[stack_counter].type = "int";
            STACK[stack_counter].value = to_string(ans);
            //Pop();
            //Push(Tokens ("int",to_string(ans)));
        }
        void Math(Tokens a){
            float ans = 0;
            if(CURR.value == "sin"){
                ans = sinf(stof(a.value));
            }
            else if(CURR.value == "cos"){
                ans = cosf(stof(a.value));
            }
            else if(CURR.value == "log"){
                ans = log10f(stof(a.value));
            }
            else if(CURR.value == "ln"){
                ans = logf(stof(a.value));
            }
            STACK[stack_counter].type = "int";
            STACK[stack_counter].value = to_string(ans);
            //Pop();
            //Push(Tokens ("int",to_string(ans)));
        }

        void Push(Tokens t){
            stack_counter++;
            STACK[stack_counter] = t;
        }
        void Pop(){
            stack_counter--;
        }

    public:
        /// @brief Runs the evaluation process.
        /// @param start Pointer to postfix array.
        /// @param X Value to be used for the evaluation.
        float Run(Tokens *start, float X){
            stack_counter = -1;
            PTR = start;
            Advance();

            while(CURR.value > ""){
                if(CURR.type == "operator"){
                    Solve(STACK[stack_counter], STACK[stack_counter-1]);
                }
                else if(CURR.type == "math"){
                    Math(STACK[stack_counter]);
                }
                else if(CURR.type == "var"){
                    CURR.value = to_string(X);
                    Push(CURR);
                }
                else if(CURR.type == "int"){
                    Push(CURR);
                }
                Advance();
            }
            return stof(STACK[0].value);
        }
        void Show(){
            // Show tokens
            for(int i=0;i<stack_counter+1;i++){
                cout << i;
                STACK[i].GiveData();
            }
        }

};
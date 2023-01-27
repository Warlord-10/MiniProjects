/* Code for Bisection method
    1) Find two numbers a and b where a-b = 0.1
    2) solve x1 = (a+b)/2
    3) Find f(x1)
*/

/*
    Grammar: integers,sinx,cosx,tanx,logx,e,x
    Ex- 2*x+3*x^3*log(x)

    Operator Power:
        math: 3
        ^: 2 
        /*: 1
        +-: 0
        ():-1
*/

#include <iostream>
#include <string>
#include <math.h>
#include "std_str.h"
#include "Lexer.h"
#include "Postfix.h"
#include "Evaluation.h"
using namespace std;


class Solver{
    private:
        float a=0, b=1;

        Lexer *LEXER;
        Postfix *POSTFIX;
        Evaluation *EVALUATION;
        Tokens *TOKENS = new Tokens[50];

        bool opp_sign(float x, float y){
            if(x == NAN || x == INFINITY || y == NAN || y == INFINITY){
                return false;
            }
            if(x>=0 && y<0){
                return true;
            }
            else if(y>=0 && x<0){
                return true;
            }
            return false;
        }
        void find_limits(float x, float y){
            if(fabs(x-y) == 0.1f);
        }
        void initialise(){
            while(opp_sign(EVALUATION->Run(TOKENS,a),EVALUATION->Run(TOKENS,b)) == false){
                a++;
                b++;
            }
            for(float i=a;i<b;i+=0.1){
                if(opp_sign(EVALUATION->Run(TOKENS,i),EVALUATION->Run(TOKENS,i+0.1))){
                    a=i;
                    b=i+0.1;
                    break;
                }
            }
            cout << "Initialised with: " <<a<<", "<<b<<endl; 
        }
        void Bisection(){
            float temp1, temp2, mid, mid_val;
            cout <<"a,b: "<<a << ", " << b << endl;
            temp1 = EVALUATION->Run(TOKENS,a);
            temp2 = EVALUATION->Run(TOKENS,b); 
            cout <<"f(a),f(b): " <<temp1 << ", " << temp2 << endl;

            mid = (a+b)/2;
            cout << "mid: " << mid << endl;
            mid_val = EVALUATION->Run(TOKENS,mid);
            cout << "f(mid): " << mid_val << endl;

            if(opp_sign(temp1,mid_val)){
                b = mid;
            }
            else{
                a = mid;
            }
            cout <<"Updated a,b: " << a << ", " << b << endl;
        }
        void Falsi(){
            float temp1, temp2, mid, mid_val;
            cout <<"a,b: "<<a << ", " << b << endl;
            temp1 = EVALUATION->Run(TOKENS,a);
            temp2 = EVALUATION->Run(TOKENS,b); 
            cout <<"f(a),f(b): " <<temp1 << ", " << temp2 << endl;
            
            mid = (a*temp2-b*temp1)/(temp2-temp1);
            cout << "mid: " << mid << endl;
            mid_val = EVALUATION->Run(TOKENS,mid);
            cout << "f(mid): " << mid_val << endl;

            if(opp_sign(temp1,mid_val)){
                b = mid;
            }
            else{
                a = mid;
            }
            cout <<"Updated a,b: " << a << ", " << b << endl;
        }

    public:
        Solver(){
            LEXER = new Lexer();
            POSTFIX = new Postfix();
            EVALUATION = new Evaluation();
        }

        void Start(){
            string eq = "x^3-x-1",x;
            cout << "EQUATION: ";
            cin >> eq;
            cout << "METHOD: ";
            cin >> x;
            LEXER->Write(eq);
            TOKENS = LEXER->Build();
            TOKENS = POSTFIX->Run(TOKENS);     // Builded the postfix notation.
            initialise();
            if(x=="bisection"){
                bisection_init();
            }
            else{
                falsi_init();
            }
        }
        
        void bisection_init(){
            for(int i=0; i<20; i++){
                cout << "\nIteration " << i+1 << ": "<< endl;
                Bisection();
            }
        }
        void falsi_init(){
            for(int i=0; i<5; i++){
                cout << "\nIteration " << i+1 << ": "<< endl;
                Falsi();
            }
        }
        void demo(){
            float n;
            cout << "Test Num: ";
            cin >> n;
            cout << EVALUATION->Run(TOKENS,n) << endl;
        }

};

int main(){
    Solver method;
    method.Start();
    string option;
    while(true){
        cout << "\nOPTION: ";
        cin >> option;
        if(option == "rerun"){
            method.Start();
        }
        else if(option == "test"){
            method.demo();
        }
        else if(option == "exit"){
            break;
        }
    }
    return 0;
}


/*

Strength: Technical Skills, Fast Learner, Leadership, Knowledge, Observing
Weakness: Short Temper, Critic
Opportunity: 
Threat: Ayush, Increasing competition, Social Media, Pranjali Vashisht

*/
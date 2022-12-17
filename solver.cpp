#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <stdlib.h>
using namespace std;


// Create Nodes
class Node{
    public:
        Node *north = NULL;
        Node *east = NULL;
        Node *south = NULL;
        Node *west = NULL;
        int Xpos=0,Ypos=0;
        int POS;

        Node(){}    // Dummy constructor
        Node(int p){    // Actual constructor
            POS = p;
        }
        // Gives the coordinate of the Node
        void give_cord(){
            cout << '[' << Xpos << ',' << Ypos << ']' << endl;
        }
        // Gives the index of the Node
        int give_pos(){   
            return POS;
        }
};



// Generate map layout
class Map{
    private:
        Node *visited;  // visited nodes 
        int SC = -1;    // stack counter

        // Construct map string
        void construct(string name){
            ifstream read_file(name, ios::in);  // Its similar to read_file.open("map.txt");
            char line;
            int X=0,Y=0;

            // Reads the map file and generates the map in string
            while(read_file.get(line)){
                if(line != ' ' && line !='\n'){
                    map_preview+=line;
                }
                if(line == 'A'){
                    START = new Node(size(map_preview)-1);
                    X++; 
                }
                else if(line == 'B'){
                    END = new Node(size(map_preview)-1);
                    X++; 
                }
                else if(line == '#' || line =='.'){
                    X++;
                }
                else if(line == '\n'){
                    Y++;
                    X=0;
                }
            }
            Xmax = X;
            Ymax = Y+1;
        }

        // Searches if the given position is visited
        int search(int val){
            for(int i=0; i<SC; i++){
                if(val == visited[i].give_pos()){
                    return i;
                };
            }
            return -1;
        }
        // Construct map object
        Node * generate(int n){
            if(map_preview[n] != '#'){
                int result = search(n);
                if(result != -1){
                    return &visited[result];
                }
                else{
                    Node *ptr = new Node(n);
                    SC++;
                    visited[SC] = *ptr;
                    ptr->north = generate(n-Xmax);
                    ptr->east = generate(n+1);
                    ptr->south = generate(n+Xmax);
                    ptr->west = generate(n-1);
                    return ptr;
                }
            }
            else{
                return NULL;
            }
        }

    public:
        // Map details
        Node *START;
        Node *END;
        string map_preview;
        int Xmax;
        int Ymax;

        // Constructor
        Map(string n){
            construct(n);  
            visited = new Node[Xmax*Ymax];
            START = generate(START->give_pos());
            delete visited;
        }

        // Displays the map
        void give_details(){    
            cout << '+';
            for(int i=0;i<(Xmax+2*Xmax);i++){
                cout << '-';
            }
            cout << '+' << endl;
            for(int i=0;i<Ymax;i++){
                cout <<'|';
                for(int j=0;j<Xmax;j++){
                    cout <<" "<<map_preview[(i*Xmax)+j]<<" ";
                }
                cout <<'|'<< endl;
            }
            cout << '+';
            for(int i=0;i<(Xmax+2*Xmax);i++){
                cout << '-';
            }
            cout << '+' << endl;
            
            cout << "START: ";
            cout << START->give_pos() << endl;
            cout << "END: ";
            cout << END->give_pos() << endl;        
            cout << "Dimentions: " << Xmax << "X" << Ymax << endl;
        }

        // displays the answer path
        void generate_ans(int ans[]){
            int pointer = 0;

            cout << '+';
            for(int i=0;i<(Xmax+2*Xmax);i++){
                cout << '-';
            }
            cout << '+' << endl;

            for(int i=0;i<Ymax;i++){    //rows
                cout <<'|';
                for(int j=0;j<Xmax;j++){    //columns
                    int curr_pos = (i*Xmax)+j;
                    if(curr_pos== ans[pointer]){
                        if(curr_pos == START->give_pos()){
                            cout << " "<<'A'<<" ";
                        }
                        else if(curr_pos == END->give_pos()){
                            cout<< ' '<<'B'<<' ';
                        }
                        else{
                            cout <<' '<<'>'<<' ';
                        }
                        pointer++;
                    }
                    else{
                        cout <<' '<<map_preview[curr_pos]<<' ';
                    }
                }
                cout <<'|'<< endl;
            }

            cout << '+';
            for(int i=0;i<(Xmax+2*Xmax);i++){
                cout << '-';
            }
            cout << '+' << endl;
        }   
};


// Traverses a map
class Traverse{
    private:  
        Map *MAP;       // Map holder
        int *visited;   // visited nodes 
        int SC = -1;    // stack counter
        bool found = false; // End checker
        queue <Node*> QUEUE;

        int search(Node *n){
            int val = n->give_pos();
            for(int i=0; i<SC; i++){
                if(val == visited[i]){
                    return 1;
                };
            }
            return 0;
        }

    public:
        // Constructor
        Traverse(string n){
            MAP = new Map(n);
            visited = new int[MAP->Xmax*MAP->Ymax];
            traverse3(MAP->START);
            //QUEUE.push(MAP->START);
            //traverse4();
            cout << endl;
        }

        bool traverse3(Node *n){
            //DFS
            SC++;
            visited[SC] = n->give_pos();
            if(n->give_pos() == MAP->END->give_pos()){
                return true;
            }
            if(n->north != NULL && traverse3(n->north)){
                return true;
            }
            if(n->east != NULL && traverse3(n->east)){
                return true;
            }
            if(n->south != NULL && traverse3(n->south)){
                return true;
            }
            if(n->west != NULL && traverse3(n->west)){
                return true;
            }
            SC--;
            return false;
        }

        void traverse4(){
            //BFS
            Node *curr = QUEUE.front();
            QUEUE.pop();
            SC++;
            visited[SC] = curr->give_pos();
            give_ans();
            //_sleep(200);
            //system("cls");
            //cout << curr->give_pos() << "=> ";
            if(curr->give_pos() == MAP->END->give_pos()){
                cout << "FOUND";
                return;
            }
            if(curr->north != NULL && search(curr->north) != 1){
                QUEUE.push(curr->north);
            }
            if(curr->east != NULL && search(curr->east) != 1){
                QUEUE.push(curr->east);
            }
            if(curr->south != NULL && search(curr->south) != 1){
                QUEUE.push(curr->south);
            }
            if(curr->west != NULL && search(curr->west) != 1){
                QUEUE.push(curr->west);
            }
            traverse4();
            
        }

        void show(){
            //shows visited nodes
            cout <<"total elements: "<<SC << endl;
            cout<<'[';
            for(int i=0;i<=SC;i++){
                cout << visited[i] << "->";
            }
            cout<<']';
            cout << endl;
        }

        void give_ans(){
            cout << endl;
            MAP->give_details();

            //sorting the answer array (insertion sort)
            for(int i=1;i<SC;i++){
                for(int j=0;j<i;j++){
                    if(visited[i]<visited[j]){
                        int temp = visited[i];
                        visited[i] = visited[j];
                        visited[j] = temp;
                    }
                }
            }  
            show();
            cout << endl << endl;
            MAP->generate_ans(visited);
        }
};


int main(){
    system("cls");
    Traverse PATH("map.txt");
    PATH.give_ans();
    return 0;
}


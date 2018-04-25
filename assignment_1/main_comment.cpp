#include<iostream>
#include<string>
#include<vector>
#include<queue>
#include<functional>
#include<stdio.h>
#include<sys/time.h>
#include<unistd.h>
#include<unordered_set>

using namespace std;
#define N 3

// puzzle structure and cmp function (for p.q)
struct puzzle{
    int dist=0;
    int gn=0;
    bool u=false,d=false,l=false,r=false;
    //string arrayS = "123456780";//trivial
    //string arrayS = "123456708";//very easy
    //string arrayS = "120453786";//easy
    //string arrayS = "012453786";//doable
    //string arrayS = "871602543";//oh boy
    string arrayS = "123456870";//impossible
    
};
struct compare_cost{
    bool operator() ( const puzzle& a, const  puzzle& b) const{
        return a.dist >= b.dist ;
    }
};
// three different method to calaulate distance
enum algorithm{uni_cost, misplace, manhattan} alg_choice;
// store the history record (all puzzle pop from queue)
unordered_set<string>history;

void dump(puzzle p){
    cout<<"current p= ";
    cout<<p.arrayS<<endl;
    cout << "gn =" <<p.gn << ",dist =" << p.dist<<endl<<endl;
}

// calculate the distance
int distance(puzzle p, algorithm alg){
    int dist = 0;
    if(alg==misplace){
        for(int i=0;i<N*N;i++){
            if(p.arrayS[i]-48!=0 && p.arrayS[i]-48!=(i+1))
                dist++;
        }
    }else if(alg==manhattan){
        for(int i=0;i<N*N;i++){
            if(p.arrayS[i]-48!=0 && p.arrayS[i]-48!=(i+1))
                dist += abs(((p.arrayS[i])-48-1)/N-i/N) + abs(((p.arrayS[i])-48-1)%N-i%N);
        }
    }else{
        //cout<<"distance():other method"<<endl;
    }
    return dist;
}

// for a given puzzle and a set of boolean value, return a puzzle after movement
puzzle move(puzzle p, bool up,bool down,bool left,bool right, algorithm alg){
    int i=0,j;
    int parent_gn = p.gn;
    puzzle output=p;
    for(i=0;i<N*N;i++){
        if(p.arrayS[i]=='0')
            break;
    }// i is the location of zero
    // the location of zero is [i/N,i%N]
    if(up)          j=(i/N-1)*N + i%N;//[i/N-1,i%N]
    else if(down)   j=(i/N+1)*N + i%N;//[i/N+1,i%N]
    else if(left)   j=i-1;//(i/N)*N + i%N + 1;//[i/N+1,i%N]
    else if(right)   j=i+1;//(i/N)*N + i%N - 1;//[i/N+1,i%N]
    else cout<<"move:something wrong"<<endl;
    swap(output.arrayS[i],output.arrayS[j]);
    output.dist=distance(output,alg);
    output.gn = (parent_gn+1);
    output.dist+=output.gn;
    return output;
}

// compare the p with history record, to see if it is exist in history
bool isRepeat(puzzle p){
    auto it = history.find(p.arrayS);
    if(it==history.end())
        return false;
    else
        return true;
}

// check is the current state is goal state
bool isGoal(puzzle p){
    if(p.arrayS!="123456780")
        return false;
    else
        return true;
}

// for a geven puzzle, the location of zero decodes where it can move
// case1: corner(4 corners), 2 directions
// case2: edge (4 edges), 3 directions
// case3: the rest, 4 directions
void moveCount(puzzle &p){
    int i=0;
    for(i=0;i<N*N;i++){
        if(p.arrayS[i]=='0')
            break;
    }
    p.r=false;p.l=false;p.u=false;p.d=false;
    
    if(i==0) {p.r=true; p.d=true;}                            // left top point
    else if(i==N-1) {p.l=true; p.d=true;}                     // right top point
    else if(i==N*(N-1)) {p.u=true; p.r=true;}                 // left bot point
    else if(i==N*N-1) {p.u=true; p.l=true;}                   //right bot point
    else if(i>=1 && i<=N-2) {p.l=true; p.d=true; p.r=true;}   // up edge
    else if(i%N == 0) {p.u=true; p.d=true; p.r=true;}         // left edge
    else if(i>=N*(N-1) && i<=N*N-1) {p.l=true; p.u=true; p.r=true;} //down edge
    else if(i%N==N-1) {p.l=true; p.d=true; p.u=true;}         // right edgw
    else {p.l=true; p.d=true; p.r=true; p.u=true;}            // center point
}

int main(void)
{
    int input;
    int alg=0;
    bool state;
    puzzle p_init;
    puzzle p_current;
    string customize_input="";
    std::priority_queue<puzzle,vector<puzzle>,compare_cost> q;
    
#if 1
    // for user input, decide puzzle and decision algorithm we are going to use
    cout << "Welcome to Bertie Woosters 8-puzzle solver."<<endl;
    do{
        cout << "Type '1' to use a default puzzle, or '2' to enter your own puzzle."<<endl;
        cin >> input;
    }while(input != 1 && input!=2);
    
    if(input==2){
        do{
            customize_input="";
            cout << "Enter your puzzle in a single line, use a zero to represent the blank"<<endl;
            cin >> customize_input;
        }while(customize_input.size()!=N*N);
        
    }else{
        // default array
    }
    do{
        cout<<"Enter your choice of algorithm"<<endl;
        cout<<"0. Uniform Cost Search"<<endl<<"1. A* with the Misplaced Tile heuristic."<<endl<<"2. A* with the Manhattan distance heuristic."<<endl;
        cin >> alg;
    }while(alg!=0 && alg!=1 &&alg!=2);
#endif
    // use input to decide which distance function
    if(alg==0) alg_choice=uni_cost;
    if(alg==1) alg_choice=misplace;
    if(alg==2) alg_choice=manhattan;
    if(customize_input.size()==N*N)
        p_init.arrayS = customize_input;
    
    cout<<"the input is:"<<p_init.arrayS;
    cout<<"method="<<alg<<endl;
    p_init.dist = distance(p_init,alg_choice);
    cout<<"the distance is:"<<distance(p_init,alg_choice)<<endl;
    state = isGoal(p_init);
    if(!state)
        q.push(p_init);
    else
        cout<<"GOAL!!"<<endl;
    
    // for candicate puzzle
    puzzle pup,pdown,pleft,pright;
    
    int total_count = 0;
    int level = 0;
    int max_q_size=0;
    
    struct  timeval start;
    struct  timeval end;
    unsigned  long diff;
    gettimeofday(&start,NULL);
    
    // before while, we already hv a initial state and it is not goal state
    while(!state){
        level++;
        //every iterator, check if we run out of state, we fail in that case
        if(q.empty()){
            cout<<"run out of state, it impossible!!!!"<<endl;
            cout<<"max q_size = "<<max_q_size<<endl;
            gettimeofday(&end,NULL);
            diff = 1000000 * (end.tv_sec-start.tv_sec)+ end.tv_usec-start.tv_usec;
            //printf("the difference is %ld\n",diff);
            cout << (double)diff/1000000 <<"sec"<<endl;
            return 0;
        }
        // pop the top of p.q, check its state, and expand it
        puzzle p_current = q.top();
        //============
        cout<<"total_count = "<<++total_count<<endl;
        dump(p_current);
        //============
        state = isGoal(p_current);
        q.pop();
        history.insert(p_current.arrayS);
        // for a given state, check which direction it can move
        // the possible move is indicated as 4 boolean value
        moveCount(p_current);
        // depends on boolean, generate the state after movement
        if(p_current.u){
            pup = move(p_current,1,0,0,0,alg_choice);
            if(!isRepeat(pup)) {q.push(pup);history.insert(pup.arrayS);}
        }
        if(p_current.d){
            pdown = move(p_current,0,1,0,0,alg_choice);
            if(!isRepeat(pdown)) {q.push(pdown);history.insert(pdown.arrayS);}
        }
        if(p_current.l){
            pleft = move(p_current,0,0,1,0,alg_choice);
            if(!isRepeat(pleft)) {q.push(pleft);history.insert(pleft.arrayS);}
        }
        if(p_current.r){
            pright = move(p_current,0,0,0,1,alg_choice);
            if(!isRepeat(pright)) {q.push(pright);history.insert(pright.arrayS);}
        }
        
        if(q.size()>=max_q_size)
            max_q_size = q.size();
    }
    
    if(state)
        cout<<"we made it!! max q_size = "<<max_q_size<<endl;
    gettimeofday(&end,NULL);
    diff = 1000000 * (end.tv_sec-start.tv_sec)+ end.tv_usec-start.tv_usec;
    cout << (double)diff/1000000 <<" sec"<<endl;
    return 0;
}


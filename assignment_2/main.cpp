#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstring>
#include<queue>
#include"stdlib.h"
#include"stdio.h"
#include"math.h"
#include <numeric>
#include<sys/time.h>
#include<map>

#define ROW 1000
#define COL 10
#define DELIM " \t\r\n"

using namespace std;

vector<vector<float> > table;

float validation_alpha(vector<int> &feature, float current_best){
    //int i=0;
    float ret=0;
    float correct=0;
    float wrong=0;
    int acc=0;
    
    for(int i=0;i<table.size();i++){
        //i is the validation data
        float dist_1_output=100000;
        float dist_2_output=100000;
        for(int j=0;j<table.size();j++){
            //j is the data used for calculating dist
            if(j==i){
                acc++;
                continue;
            }
            // go through feature
            float dist_1=0;
            float dist_2=0;
            for(int k=0;k<feature.size();k++){
                int target = feature[k];
                //cout<<target<<endl;
                if(table[j][0]==1){
                    dist_1+=(table[j][target]-table[i][target])*(table[j][target]-table[i][target]);
                }else if(table[j][0]==2){
                    dist_2+=(table[j][target]-table[i][target])*(table[j][target]-table[i][target]);
                }else{
                    cout<<"illegal label1"<<endl;
                }
            }
            dist_1 = sqrt(dist_1);
            dist_2 = sqrt(dist_2);
            if(table[j][0]==1 && dist_1<=dist_1_output){
                dist_1_output=dist_1;
            }else if(table[j][0]==2 && dist_2<=dist_2_output){
                dist_2_output=dist_2;
            }else{
                //cout<<"illegal label2"<<endl;
            }
            
        }// j loop
        // now we hv distance for both lable
        if(dist_1_output==dist_2_output){
            cout<<"equal"<<endl;
            correct++;
        }else if(dist_1_output > dist_2_output){
            // we think it is 2
            if(table[i][0]==2)
                correct++;
            else
                wrong++;
        }else if(dist_1_output < dist_2_output){
            // we think it is 1
            if(table[i][0]==1)
                correct++;
            else
                wrong++;
        }
        if(wrong/table.size() > (1-current_best)){
            return 0.000000001;
        }
        //ret+=correct/table.size();
    }// i loop
    //cout<<"testing feature:";
    //for(int m=0;m<feature.size();m++)
    //    cout<<feature[m];
    //cout<<"acc="<<acc<<endl;
    //cout<<"we got correctness "<<correct<<" /"<<table.size()<<"="<<(correct/table.size())<<endl;
    cout<<"Correctness "<<(correct/table.size())<<" ";
    //cout<<"we got wrong "<<wrong<<" /"<<table.size()<<"="<<(wrong/table.size())<<endl;
    //cout<<"aaaaaa"<<endl;
    float out =correct/table.size();
    return out;
}

float validation(vector<int> &feature){
    //int i=0;
    float ret=0;
    float correct=0;
    float wrong=0;
    int acc=0;
    
    for(int i=0;i<table.size();i++){
        //i is the validation data
        float dist_1_output=100000;
        float dist_2_output=100000;
        for(int j=0;j<table.size();j++){
            //j is the data used for calculating dist
            if(j==i){
                acc++;
                continue;
            }
            // go through feature
            float dist_1=0;
            float dist_2=0;
            for(int k=0;k<feature.size();k++){
                int target = feature[k];
                //cout<<target<<endl;
                if(table[j][0]==1){
                    dist_1+=(table[j][target]-table[i][target])*(table[j][target]-table[i][target]);
                }else if(table[j][0]==2){
                    dist_2+=(table[j][target]-table[i][target])*(table[j][target]-table[i][target]);
                }else{
                    cout<<"illegal label1"<<endl;
                }
            }
            dist_1 = sqrt(dist_1);
            dist_2 = sqrt(dist_2);
            if(table[j][0]==1 && dist_1<=dist_1_output){
                dist_1_output=dist_1;
            }else if(table[j][0]==2 && dist_2<=dist_2_output){
                dist_2_output=dist_2;
            }else{
                //cout<<"illegal label2"<<endl;
            }
            
        }// j loop
        // now we hv distance for both lable
        if(dist_1_output==dist_2_output){
            cout<<"equal"<<endl;
            correct++;
        }else if(dist_1_output > dist_2_output){
            // we think it is 2
            if(table[i][0]==2)
                correct++;
            else
                wrong++;
        }else if(dist_1_output < dist_2_output){
            // we think it is 1
            if(table[i][0]==1)
                correct++;
            else
                wrong++;
        }
        //ret+=correct/table.size();
    }// i loop
    //cout<<"testing feature:";
    //for(int m=0;m<feature.size();m++)
    //    cout<<feature[m];
    //cout<<"acc="<<acc<<endl;
    //cout<<"we got correctness "<<correct<<" /"<<table.size()<<"="<<(correct/table.size())<<endl;
    //cout<<"Correctness "<<(correct/table.size())<<"; ";
    //cout<<"we got wrong "<<wrong<<" /"<<table.size()<<"="<<(wrong/table.size())<<endl;
    //cout<<"aaaaaa"<<endl;
    float out =correct/table.size();
    return out;
}

void Third(){
    //we hv initial recored: all zero
    vector <float> accuracy_level(table[1].size()-1,0); // 10個
    
    vector<vector<int> > feature_table; // 10*10個
    std::vector<int> candidate(table[1].size()-1);// 10, 1,2,3...,9,10
    std::iota(std::begin(candidate), std::end(candidate), 1);
    vector<int>tmp;
    vector<int>accuracy_candicate;
    
    float accuracy = 0;
    int i=0;
    for(int j=0;j<candidate.size();j++){
        cout<<candidate[j]<<" ";
    }
    cout<<endl;
    /*vector<int> f;
     f.push_back(1);
     validation(f);*/
#if 1
    while(candidate.size()>0){
        //while(1){
        // should pick i+1 nodes
        tmp.clear();
        if(i>=1){
            tmp.clear();
            if(feature_table.size()>0)
                tmp.assign(feature_table[i-1].begin(),feature_table[i-1].end());
        }
        for(int s=0;s<candidate.size();s++){
            cout<<"push "<<candidate[s]<<endl;
            tmp.push_back(candidate[s]);
            //cout<<"-1!";
            float tmp_acc = validation_alpha(tmp,accuracy_level[i]);
            //cout<<"0!";
            if(tmp_acc > accuracy_level[i]){
                //cout<<"1!";
                accuracy_level[i] = tmp_acc;
                //cout<<"2!";
                //if(feature_table[i].size()==i+1)
                //    feature_table.pop_back();
                //cout<<"3!";
                //feature_table.push_back(tmp);
                accuracy_candicate.assign(tmp.begin(),tmp.end());
            }
            tmp.pop_back();
            //cout<<"4!";
            //tmp.clear();
        }
        cout<<"layer["<<i+1<<"] end: winner rate="<<accuracy_level[i]<<", feature: ";
        for(int m=0;m<accuracy_candicate.size();m++)
            cout<<accuracy_candicate[m]<<" ";
        cout<<endl;
        feature_table.push_back(accuracy_candicate);
        // 最新加進來的在tmp的end()-1
        //find(candidate.begin(),candidate.end(),accuracy_candicate.back());
        candidate.erase(find(candidate.begin(),candidate.end(),accuracy_candicate.back()));
        i++;
    }
    float max=0;
    int index;
    for(int i=0;i<accuracy_level.size();i++){
        if(accuracy_level[i]>=max){
            max=accuracy_level[i];
            index=i;
        }
    }
    cout<<endl<<endl<<endl<<"Optimal Rate="<<accuracy_level[index]<<", feature=";
    for(int i=0;i<feature_table[index].size();i++)
        cout<<feature_table[index][i]<<" ";
    cout<<endl;
#endif
}

void forward(){
    //we hv initial recored: all zero
    vector <float> accuracy_level(table[1].size()-1,0); // 10個
    
    vector<vector<int> > feature_table; // 10*10個
    std::vector<int> candidate(table[1].size()-1);// 10, 1,2,3...,9,10
    std::iota(std::begin(candidate), std::end(candidate), 1);
    vector<int>tmp;
    vector<int>accuracy_candicate;
    
    float accuracy = 0;
    int i=0;
    for(int j=0;j<candidate.size();j++){
        cout<<candidate[j]<<" ";
    }
    cout<<endl;
    /*vector<int> f;
    f.push_back(1);
    validation(f);*/
#if 1
    while(candidate.size()>0){
    //while(1){
        // should pick i+1 nodes
        tmp.clear();
        if(i>=1){
            tmp.clear();
            if(feature_table.size()>0)
                tmp.assign(feature_table[i-1].begin(),feature_table[i-1].end());
        }
        for(int s=0;s<candidate.size();s++){
            cout<<"test "<<candidate[s]<<" ";
            tmp.push_back(candidate[s]);
            //cout<<"-1!";
            float tmp_acc = validation(tmp);
            //cout<<"0!";
            if(tmp_acc > accuracy_level[i]){
                //cout<<"1!";
                accuracy_level[i] = tmp_acc;
                //cout<<"2!";
                //if(feature_table[i].size()==i+1)
                //    feature_table.pop_back();
                //cout<<"3!";
                //feature_table.push_back(tmp);
                accuracy_candicate.assign(tmp.begin(),tmp.end());
            }
            tmp.pop_back();
            //cout<<"4!";
            //tmp.clear();
        }
        cout<<endl<<endl<<"layer["<<i+1<<"] end: winner rate="<<accuracy_level[i]<<", feature: ";
        for(int m=0;m<accuracy_candicate.size();m++)
            cout<<accuracy_candicate[m]<<" ";
        cout<<endl;
        feature_table.push_back(accuracy_candicate);
        // 最新加進來的在tmp的end()-1
        //find(candidate.begin(),candidate.end(),accuracy_candicate.back());
        candidate.erase(find(candidate.begin(),candidate.end(),accuracy_candicate.back()));
        i++;
    }
    float max=0;
    int index;
    for(int i=0;i<accuracy_level.size();i++){
        if(accuracy_level[i]>=max){
            max=accuracy_level[i];
            index=i;
        }
    }
    cout<<endl<<endl<<endl<<"Optimal Rate="<<accuracy_level[index]<<", feature=";
    for(int i=0;i<feature_table[index].size();i++)
        cout<<feature_table[index][i]<<" ";
    cout<<endl;
#endif
}

vector<int> implementCandicate(vector<int>input,int size){
    std::vector<int> candidate(size);// 10, 1,2,3...,9,10
    std::iota(std::begin(candidate), std::end(candidate), 1);
    
    for(int i=0;i<input.size();i++){
        candidate.erase(find(candidate.begin(),candidate.end(),input[i]));
    }
    return candidate;
}
void backward(){
    //we hv initial recored: all zero
    vector <float> accuracy_level(table[1].size()-1,0); // 10個
    
    vector<vector<int> > feature_table; // 10*10個
    std::vector<int> candidate(table[1].size()-1);// 10, 1,2,3...,9,10
    std::iota(std::begin(candidate), std::end(candidate), 1);
    vector<int>tmp;
    vector<int>accuracy_candicate;
    
    float accuracy = 0;
    int i=0;
    for(int j=0;j<candidate.size();j++){
        cout<<candidate[j]<<" ";
    }
    cout<<endl;
    /*vector<int> f;
     f.push_back(1);
     validation(f);*/
#if 1
    while(candidate.size()>1){
        cout<<"we hv "<<candidate.size()<<" candicate"<<endl;
        //while(1){
        // should pick i+1 nodes
        tmp.clear();
        if(i>=1){
            tmp.clear();
            if(feature_table.size()>0)
                tmp.assign(feature_table[i-1].begin(),feature_table[i-1].end());
        }
        for(int s=0;s<candidate.size();s++){
            cout<<"push "<<candidate[s]<<endl;
            tmp.push_back(candidate[s]);
            vector<int> imp = implementCandicate(tmp,table[1].size()-1);
            //cout<<"-1!";
            float tmp_acc = validation(imp);
            //cout<<"0!";
            if(tmp_acc > accuracy_level[i]){
                //cout<<"1!";
                accuracy_level[i] = tmp_acc;
                //cout<<"2!";
                //if(feature_table[i].size()==i+1)
                //    feature_table.pop_back();
                //cout<<"3!";
                //feature_table.push_back(tmp);
                accuracy_candicate.assign(tmp.begin(),tmp.end());
            }
            tmp.pop_back();
            //cout<<"4!";
            //tmp.clear();
        }
        cout<<"layer["<<i+1<<"] end: winner rate="<<accuracy_level[i]<<", feature: ";
        vector<int> imp2 = implementCandicate(accuracy_candicate,table[1].size()-1);
        for(int m=0;m<imp2.size();m++)
            cout<<imp2[m]<<" ";
        cout<<endl;
        feature_table.push_back(accuracy_candicate);
        // 最新加進來的在tmp的end()-1
        //find(candidate.begin(),candidate.end(),accuracy_candicate.back());
        candidate.erase(find(candidate.begin(),candidate.end(),accuracy_candicate.back()));
        i++;
    }
    float max=0;
    int index;
    for(int i=0;i<accuracy_level.size();i++){
        if(accuracy_level[i]>=max){
            max=accuracy_level[i];
            index=i;
        }
    }
    cout<<endl<<endl<<endl<<"Optimal Rate="<<accuracy_level[index]<<", feature=";
    for(int i=0;i<feature_table[index].size();i++)
        cout<<feature_table[index][i]<<" ";
    cout<<endl;
#endif
}

bool cmp(const pair<int,float> &p1,const pair<int,float> &p2)//要用常数，不然编译错误
{
    return p1.second<p2.second;
}

void greedy(){
    //we hv initial recored: all zero
    vector <float> accuracy_level(table[1].size()-1,0); // 10個
    
    vector<vector<int> > feature_table; // 10*10個
    std::vector<int> candidate(table[1].size()-1);// 10, 1,2,3...,9,10
    std::iota(std::begin(candidate), std::end(candidate), 1);
    vector<int>tmp;
    vector<int>accuracy_candicate;
    vector<pair<int,float> >greedy_v;
    map<int, float> greedy_map;
    float accuracy = 0;

    for(int j=0;j<candidate.size();j++){
        cout<<candidate[j]<<" ";
    }
    cout<<endl;

    tmp.clear();

    for(int s=0;s<candidate.size();s++){
        cout<<"push "<<candidate[s]<<endl;
        tmp.push_back(candidate[s]);
        float tmp_acc = validation(tmp);
        greedy_map.insert(make_pair(candidate[s],tmp_acc));
        tmp.pop_back();
    }
    
    for(auto it=greedy_map.begin();it!=greedy_map.end();it++){
        cout<<"("<<it->first<<", "<<it->second<<")";
        greedy_v.push_back(make_pair(it->first,it->second));
    }
    cout<<endl;
    sort(greedy_v.begin(),greedy_v.end(),cmp);
    for(auto iter = greedy_v.begin(); iter != greedy_v.end(); iter++)
        cout<<"("<<iter->first<<", "<<iter->second<<")";
    cout<<endl;
    
    tmp.clear();
    tmp.push_back(greedy_v.rbegin()->first);
    feature_table.push_back(tmp);
    accuracy_level[0] = greedy_v.rbegin()->second;
    greedy_v.pop_back();
    cout<<"layer["<<0<<"] end: winner rate="<<accuracy_level[0]<<", feature: ";
    for(int m=0;m<feature_table[0].size();m++)
        cout<<feature_table[0][m]<<" ";
    cout<<endl;
    
    int count = greedy_v.size();
    for(int i=0;i<count;i++){
        tmp.push_back(greedy_v.rbegin()->first);
        float tmp_acc = validation(tmp);
        feature_table.push_back(tmp);
        accuracy_level[i+1] = tmp_acc;
        greedy_v.pop_back();
        cout<<"layer["<<i+1<<"] end: winner rate="<<accuracy_level[i+1]<<", feature: ";
        for(int m=0;m<feature_table[i+1].size();m++)
            cout<<feature_table[i+1][m]<<" ";
        cout<<endl;
    }
    
    float max=0;
    int index;
    for(int i=0;i<accuracy_level.size();i++){
        if(accuracy_level[i]>=max){
            max=accuracy_level[i];
            index=i;
        }
    }
    cout<<endl<<endl<<endl<<"Optimal Rate="<<accuracy_level[index]<<", feature=";
    for(int i=0;i<feature_table[index].size();i++)
        cout<<feature_table[index][i]<<" ";
    cout<<endl;
    
    
}

int main(){
    
    float input;
    FILE *fp = fopen("CS205_SMALLtestdata__22.txt","r");
    vector<float> v;
    vector<float> min;
    vector<float> max;
    vector<float> diff;
    vector<int> f;
    char buf[BUFSIZ];
    char *p;
    
    if(fp == NULL){
        printf("fopen failed\n");
        goto ERROR;
    }
    while(fgets(buf,BUFSIZ,fp) != NULL){
        v.clear();
        for(p = strtok(buf,DELIM); p != NULL; p = strtok(NULL,DELIM)){
            sscanf(p,"%f",&input);
            v.push_back(input);
            cout<<input<<" ";
        }
        table.push_back(v);
        cout<<endl;
    }
    cout<<"table:"<<table.size()<<","<<table[1].size()<<endl;
    
    cout<<"normalizing1"<<endl;
    for(int i=0;i<table[1].size();i++){
        min.push_back(100000);
        max.push_back(0);
    }
    cout<<"normalizing2"<<endl;
    for(int i=0;i<table.size();i++){
        for(int j=0;j<table[1].size();j++){
            if(table[i][j]<=min[j])
                min[j]=table[i][j];
            if(table[i][j]>=max[j])
                max[j]=table[i][j];
        }
    }
    cout<<"normalizing3"<<endl;
    for(int i=0;i<table.size();i++){
        cout<<table[i][0]<<" ";
        for(int j=1;j<table[1].size();j++){
            table[i][j] = (table[i][j]-min[j])/(max[j]-min[j]);
            cout<<table[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<"table:"<<table.size()<<","<<table[1].size()<<endl;
    //vadility(1,1);
    //f.push_back(1);
    //f.push_back(4);
    //f.push_back(6);
    //f.push_back(3);
    //validation(f);
    
    
    struct  timeval start;
    struct  timeval end;
    unsigned  long diff_t;
    gettimeofday(&start,NULL);
    
    //=================== search algorithm
    forward();
    //backward();
    //Third();
    //greedy();
    //=================== search algorithm
    gettimeofday(&end,NULL);
    diff_t = 1000000 * (end.tv_sec-start.tv_sec)+ end.tv_usec-start.tv_usec;
    cout << (double)diff_t/1000000 <<" sec"<<endl;
    fclose(fp);
    return 0;
ERROR:
    return -1;
    
}



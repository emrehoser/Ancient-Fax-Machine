#include <iostream>
#include <fstream>
#include <vector>


using  namespace std;
int prime = 17;
long long int modulo = 1000000007;
string baseStr;
vector<long long int> dymarr;
int dicNum;
vector<string> dicWords;
vector<long long int> hashWords;
vector<long long int> hashSubStr;
long powerofprime[1001];

void findpower(){
    powerofprime[0]=1;
    for(int i=1;i<1001;i++){
        powerofprime[i]=(powerofprime[i-1]*prime)%modulo;
    }
}

long long int hashing(string str){
    long long int hash= 0;

    for(int i = 0;i < str.length();i++ ){

        hash += ((str[i]-96)*powerofprime[str.length()-(i+1)])%modulo;
    }
    hash = hash%modulo;
    return hash;
}


    long long int func(int index){

        long long int  result =0;
        if(index ==baseStr.length() ){
            result =1;
        }
        if(dymarr[index]==-1){
            for(int i = 0;i<dicWords.size();i++){
                long long int wordhash = hashWords[i];
                long long int ab=0;
                if(index+dicWords[i].length()>baseStr.length()) continue;
                if(index ==0){
                    ab = hashSubStr[index+dicWords[i].length()-1];
                    ab=ab%modulo;
                }
                else{
                    if(hashSubStr[index+dicWords[i].length()-1]<hashSubStr[index-1]){
                        long long int xyz = hashSubStr[index+dicWords[i].length()-1];
                        xyz+=modulo;
                        ab = xyz-(hashSubStr[index-1]*powerofprime[dicWords[i].length()])%modulo;

                        ab+=modulo;
                        ab =ab%modulo;

                    }
                    else{
                        ab = hashSubStr[index+dicWords[i].length()-1]-(hashSubStr[index-1]*powerofprime[dicWords[i].length()])%modulo;
                        ab+=modulo;
                        ab = ab % modulo;
                    }
                    while(ab<0) ab+=modulo;

                }
                if(wordhash == ab){
                    string compStr  = baseStr.substr(index,dicWords[i].length());
                    if(compStr.compare(dicWords[i])==0){

                        result += func(index+compStr.length());
                        result = result %  modulo;
                    }
                }
            }
            result = result%modulo;
            dymarr[index] = result;
        }
        return dymarr[index];
    }


int main(int argc, char* argv[]) {
    findpower();


    ofstream write(argv[2]);
    ifstream read;
    read.open(argv[1]);
    read >> baseStr;
    read >> dicNum;
    dymarr.resize(baseStr.length()+1,-1);


    for(int i = 0;i<dicNum;i++){
        string temp;
        read >> temp;
        dicWords.push_back(temp);
        hashWords.push_back(hashing(temp));
    }

    for(int i = 0; i< baseStr.length();i++ ){
        hashSubStr.push_back(hashing(baseStr.substr(0,i+1)));
    }
    write<<func(0);



    return 0;
}
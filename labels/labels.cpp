#include<iostream>
#include"labels.hpp"
#include<string>
#include<unordered_map>

using namespace std;


namespace labels{
    
    std::unordered_map<std::string,int> symbol_table;

    void setup(){
        std::cout<<"abc"<<endl;
        symbol_table["R0"]=0;
        symbol_table["R1"]=1;
        symbol_table["R2"]=2;
        symbol_table["R3"]=3;
        symbol_table["R4"]=4;
        symbol_table["R5"]=5;
        symbol_table["R6"]=6;
        symbol_table["R7"]=7;
        symbol_table["R8"]=8;
        symbol_table["R9"]=9;
        symbol_table["R10"]=10;
        symbol_table["R11"]=11;
        symbol_table["R12"]=12;
        symbol_table["R13"]=13;
        symbol_table["R14"]=14;
        symbol_table["R15"]=15;
        symbol_table["SCREEN"]=16384;
        symbol_table["KBD"]=24576;
        symbol_table["SP"]=0;
        symbol_table["LCL"]=1;
        symbol_table["ARG"]=2;
        symbol_table["THIS"]=3;
        symbol_table["THAT"]=4;
    }

    void first_pass(){
       // cout<<"first_pass runs"<<endl;
        ifstream fin;
        int inst_no=0;
        fin.open("/Users/utsavjn/Desktop/cpp/assembler_project/format/formatted.txt");
        std::string l;
        int label_commands_till_now=0;
        while(fin){
            getline(fin,l);
           // cout<<l<<endl;
            std::string symbol;
            if(l[0]=='('){
                symbol=l.substr(1,l.size()-2);
                symbol_table[symbol]=inst_no-label_commands_till_now;
                label_commands_till_now++;
            }
            inst_no++;   
        }
        fin.close();
    }


    void pre_executor(){
        first_pass();
        ifstream fin;
        ofstream fout;
        int n=16;
        fin.open("/Users/utsavjn/Desktop/cpp/assembler_project/format/formatted.txt");
        fout.open("/Users/utsavjn/Desktop/cpp/assembler_project/labels/only_instructions.txt");
        string l;
        //cout<<fin.eof()<<endl;
        while(fin){
            getline(fin,l);
            //cout<<"in fin loop"<<endl;
            if(l[0]=='('){
                continue;
            }

            else if(l[0]=='@'){
                string a=l.substr(1);
                if(a[0]>='0' && a[0]<='9'){
                    //cout<<l<<endl;
                    fout<<l<<endl;
                    continue;
                }
                else{
                    if(symbol_table.count(a)==0){
                        symbol_table[a]=n;
                        int x=n;
                        n++;
                        string num="";
                        while(x){
                            int a=x%10;
                            x/=10;
                            num+=(a+'0');
                        }
                        reverse(num.begin(),num.end());
                        fout<<'@'+num<<endl;
                    }
                    else{
                        int x=symbol_table[a];
                        string num="";
                        while(x){
                            int a=x%10;
                            x/=10;
                            num+=(a+'0');
                        }
                        reverse(num.begin(),num.end());
                        fout<<'@'+num<<endl;
                    }
                }
            }
            else{
                fout<<l<<endl;
            }
        }
        fin.close();
        fout.close();
        
    }
    
}
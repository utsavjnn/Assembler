#include<iostream>
#include<string>
#include<unordered_map>
#include<fstream>

using namespace std;
namespace instruction{

    std::unordered_map<std::string,std::string> dest;
    std::unordered_map<std::string,std::string> comp;
    std::unordered_map<std::string,std::string> jump;

    void set_vals(){
        dest["null"]="000";
        dest["M"]="001";
        dest["D"]="010";
        dest["MD"]="011";
        dest["A"]="100";
        dest["AM"]="101";
        dest["AD"]="110";
        dest["AMD"]="111";

        jump["null"]="000";
        jump["JGT"]="001";
        jump["JEQ"]="010";
        jump["JGE"]="011";
        jump["JLT"]="100";
        jump["JNE"]="101";
        jump["JLE"]="110";
        jump["JMP"]="111";

        comp["0"]="0101010";
        comp["1"]="0111111";
        comp["-1"]="0111010";
        comp["D"]="0001100";
        comp["A"]="0110000";
        comp["!D"]="0001101";
        comp["!A"]="0110001";
        comp["-D"]="0001111";
        comp["-A"]="0110011";
        comp["D+1"]="0011111";
        comp["A+1"]="0110111";
        comp["D-1"]="0001110";
        comp["A-1"]="0110010";
        comp["D+A"]="0000010";
        comp["D-A"]="0010011";
        comp["A-D"]="0000111";
        comp["D&A"]="0000000";
        comp["D|A"]="0010101";
        comp["M"]="1110000";
        comp["!M"]="1110001";
        comp["-M"]="1110011";
        comp["M+1"]="1110111";
        comp["M-1"]="1110010";
        comp["D+M"]="1000010";
        comp["D-M"]="1010011";
        comp["M-D"]="1000111";
        comp["D&M"]="1000000";
        comp["D|M"]="1010101";

    }

            
    std::string to_binary(std::string num){
        int a=0;
        for(int i=0;i<num.length();i++){
            a*=10;
            a+=(num[i]-'0');
        }
        std::string x="";
        while(a){
            x+=((a%2)+'0');
            a/=2;
        }
        for(int i=x.length();i<15;i++){
            x+='0';
        }

        reverse(x.begin(),x.end());

        return x;
    }

    std::string a_command(std::string in){
        std::string ans="0";
        ans+=instruction::to_binary(in);
        return ans;
    }

    std::string c_command(std::string in){
        std::string d="null";
        std::string jm="null";

        //scan for '=',at posn i
        std::string inst=in;
        int i=0;
        while(inst[i]!='=' && i<inst.size()){
            i++;
        }
        if(i!=0 && i!=inst.size()){
            d=inst.substr(0,i);
            inst=inst.substr(i+1);
        }

        //scanning for ';'
        int j=0;
        while(inst[j]!=';' && j<inst.size()){
            j++;
        }
        if(j!=0 && j!=inst.size()){
        	jm=inst.substr(j+1);
        	inst=inst.substr(0,j);
        }

        std::string c=inst;
        
        std::string bin_c="111"+comp[c]+dest[d]+jump[jm];
        return bin_c;
        
    }

    std::string executor(std::string in){

        //std::cout<<dest["M"]<<std::endl;
        if(in[0]=='@'){
            return a_command(in.substr(1));
        }
        else{
            return c_command(in);
        }
    }

    void inst_to_binary(){
        std::ifstream fin;
        std::ofstream fout;
        fin.open("/Users/utsavjn/Desktop/cpp/assembler_project/labels/only_instructions.txt");
        fout.open("/Users/utsavjn/Desktop/cpp/assembler_project/binary.txt");
        std::string l;
        while(fin){
            getline(fin,l);
            if(l.size()==0)
                break;
            fout<<executor(l)<<endl;
        }
    }
}


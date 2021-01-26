#include<iostream>
#include<string>
#include<fstream>
#include"format.hpp"

using namespace std;
void format::formatter(){
    ifstream fin;
	ofstream fout;
	fin.open("/Users/utsavjn/Desktop/cpp/assembler_project/testfile.txt");
    fout.open("/Users/utsavjn/Desktop/cpp/assembler_project/format/formatted.txt");

    if(!fin){
		cout<<"file not there"<<endl;
	}
    string l;
	while(fin){
		//cout<<"x"<<endl;
		getline(fin,l);
		if(!fin)
			break;
		if(l.size()==0){
			continue;
		}
		string x;//after parsing a instruction

		//remove the whitespaces and comments
		for(int i=0;i<l.length();i++){

			if(l[i]=='/'){
				break;
			}
			if(l[i]!=' '){
				x+=l[i];
			}
		}
		if(x.size()==0)
			continue;
        fout<<x<<endl;
    }
    fin.close();
    fout.close();

}
#include<iostream>
#include<fstream>

#include<instruction.hpp>
#include<format.hpp>
#include<labels.hpp>

using namespace std;

int main(){

	//remove all whitespaces and comments-->formatted.txt
	format::formatter();

	//handle labels and put then into symbol table and replace them with their numeric values-->only_instructions.txt
	labels::setup();
	labels::pre_executor();

	//lets convert instructions to binary --> binary.txt
	instruction::set_vals();
	instruction::inst_to_binary();
	
}
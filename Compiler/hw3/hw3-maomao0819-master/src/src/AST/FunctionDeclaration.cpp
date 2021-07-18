#include <iostream>
#include "AST/FunctionDeclaration.hpp"
#include "visitor/visitor.hpp"
#include <string.h>
using namespace std;
FunctionDeclarationNode::FunctionDeclarationNode(uint32_t line, uint32_t col): ASTNodeBase(line,col){
}

void FunctionDeclarationNode::printNode(){
	// ouput format
	for(int i = 0; i < level; i++)
 		cout << "  ";
   	
   	cout << "function declaration <line: " << location.line<< ", col: " << location.col << "> " << name << " " << returntype << " (";
   	
   	for (int i = 0; i < parameter.size(); i++)
	{
		string str2(parameter[i]);
		string str;
		for(int i = 0; i < str2.size(); i++)
		{
			if(str2[i] <= '9' && str2[i] >= '0')
			{
				str += to_string(str2[i + 4] - str2[i]);
				i = i + 4;
			}
			else
				str += str2[i];
		}
		cout << str;
		if(i < parameter.size() - 1)
			cout << ", ";
	}
   	cout << ")" << endl;
}

FunctionDeclarationNode::~FunctionDeclarationNode(){
	;
}

void FunctionDeclarationNode::accept(ASTNodeVisitorBase &v){
	v.visit(this);
	for (int i = 0; i < vd.size(); i++)
	{
		vd[i] -> level = this -> level + 1;
		vd[i] -> accept(v);
	}
	if(c != NULL)
	{
		c -> level = this -> level + 1;
		c -> accept(v);
	}
	
}

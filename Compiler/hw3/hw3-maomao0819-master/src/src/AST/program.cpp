#include <iostream>
#include "AST/program.hpp"
#include "visitor/visitor.hpp"

using namespace std;
ProgramNode::ProgramNode(uint32_t line, uint32_t col): ASTNodeBase(line,col){
}

void ProgramNode::printNode(){
	// ouput format
    	cout << "program" << " <line: " << location.line << ", col: " << location.col << "> " << name << " void" << endl;
}

ProgramNode::~ProgramNode(){
	;
}

void ProgramNode::accept(ASTNodeVisitorBase &v){
	v.visit(this);
	while(d != NULL)
		{
			d -> level = this -> level + 1;
			d -> accept(v);
			d = d -> next;		
		}
	for (int i = 0; i < vf.size(); i++)
	{
		vf[i] -> level = this -> level + 1;
		vf[i] -> accept(v);
	}
	if(c != NULL)
	{
		c -> level = this -> level + 1;
		c -> accept(v);
	}

}

#include <iostream>
#include "AST/VariableReference.hpp"
#include "visitor/visitor.hpp"

using namespace std;
VariableReferenceNode::VariableReferenceNode(uint32_t line, uint32_t col): ASTNodeBase(line,col){
}

void VariableReferenceNode::printNode(){
	// ouput format
	for(int i = 0; i < level; i++)
 	 	cout << "  ";
    	cout << "variable reference <line: " << location.line<<", col: "<< location.col << "> " << name << endl;
}

VariableReferenceNode::~VariableReferenceNode(){
	;
}

void VariableReferenceNode::accept(ASTNodeVisitorBase &v){
	v.visit(this);
	while(e != NULL)
	{	
		for(int i = 0; i < level; i++)
 	 		cout << "  ";
		cout << "[" << endl;
		e -> level = this -> level + 1;
		e -> accept(v);
		for(int i = 0; i < level; i++)
 	 		cout << "  ";
		cout << "]" << endl;
		e = e -> next;
	}
	if(cv != NULL)
	{
		cv -> level = this -> level;
		cv -> accept(v);
	}
}

#include <iostream>
#include "AST/If.hpp"
#include "visitor/visitor.hpp"

using namespace std;
IfNode::IfNode(uint32_t line, uint32_t col): ASTNodeBase(line,col){
}

void IfNode::printNode(){
	for(int i = 0; i < level; i++)
 		cout << "  ";
    cout << "if statement <line: " << location.line << ", col: " << location.col << "> " << endl;
}

IfNode::~IfNode(){
	;
}

void IfNode::accept(ASTNodeVisitorBase &v){
	v.visit(this);
	if(e != NULL)
	{
		e -> level = this -> level + 1;
		e -> accept(v);
	}
	if(s != NULL)
	{
		s -> level = this -> level + 1;
		s -> accept(v);
	}
	if(else_mark)
	{
		for(int i = 0; i < level; i++)
 			cout << "  ";
    	cout << "else" << endl;
	}
	if(es != NULL)
	{
		es -> level = this -> level + 1;
		es -> accept(v);
	}
}

#include <iostream>
#include "AST/Simple.hpp"
#include "visitor/visitor.hpp"

using namespace std;
SimpleNode::SimpleNode(uint32_t line, uint32_t col): ASTNodeBase(line,col){
}

void SimpleNode::printNode(){
	;
}

SimpleNode::~SimpleNode(){
	;
}

void SimpleNode::accept(ASTNodeVisitorBase &v){
	v.visit(this);
	if(p != NULL)
	{
		p -> level = this -> level;
		p -> accept(v);
	}
	if(a != NULL)
	{
		a -> level = this -> level;
		a -> accept(v);
	}
	if(r != NULL)
	{
		r -> level = this -> level;
		r -> accept(v);
	}
}

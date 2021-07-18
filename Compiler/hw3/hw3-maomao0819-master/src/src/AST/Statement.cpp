#include <iostream>
#include "AST/Statement.hpp"
#include "visitor/visitor.hpp"

using namespace std;
StatementNode::StatementNode(uint32_t line, uint32_t col): ASTNodeBase(line,col){
}

void StatementNode::printNode(){
	;
}

StatementNode::~StatementNode(){
	;
}

void StatementNode::accept(ASTNodeVisitorBase &v){
	v.visit(this);
	if(c != NULL)
	{
		c -> level = this -> level;
		c -> accept(v);
	}
	if(s != NULL)
	{
		s -> level = this -> level;
		s -> accept(v);
	}
	if(i != NULL)
	{
		i -> level = this -> level;
		i -> accept(v);
	}
	
	if(w != NULL)
	{
		w -> level = this -> level;
		w -> accept(v);
	}
	if(f != NULL)
	{
		f -> level = this -> level;
		f -> accept(v);
	}
	if(r != NULL)
	{
		r -> level = this -> level;
		r -> accept(v);
	}
	if(fc != NULL)
	{
		fc -> level = this -> level;
		fc -> accept(v);
	}
}

#include <iostream>
#include "AST/For.hpp"
#include "visitor/visitor.hpp"

using namespace std;
ForNode::ForNode(uint32_t line, uint32_t col): ASTNodeBase(line,col){
}

void ForNode::printNode(){
	for(int i = 0; i < level; i++)
 		cout << "  ";
    cout << "for statement "<< "<line: " << location.line<< ", col: "<< location.col << ">" << endl;
}

ForNode::~ForNode(){
	;
}

void ForNode::accept(ASTNodeVisitorBase &v){
	v.visit(this);
	if(d != NULL)
	{
		d -> level = this -> level + 1;
		d -> accept(v);
	}
	if(a != NULL)
	{
		a -> level = this -> level + 1;
		a -> accept(v);
	}
	if(cv != NULL)
	{
		cv -> level = this -> level + 1;
		cv -> accept(v);
	}
	while(s != NULL)
	{
		s -> level = this -> level + 1;
		s -> accept(v);
		s = s -> next;		
	}
}

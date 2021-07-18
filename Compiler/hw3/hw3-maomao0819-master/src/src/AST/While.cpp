#include <iostream>
#include "AST/While.hpp"
#include "visitor/visitor.hpp"

using namespace std;
WhileNode::WhileNode(uint32_t line, uint32_t col): ASTNodeBase(line,col){
}

void WhileNode::printNode(){
	for(int i = 0; i < level; i++)
 		cout << "  ";
    cout << "while statement "<< "<line: " << location.line<< ", col: "<< location.col << ">" << endl;
}

WhileNode::~WhileNode(){
	;
}

void WhileNode::accept(ASTNodeVisitorBase &v){
	v.visit(this);
	if(e != NULL)
	{
		e -> level = this -> level + 1;
		e -> accept(v);
	}
	while(s != NULL)
		{
			s -> level = this -> level + 1;
			s -> accept(v);
			s = s -> next;		
		}
}

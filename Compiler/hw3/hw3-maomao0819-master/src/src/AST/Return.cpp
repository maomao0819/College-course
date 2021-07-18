#include <iostream>
#include "AST/Return.hpp"
#include "visitor/visitor.hpp"

using namespace std;
ReturnNode::ReturnNode(uint32_t line, uint32_t col): ASTNodeBase(line,col){
}

void ReturnNode::printNode(){
	for(int i = 0; i < level; i++)
 		cout << "  ";
    cout << "return statement <line: " << location.line << ", col: " << location.col << "> " << endl;
}

ReturnNode::~ReturnNode(){
	;
}

void ReturnNode::accept(ASTNodeVisitorBase &v){
	v.visit(this);
	if(e != NULL)
	{
		e -> level = this -> level + 1;
		e -> accept(v);
	}
}


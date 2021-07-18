#include <iostream>
#include "AST/Read.hpp"
#include "visitor/visitor.hpp"

using namespace std;
ReadNode::ReadNode(uint32_t line, uint32_t col): ASTNodeBase(line,col){
}

void ReadNode::printNode(){
	// ouput format
	for(int i = 0; i < level; i++)
 		cout << "  ";
    cout << "read statement <line: " << location.line << ", col: " << location.col << "> " << endl;
}

ReadNode::~ReadNode(){
	;
}

void ReadNode::accept(ASTNodeVisitorBase &v){
	v.visit(this);
	if(vr != NULL)
	{
		vr -> level = this -> level + 1;
		vr -> accept(v);
	}
}

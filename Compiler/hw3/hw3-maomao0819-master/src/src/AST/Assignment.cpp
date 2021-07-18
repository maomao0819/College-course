#include <iostream>
#include "AST/Assignment.hpp"
#include "visitor/visitor.hpp"

using namespace std;
AssignmentNode::AssignmentNode(uint32_t line, uint32_t col): ASTNodeBase(line,col){
}

void AssignmentNode::printNode(){
	for(int i = 0; i < level; i++)
 		cout << "  ";
    cout << "assignment statement <line: " << location.line << ", col: " << location.col << "> " << endl;
}

AssignmentNode::~AssignmentNode(){
	;
}

void AssignmentNode::accept(ASTNodeVisitorBase &v){
	v.visit(this);
	if(vr != NULL)
	{
		vr -> level = this -> level + 1;
		vr -> accept(v);
	}
	if(e != NULL)
	{
		e -> level = this -> level + 1;
		e -> accept(v);
	}
}

#include <iostream>
#include "AST/Variable.hpp"
#include "visitor/visitor.hpp"

using namespace std;
VariableNode::VariableNode(uint32_t line, uint32_t col): ASTNodeBase(line, col){
}
void VariableNode::reset(uint32_t l, uint32_t c){
	location.line = l;
	location.col = c;
}
void VariableNode::printNode(){
	// ouput format
	for(int i = 0; i < level; i++)
 		cout << "  ";
    cout << "variable <line: " << location.line << ", col: " << location.col << "> " << name << " " << type << endl;
}

VariableNode::~VariableNode(){
	;
}

void VariableNode::accept(ASTNodeVisitorBase &v){
	v.visit(this);
	if (c != NULL)
	{
		c -> level = this -> level + 1;
		c -> accept(v);
	}
}

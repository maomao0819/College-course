#include <iostream>
#include "AST/UnaryOperator.hpp"
#include "visitor/visitor.hpp"

using namespace std;
UnaryOperatorNode::UnaryOperatorNode(uint32_t line, uint32_t col): ASTNodeBase(line,col){
}

void UnaryOperatorNode::printNode(){
	// ouput format
	for(int i = 0; i < level; i++)
 		cout << "  ";
    cout << "unary operator" << " <line: " << location.line << ", col: " << location.col << "> " << op << endl;
}

UnaryOperatorNode::~UnaryOperatorNode(){
	;
}

void UnaryOperatorNode::accept(ASTNodeVisitorBase &v){
	v.visit(this);
	if(cv != NULL)
	{
		cv -> level = this -> level + 1;
		cv -> accept(v);
	}
}

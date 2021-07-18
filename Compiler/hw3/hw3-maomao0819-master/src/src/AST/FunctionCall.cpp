#include <iostream>
#include "AST/FunctionCall.hpp"
#include "visitor/visitor.hpp"

using namespace std;
FunctionCallNode::FunctionCallNode(uint32_t line, uint32_t col): ASTNodeBase(line,col){
}

void FunctionCallNode::printNode(){
	// ouput format
	for(int i = 0; i < level; i++)
 		cout << "  ";
    cout << "function call statement <line: " << location.line<<", col: "<< location.col << "> " << name << endl;
}

FunctionCallNode::~FunctionCallNode(){
	;
}

void FunctionCallNode::accept(ASTNodeVisitorBase &v){
	v.visit(this);
	while(e != NULL && e -> empty_mark == false)
		{
			e -> level = this -> level + 1;
			e -> accept(v);
			e = e -> next;		
		}

}

#include <iostream>
#include "AST/Print.hpp"
#include "visitor/visitor.hpp"

using namespace std;
PrintNode::PrintNode(uint32_t line, uint32_t col): ASTNodeBase(line,col){
}

void PrintNode::printNode(){
	// ouput format
	for(int i = 0; i < level; i++)
 		cout << "  ";
    cout << "print statement "<< "<line: " << location.line <<", col: "<< location.col << ">" << endl;
}

PrintNode::~PrintNode(){
	;
}

void PrintNode::accept(ASTNodeVisitorBase &v){
	v.visit(this);
	if(e != NULL)
	{
		e -> level = this -> level + 1;
		e -> accept(v);
	}
}

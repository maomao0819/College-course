#include <iostream>
#include "AST/CompoundStatement.hpp"
#include "visitor/visitor.hpp"

using namespace std;
CompoundStatementNode::CompoundStatementNode(uint32_t line, uint32_t col): ASTNodeBase(line,col){
}

void CompoundStatementNode::printNode(){
	// ouput format
 	for(int i = 0; i < level; i++)
 		cout << "  ";
    cout << "compound statement "<< "<line: " << location.line<<", col: "<< location.col << ">" << endl;
}

CompoundStatementNode::~CompoundStatementNode(){
	;
}

void CompoundStatementNode::accept(ASTNodeVisitorBase &v){
	v.visit(this);
	while(d != NULL)
		{
			d -> level = this -> level + 1;
			d -> accept(v);
			d = d -> next;		
		}
	while(s != NULL)
		{
			s -> level = this -> level + 1;
			s -> accept(v);
			s = s -> next;		
		}
	
}

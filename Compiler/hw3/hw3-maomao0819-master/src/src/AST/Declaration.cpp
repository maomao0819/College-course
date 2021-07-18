#include <iostream>
#include "AST/Declaration.hpp"
#include "visitor/visitor.hpp"

using namespace std;
DeclarationNode::DeclarationNode(uint32_t line, uint32_t col): ASTNodeBase(line,col){
}

void DeclarationNode::printNode(){
	// ouput format
	if(mark)
	{
		for(int i = 0; i < level; i++)
 			cout << "  ";
   		cout << "declaration <line: " << location.line<< ", col: " << location.col << ">" << endl;
	}
	
}

DeclarationNode::~DeclarationNode(){
	;
}

void DeclarationNode::accept(ASTNodeVisitorBase &v){
	if(mark)
	{
		v.visit(this);
		for (int i = 0; i < vv.size(); i++)
		{
			vv[i] -> level = this -> level + 1;
			vv[i] -> accept(v);
		}
	}

}

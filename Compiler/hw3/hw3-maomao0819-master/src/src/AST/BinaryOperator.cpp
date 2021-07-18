#include <iostream>
#include "AST/BinaryOperator.hpp"
#include "visitor/visitor.hpp"

using namespace std;
BinaryOperatorNode::BinaryOperatorNode(uint32_t line, uint32_t col): ASTNodeBase(line,col){
}

void BinaryOperatorNode::printNode(){
	// ouput format
	for(int i = 0; i < level; i++)
 		cout << "  ";
    cout << "binary operator" << " <line: " << location.line << ", col: " << location.col << "> " << op << endl;
}

BinaryOperatorNode::~BinaryOperatorNode(){
	;
}

void BinaryOperatorNode::accept(ASTNodeVisitorBase &v){
	v.visit(this);
	if(scope_mark)
	{
		bo_next -> level = this -> level + 1;
		bo_next -> accept(v);
	}
	if(uo1 != NULL)
	{
		uo1 -> level = this -> level + 1;
		uo1 -> accept(v);
	}
	else 
	{
		if(vr1 != NULL && !scope_mark)
		{
			vr1 -> level = this -> level + 1;
			vr1 -> accept(v);
		}
		else if(cv1 != NULL && !scope_mark)
		{
			cv1 -> level = this -> level + 1;
			cv1 -> accept(v);
		}
		
	}
	if(uo2 != NULL)
	{
		uo2 -> level = this -> level + 1;
		uo2 -> accept(v);
	}
	else 
	{
		if(vr2 != NULL)
		{
			vr2 -> level = this -> level + 1;
			vr2 -> accept(v);
		}
		else if(cv2 != NULL)
		{
			cv2 -> level = this -> level + 1;
			cv2 -> accept(v);
		}
		
	}


}

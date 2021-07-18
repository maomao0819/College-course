#include <iostream>
#include "AST/Expression.hpp"
#include "visitor/visitor.hpp"

using namespace std;
ExpressionNode::ExpressionNode(uint32_t line, uint32_t col): ASTNodeBase(line,col){
}

void ExpressionNode::printNode(){
	;
}

ExpressionNode::~ExpressionNode(){
	;
}

void ExpressionNode::accept(ASTNodeVisitorBase &v){
	v.visit(this);
	if(bo_mark && bo != NULL)
	{
		bo -> level = this -> level;
		bo -> accept(v);
	}
	else if(uo_mark && uo != NULL)
	{
		uo -> level = this -> level;
		uo -> accept(v);
	}
	if(cv_mark && cv != NULL)
	{
		cv -> level = this -> level;
		cv -> accept(v);
	}
	if(vr_mark && vr != NULL)
	{
		vr -> level = this -> level;
		vr -> accept(v);
	}
	if(fc_mark && fc != NULL)
	{
		fc -> level = this -> level;
		fc -> accept(v);
	}
}

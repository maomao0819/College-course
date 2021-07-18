// 針對 AST node的visitor
#pragma once
#include "AST/ast.hpp"
#include "AST/program.hpp"
#include "AST/FunctionDeclaration.hpp"
#include "AST/Declaration.hpp"
#include "AST/Statement.hpp"
#include "AST/CompoundStatement.hpp"
#include "AST/Simple.hpp"
#include "AST/VariableReference.hpp"
#include "AST/While.hpp"
#include "AST/For.hpp"
#include "AST/Return.hpp"
#include "AST/FunctionCall.hpp"
#include "AST/Expression.hpp"
#include "AST/Variable.hpp"
#include "AST/ConstantValue.hpp"
#include "AST/Assignment.hpp"
#include "AST/Print.hpp"
#include "AST/Read.hpp"
#include "AST/BinaryOperator.hpp"
#include "AST/UnaryOperator.hpp"
#include "AST/If.hpp"

// 讓所有visitor繼承的
class ASTNodeVisitorBase
{
public:
    virtual void visit(ProgramNode *e) = 0;
 	virtual void visit(FunctionDeclarationNode *e) = 0;
 	virtual void visit(DeclarationNode *e) = 0;
 	virtual void visit(StatementNode *e) = 0;
 	virtual void visit(CompoundStatementNode *e) = 0;
 	virtual void visit(SimpleNode *e) = 0;
 	virtual void visit(VariableReferenceNode *e) = 0;
 	virtual void visit(WhileNode *e) = 0;
 	virtual void visit(ForNode *e) = 0;
 	virtual void visit(ReturnNode *e) = 0;
 	virtual void visit(FunctionCallNode *e) = 0;
 	virtual void visit(ExpressionNode *e) = 0;
 	virtual void visit(VariableNode *e) = 0;
 	virtual void visit(ConstantValueNode *e) = 0;
 	virtual void visit(AssignmentNode *e) = 0;
 	virtual void visit(PrintNode *e) = 0;
 	virtual void visit(ReadNode *e) = 0;
 	virtual void visit(BinaryOperatorNode *e) = 0;
 	virtual void visit(UnaryOperatorNode *e) = 0;
 	virtual void visit(IfNode *e) = 0;
};

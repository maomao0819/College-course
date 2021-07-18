// 專屬ProgramNode的定義
#pragma once
#include <string>
// because of Makfile, include us starting from src and the path won't need "include/"
#include "AST/ast.hpp"
#include "AST/Simple.hpp"
#include "AST/Return.hpp"
#include "AST/If.hpp"
#include "AST/For.hpp"
#include "AST/While.hpp"
#include "AST/FunctionCall.hpp"
#include "AST/CompoundStatement.hpp"
// not necessary but prefered
class ASTNodeVisitorBase;
class IfNode;
class ForNode;
class WhileNode;
class CompoundStatementNode;
class StatementNode : public ASTNodeBase
{
public:
  std::string name;
  StatementNode(uint32_t line, uint32_t col);
  void printNode();
  ~StatementNode();
  void accept(ASTNodeVisitorBase &v);
  SimpleNode* s = NULL;
  ReturnNode* r = NULL;
  IfNode* i = NULL;
  ForNode* f = NULL;
  WhileNode* w = NULL;
  FunctionCallNode* fc = NULL;
  CompoundStatementNode *c = NULL;
  StatementNode* next = NULL;
  StatementNode* prev = NULL;
  StatementNode* now = this;
};

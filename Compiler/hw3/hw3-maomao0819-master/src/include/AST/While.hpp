// 專屬ProgramNode的定義
#pragma once
#include <string>
// because of Makfile, include us starting from src and the path won't need "include/"
#include "AST/ast.hpp"
#include "AST/Expression.hpp"
#include "AST/Statement.hpp"
// not necessary but prefered
class ASTNodeVisitorBase;
class StatementNode;

class WhileNode : public ASTNodeBase
{
public:
  std::string name;
  WhileNode(uint32_t line, uint32_t col);
  void printNode();
  ~WhileNode();
  void accept(ASTNodeVisitorBase &v);
  ExpressionNode* e = NULL;
  StatementNode* s = NULL;
};

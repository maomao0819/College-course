// 專屬ProgramNode的定義
#pragma once
#include <string>
// because of Makfile, include us starting from src and the path won't need "include/"
#include "AST/ast.hpp"
#include "AST/Expression.hpp"
// not necessary but prefered
class ASTNodeVisitorBase;

class ReturnNode : public ASTNodeBase
{
public:
  std::string name;
  ReturnNode(uint32_t line, uint32_t col);
  void printNode();
  ~ReturnNode();
  void accept(ASTNodeVisitorBase &v);
  ExpressionNode* e = NULL;
};

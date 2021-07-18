// 專屬PrintNode的定義
#pragma once
#include <string>
#include <vector>
// because of Makfile, include us starting from src and the path won't need "include/"
#include "AST/ast.hpp"
#include "AST/Expression.hpp"
// not necessary but prefered
class ASTNodeVisitorBase;

class PrintNode : public ASTNodeBase
{
public:
  std::string name;
  PrintNode(uint32_t line, uint32_t col);
  void printNode();
  ~PrintNode();
  void accept(ASTNodeVisitorBase &v);
  ExpressionNode* e = NULL; 
};

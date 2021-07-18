// 專屬UnaryOperatorNode的定義
#pragma once
#include <string>
// because of Makfile, include us starting from src and the path won't need "include/"
#include "AST/ast.hpp"
#include "AST/ConstantValue.hpp"
// not necessary but prefered
class ASTNodeVisitorBase;

class UnaryOperatorNode : public ASTNodeBase
{
public:
  std::string name;
  std::string op;
  UnaryOperatorNode(uint32_t line, uint32_t col);
  void printNode();
  ~UnaryOperatorNode();
  void accept(ASTNodeVisitorBase &v);
  ConstantValueNode* cv = NULL;
};

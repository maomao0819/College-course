// 專屬ProgramNode的定義
#pragma once
#include <string>
// because of Makfile, include us starting from src and the path won't need "include/"
#include "AST/ast.hpp"
#include "AST/ConstantValue.hpp"
#include "AST/Expression.hpp"
// not necessary but prefered
class ASTNodeVisitorBase;
class ExpressionNode;

class VariableReferenceNode : public ASTNodeBase
{
public:
  std::string name;
  VariableReferenceNode(uint32_t line, uint32_t col);
  void printNode();
  ~VariableReferenceNode();
  void accept(ASTNodeVisitorBase &v);
  ConstantValueNode* cv = NULL;
  bool arr_mark = false;
  ExpressionNode* e = NULL;
};

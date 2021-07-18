// 專屬VariableNode的定義
#pragma once
#include <string>
#include <vector>
// because of Makfile, include us starting from src and the path won't need "include/"
#include "AST/ast.hpp"
#include "AST/ConstantValue.hpp"
// not necessary but prefered
class ASTNodeVisitorBase;

class VariableNode : public ASTNodeBase
{
public:
  std::string name;
  std::string type;
  VariableNode(uint32_t line, uint32_t col);
  void reset(uint32_t l, uint32_t c);
  void printNode();
  ~VariableNode();
  void accept(ASTNodeVisitorBase &v);
  ConstantValueNode *c = NULL;
  VariableNode* next = NULL;
  VariableNode* prev = NULL;
};

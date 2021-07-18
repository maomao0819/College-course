#pragma once
#include <string>
// because of Makfile, include us starting from src and the path won't need "include/"
#include "AST/ast.hpp"
#include "VariableReference.hpp"
#include "AST/Expression.hpp"
// not necessary but prefered
class ASTNodeVisitorBase;

class AssignmentNode : public ASTNodeBase
{
public:
  std::string name;
  AssignmentNode(uint32_t line, uint32_t col);
  void printNode();
  ~AssignmentNode();
  void accept(ASTNodeVisitorBase &v);
  VariableReferenceNode *vr = NULL;
  ExpressionNode* e = NULL;
};

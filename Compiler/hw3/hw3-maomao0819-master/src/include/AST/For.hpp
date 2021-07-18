// 專屬ProgramNode的定義
#pragma once
#include <string>
// because of Makfile, include us starting from src and the path won't need "include/"
#include "AST/ast.hpp"
#include "AST/Statement.hpp"
#include "AST/Declaration.hpp"
#include "AST/Assignment.hpp"
#include "AST/ConstantValue.hpp"
// not necessary but prefered
class ASTNodeVisitorBase;
class StatementNode;

class ForNode : public ASTNodeBase
{
public:
  std::string name;
  ForNode(uint32_t line, uint32_t col);
  void printNode();
  ~ForNode();
  void accept(ASTNodeVisitorBase &v);
  DeclarationNode* d = NULL;
  AssignmentNode* a = NULL;
  ConstantValueNode* cv = NULL;
  StatementNode* s = NULL;
};

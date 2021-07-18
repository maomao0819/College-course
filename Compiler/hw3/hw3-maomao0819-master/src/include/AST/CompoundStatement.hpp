
#pragma once
#include <string>
// because of Makfile, include us starting from src and the path won't need "include/"
#include "AST/ast.hpp"
#include "AST/Print.hpp"
#include "AST/Declaration.hpp"
#include "AST/Statement.hpp"
// not necessary but prefered
class ASTNodeVisitorBase;

class CompoundStatementNode : public ASTNodeBase
{
public:
  std::string name;
  CompoundStatementNode(uint32_t line, uint32_t col);
  void printNode();
  ~CompoundStatementNode();
  void accept(ASTNodeVisitorBase &v);
  DeclarationNode* d = NULL;
  StatementNode* s = NULL;
  int t = 0;
};

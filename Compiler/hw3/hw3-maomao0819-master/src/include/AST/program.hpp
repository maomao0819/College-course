// 專屬ProgramNode的定義
#pragma once
#include <string>
#include <vector>
// because of Makfile, include us starting from src and the path won't need "include/"
#include "AST/ast.hpp"
#include "AST/Declaration.hpp"
#include "AST/FunctionDeclaration.hpp"
#include "AST/CompoundStatement.hpp"
// not necessary but prefered
class ASTNodeVisitorBase;

class ProgramNode : public ASTNodeBase
{
public:
  std::string name;
  int count = -1;
  ProgramNode(uint32_t line, uint32_t col);
  void printNode();
  ~ProgramNode();
  void accept(ASTNodeVisitorBase &v);
  DeclarationNode *d = NULL;
  std::vector <DeclarationNode*> vd;
  FunctionDeclarationNode *f = NULL;
  std::vector <FunctionDeclarationNode*> vf;
  CompoundStatementNode *c = NULL;
  int vf_id = 0;
  int t = 0;
};

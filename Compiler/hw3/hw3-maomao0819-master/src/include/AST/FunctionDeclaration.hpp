// 專屬ProgramNode的定義
#pragma once
#include <string>
#include <vector>
// because of Makfile, include us starting from src and the path won't need "include/"
#include "AST/ast.hpp"
#include "AST/CompoundStatement.hpp"
#include "AST/Declaration.hpp"

// not necessary but prefered
class ASTNodeVisitorBase;

class FunctionDeclarationNode : public ASTNodeBase
{
public:
  std::string name;
  std::string returntype = "void";
  std::vector <std::string> parameter;
  FunctionDeclarationNode(uint32_t line, uint32_t col);
  void printNode();
  ~FunctionDeclarationNode();
  void accept(ASTNodeVisitorBase &v);
  std::vector <DeclarationNode*> vd;
  CompoundStatementNode *c = NULL;
};

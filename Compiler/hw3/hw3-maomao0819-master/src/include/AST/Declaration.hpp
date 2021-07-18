// 專屬ProgramNode的定義
#pragma once
#include <string>
#include <vector>
// because of Makfile, include us starting from src and the path won't need "include/"
#include "AST/ast.hpp"
#include "AST/Variable.hpp"
// not necessary but prefered
class ASTNodeVisitorBase;

class DeclarationNode : public ASTNodeBase
{
public:
  std::string name;
  std::string type;
  int count = -1;
  bool mark = true;
  DeclarationNode(uint32_t line, uint32_t col);
  void printNode();
  ~DeclarationNode();
  void accept(ASTNodeVisitorBase &v);
  VariableNode *var = NULL;
  std::vector <VariableNode*> vv;
  int t = 0;
  DeclarationNode* next = NULL;
  DeclarationNode* prev = NULL;
  DeclarationNode* now = this;
};

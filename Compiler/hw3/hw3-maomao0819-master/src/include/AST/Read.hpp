// 專屬ReadNode的定義
#pragma once
#include <string>
// because of Makfile, include us starting from src and the path won't need "include/"
#include "AST/ast.hpp"
#include "AST/VariableReference.hpp"
// not necessary but prefered
class ASTNodeVisitorBase;

class ReadNode : public ASTNodeBase
{
public:
  std::string name;
  ReadNode(uint32_t line, uint32_t col);
  void printNode();
  ~ReadNode();
  void accept(ASTNodeVisitorBase &v);
  VariableReferenceNode* vr = NULL;
};

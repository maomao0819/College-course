// 專屬ProgramNode的定義
#pragma once
#include <string>
// because of Makfile, include us starting from src and the path won't need "include/"
#include "AST/ast.hpp"
#include "AST/Print.hpp"
//#include "VariableReference.hpp"
#include "AST/Assignment.hpp"
#include "AST/Read.hpp"
// not necessary but prefered
class ASTNodeVisitorBase;

class SimpleNode : public ASTNodeBase
{
public:
  std::string name;
  SimpleNode(uint32_t line, uint32_t col);
  void printNode();
  ~SimpleNode();
  void accept(ASTNodeVisitorBase &v);
  PrintNode* p = NULL;
  AssignmentNode *a = NULL;
  ReadNode *r = NULL;
};

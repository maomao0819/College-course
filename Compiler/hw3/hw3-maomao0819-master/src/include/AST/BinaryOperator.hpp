// 專屬BinaryOperatorNode的定義
#pragma once
#include <string>
// because of Makfile, include us starting from src and the path won't need "include/"
#include "AST/ast.hpp"
#include "AST/ConstantValue.hpp"
#include "AST/UnaryOperator.hpp"
#include "AST/VariableReference.hpp"
// not necessary but prefered
class ASTNodeVisitorBase;
class VariableReferenceNode;

class BinaryOperatorNode : public ASTNodeBase
{
public:
  std::string name;
  std::string op;
  bool scope_mark = false;
  BinaryOperatorNode(uint32_t line, uint32_t col);
  void printNode();
  ~BinaryOperatorNode();
  void accept(ASTNodeVisitorBase &v);
  ConstantValueNode* cv1 = NULL;
  ConstantValueNode* cv2 = NULL;
  VariableReferenceNode* vr1 = NULL;
  VariableReferenceNode* vr2 = NULL;
  UnaryOperatorNode* uo1 = NULL;
  UnaryOperatorNode* uo2 = NULL;
  BinaryOperatorNode* bo_next = NULL;
  BinaryOperatorNode* bo_prev = NULL;
};

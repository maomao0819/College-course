// 專屬ProgramNode的定義
#pragma once
#include <string>
// because of Makfile, include us starting from src and the path won't need "include/"
#include "AST/ast.hpp"
#include "AST/BinaryOperator.hpp"
#include "AST/UnaryOperator.hpp"
#include "AST/ConstantValue.hpp"
#include "AST/VariableReference.hpp"
#include "AST/FunctionCall.hpp"
// not necessary but prefered
class ASTNodeVisitorBase;
class FunctionCallNode;
class VariableReferenceNode;
class BinaryOperatorNode;

class ExpressionNode : public ASTNodeBase
{
public:
  std::string name;
  bool empty_mark = false;
  bool scope_mark = false;
  bool bo_mark = false;
  bool uo_mark = false;
  bool uom_mark = false;
  bool cv_mark = false;
  bool vr_mark = false;
  bool fc_mark = false;
  ExpressionNode(uint32_t line, uint32_t col);
  void printNode();
  ~ExpressionNode();
  void accept(ASTNodeVisitorBase &v);
  BinaryOperatorNode* bo = NULL;
  UnaryOperatorNode* uo = NULL;
  UnaryOperatorNode* uom = NULL;
  ConstantValueNode* cv = NULL;
  VariableReferenceNode* vr = NULL;
  FunctionCallNode* fc = NULL;
  ExpressionNode* next = NULL;
  ExpressionNode* prev = NULL;
  ExpressionNode* now = this;
};

// 專屬ConstantValueNode的定義
#pragma once
#include <string>
// because of Makfile, include us starting from src and the path won't need "include/"
#include "AST/ast.hpp"

// not necessary but prefered
class ASTNodeVisitorBase;

class ConstantValueNode : public ASTNodeBase
{
public:
  std::string name;
  bool neg_power_op = false;
  bool sc_power = false;
  bool int_mark = false;
  bool oct_mark = false;
  bool float_mark = false;
  bool bool_mark = false;
  bool str_mark = false;
  int int_value = 0;
  float float_value = 0;
  std::string bool_value = "-1";
  std::string str = "\0";
  std::string str_value;
  ConstantValueNode(uint32_t line, uint32_t col);
  void printNode();
  ~ConstantValueNode();
  void accept(ASTNodeVisitorBase &v);
  ConstantValueNode* arr_next = NULL;
  ConstantValueNode* arr_prev = NULL;
};

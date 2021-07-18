// include all AST需要include的東西
#pragma once
#include <cstdint>
// 吃什麼不重要
class ASTNodeVisitorBase;

struct Location
{
  uint32_t line;
  uint32_t col;
  // constructure
  Location(uint32_t line, uint32_t col) : line(line), col(col){};
};

class ASTNodeBase
{
public:
  Location location;
  int level = 0;
  ASTNodeBase(int32_t line, int32_t col) : location(line, col){};

  // virtual : 大致上共用，會依據不同情形有不同的細節處理
  virtual ~ASTNodeBase(){};
  // visitor will call it
  virtual void printNode();
  // 開放給visitor	"= 0" : pure virtual function
  virtual void accept(ASTNodeVisitorBase &v) = 0;
};

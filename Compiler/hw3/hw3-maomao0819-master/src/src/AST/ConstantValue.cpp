#include <iostream>
#include "AST/ConstantValue.hpp"
#include "visitor/visitor.hpp"
#include <iomanip>
using namespace std;
ConstantValueNode::ConstantValueNode(uint32_t line, uint32_t col): ASTNodeBase(line,col){
}

void ConstantValueNode::printNode(){
	// ouput format
	for(int i = 0; i < level; i++)
 		cout << "  ";
    cout << "constant <line: " << location.line<< ", col: " << location.col << "> ";
	if(int_mark)
	{
		if(oct_mark)
		{
			int temp = 0;
			int power = 1;
			int r = 0;
			while(int_value)
			{
				r = int_value % 10;
				temp += r * power;
				power *= 8;
				int_value /= 10;
			}
			int_value = temp;
		}
		cout << int_value;
	}
	else if(float_mark)
		cout << fixed << setprecision(6) << float_value;
	else if(bool_mark)
		cout << bool_value;
	else if(str_mark)
		cout << str_value;
    cout << "\n";
}

ConstantValueNode::~ConstantValueNode(){
	;
}

void ConstantValueNode::accept(ASTNodeVisitorBase &v){
	v.visit(this);
}

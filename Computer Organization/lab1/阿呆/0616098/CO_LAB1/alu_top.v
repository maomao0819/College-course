//0616098
`timescale 1ns/1ps

//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    10:58:01 10/10/2013
// Design Name: 
// Module Name:    alu_top 
// Project Name: 
// Target Devices: 
// Tool versions: 
// Description: 
//
// Dependencies: 
//
// Revision: 
// Revision 0.01 - File Created
// Additional Comments: 
//
//////////////////////////////////////////////////////////////////////////////////

module alu_top(
               src1,       //1 bit source 1 (input)
               src2,       //1 bit source 2 (input)
               less,       //1 bit less     (input)
               A_invert,   //1 bit A_invert (input)
               B_invert,   //1 bit B_invert (input)
               cin,        //1 bit carry in (input)
               operation,  //operation      (input)
               result,     //1 bit result   (output)
               cout     //1 bit carry out(output)
               );

input         src1;
input         src2;
input         less;
input         A_invert;
input         B_invert;
input         cin;
input [2-1:0] operation;

output        result;
output        cout;

reg           result;

wire A, B;
assign A = src1 ^ A_invert;   //complement
assign B = src2 ^ B_invert;   //complement
assign cout = (A & B) | ((A | B) & cin) ;

always@( src1, src2, A_invert, B_invert, cin, operation, result, cout )
begin
	case(operation)
		2'd0:       //And
				result = A & B;
        2'd1:       //Or
            	result = A | B;
        2'd2:       //Add
       		    result = A ^ B ^ cin;
        2'd3:       //Slt
            	result = less;
    endcase
end

endmodule

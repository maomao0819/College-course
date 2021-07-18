//0616098
`timescale 1ns/1ps

//////////////////////////////////////////////////////////////////////////////////
// Company:
// Engineer:
//
// Create Date:    15:15:11 08/18/2013
// Design Name:
// Module Name:    alu
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

module alu(
           clk,           // system clock              (input)
           rst_n,         // negative reset            (input)
           src1,          // 32 bits source 1          (input)
           src2,          // 32 bits source 2          (input)
           ALU_control,   // 4 bits ALU control input  (input)
						  //bonus_control, // 3 bits bonus control input(input) 
           result,        // 32 bits result            (output)
           zero,          // 1 bit when the output is 0, zero must be set (output)
           cout,          // 1 bit carry out           (output)
           overflow       // 1 bit overflow            (output)
           );

input           clk;
input           rst_n;
input  [32-1:0] src1;
input  [32-1:0] src2;
input   [4-1:0] ALU_control;
//input   [3-1:0] bonus_control; 

output [32-1:0] result;
output          zero;
output          cout;
output          overflow;

//reg    [32-1:0] result;
//reg             zero;
//reg             cout;
//reg             overflow;

reg     [32-1:0] src1_temp;
reg     [32-1:0] src2_temp;
wire    [32-1:0] carry;
reg		[2-1:0]  operation;
reg	        	 A_invert;
reg	        	 B_invert;
//			alu (src1,         src2,         less, A_invert, B_invert, cin, operation, result,    cout)
alu_top		alu0(src1_temp[0], src2_temp[0], set, A_invert, B_invert, 1'b0, operation, result[0], carry[0]),
			alu1(src1_temp[1], src2_temp[1], 1'b0, A_invert, B_invert, carry[0], operation, result[1], carry[1]),
			alu2(src1_temp[2], src2_temp[2], 1'b0, A_invert, B_invert, carry[1], operation, result[2], carry[2]),
			alu3(src1_temp[3], src2_temp[3], 1'b0, A_invert, B_invert, carry[2], operation, result[3], carry[3]),
			alu4(src1_temp[4], src2_temp[4], 1'b0, A_invert, B_invert, carry[3], operation, result[4], carry[4]),
			alu5(src1_temp[5], src2_temp[5], 1'b0, A_invert, B_invert, carry[4], operation, result[5], carry[5]),
			alu6(src1_temp[6], src2_temp[6], 1'b0, A_invert, B_invert, carry[5], operation, result[6], carry[6]),
			alu7(src1_temp[7], src2_temp[7], 1'b0, A_invert, B_invert, carry[6], operation, result[7], carry[7]),
			alu8(src1_temp[8], src2_temp[8], 1'b0, A_invert, B_invert, carry[7], operation, result[8], carry[8]),
			alu9(src1_temp[9], src2_temp[9], 1'b0, A_invert, B_invert, carry[8], operation, result[9], carry[9]),
			alu10(src1_temp[10], src2_temp[10], 1'b0, A_invert, B_invert, carry[9], operation, result[10], carry[10]),
			alu11(src1_temp[11], src2_temp[11], 1'b0, A_invert, B_invert, carry[10], operation, result[11], carry[11]),
			alu12(src1_temp[12], src2_temp[12], 1'b0, A_invert, B_invert, carry[11], operation, result[12], carry[12]),
			alu13(src1_temp[13], src2_temp[13], 1'b0, A_invert, B_invert, carry[12], operation, result[13], carry[13]),
			alu14(src1_temp[14], src2_temp[14], 1'b0, A_invert, B_invert, carry[13], operation, result[14], carry[14]),
			alu15(src1_temp[15], src2_temp[15], 1'b0, A_invert, B_invert, carry[14], operation, result[15], carry[15]),
			alu16(src1_temp[16], src2_temp[16], 1'b0, A_invert, B_invert, carry[15], operation, result[16], carry[16]),
			alu17(src1_temp[17], src2_temp[17], 1'b0, A_invert, B_invert, carry[16], operation, result[17], carry[17]),
			alu18(src1_temp[18], src2_temp[18], 1'b0, A_invert, B_invert, carry[17], operation, result[18], carry[18]),
			alu19(src1_temp[19], src2_temp[19], 1'b0, A_invert, B_invert, carry[18], operation, result[19], carry[19]),
			alu20(src1_temp[20], src2_temp[20], 1'b0, A_invert, B_invert, carry[19], operation, result[20], carry[20]),
			alu21(src1_temp[21], src2_temp[21], 1'b0, A_invert, B_invert, carry[20], operation, result[21], carry[21]),
			alu22(src1_temp[22], src2_temp[22], 1'b0, A_invert, B_invert, carry[21], operation, result[22], carry[22]),
			alu23(src1_temp[23], src2_temp[23], 1'b0, A_invert, B_invert, carry[22], operation, result[23], carry[23]),
			alu24(src1_temp[24], src2_temp[24], 1'b0, A_invert, B_invert, carry[23], operation, result[24], carry[24]),
			alu25(src1_temp[25], src2_temp[25], 1'b0, A_invert, B_invert, carry[24], operation, result[25], carry[25]),
			alu26(src1_temp[26], src2_temp[26], 1'b0, A_invert, B_invert, carry[25], operation, result[26], carry[26]),
			alu27(src1_temp[27], src2_temp[27], 1'b0, A_invert, B_invert, carry[26], operation, result[27], carry[27]),
			alu28(src1_temp[28], src2_temp[28], 1'b0, A_invert, B_invert, carry[27], operation, result[28], carry[28]),
			alu29(src1_temp[29], src2_temp[29], 1'b0, A_invert, B_invert, carry[28], operation, result[29], carry[29]),
			alu30(src1_temp[30], src2_temp[30], 1'b0, A_invert, B_invert, carry[29], operation, result[30], carry[30]);

alu_bottom	alu31(src1_temp[31], src2_temp[31], 1'b0, A_invert, B_invert, carry[30], operation, result[31], cout, set, overflow);

always@( posedge clk or negedge rst_n ) 
begin
	if(!rst_n) begin
		A_invert = 1'b0;
		B_invert = 1'b0;  
	end
	else begin
		src1_temp = src1;
		src2_temp = src2;
		A_invert = 1'b0;
		B_invert = 1'b0;                
		case (ALU_control)
			4'b0000: 	//And
				operation = 2'b00;
			4'b0001: 	//Or
				operation = 2'b01;
			4'b0010: 	//Add
				operation = 2'b10;
			4'b0110:	//Sub 
			begin	
				src2_temp = src2_temp - 1;
				A_invert = 1'b0;
				B_invert = 1'b1;
				operation = 2'b10;
			end
			4'b1100:	//Nor 
			begin	
				A_invert = 1'b1;
				B_invert = 1'b1;
				operation = 2'b00;
			end
			4'b0111:	//Slt 
			begin	
				src2_temp = src2_temp - 1;
				A_invert = 1'b0;
				B_invert = 1'b1;
				operation = 2'b11;
			end
		endcase
	end
end

assign zero = (result==0) ? 1 : 0;

endmodule

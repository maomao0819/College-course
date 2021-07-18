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
			 // bonus_control, // 3 bits bonus control input(input) 
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

reg    [32-1:0] result;
reg             zero;
reg             cout;
reg             overflow;

reg [2-1:0] op;     //operator
reg A_inv;          //A_invert
reg B_inv;          //B_invert

wire [32-1:0] res;  //result
wire [32-1:0] ci;   //cin
wire co;            //cout
wire set;
wire ovf;           //overflow

assign ci[0] = (ALU_control == 4'b0110) | (ALU_control == 4'b0111);      //sub add 1 for 2's complements

always@( posedge clk or  rst_n , ALU_control , co , res , ovf, zero) 
begin
    	
		if(!rst_n ) begin    //clear and initialize all registers
       		result = 0;
        	zero = 1'b0;
        	cout = 1'b0;
        	overflow = 1'b0;
        	op = 2'b00;
        	A_inv = 1'b0;
        	B_inv = 1'b0;
    	end
    	else
		begin
		$display("%8h, %8h",src1, src2);
		$display("%4b",ALU_control);
        	A_inv = 1'b0;
        	B_inv = 1'b0;
        	case(ALU_control)
            	4'b0000:            //And
               		op = 2'b00;
            	4'b0001:            //Or
               		op = 2'b01;
           		4'b0010:            //Add
            	 	op = 2'b10;
           		4'b0110:            //Sub
           		begin
                	A_inv = 1'b0;
               		B_inv = 1'b1;
               		op = 2'b10;
            	end
				4'b0111:            //Slt
           		begin
               		A_inv = 1'b0;
               		B_inv = 1'b1;
               		op = 2'b11;     //slt
           		end
           		4'b1100:            //Nor
           		begin
               		A_inv = 1'b1;
               		B_inv = 1'b1;
               		op = 2'b00;     //and
           		end
           		
        	endcase
        	result = res;
        	zero = ~|result;     //nor all outputs
        	cout = (ALU_control == 4'b0010 || ALU_control == 4'b0110) ? co : 1'b0;
        	overflow = (ALU_control == 4'b0010 || ALU_control == 4'b0110) ? ovf : 1'b0;
    	end
		$display("%8h",result);
end

genvar i;       //iterator use for loop
generate
	for(i = 0; i < 31; i = i + 1) 
	begin 
      alu_top alu_t(src1[i], 
		    src2[i], 
		    (i == 0) ? set : 1'b0,
       	A_inv,
			  B_inv, 
			  ci[i], 
			  op,
			  res[i],
			  ci[i + 1]);
  end
endgenerate

alu_bottom alu_b(
	.src1(src1[31]),
    	.src2(src2[31]),
    	.less(1'b0),
    	.equal(src1 == src2),
    	.A_invert(A_inv),
    	.B_invert(B_inv),
    	.cin(ci[31]),
    	.operation(op),
    	.result(res[31]),
    	.cout(co),
    	.set(set),
    	.overflow(ovf)   
    	);

endmodule


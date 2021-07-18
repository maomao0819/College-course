//0616098
`timescale 1ns / 1ps
//Subject:     CO project 4 - Pipe Register
//--------------------------------------------------------------------------------
//Version:     1
//--------------------------------------------------------------------------------
//Writer:      黃秉茂
//----------------------------------------------
//Date:        6/26
//----------------------------------------------
//Description: 
//--------------------------------------------------------------------------------
module Forwarding(
	EX_Rs,
	EX_Rt,
	MEM_Rd,
	MEM_RegWrite,
	WB_Rd,
	WB_RegWrite,
	Forward_A,
	Forward_B
    );

input 	[4:0]	EX_Rs;
input 	[4:0]	EX_Rt;
input 	[4:0]	MEM_Rd;
input 			MEM_RegWrite;
input 	[4:0]	WB_Rd;
input 			WB_RegWrite;
output	[1:0]	Forward_A;
output	[1:0]	Forward_B;

reg	    [1:0]	Forward_A;
reg	    [1:0]	Forward_B;

always@( * )begin
	if((MEM_RegWrite) && (MEM_Rd != 0) && (MEM_Rd == EX_Rs)) 
		Forward_A = 2'd1;
	else if((WB_RegWrite) && (WB_Rd != 0) && (~((MEM_RegWrite) && (MEM_Rd != 0) && (MEM_Rd == EX_Rs))) && (WB_Rd == EX_Rs)) 
		Forward_A = 2'd2;
	else 
		Forward_A = 2'd0;
		
	if((MEM_RegWrite) && (MEM_Rd != 0) && (MEM_Rd == EX_Rt)) 
		Forward_B = 2'd1;
	else if((WB_RegWrite) && (WB_Rd != 0) && (~((MEM_RegWrite) && (MEM_Rd != 0) && (MEM_Rd == EX_Rt))) && (WB_Rd == EX_Rt)) 
		Forward_B = 2'd2;
	else 
		Forward_B = 2'd0;
end


endmodule	
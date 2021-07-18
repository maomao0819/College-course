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
module HazardDetection(
	EX_MemRead,
	EX_Rt,
	ID_Rs,
	ID_Rt,
	PC_Src,
	PC_Write,
	IF_ID_Write,
	IF_Flush,
	ID_Flush,
	EX_Flush
    );
input			EX_MemRead;
input	[4:0]	EX_Rt;
input	[4:0]	ID_Rs;
input	[4:0]	ID_Rt;
input			PC_Src;
output			PC_Write;
output			IF_ID_Write;
output			IF_Flush;
output			ID_Flush;
output			EX_Flush;

reg	  			PC_Write;
reg	  			IF_ID_Write;
reg	  			IF_Flush;
reg	   			ID_Flush;
reg	     		EX_Flush;

always@( * )begin
	PC_Write = 1'd1;
	IF_ID_Write = 1'd1;
	IF_Flush = 1'd0;
	ID_Flush = 1'd0;
	EX_Flush = 1'd0;
	if((EX_MemRead) && ((EX_Rt == ID_Rs) || (EX_Rt == ID_Rt))) 
	begin
		PC_Write = 1'd0;
		IF_ID_Write = 1'd0;
		ID_Flush = 1'd1;
	end 
	else 
	begin
		PC_Write = 1'd1;
		IF_ID_Write = 1'd1;
		ID_Flush = 1'd0;
	end
	if(PC_Src)
	begin
		IF_Flush = 1'd1;
		ID_Flush = 1'd1;
		EX_Flush = 1'd1;
	end
end


endmodule	
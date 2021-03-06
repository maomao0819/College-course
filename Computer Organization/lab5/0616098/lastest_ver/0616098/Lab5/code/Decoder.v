//0616098
//Subject:     CO project 4 - Decoder
//--------------------------------------------------------------------------------
//Version:     1
//--------------------------------------------------------------------------------
//Writer:      黃秉茂
//----------------------------------------------
//Date:        6/27
//----------------------------------------------
//Description: 
//--------------------------------------------------------------------------------

module Decoder(
	instr_op_i,
    Branch,
	MemToReg,
	MemRead,
	MemWrite,
	ALUOp,
	ALUSrc,
	RegWrite,
	RegDest,
	BranchType
	);
     
//I/O ports
input  [5:0] 	instr_op_i;

output         	Branch;
output			MemToReg;
output			MemRead;
output			MemWrite;
output 	[2:0]	ALUOp;
output         	ALUSrc;
output         	RegWrite;
output	     	RegDest; 
output	[1:0]	BranchType;

assign Branch = ((~instr_op_i[5]) & (~instr_op_i[4]) & (~instr_op_i[3]) & (instr_op_i[2]) & (~instr_op_i[1]) & (~instr_op_i[0])) | ((~instr_op_i[5]) & (~instr_op_i[4]) & (~instr_op_i[3]) & (instr_op_i[2]) & (~instr_op_i[1]) & (instr_op_i[0])) | ((~instr_op_i[5]) & (~instr_op_i[4]) & (~instr_op_i[3]) & (~instr_op_i[2]) & (~instr_op_i[1]) & (instr_op_i[0])) | ((~instr_op_i[5]) & (~instr_op_i[4]) & (~instr_op_i[3]) & (instr_op_i[2]) & (instr_op_i[1]) & (instr_op_i[0]));
assign MemToReg = ~((instr_op_i[5]) & (~instr_op_i[4]) & (~instr_op_i[3]) & (~instr_op_i[2]) & (instr_op_i[1]) & (instr_op_i[0]));
assign MemRead = (instr_op_i[5]) & (~instr_op_i[4]) & (~instr_op_i[3]) & (~instr_op_i[2]) & (instr_op_i[1]) & (instr_op_i[0]);
assign MemWrite = (instr_op_i[5]) & (~instr_op_i[4]) & (instr_op_i[3]) & (~instr_op_i[2]) & (instr_op_i[1]) & (instr_op_i[0]);
assign ALUOp[2] = ((~instr_op_i[5]) & (~instr_op_i[4]) & (~instr_op_i[3]) & (~instr_op_i[2]) & (instr_op_i[1]) & (~instr_op_i[0])) | ((~instr_op_i[5]) & (~instr_op_i[4]) & (~instr_op_i[3]) & (~instr_op_i[2]) & (instr_op_i[1]) & (instr_op_i[0])) | ((~instr_op_i[5]) & (~instr_op_i[4]) & (instr_op_i[3]) & (~instr_op_i[2]) & (instr_op_i[1]) & (~instr_op_i[0]));
assign ALUOp[1] = ((~instr_op_i[5]) & (~instr_op_i[4]) & (instr_op_i[3]) & (~instr_op_i[2]) & (~instr_op_i[1]) & (~instr_op_i[0])) | ((~instr_op_i[5]) & (~instr_op_i[4]) & (~instr_op_i[3]) & (instr_op_i[2]) & (~instr_op_i[1]) & (~instr_op_i[0])) | ((~instr_op_i[5]) & (~instr_op_i[4]) & (~instr_op_i[3]) & (instr_op_i[2]) & (~instr_op_i[1]) & (instr_op_i[0])) | ((~instr_op_i[5]) & (~instr_op_i[4]) & (~instr_op_i[3]) & (~instr_op_i[2]) & (~instr_op_i[1]) & (instr_op_i[0])) | ((~instr_op_i[5]) & (~instr_op_i[4]) & (~instr_op_i[3]) & (instr_op_i[2]) & (instr_op_i[1]) & (instr_op_i[0]));
assign ALUOp[0] = ~(((~instr_op_i[5]) & (~instr_op_i[4]) & (~instr_op_i[3]) & (~instr_op_i[2]) & (~instr_op_i[1]) & (~instr_op_i[0])) | ((~instr_op_i[5]) & (~instr_op_i[4]) & (instr_op_i[3]) & (~instr_op_i[2]) & (instr_op_i[1]) & (~instr_op_i[0])) | ((~instr_op_i[5]) & (~instr_op_i[4]) & (~instr_op_i[3]) & (instr_op_i[2]) & (~instr_op_i[1]) & (~instr_op_i[0])) | ((~instr_op_i[5]) & (~instr_op_i[4]) & (~instr_op_i[3]) & (instr_op_i[2]) & (~instr_op_i[1]) & (instr_op_i[0])) | ((~instr_op_i[5]) & (~instr_op_i[4]) & (~instr_op_i[3]) & (~instr_op_i[2]) & (~instr_op_i[1]) & (instr_op_i[0])) | ((~instr_op_i[5]) & (~instr_op_i[4]) & (~instr_op_i[3]) & (instr_op_i[2]) & (instr_op_i[1]) & (instr_op_i[0])));
assign ALUSrc = ((instr_op_i[5]) & (~instr_op_i[4]) & (~instr_op_i[3]) & (~instr_op_i[2]) & (instr_op_i[1]) & (instr_op_i[0])) | ((instr_op_i[5]) & (~instr_op_i[4]) & (instr_op_i[3]) & (~instr_op_i[2]) & (instr_op_i[1]) & (instr_op_i[0])) | ((~instr_op_i[5]) & (~instr_op_i[4]) & (instr_op_i[3]) & (~instr_op_i[2]) & (~instr_op_i[1]) & (~instr_op_i[0])) | ((~instr_op_i[5]) & (~instr_op_i[4]) & (instr_op_i[3]) & (~instr_op_i[2]) & (instr_op_i[1]) & (~instr_op_i[0]));
assign RegWrite = ~(((instr_op_i[5]) & (~instr_op_i[4]) & (instr_op_i[3]) & (~instr_op_i[2]) & (instr_op_i[1]) & (instr_op_i[0])) | ((~instr_op_i[5]) & (~instr_op_i[4]) & (~instr_op_i[3]) & (~instr_op_i[2]) & (instr_op_i[1]) & (~instr_op_i[0])) |  ((~instr_op_i[5]) & (~instr_op_i[4]) & (~instr_op_i[3]) & (instr_op_i[2]) & (~instr_op_i[1]) & (~instr_op_i[0])) | ((~instr_op_i[5]) & (~instr_op_i[4]) & (~instr_op_i[3]) & (instr_op_i[2]) & (~instr_op_i[1]) & (instr_op_i[0])) | ((~instr_op_i[5]) & (~instr_op_i[4]) & (~instr_op_i[3]) & (~instr_op_i[2]) & (~instr_op_i[1]) & (instr_op_i[0])) | ((~instr_op_i[5]) & (~instr_op_i[4]) & (~instr_op_i[3]) & (instr_op_i[2]) & (instr_op_i[1]) & (instr_op_i[0])));
assign RegDest = (~instr_op_i[5]) & (~instr_op_i[4]) & (~instr_op_i[3]) & (~instr_op_i[2]) & (~instr_op_i[1]) & (~instr_op_i[0]);
assign BranchType[1] = ((~instr_op_i[5]) & (~instr_op_i[4]) & (~instr_op_i[3]) & (instr_op_i[2]) & (~instr_op_i[1]) & (instr_op_i[0])) | ((~instr_op_i[5]) & (~instr_op_i[4]) & (~instr_op_i[3]) & (~instr_op_i[2]) & (~instr_op_i[1]) & (instr_op_i[0]));
assign BranchType[0] = ((~instr_op_i[5]) & (~instr_op_i[4]) & (~instr_op_i[3]) & (instr_op_i[2]) & (~instr_op_i[1]) & (instr_op_i[0])) | ((~instr_op_i[5]) & (~instr_op_i[4]) & (~instr_op_i[3]) & (instr_op_i[2]) & (instr_op_i[1]) & (instr_op_i[0]));

endmodule
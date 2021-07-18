//0616098
//Subject:     CO project 2 - Decoder
//--------------------------------------------------------------------------------
//Version:     1
//--------------------------------------------------------------------------------
//Writer:      黃秉茂
//----------------------------------------------
//Date:        5/29
//----------------------------------------------
//Description: 
//--------------------------------------------------------------------------------

module Decoder(
    instr_op_i,
	RegWrite_o,
	ALU_op_o,
	ALUSrc_o,
	RegDst_o,
	Branch_o,
	Jump_o,
	MemRead_o,
	MemWrite_o,
	MemtoReg_o
	);
     
//I/O ports
input  [6-1:0] instr_op_i;

output         RegWrite_o;
output [3-1:0] ALU_op_o;
output         ALUSrc_o;
output [2-1:0] RegDst_o;
output         Branch_o;
output         Jump_o;
output 		   MemRead_o;
output		   MemWrite_o;
output [2-1:0] MemtoReg_o; 
//Internal Signals
reg    [3-1:0] ALU_op_o;
reg            ALUSrc_o;
reg            RegWrite_o;
reg    [2-1:0] RegDst_o;
reg            Branch_o;
reg	           Jump_o;
reg 		   MemRead_o;
reg			   MemWrite_o;
reg	   [2-1:0] MemtoReg_o;
//Parameter


//Main function
always @ ( * ) begin
    case (instr_op_i)
        6'b000000:      //R_type
        begin
            ALU_op_o = 3'd0;
            ALUSrc_o = 1'b0;
            RegWrite_o = 1'b1;
            RegDst_o = 2'b01;        //write to rd
            Branch_o = 1'b0;
            Jump_o = 1'b0;
			MemRead_o = 1'b0;
			MemWrite_o = 1'b0;
			MemtoReg_o = 2'b00;
        end
        6'b001000:      //ADDI
        begin
            ALU_op_o = 3'd1;
            ALUSrc_o = 1'b1;
            RegWrite_o = 1'b1;
            RegDst_o = 2'b00;        //write to rt
            Branch_o = 1'b0;
            Jump_o = 1'b0;
			MemRead_o = 1'b0;
			MemWrite_o = 1'b0;
			MemtoReg_o = 2'b00;
        end
        6'b001010:      //SLTi
        begin
            ALU_op_o = 3'd2;
            ALUSrc_o = 1'b1;        //not used
            RegWrite_o = 1'b1;
            RegDst_o = 2'b00;        //write to rt
            Branch_o = 1'b0;
            Jump_o = 1'b0;
			MemRead_o = 1'b0;
			MemWrite_o = 1'b0;
			MemtoReg_o = 2'b00;
        end
        6'b000100:      //BEQ
        begin
            ALU_op_o = 3'd3;
            ALUSrc_o = 1'b0;        //RD
            RegWrite_o = 1'b0;
            RegDst_o = 2'b00;        //write to rt
            Branch_o = 1'b1;
            Jump_o = 1'b0;
			MemRead_o = 1'b0;
			MemWrite_o = 1'b0;
			MemtoReg_o = 2'b00;
        end
        6'b100011:      //lw
        begin
            ALU_op_o = 3'd4;		//add
            ALUSrc_o = 1'b1;        //im
            RegWrite_o = 1'b1;		//write back
            RegDst_o = 2'b00;        //not used
            Branch_o = 1'b0;
            Jump_o = 1'b0;
			MemRead_o = 1'b1;
			MemWrite_o = 1'b0;
			MemtoReg_o = 2'b01;
        end
        6'b101011:      //sw
        begin
            ALU_op_o = 3'd4;		//add
            ALUSrc_o = 1'b1;        //im
            RegWrite_o = 1'b0;		//no write back
            RegDst_o = 2'b00;        //not used
            Branch_o = 1'b0;
            Jump_o = 1'b0;
			MemRead_o = 1'b0;
			MemWrite_o = 1'b1;
			MemtoReg_o = 2'b00;
        end
        6'b000010:      //jump
        begin
            ALU_op_o = 3'd4;		//not used
            ALUSrc_o = 1'b0;        //not used
            RegWrite_o = 1'b0;
            RegDst_o = 2'b00;        
            Branch_o = 1'b0;
            Jump_o = 1'b1;
			MemRead_o = 1'b0;
			MemWrite_o = 1'b0;
			MemtoReg_o = 2'b00;
        end
        6'b000011:      //jal
        begin
            ALU_op_o = 3'd4;		//not used
            ALUSrc_o = 1'b0;        //not used
            RegWrite_o = 1'b1;
            RegDst_o = 2'b10;        //write to rt
            Branch_o = 1'b0;
            Jump_o = 1'b1;
			MemRead_o = 1'b0;
			MemWrite_o = 1'b0;
			MemtoReg_o = 2'b11;
        end
    endcase
end

endmodule





                    
                    





                    
                    
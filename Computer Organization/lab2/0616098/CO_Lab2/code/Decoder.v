//0616098
//Subject:     CO project 2 - Decoder
//--------------------------------------------------------------------------------
//Version:     1
//--------------------------------------------------------------------------------
//Writer:      黃秉茂
//----------------------------------------------
//Date:        5/9
//----------------------------------------------
//Description: 
//--------------------------------------------------------------------------------

module Decoder(
    instr_op_i,
	RegWrite_o,
	ALU_op_o,
	ALUSrc_o,
	RegDst_o,
	Branch_o
	);
     
//I/O ports
input  [6-1:0] instr_op_i;

output         RegWrite_o;
output [3-1:0] ALU_op_o;
output         ALUSrc_o;
output         RegDst_o;
output         Branch_o;
 
//Internal Signals
reg    [3-1:0] ALU_op_o;
reg            ALUSrc_o;
reg            RegWrite_o;
reg            RegDst_o;
reg            Branch_o;

//Parameter


//Main function
always @ ( * ) begin
    case (instr_op_i)
        6'b000000:      //R_type
        begin
            ALU_op_o = 3'd0;
            ALUSrc_o = 1'b0;
            RegWrite_o = 1'b1;
            RegDst_o = 1'b1;        //write to rd
            Branch_o = 1'b0;
        end
        6'b001000:      //ADDI
        begin
            ALU_op_o = 3'd1;
            ALUSrc_o = 1'b1;
            RegWrite_o = 1'b1;
            RegDst_o = 1'b0;        //write to rt
            Branch_o = 1'b0;
        end
        6'b001010:      //SLTi
        begin
            ALU_op_o = 3'd2;
            ALUSrc_o = 1'b1;        //not used
            RegWrite_o = 1'b1;
            RegDst_o = 1'b0;        //write to rt
            Branch_o = 1'b0;
        end
        6'b000100:      //BEQ
        begin
            ALU_op_o = 3'd3;
            ALUSrc_o = 1'b0;        
            RegWrite_o = 1'b0;
            RegDst_o = 1'b0;        //write to rt
            Branch_o = 1'b1;
        end
    endcase
end

endmodule





                    
                    





                    
                    
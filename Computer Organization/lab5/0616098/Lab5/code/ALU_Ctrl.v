//0616098
//Subject:     CO project 4 - ALU Controller
//--------------------------------------------------------------------------------
//Version:     1
//--------------------------------------------------------------------------------
//Writer:      黃秉茂
//----------------------------------------------
//Date:        6/27
//----------------------------------------------
//Description: 
//--------------------------------------------------------------------------------

module ALU_Ctrl(
	funct_i,
	ALUOp_i,
	ALUCtrl_o
);
//I/O ports 
input      [6-1:0] funct_i;
input      [3-1:0] ALUOp_i;

output     [4-1:0] ALUCtrl_o;    
     
//Internal Signals
reg        [4-1:0] ALUCtrl_o;

//Parameter

//Select exact operation
always@(*)begin
	if(ALUOp_i == 3'd0)begin    //R_type
        case(funct_i)
            6'd32:      //ADD
                ALUCtrl_o = 4'b0010;
            6'd34:      //SUB
                ALUCtrl_o = 4'b0110;
            6'd36:      //AND
                ALUCtrl_o = 4'b0000;
            6'd37:      //OR
                ALUCtrl_o = 4'b0001;
            6'd42:      //SLT
                ALUCtrl_o = 4'b0111;
            6'd8:      //jr
                ALUCtrl_o = 4'b0000;	  //not used
            6'd24:      //OR
                ALUCtrl_o = 4'b1111;
            default: ALUCtrl_o = 4'd0;
        endcase
    end
    else begin      //non R-type
    	case (ALUOp_i)
		/*3'd1:
			ALUCtrl_o = 4'b0010;
		3'd2:
			ALUCtrl_o = 4'b0110;
		3'd3:
			ALUCtrl_o = 4'b0010;
		3'd4:
			ALUCtrl_o = 4'b0111;
		3'd5:
			ALUCtrl_o = 4'b0000;*/
		3'd1:       //ADDI
                ALUCtrl_o = 4'b0010;      //ALU add
        3'd2:       //SLTi
                ALUCtrl_o = 4'b0111;      //ALU SLTi
        3'd3:       //BEQ
                ALUCtrl_o = 4'b0110;      //ALU BEQ
        3'd4:		//LW, SW
            	ALUCtrl_o = 4'b0010;      //ALU add
        3'd4:       // andi
                ALUCtrl_o = 4'b0000; 
        3'd5:       // ori
                ALUCtrl_o = 4'b0001;
		endcase
	end
end


endmodule
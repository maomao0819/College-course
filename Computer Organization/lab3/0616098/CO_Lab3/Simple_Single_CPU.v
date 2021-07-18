//Subject:     CO project 2 - Simple Single CPU
//--------------------------------------------------------------------------------
//Version:     1
//--------------------------------------------------------------------------------
//Writer:      
//----------------------------------------------
//Date:        
//----------------------------------------------
//Description: 
//--------------------------------------------------------------------------------
module Simple_Single_CPU(
        clk_i,
		rst_i
		);
		
//I/O port
input         clk_i;
input         rst_i;

//Internal Signles
wire [32-1:0] pc_out;
wire [32-1:0] pc_in;
wire [32-1:0] adder_pc_add_4_out;
wire [32-1:0] adder2_out;
wire [32-1:0] left_shifter_out;

wire [32-1:0] instruction;

wire          RegWrite;
wire [3-1:0]  ALUOp;
wire          ALUSrc;
wire [2-1:0]  RegDst;
wire          Branch;
wire [4-1:0]  ALUCtrl;
wire          Zero;

wire          JumpReg;

wire [5-1:0]  Mux_Write_Reg_out;
wire [32-1:0] Mux_out_Write_Data;
wire [32-1:0] RSdata_o;
wire [32-1:0] reg_data2_i;
wire [32-1:0] data2;
wire [32-1:0] PCSource_out;

wire [32-1:0] data_extended;
wire [32-1:0] alu_result;

wire 		  Jump;
wire		  MemRead;
wire		  MemWrite;
wire [2-1:0]  MemtoReg;
wire [32-1:0] Data_Memory_out;
//Greate componentes
ProgramCounter PC(
        .clk_i(clk_i),
        .rst_i(rst_i),
        .pc_in_i(pc_in),
        .pc_out_o(pc_out)
        );
	
Adder Adder1(
        .src1_i(32'd4),
        .src2_i(pc_out),
        .sum_o(adder_pc_add_4_out)
        );
	
Instr_Memory IM(
        .pc_addr_i(pc_out),
        .instr_o(instruction)
        );

MUX_4to1 #(.size(5)) Mux_Write_Reg(
        .data0_i(instruction[20:16]),
        .data1_i(instruction[15:11]),
        .data2_i(5'd31),
        .data3_i(5'd31),
        .select_i(RegDst),
        .data_o(Mux_Write_Reg_out)
        );	
		
Reg_File Registers(
        .clk_i(clk_i),
        .rst_i(rst_i),
        .RSaddr_i(instruction[25:21]),
        .RTaddr_i(instruction[20:16]),
        .RDaddr_i(Mux_Write_Reg_out),
        .RDdata_i(Mux_out_Write_Data),
        .RegWrite_i( RegWrite & (Mux_Write_Reg_out != 0)),
        .RSdata_o(RSdata_o),
        .RTdata_o(reg_data2_i)   
        );
	
Decoder Decoder(
        .instr_op_i(instruction[31:26]),
        .RegWrite_o(RegWrite),
        .ALU_op_o(ALUOp),
        .ALUSrc_o(ALUSrc),
        .RegDst_o(RegDst),
        .Branch_o(Branch),
        .Jump_o(Jump),
        .MemRead_o(MemRead),
        .MemWrite_o(MemWrite),
        .MemtoReg_o(MemtoReg)  
	    );

ALU_Ctrl AC(
        .funct_i(instruction[5:0]),
        .ALUOp_i(ALUOp),
        .ALUCtrl_o(ALUCtrl),
        .JumpReg_o(JumpReg)
        );
	
Sign_Extend SE(
        .data_i(instruction[15:0]),
        .data_o(data_extended)
        );

MUX_2to1 #(.size(32)) Mux_ALUSrc(
        .data0_i(reg_data2_i),
        .data1_i(data_extended),
        .select_i(ALUSrc),
        .data_o(data2)
        );	
		
ALU ALU(
        .src1_i(RSdata_o),
        .src2_i(data2),
        .ctrl_i(ALUCtrl),
        .result_o(alu_result),
        .zero_o(Zero)
	    );
	
Data_Memory Data_Memory(
	.clk_i(clk_i),
    .addr_i(alu_result),
    .data_i(reg_data2_i),
    .MemRead_i(MemRead),
    .MemWrite_i(MemWrite),
    .data_o(Data_Memory_out)
	);
	
Adder Adder2(
        .src1_i(adder_pc_add_4_out),
        .src2_i(left_shifter_out),
        .sum_o(adder2_out)      
	    );
		
Shift_Left_Two_32 Shifter(
        .data_i(data_extended),
        .data_o(left_shifter_out)
        ); 		
		
MUX_2to1 #(.size(32)) Mux_PC_Source(
        .data0_i(adder_pc_add_4_out),
        .data1_i(adder2_out),
        .select_i(Branch && Zero),
        .data_o(PCSource_out)
        );	
MUX_4to1 #(.size(32)) Mux_out_pc_in(
        .data0_i(PCSource_out),
        .data1_i({adder_pc_add_4_out[31:28],instruction[26-1:0], 2'b0}),
        .data2_i(RSdata_o),
        .data3_i(RSdata_o),
        .select_i({JumpReg, Jump}),
        .data_o(pc_in)
        );
MUX_4to1 #(.size(32)) Mux_Write_Data(
        .data0_i(alu_result),
        .data1_i(Data_Memory_out),
        .data2_i(data_extended),
        .data3_i(adder_pc_add_4_out),
        .select_i(MemtoReg),
        .data_o(Mux_out_Write_Data)
        );
endmodule
		  



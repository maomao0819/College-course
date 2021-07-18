//0616098
//Subject:     CO project 2 - Simple Single CPU
//--------------------------------------------------------------------------------
//Version:     1
//--------------------------------------------------------------------------------
//Writer:      黃秉茂
//----------------------------------------------
//Date:        5/9
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
wire [32-1:0] Mux_adder_out;
wire [32-1:0] adder1_out;
wire [32-1:0] adder2_out;
wire [32-1:0] left_shifter_out;

wire [32-1:0] instruction;

wire          RegWrite;
wire [3-1:0]  ALUOp;
wire          ALUSrc;
wire          RegDst;
wire          Branch;
wire [4-1:0]  ALUCtrl;
wire          Zero;

wire [5-1:0]  Mux_Write_Reg_out;
wire [32-1:0] RSdata_o;
wire [32-1:0] reg_data2_i;
wire [32-1:0] data2;

wire [32-1:0] data_extended;
wire [32-1:0] alu_result;

//Greate componentes
ProgramCounter PC(
        .clk_i(clk_i),
        .rst_i(rst_i),
        .pc_in_i(Mux_adder_out),
        .pc_out_o(pc_out)
        );

Adder Adder1(
        .src1_i(32'd4),
        .src2_i(pc_out),
        .sum_o(adder1_out)
        );

Instr_Memory IM(
        .pc_addr_i(pc_out),
        .instr_o(instruction)
        );

MUX_2to1 #(.size(5)) Mux_Write_Reg(
        .data0_i(instruction[20:16]),
        .data1_i(instruction[15:11]),
        .select_i(RegDst),
        .data_o(Mux_Write_Reg_out)
        );

Reg_File RF(
        .clk_i(clk_i),
        .rst_i(rst_i),
        .RSaddr_i(instruction[25:21]),
        .RTaddr_i(instruction[20:16]),
        .RDaddr_i(Mux_Write_Reg_out),
        .RDdata_i(alu_result),
        .RegWrite_i(RegWrite),
        .RSdata_o(RSdata_o),
        .RTdata_o(reg_data2_i)
        );

Decoder Decoder(
        .instr_op_i(instruction[31:26]),
        .RegWrite_o(RegWrite),
        .ALU_op_o(ALUOp),
        .ALUSrc_o(ALUSrc),
        .RegDst_o(RegDst),
        .Branch_o(Branch)
        );

ALU_Ctrl AC(
        .funct_i(instruction[5:0]),
        .ALUOp_i(ALUOp),
        .ALUCtrl_o(ALUCtrl)
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

Adder Adder2(
        .src1_i(adder1_out),
        .src2_i(left_shifter_out),
        .sum_o(adder2_out)
        );

Shift_Left_Two_32 Shifter(
        .data_i(data_extended),
        .data_o(left_shifter_out)
        );

MUX_2to1 #(.size(32)) Mux_PC_Source(
        .data0_i(adder1_out),
        .data1_i(adder2_out),
        .select_i(Branch && Zero),
        .data_o(Mux_adder_out)
        );

endmodule

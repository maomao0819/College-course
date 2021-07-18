//0616098
`timescale 1ns / 1ps
//Subject:     CO project 4 - Instruction Memory
//--------------------------------------------------------------------------------
//Version:     1
//--------------------------------------------------------------------------------
//Writer:      黃秉茂
//----------------------------------------------
//Date:        6/27
//----------------------------------------------
//Description: 
//--------------------------------------------------------------------------------
module Instruction_Memory(
    addr_i,
    instr_o
    );

// Interface
input   [31:0]  addr_i;
output  [31:0]  instr_o;

// Instruction File
reg     [31:0]  instruction_file    [0:15];

assign  instr_o = instruction_file[addr_i / 4];  

endmodule
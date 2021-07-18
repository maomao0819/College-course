module   Lab2_encoder_4bit_dataflow (output [1:0] Aout, output V, input [3:0] D);

assign V=D[0]|D[1]|D[2]|D[3];
assign Aout[1]=!(D[0]|D[1]);
assign Aout[0]=!(D[0]|((!D[1])&D[2]));
endmodule

module   Lab2_encoder_4bit_gate_level (output [1:0] Aout, output V, input [3:0] D);
wire w;

or(V,D[0],D[1],D[2],D[3]);
and(Aout[1],!D[0],!D[1]);
and(w,D[2],!D[1]);
and(Aout[0],!D[0],!w);
endmodule

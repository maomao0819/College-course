module Lab3_Mealy_structural(output z, input x, clock, reset);
	
wire JA, KA, JB, KB, A, B;

assign JA = B^x;
assign KA = ~x;
assign JB = ~A||x;
assign KB = ~A&&~x;
assign z = ~B&&~x;

JK_ff_AR
	G1(A, JA, KA, clock, reset),
	G2(B, JB, KB, clock, reset);

endmodule

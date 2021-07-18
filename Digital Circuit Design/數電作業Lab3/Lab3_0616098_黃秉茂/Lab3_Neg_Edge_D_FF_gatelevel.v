module Lab3_Neg_Edge_D_FF_gatelevel(output Q, NQ, input D, clock);

wire w1, R, S, w4;
nor
	#(2)G1(w1, w4, R),
	G2(R, w1, clock),
	G3(S, R, clock, w4),
	G4(w4, S, D);
	Lab3_SR_Latch_gatelevel
	G5(Q, NQ, S, R);
endmodule

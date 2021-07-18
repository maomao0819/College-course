module Lab3_SR_Latch_gatelevel(output Q, NQ, input S, R);

nor
	#(5)G1(Q, R, NQ),
	G2(NQ, S, Q);
endmodule

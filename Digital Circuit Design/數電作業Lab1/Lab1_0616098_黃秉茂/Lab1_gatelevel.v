module Lab1_gatelevel(F,A,B,C,D);

output 	F;
input 	A,B,C,D;
wire 	w1,w2,w3,w4,w5;

and	(w1,A,B);
and	(w2,C,!D);
or	(w3,w1,w2);
and	(w4,B,D);
or	(w5,!A,w4);
and	(F,w3,w5);

endmodule

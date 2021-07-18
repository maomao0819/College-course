module Lab1_gatelevel_UDP(F,A,B,C,D);

output F;
input A,B,C,D;
wire w1,w2,w3;

Lab1_UDP M3(w1,A,B,C,D);

and(w2,B,D);
or(w3,!A,w2);
and(F,w1,w3);

endmodule

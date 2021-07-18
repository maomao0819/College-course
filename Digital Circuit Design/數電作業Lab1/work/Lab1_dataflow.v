module  Lab1_gatelevel(F,A,B,C,D);
output F;

input A,B,C,D;

assign F=((A&&B)||(C&&!D))&&((B&&D)||!A);

endmodule

module Lab2_borrow_lookahead_sub (output [3:0] Diff, output Bout, input[3:0] X, Y, input Bin);
wire B1,B2,B3;
wire [3:0]P,G;

assign P[0]=X[0]^Y[0];
assign G[0]=!X[0]&Y[0];
assign Diff[0]=P[0]^Bin;
assign B1=G[0]|((!P[0])&Bin);
assign P[1]=X[1]^Y[1];
assign G[1]=X[1]&Y[1];
assign Diff[1]=P[1]^B1;
assign B2=G[1]|((!P[1])&B1);
assign P[2]=X[2]^Y[2];
assign G[2]=X[2]&Y[2];
assign Diff[2]=P[2]^B2;
assign B3=G[2]|((!P[2])&B2);
assign P[3]=X[3]^Y[3];
assign G[3]=X[3]&Y[3];
assign Diff[3]=P[3]^B3;
assign Bout=G[3]|((!P[3])&B3);

endmodule

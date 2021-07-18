module t_Lab1_gatelevel_UDP;

wire F;
reg A,B,C,D;

Lab1_gatelevel_UDP M2(F,A,B,C,D);

initial
	begin
	A=1'b0;B=1'b0;C=1'b0;D=1'b0;

	#150 A=1'b1;B=1'b1;C=1'b0;D=1'b0;
	end

	initial#300 $finish;
endmodule


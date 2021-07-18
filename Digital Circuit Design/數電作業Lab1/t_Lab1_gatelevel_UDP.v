module t_Lab1_gatelevel_UDP;

wire F;
reg A,B,C,D;

Lab1_gatelevel_UDP M3(F,A,B,C,D);

initial
	begin
		A =1'b0; B=1'b0; C=1'b0; D=1'b0;
		#50 A =1'b0; B=1'b0; C=1'b0; D=1'b1;
		#50 A =1'b0; B=1'b0; C=1'b1; D=1'b0;
		#50 A =1'b0; B=1'b0; C=1'b1; D=1'b1;
		#50 A =1'b0; B=1'b1; C=1'b0; D=1'b0;
		#50 A =1'b0; B=1'b1; C=1'b0; D=1'b1;
		#50 A =1'b0; B=1'b1; C=1'b1; D=1'b0;
		#50 A =1'b0; B=1'b1; C=1'b1; D=1'b1;
		#50 A =1'b1; B=1'b0; C=1'b0; D=1'b0;
		#50 A =1'b1; B=1'b0; C=1'b0; D=1'b1;
		#50 A =1'b1; B=1'b0; C=1'b1; D=1'b0;
		#50 A =1'b1; B=1'b0; C=1'b1; D=1'b1;
		#50 A =1'b1; B=1'b1; C=1'b0; D=1'b0;
		#50 A =1'b1; B=1'b1; C=1'b0; D=1'b1;
		#50 A =1'b1; B=1'b1; C=1'b1; D=1'b0;
		#50 A =1'b1; B=1'b1; C=1'b1; D=1'b1;
	end
initial #800 $finish;
endmodule


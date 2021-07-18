module t_Lab2_4_bit_sub;

wire [3:0] t_Diff;
wire t_Bout;
reg [3:0] t_X,t_Y;
reg t_Bin;

Lab2_ripple_borrow_4_bit_sub RBS(t_Diff,t_Bout,t_X,t_Y,t_Bin);
//Lab2_borrow_lookahead_sub BLS(t_Diff,t_Bout,t_X,t_Y,t_Bin);

initial 
	begin
	 	t_X=4'b1100;t_Y=4'b0101;t_Bin=1;
	#50	t_X=4'b1101;t_Y=4'b0110;t_Bin=0;
	#50	t_X=4'b0101;t_Y=4'b1101;t_Bin=0;
	#50	t_X=4'b0110;t_Y=4'b1101;t_Bin=1;
	#50	t_X=4'b1001;t_Y=4'b1001;t_Bin=0;
	#50	t_X=4'b0101;t_Y=4'b0101;t_Bin=1;
	end
initial #300 $finish;
endmodule

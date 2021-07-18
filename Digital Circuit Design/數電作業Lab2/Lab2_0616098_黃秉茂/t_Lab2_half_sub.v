module t_Lab2_half_sub;

wire t_BGL,t_BDF,t_BBH,t_DGL,t_DDF,t_DBH;
reg t_xGL,t_xDF,t_xBH,t_yGL,t_yDF,t_yBH;

Lab2_half_sub_gate_level t_HS0(t_DGL,t_BGL,t_xGL,t_yGL);

initial 
	begin 
		t_xGL=1'b0;t_yGL=1'b0;
	#50	t_xGL=1'b0;t_yGL=1'b1;
	#50	t_xGL=1'b1;t_yGL=1'b0;
	#50	t_xGL=1'b1;t_yGL=1'b1;
	end

Lab2_half_sub_dataflow t_HS1(t_DDF,t_BDF,t_xDF,t_yDF);

initial 
	begin 
		t_xDF=1'b0;t_yDF=1'b0;
	#50	t_xDF=1'b0;t_yDF=1'b1;
	#50	t_xDF=1'b1;t_yDF=1'b0;
	#50	t_xDF=1'b1;t_yDF=1'b1;
	end

Lab2_half_sub_behavior t_HS2(t_DBH,t_BBH,t_xBH,t_yBH);

initial 
	begin 
		t_xBH=1'b0;t_yBH=1'b0;
	#50	t_xBH=1'b0;t_yBH=1'b1;
	#50	t_xBH=1'b1;t_yBH=1'b0;
	#50	t_xBH=1'b1;t_yBH=1'b1;
	end
initial #200 $finish;
endmodule


module t_Lab2_encoder_4bit;

wire [1:0] t_AoutGL,t_AoutDF,t_AoutBH;
wire t_VGL,t_VDF,t_VBH;
reg [3:0]t_DGL,t_DDF,t_DBH;

Lab2_encoder_4bit_gate_level t_E4GL(t_AoutGL,t_VGL,t_DGL);

initial 
	begin
	 	t_DGL=4'b0000;
		repeat(15)
		#50 t_DGL=t_DGL+4'b0001;
	end

Lab2_encoder_4bit_dataflow t_E4DF(t_AoutDF,t_VDF,t_DDF);

initial 
	begin
 		t_DDF=4'b0000;
		repeat(15)
		#50 t_DDF=t_DDF+4'b0001;
	end

Lab2_encoder_4bit_behavior t_E4BH(t_AoutBH,t_VBH,t_DBH);

initial 
	begin
 		t_DBH=4'b0000;
		repeat(15)
		#50 t_DBH=t_DBH+4'b0001;
	end
initial #800 $finish;

endmodule

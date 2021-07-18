module	t_Lab3_SR_Latch_gatelevel;
	
wire Q, NQ;
reg S, R;	
	
Lab3_SR_Latch_gatelevel	SR1(Q, NQ, S, R);	

initial	begin
	S=1'b1; R=1'b0;
	#10 S=1'b0; R=1'b0;
	#10 S=1'b0; R=1'b1;
	#10 S=1'b0; R=1'b0;
	#10 S=1'b0; R=1'b0;
	#10 S=1'b1; R=1'b1;
	#10 S=1'b0; R=1'b0;
end
initial #70 $finish;

endmodule

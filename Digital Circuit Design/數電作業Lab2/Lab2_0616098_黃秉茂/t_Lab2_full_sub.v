module t_Lab2_full_sub;

wire t_B,t_D;
reg t_x,t_y,t_z;

Lab2_full_sub t_FS(t_D,t_B,t_x,t_y,t_z);

initial 
	begin 
		t_x=1'b0;t_y=1'b0;t_z=1'b0;
	#50	t_x=1'b0;t_y=1'b0;t_z=1'b1;
	#50	t_x=1'b0;t_y=1'b1;t_z=1'b0;
	#50	t_x=1'b0;t_y=1'b1;t_z=1'b1;
	#50	t_x=1'b1;t_y=1'b0;t_z=1'b0;
	#50	t_x=1'b1;t_y=1'b0;t_z=1'b1;
	#50	t_x=1'b1;t_y=1'b1;t_z=1'b0;
	#50	t_x=1'b1;t_y=1'b1;t_z=1'b1;
	end
initial #400 $finish;

endmodule


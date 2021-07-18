module t_Lab3_Mealy;
	
wire z;
reg x, clock, reset;

Lab3_Mealy_state_diagram M1(z, x, clock, reset);
Lab3_Mealy_structural M2(z, x, clock, reset);
	
initial begin
	clock=0;
	forever #10 clock=~clock;
end

initial fork
	reset=0;
	#2 reset=1;
	#182 reset=0;
	#184 reset=1;
join

initial begin
	x=0;
	#15 x=1;
	#20 x=0;
	#20 x=1;
	#20 x=1;
	#20 x=0;
	#20 x=0;
	#20 x=0;
	#20 x=1;
	#2 x=0;
	#2 x=1;
	#2 x=0;
	#2 x=1;
	#11 x=0;
end

initial #190 $finish;

endmodule

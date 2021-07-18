module Lab3_Mealy_state_diagram(output reg z, input x, clock, reset);
	
reg[1:0] now, next;
parameter S0=2'b00, S1=2'b01, S2=2'b10, S3=2'b11;

always@(posedge clock, negedge reset)
	if (reset == 0) 
		now <= S0;
	else 
		now <= next;

always@(now, x)
	case (now)
		S0: if(x) next = S3; else next = S1;
		S1: if(x) next = S1; else next = S2;
		S2: if(x) next = S3; else next = S0;
		S3: if(x) next = S3; else next = S1;
	endcase

always@(now, x)
	case (now)
		S1, S3: z = 0;
		S0, S2: z = ~x;
	endcase
endmodule

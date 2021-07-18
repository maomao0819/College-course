module JK_ff_AR (output reg Q, input J, K, clock, reset);
	
always@(posedge clock, negedge reset)
	if (reset == 0) 
		Q = 1'b0;
	else 
		begin
			case({J, K})
				2'b00: Q <= Q;
				2'b01: Q <= 1'b0;
				2'b10: Q <= 1'b1;
				2'b11: Q <= ~Q;
			endcase
		end
endmodule

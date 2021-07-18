module Lab2_half_sub_gate_level(output D,B, input x,y);
	
	and (B,!x,y);
	xor (D,x,y);
endmodule

module   Lab2_encoder_4bit_behavior (output reg[1:0] Aout, output reg V, input [3:0] D);

always @(D[0],D[1],D[2],D[3])
if(D[0]==1)	
	begin
		Aout[0]=0;Aout[1]=0;
	end
else if(D[1]==1)	
	begin
		Aout[0]=1;Aout[1]=0;
	end
else if(D[2]==1)	
	begin
		Aout[0]=0;Aout[1]=1;
	end
else if(D[3]==1)	
	begin
		Aout[0]=1;Aout[1]=1;
	end
always @(D[0],D[1],D[2],D[3])
if(D[0]==0 && D[1]==0 && D[2]==0 && D[3]==0)	
	V=0;
else
	V=1;
endmodule

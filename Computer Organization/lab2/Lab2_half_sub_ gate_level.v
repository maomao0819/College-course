module Lab2_half_sub_ gate_level(output D,B, input x,y);


output D,B;
input x,y;
wire x_not;

not(x_not,x);

xor(D,x,y);

and(B,x_not,y);
endmodule




module Lab2_full_sub(output D,B, input x,y,z);

wire w1,w2,w3;

Lab2_half_sub_dataflow HS1(w1,w2,x,y);
Lab2_half_sub_dataflow HS2(D,w3,w1,z);
or (B,w2,w3);
endmodule

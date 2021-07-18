//0616098
//Subject:     CO project 2 - MUX 221
//--------------------------------------------------------------------------------
//Version:     1
//--------------------------------------------------------------------------------
//Writer:      黃秉茂
//----------------------------------------------
//Date:        6/26
//----------------------------------------------
//Description: 
//--------------------------------------------------------------------------------
     
module MUX_3to1(
               data0_i,
               data1_i,
			   data2_i,
               select_i,
               data_o
               );	   
			
parameter size = 0;	
			
//I/O ports               
input	[size-1:0]   data0_i;          
input	[size-1:0]   data1_i;
input	[size-1:0]   data2_i;
input   [1:0]		 select_i;

output	[size-1:0]   data_o; 
reg  	[size-1:0]   data_o;

always@( * )
begin
	case (select_i)
		2'b00:
			data_o = data0_i;
		2'b01:
			data_o = data1_i;
		2'b10:
			data_o = data2_i;
	endcase 
end

endmodule
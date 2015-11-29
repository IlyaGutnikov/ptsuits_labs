// Copyright (C) 1991-2015 Altera Corporation. All rights reserved.
// Your use of Altera Corporation's design tools, logic functions 
// and other software and tools, and its AMPP partner logic 
// functions, and any output files from any of the foregoing 
// (including device programming or simulation files), and any 
// associated documentation or information are expressly subject 
// to the terms and conditions of the Altera Program License 
// Subscription Agreement, the Altera Quartus II License Agreement,
// the Altera MegaCore Function License Agreement, or other 
// applicable license agreement, including, without limitation, 
// that your use is for the sole purpose of programming logic 
// devices manufactured by Altera and sold by Altera or its 
// authorized distributors.  Please refer to the applicable 
// agreement for further details.

// *****************************************************************************
// This file contains a Verilog test bench template that is freely editable to  
// suit user's needs .Comments are provided in each section to help the user    
// fill out necessary details.                                                  
// *****************************************************************************
// Generated on "11/22/2015 17:38:10"
                                                                                
// Verilog Test Bench template for design : avalon_pwm
// 
// Simulation tool : ModelSim-Altera (Verilog)
// 

`timescale 1 ps/ 1 ps
module avalon_pwm_vlg_tst();
// constants                                           
// general purpose registers
reg eachvec;
// test vector input registers
reg addr;
reg clk;
reg clr_n;
reg cs;
reg [31:0] dither;
reg [31:0] wr_data;
reg wr_n;
// wires                                               
wire [7:0]  pwm_out;
wire [31:0]  rd_data;

// assign statements (if any)                          
avalon_pwm i1 (
// port map - connection between master ports and signals/registers   
	.addr(addr),
	.clk(clk),
	.clr_n(clr_n),
	.cs(cs),
	.dither(dither),
	.pwm_out(pwm_out),
	.rd_data(rd_data),
	.wr_data(wr_data),
	.wr_n(wr_n)
);

initial                                                
begin 
	clk = 0;
	forever #10 clk = ~clk;
end

initial                                                
begin                                                  
// code that executes only once                        
// insert code here --> begin                          
	cs = 0;
	wr_n = 0;
	addr = 0;
	wr_data = 0;
	dither = 0;
	wr_data = 0;

	#10 clr_n = 0;
	#10 clr_n = 1;
	
	wr_data = 16;
	addr = 0; //0 - div
	#20 cs = 1;
	#20 cs = 0;	

	wr_data = 8;
	addr = 1; //1 - duty
	#20 cs = 1;
	#20 cs = 0;
	#20 wr_n = 1;
	
end                                                 
endmodule


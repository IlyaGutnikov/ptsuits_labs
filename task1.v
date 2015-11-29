module avalon_pwm
(
	clk, wr_data, dither, cs, wr_n, addr, clr_n, rd_data, pwm_out
);

	input clk;
	input [31:0] wr_data;
	input [31:0] dither;
	input cs;
	input wr_n;
	input addr;
	input clr_n;
	output [31:0] rd_data;
	output [7:0] pwm_out;

	/////////////////////////////////////////////////////////////////////
	// Registers and wires
	
	reg [31:0]	div;
	reg [31:0]	duty;
	reg [31:0] counter;
	reg [31:0] counter2;
	reg off;
	reg state;
	reg [31:0] rd_data;
	wire div_en, duty_en;

	/////////////////////////////////////////////////////////////////////
	// Avalon slave interface
	
	//chip select and address decoder
	assign div_en = cs & !wr_n & !addr ;
	assign duty_en = cs & !wr_n & addr ;

	//register write
	always @(posedge clk or negedge clr_n)
	begin
		if (clr_n == 0)
		begin
			div <= 0;
			duty <= 0;
		end
		else
		begin
			if (div_en)	div <= wr_data;
			if (duty_en) duty <= wr_data;
		end		
	end

	//register read
	always @(*)
	begin
		if (addr == 0)
			rd_data = div;
		else
			rd_data = duty;
	end
	
	/////////////////////////////////////////////////////////////////////
	// PWM logic
	
	//PWM counter
	always @(posedge clk or negedge clr_n)
	begin
		if (clr_n == 0)
			counter <= 0;
		else
			if (counter >= div)
				counter <= 0;
			else	
				counter <= counter + 1;
	end
	
	//PWM compare
	always @(posedge clk or negedge clr_n)
	begin
		if (clr_n == 0) begin
			off <= 0;
			state <= 1;
				end
		else
			if (counter >= duty)
					if ((clk == 1)&&(state == 1)) begin 
						off <= 0;
						state <= 0;	
					end
					else begin
						off <= 1;
						state <= 1;
					end
			else
				off <= 1;

	end

	assign pwm_out = {8{!off}};
	
endmodule

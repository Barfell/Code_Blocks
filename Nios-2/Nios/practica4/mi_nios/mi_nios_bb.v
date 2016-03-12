
module mi_nios (
	clk_clk,
	flash_dclk,
	flash_sce,
	flash_sdo,
	flash_data0,
	led_export,
	reset_reset_n,
	sdram_addr,
	sdram_ba,
	sdram_cas_n,
	sdram_cke,
	sdram_cs_n,
	sdram_dq,
	sdram_dqm,
	sdram_ras_n,
	sdram_we_n,
	sdram_clk_clk,
	sw_export);	

	input		clk_clk;
	output		flash_dclk;
	output		flash_sce;
	output		flash_sdo;
	input		flash_data0;
	output	[7:0]	led_export;
	input		reset_reset_n;
	output	[11:0]	sdram_addr;
	output	[1:0]	sdram_ba;
	output		sdram_cas_n;
	output		sdram_cke;
	output		sdram_cs_n;
	inout	[15:0]	sdram_dq;
	output	[1:0]	sdram_dqm;
	output		sdram_ras_n;
	output		sdram_we_n;
	output		sdram_clk_clk;
	input	[3:0]	sw_export;
endmodule

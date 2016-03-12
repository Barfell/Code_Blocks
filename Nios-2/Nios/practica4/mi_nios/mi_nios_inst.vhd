	component mi_nios is
		port (
			clk_clk       : in    std_logic                     := 'X';             -- clk
			flash_dclk    : out   std_logic;                                        -- dclk
			flash_sce     : out   std_logic;                                        -- sce
			flash_sdo     : out   std_logic;                                        -- sdo
			flash_data0   : in    std_logic                     := 'X';             -- data0
			led_export    : out   std_logic_vector(7 downto 0);                     -- export
			reset_reset_n : in    std_logic                     := 'X';             -- reset_n
			sdram_addr    : out   std_logic_vector(11 downto 0);                    -- addr
			sdram_ba      : out   std_logic_vector(1 downto 0);                     -- ba
			sdram_cas_n   : out   std_logic;                                        -- cas_n
			sdram_cke     : out   std_logic;                                        -- cke
			sdram_cs_n    : out   std_logic;                                        -- cs_n
			sdram_dq      : inout std_logic_vector(15 downto 0) := (others => 'X'); -- dq
			sdram_dqm     : out   std_logic_vector(1 downto 0);                     -- dqm
			sdram_ras_n   : out   std_logic;                                        -- ras_n
			sdram_we_n    : out   std_logic;                                        -- we_n
			sdram_clk_clk : out   std_logic;                                        -- clk
			sw_export     : in    std_logic_vector(3 downto 0)  := (others => 'X')  -- export
		);
	end component mi_nios;

	u0 : component mi_nios
		port map (
			clk_clk       => CONNECTED_TO_clk_clk,       --       clk.clk
			flash_dclk    => CONNECTED_TO_flash_dclk,    --     flash.dclk
			flash_sce     => CONNECTED_TO_flash_sce,     --          .sce
			flash_sdo     => CONNECTED_TO_flash_sdo,     --          .sdo
			flash_data0   => CONNECTED_TO_flash_data0,   --          .data0
			led_export    => CONNECTED_TO_led_export,    --       led.export
			reset_reset_n => CONNECTED_TO_reset_reset_n, --     reset.reset_n
			sdram_addr    => CONNECTED_TO_sdram_addr,    --     sdram.addr
			sdram_ba      => CONNECTED_TO_sdram_ba,      --          .ba
			sdram_cas_n   => CONNECTED_TO_sdram_cas_n,   --          .cas_n
			sdram_cke     => CONNECTED_TO_sdram_cke,     --          .cke
			sdram_cs_n    => CONNECTED_TO_sdram_cs_n,    --          .cs_n
			sdram_dq      => CONNECTED_TO_sdram_dq,      --          .dq
			sdram_dqm     => CONNECTED_TO_sdram_dqm,     --          .dqm
			sdram_ras_n   => CONNECTED_TO_sdram_ras_n,   --          .ras_n
			sdram_we_n    => CONNECTED_TO_sdram_we_n,    --          .we_n
			sdram_clk_clk => CONNECTED_TO_sdram_clk_clk, -- sdram_clk.clk
			sw_export     => CONNECTED_TO_sw_export      --        sw.export
		);


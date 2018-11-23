# lpc12xx_iap_ram
## iap implement 
ide:keil v5
should works well on LPC12/25/26/27 except LPC1224(only 4KB ram)
## swd samples code

```C
  /* set sp/pc/xpsr/vector table/shadow pointer */
  state |= writecore(CORTEXMX_WR_R(13), sp);
  state |= writecore(CORTEXMX_WR_R(14), 0xFFFFFFFF);
  state |= writecore(CORTEXMX_WR_R(15), pc | 1);
  state |= writecore(CORTEXMX_WR_XPSR, XPSR_THUMB_BIT);;

  /* run the core */
  state |= writemem(nvic_base_address + DHCSR_ADDR_OFFSET, DHCSR_C_DEBUGEN);
 ```
## note
load code to ram by SWD then send data source and command via SWD.

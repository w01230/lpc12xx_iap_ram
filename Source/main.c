/*----------------------------------------------------------------------------
 * Name:    main.c
 * Purpose: boot code for NXP LPC12xx(25/26/27 not include 24)
 *----------------------------------------------------------------------------
 * This file is part of the uVision/ARM development tools.
 * This software may only be used under the terms of a valid, current,
 * end user licence from KEIL for a compatible version of KEIL software
 * development tools. Nothing else gives you the right to use this software.
 *
 * This software is supplied "AS IS" without warranties of any kind.
 *
 * Copyright (c) 2004-2014 Keil - An ARM Company. All rights reserved.
 *----------------------------------------------------------------------------*/
 
/*----------------------------------------------------------------------------
        start        size
  iap:  0x1000 0000  0x100 (0.25KB)
  code: 0x1000 0100  0x1000(4KB)
  ram:  0x1000 1500  0x800 (2KB)
  data: 0x1000 1900  0x600 (1.5KB)
  iap:  0x1000 1F00  0x100 (0.25KB)

  TODO:add parameter check
 *----------------------------------------------------------------------------*/
 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <LPC122x.h>
#include "boot_op.h"

#define BOOT_DATA       (struct boot_data_struct *)0x10001900
#define DATA_SOURCE     (unsigned char *)0x10001980

int main (void) 
{
	struct boot_data_struct *boot_data = BOOT_DATA;
	unsigned char *source = DATA_SOURCE;
	int state = 0;
	
	SystemCoreClockUpdate();
	
	/* remap flash */
	LPC_SYSCON->SYSMEMREMAP = 0x02;

	state = boot_op(source, boot_data);
	boot_data->state = state;
	
	return state;
}

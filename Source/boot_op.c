/* *
 *  boot interface
 *
 *
 *  get command from swd and excute the code
 */
 
#include <LPC122x.h>
#include "flash.h"
#include "boot_op.h"

int boot_op(unsigned char *source, struct boot_data_struct *boot_data)
{
	int state = 0;
	
	unsigned long magic = boot_data->command & 0xF000;
	unsigned long offset = boot_data->command & 0x000F;
	struct boot_handler mem_handler = flash_handler;
	
	int (*handler_a)(void *) = (void *)0;
	int (*handler_b)(void *, void *) = (void *)0;
	
	if (offset == 0)
		return BOOT_ERROR;
	
	if (offset >= (OP_END & 0x000F))
		return BOOT_ERROR;
	
	switch (magic) {
	case OPS_MAGIC_A:
		handler_a = (int (*) (void *))(*((unsigned long *)&mem_handler + (offset - 1)));
		state = handler_a(boot_data);
		break;
	
	case OPS_MAGIC_B:
		handler_b = (int (*) (void *, void *))(*((unsigned long *)&mem_handler + (offset - 1)));
		state = handler_b(source, boot_data);
		break;
	
	default:
		state = BOOT_ERROR;
		break;
	}
	
	return state;
}

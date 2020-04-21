/*
 * Copyright (C) 2016  Siarhei Siamashka <siarhei.siamashka@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/*
 * Partially based on the uart code from ar100-info
 *
 * (C) Copyright 2013 Stefan Kristiansson <stefan.kristiansson@saunalahti.fi>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

/*
 * Partially based on the sunxi gpio code from U-Boot
 *
 * (C) Copyright 2012 Henrik Nordstrom <henrik@henriknordstrom.net>
 *
 * Based on earlier arch/arm/cpu/armv7/sunxi/gpio.c:
 *
 * (C) Copyright 2007-2011
 * Allwinner Technology Co., Ltd. <www.allwinnertech.com>
 * Tom Cubie <tangliang@allwinnertech.com>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#define SUNXI_UART0_BASE	0x01C28000
#define UART0_THR ((SUNXI_UART0_BASE) + 0x0)    /* transmit holding register */
#define UART0_LSR ((SUNXI_UART0_BASE) + 0x14)   /* line status register */

#define PCR_CPU_X_BASE_ADDR		(0x01C20800)
#define PCR_PB_CFG0				(PCR_CPU_X_BASE_ADDR + (0x24 * 1))
#define PCR_PB_DAT				(PCR_CPU_X_BASE_ADDR + (0x24 * 1) + 0x10)

// =============================================================================
// main
// =============================================================================

#define readl(addr)		(*((volatile unsigned long  *)(addr)))
#define writel(v, addr)		(*((volatile unsigned long  *)(addr)) = (unsigned long)(v))
void mmu_init();
void uart0_putc(char c)
{
  //  while (!(readl(UART0_LSR) & (1 << 6))) {}
	writel(c, UART0_THR);
}

void uart0_puts(const char *s)
{
	while (*s) {
		if (*s == '\n')
			uart0_putc('\r');
		uart0_putc(*s++);
	}
}


void led_test(void){
	volatile int j;
	unsigned long val = 0x04;
	while (1) {
	  	volatile int i;
		for(i = 0; i < 500000; i++);
		*(unsigned int *)(PCR_PB_DAT) ^= val;
		//		val ^= 0x04;
		if(((j++) % 1000) == 0){
		  uart0_puts("\nHello 64bit World!!!!\n");
		}
	}
	return;
}

int main(void)
{
  *(unsigned int *)(PCR_PB_CFG0) = 0x00000100;
  uart0_puts("\n\nStart 64bit World!!!!\n\n");
  mmu_init();
  led_test();
  return 0;
}

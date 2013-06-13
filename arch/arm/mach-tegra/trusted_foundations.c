/*
 * Trusted Foundations support for Tegra CPUs
 *
 * Copyright (c) 2013, NVIDIA Corporation.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 */

#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/of.h>
#include <asm/firmware.h>

#define TF_SET_CPU_BOOT_ADDR_SMC 0xfffff200

static void __attribute__((naked)) tegra_tf_generic_smc(u32 type, u32 subtype,
							u32 arg)
{
	asm volatile(
		".arch_extension	sec\n\t"
		"stmfd	sp!, {r4 - r11, lr}\n\t"
		__asmeq("%0", "r0")
		__asmeq("%1", "r1")
		__asmeq("%2", "r2")
		"mov	r3, #0\n\t"
		"mov	r4, #0\n\t"
		"smc	#0\n\t"
		"ldmfd	sp!, {r4 - r11, pc}"
		:
		: "r" (type), "r" (subtype), "r" (arg)
		: "memory");
}

static int tegra_tf_set_cpu_boot_addr(int cpu, unsigned long boot_addr)
{
	tegra_tf_generic_smc(TF_SET_CPU_BOOT_ADDR_SMC, boot_addr, 0);

	return 0;
}

const struct firmware_ops tegra_trusted_foundations_ops = {
	.set_cpu_boot_addr = tegra_tf_set_cpu_boot_addr,
};

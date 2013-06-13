/*
 * Firmware/Secure monitor support for Tegra CPUs
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

#include <linux/printk.h>
#include <linux/kconfig.h>
#include <linux/of.h>
#include <asm/firmware.h>

#if IS_ENABLED(CONFIG_TEGRA_TRUSTED_FOUNDATIONS)
extern const struct firmware_ops tegra_trusted_foundations_ops;
#endif

void __init tegra_init_firmware(void)
{
	struct device_node *node;

	if (!of_have_populated_dt())
		return;

	node = of_find_compatible_node(NULL, NULL, "tl,trusted-foundations");
	if (node && !IS_ENABLED(CONFIG_TEGRA_TRUSTED_FOUNDATIONS))
		pr_warn("Trusted Foundations detected but support missing!\n");
#if IS_ENABLED(CONFIG_TEGRA_TRUSTED_FOUNDATIONS)
	else if (node)
		register_firmware_ops(&tegra_trusted_foundations_ops);
#endif
}

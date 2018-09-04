/*
 * Copyright (c) 2016-2017 The Linux Foundation. All rights reserved.
 *
 * Permission to use, copy, modify, and/or distribute this software for
 * any purpose with or without fee is hereby granted, provided that the
 * above copyright notice and this permission notice appear in all
 * copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
 * WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
 * AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 * DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
 * PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 * TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 * PERFORMANCE OF THIS SOFTWARE.
 */

#ifndef __PLD_SNOC_H__
#define __PLD_SNOC_H__

#ifdef CONFIG_PLD_SNOC_ICNSS
#include <soc/qcom/icnss.h>
#endif
#include "pld_internal.h"

#ifndef CONFIG_PLD_SNOC_ICNSS
static inline int pld_snoc_register_driver(void)
{
	return 0;
}

static inline void pld_snoc_unregister_driver(void)
{
}
static inline int pld_snoc_wlan_enable(struct device *dev,
			struct pld_wlan_enable_cfg *config,
			enum pld_driver_mode mode, const char *host_version)
{
	return 0;
}
static inline int pld_snoc_wlan_disable(struct device *dev,
					enum pld_driver_mode mode)
{
	return 0;
}
static inline int pld_snoc_ce_request_irq(struct device *dev,
					  unsigned int ce_id,
					  irqreturn_t (*handler)(int, void *),
					  unsigned long flags,
					  const char *name, void *ctx)
{
	return 0;
}
static inline int pld_snoc_ce_free_irq(struct device *dev,
				       unsigned int ce_id, void *ctx)
{
	return 0;
}
static inline void pld_snoc_enable_irq(struct device *dev, unsigned int ce_id)
{
}
static inline void pld_snoc_disable_irq(struct device *dev, unsigned int ce_id)
{
}
static inline int pld_snoc_get_soc_info(struct device *dev, struct pld_soc_info *info)
{
	return 0;
}
static inline int pld_snoc_get_ce_id(struct device *dev, int irq)
{
	return 0;
}
static inline int pld_snoc_power_on(struct device *dev)
{
	return 0;
}
static inline int pld_snoc_power_off(struct device *dev)
{
	return 0;
}
static inline int pld_snoc_get_irq(struct device *dev, int ce_id)
{
	return 0;
}
static inline int pld_snoc_athdiag_read(struct device *dev, uint32_t offset,
					uint32_t memtype, uint32_t datalen,
					uint8_t *output)
{
	return 0;
}
static inline int pld_snoc_athdiag_write(struct device *dev, uint32_t offset,
					 uint32_t memtype, uint32_t datalen,
					 uint8_t *input)
{
	return 0;
}
static inline void *pld_snoc_smmu_get_mapping(struct device *dev)
{
	return NULL;
}
static inline int pld_snoc_smmu_map(struct device *dev, phys_addr_t paddr,
				    uint32_t *iova_addr, size_t size)
{
	return 0;
}
static inline
unsigned int pld_snoc_socinfo_get_serial_number(struct device *dev)
{
	return 0;
}
static inline int pld_snoc_is_qmi_disable(struct device *dev)
{
	return 0;
}
static inline int pld_snoc_set_fw_log_mode(struct device *dev, u8 fw_log_mode)
{
	return 0;
}
static inline int pld_snoc_force_assert_target(struct device *dev)
{
	return 0;
}
#else
int pld_snoc_register_driver(void);
void pld_snoc_unregister_driver(void);
int pld_snoc_wlan_enable(struct device *dev,
			 struct pld_wlan_enable_cfg *config,
			 enum pld_driver_mode mode, const char *host_version);
int pld_snoc_wlan_disable(struct device *dev, enum pld_driver_mode mode);
int pld_snoc_get_soc_info(struct device *dev, struct pld_soc_info *info);

#ifdef ICNSS_API_WITH_DEV
static inline int pld_snoc_ce_request_irq(struct device *dev,
					  unsigned int ce_id,
					  irqreturn_t (*handler)(int, void *),
					  unsigned long flags,
					  const char *name, void *ctx)
{
	if (!dev)
		return -ENODEV;

	return icnss_ce_request_irq(dev, ce_id, handler, flags, name, ctx);
}

static inline int pld_snoc_ce_free_irq(struct device *dev,
				       unsigned int ce_id, void *ctx)
{
	if (!dev)
		return -ENODEV;

	return icnss_ce_free_irq(dev, ce_id, ctx);
}

static inline void pld_snoc_enable_irq(struct device *dev, unsigned int ce_id)
{
	if (dev)
		icnss_enable_irq(dev, ce_id);
}

static inline void pld_snoc_disable_irq(struct device *dev, unsigned int ce_id)
{
	if (dev)
		icnss_disable_irq(dev, ce_id);
}

static inline int pld_snoc_get_ce_id(struct device *dev, int irq)
{
	if (!dev)
		return -ENODEV;

	return icnss_get_ce_id(dev, irq);
}

static inline int pld_snoc_get_irq(struct device *dev, int ce_id)
{
	if (!dev)
		return -ENODEV;

	return icnss_get_irq(dev, ce_id);
}
#else
static inline int pld_snoc_ce_request_irq(struct device *dev,
					  unsigned int ce_id,
					  irqreturn_t (*handler)(int, void *),
					  unsigned long flags,
					  const char *name, void *ctx)
{
	return icnss_ce_request_irq(ce_id, handler, flags, name, ctx);
}

static inline void pld_snoc_enable_irq(struct device *dev, unsigned int ce_id)
{
	icnss_enable_irq(ce_id);
}

static inline void pld_snoc_disable_irq(struct device *dev, unsigned int ce_id)
{
	icnss_disable_irq(ce_id);
}

static inline int pld_snoc_ce_free_irq(struct device *dev,
				       unsigned int ce_id, void *ctx)
{
	return icnss_ce_free_irq(ce_id, ctx);
}

static inline int pld_snoc_get_ce_id(struct device *dev, int irq)
{
	return icnss_get_ce_id(irq);
}

static inline int pld_snoc_get_irq(struct device *dev, int ce_id)
{
	return icnss_get_irq(ce_id);
}
#endif

static inline int pld_snoc_power_on(struct device *dev)
{
	return icnss_power_on(dev);
}
static inline int pld_snoc_power_off(struct device *dev)
{
	return icnss_power_off(dev);
}
static inline int pld_snoc_athdiag_read(struct device *dev, uint32_t offset,
					uint32_t memtype, uint32_t datalen,
					uint8_t *output)
{
	return icnss_athdiag_read(dev, offset, memtype, datalen, output);
}
static inline int pld_snoc_athdiag_write(struct device *dev, uint32_t offset,
					 uint32_t memtype, uint32_t datalen,
					 uint8_t *input)
{
	return icnss_athdiag_write(dev, offset, memtype, datalen, input);
}
static inline void *pld_snoc_smmu_get_mapping(struct device *dev)
{
	return icnss_smmu_get_mapping(dev);
}
static inline int pld_snoc_smmu_map(struct device *dev, phys_addr_t paddr,
				    uint32_t *iova_addr, size_t size)
{
	return icnss_smmu_map(dev, paddr, iova_addr, size);
}
static inline
unsigned int pld_snoc_socinfo_get_serial_number(struct device *dev)
{
	return icnss_socinfo_get_serial_number(dev);
}

#ifdef ICNSS_API_WITH_DEV
static inline int pld_snoc_is_qmi_disable(struct device *dev)
{
	if (!dev)
		return -ENODEV;

	return icnss_is_qmi_disable(dev);
}

static inline int pld_snoc_set_fw_log_mode(struct device *dev, u8 fw_log_mode)
{
	if (!dev)
		return -ENODEV;

	return icnss_set_fw_log_mode(dev, fw_log_mode);
}
#else
static inline int pld_snoc_is_qmi_disable(struct device *dev)
{
	return icnss_is_qmi_disable();
}

static inline int pld_snoc_set_fw_log_mode(struct device *dev, u8 fw_log_mode)
{
	return icnss_set_fw_log_mode(fw_log_mode);
}
#endif

static inline int pld_snoc_force_assert_target(struct device *dev)
{
	return icnss_trigger_recovery(dev);
}
#endif
#endif

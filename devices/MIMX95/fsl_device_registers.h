/*
 * Copyright 2014-2016 Freescale Semiconductor, Inc.
 * Copyright 2016-2022 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef __FSL_DEVICE_REGISTERS_H__
#define __FSL_DEVICE_REGISTERS_H__

/*
 * Include the cpu specific register header files.
 *
 * The CPU macro should be declared in the project or makefile.
 */
#if (defined(CPU_MIMX95_cm33))

#define MIMX95_cm33_SERIES

/* CMSIS-style register definitions */
#include "MIMX95_cm33.h"
/* CPU specific feature definitions */
#include "MIMX95_cm33_features.h"
/* CPU electrical spec definitions */
#include "MIMX95_elec_spec.h"

#else
#error "No valid CPU defined!"
#endif

/* SWI mapping */
#define SWI_0_IRQn Reserved110_IRQn

#endif /* __FSL_DEVICE_REGISTERS_H__ */

/*******************************************************************************
 * EOF
 ******************************************************************************/

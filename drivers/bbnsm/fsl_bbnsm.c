/*
 * Copyright 2021, 2025 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_bbnsm.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.bbnsm"
#endif

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
#if (!(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && defined(BBNSM_CLOCKS))
/*!
 * @brief Get the BBNSM instance from peripheral base address.
 *
 * @param base BBNSM peripheral base address.
 *
 * @return BBNSM instance.
 */
static uint32_t BBNSM_GetInstance(BBNSM_Type *base);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

/*******************************************************************************
 * Variables
 ******************************************************************************/
#if (!(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && defined(BBNSM_CLOCKS))
/*! @brief Pointer to bbnsm_lp clock. */
const clock_ip_name_t s_bbnsmClock[] = BBNSM_CLOCKS;
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

/*******************************************************************************
 * Code
 ******************************************************************************/
#if (!(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && defined(BBNSM_CLOCKS))
static uint32_t BBNSM_GetInstance(BBNSM_Type *base)
{
    return 0U;
}
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

/*!
 * brief Ungates the BBNSM clock.
 *
 * note This API should be called at the beginning of the application using the BBNSM driver.
 *
 * param base   BBNSM peripheral base address
 */
void BBNSM_Init(BBNSM_Type *base)
{
#if (!(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && defined(BBNSM_CLOCKS))
    uint32_t instance = BBNSM_GetInstance(base);
    CLOCK_EnableClock(s_bbnsmClock[instance]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
}

/*!
 * brief Deinit the BBNSM section.
 *
 * param base BBNSM peripheral base address
 */
void BBNSM_Deinit(BBNSM_Type *base)
{
#if (!(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && defined(BBNSM_CLOCKS))
    uint32_t instance = BBNSM_GetInstance(base);
    CLOCK_DisableClock(s_bbnsmClock[instance]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
}

/*!
 * brief Ungates the BBNSM clock and configures the peripheral for basic operation.
 *
 * note This API should be called at the beginning of the application using the BBNSM driver.
 *
 * param base   BBNSM peripheral base address
 * param config Pointer to the user's BBNSM configuration structure.
 */
void BBNSM_RTC_Init(BBNSM_Type *base, const bbnsm_rtc_config_t *config)
{
    assert(config != NULL);

#if (!(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && defined(BBNSM_CLOCKS))
    uint32_t instance = BBNSM_GetInstance(base);
    CLOCK_EnableClock(s_bbnsmClock[instance]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

    if (config->rtcCalEnable)
    {
        base->BBNSM_CTRL = BBNSM_BBNSM_CTRL_CAL_VAL(config->rtcCalValue);
        base->BBNSM_CTRL |= BBNSM_BBNSM_CTRL_CAL_EN(0x1);
    }

    BBNSM_RTC_StartTimer(base);
}

/*!
 * brief Stops the RTC timer.
 *
 * param base BBNSM peripheral base address
 */
void BBNSM_RTC_Deinit(BBNSM_Type *base)
{
    base->BBNSM_CTRL &= ~BBNSM_BBNSM_CTRL_RTC_EN(0x2);

#if (!(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && defined(BBNSM_CLOCKS))
    uint32_t instance = BBNSM_GetInstance(base);
    CLOCK_DisableClock(s_bbnsmClock[instance]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
}

/*!
 * brief Fills in the BBNSM config struct with the default settings.
 *
 * The default values are as follows.
 * code
 *    config->rtccalenable = false;
 *    config->rtccalvalue = 0U;
 * endcode
 * param config Pointer to the user's BBNSM RTC configuration structure.
 */
void BBNSM_RTC_GetDefaultConfig(bbnsm_rtc_config_t *config)
{
    assert(config != NULL);

    /* Initializes the configure structure to zero. */
    (void)memset(config, 0, sizeof(*config));

    config->rtcCalEnable = false;
    config->rtcCalValue  = 0U;
}

uint32_t BBNSM_RTC_GetSeconds(BBNSM_Type *base)
{
    uint32_t ls, ms, ls2;

    /* Do consecutive reads until value is correct */
    ls2 = (base->BBNSM_RTC_LS >> 15U);
    do
    {
        ls = ls2;
        ms = (base->BBNSM_RTC_MS << 17U);
        ls2 = (base->BBNSM_RTC_LS >> 15U);
    } while (ls != ls2);

    return ms | ls;
}

/*!
 * brief Sets the BBNSM RTC date and time according to the given time structure.
 *
 * param base     BBNSM peripheral base address
 * param seconds
 */
void BBNSM_RTC_SetSeconds(BBNSM_Type *base, uint32_t seconds)
{
    uint32_t origCtrl = base->BBNSM_CTRL;
    uint32_t clrCtrl = origCtrl & ~BBNSM_BBNSM_CTRL_RTC_EN(0x3); 

    /* Disable RTC */
    base->BBNSM_CTRL = clrCtrl | BBNSM_BBNSM_CTRL_RTC_EN(0x1);
    while ((base->BBNSM_CTRL & (BBNSM_BBNSM_CTRL_RTC_EN(0x1))) == 0U)
    {
    }

    base->BBNSM_RTC_MS = (uint32_t)(seconds >> 17U);
    base->BBNSM_RTC_LS = (uint32_t)(seconds << 15U);

    /* Reenable RTC in case that it was enabled before */
    if ((origCtrl & BBNSM_BBNSM_CTRL_RTC_EN(0x2)) != 0U)
    {
        base->BBNSM_CTRL = clrCtrl | BBNSM_BBNSM_CTRL_RTC_EN(0x2);
        while ((base->BBNSM_CTRL & BBNSM_BBNSM_CTRL_RTC_EN(0x2)) == 0U)
        {
        }
    }
}

/*!
 * brief Sets the BBNSM RTC alarm time.
 *
 * The function sets the RTC alarm. It also checks whether the specified alarm
 * time is greater than the present time. If not, the function does not set the alarm
 * and returns an error.
 * Please note, that RTC alarm has limited resolution because only 32 most
 * significant bits of RTC counter are compared to RTC Alarm register.
 * If the alarm time is beyond RTC resolution, the function does not set the alarm
 * and returns an error.
 *
 * param base      BBNSM peripheral base address
 * param alarmTime Pointer to the structure where the alarm time is stored.
 *
 * return kStatus_Success: success in setting the BBNSM RTC alarm
 *         kStatus_InvalidArgument: Error because the alarm datetime format is incorrect
 *         kStatus_Fail: Error because the alarm time has already passed or is beyond resolution
 */
status_t BBNSM_RTC_SetAlarm(BBNSM_Type *base, uint32_t alarmSeconds)
{
    uint32_t currSeconds = 0U;
    uint32_t tmp;

    currSeconds = BBNSM_RTC_GetSeconds(base);

    /* Return error if the alarm time has passed */
    if (alarmSeconds <= currSeconds)
    {
        return kStatus_Fail;
    }

    /* Disable RTC alarm interrupt */
    tmp = base->BBNSM_INT_EN &
          ~BBNSM_BBNSM_INT_EN_TA_INT_EN(
              0x3); /* Clear TA_INT_EN field to avoid writing an invalid value(0b00/0b11) to the TA_INT_EN field */

    base->BBNSM_INT_EN = tmp | BBNSM_BBNSM_INT_EN_TA_INT_EN(0x1);
    while ((base->BBNSM_INT_EN & BBNSM_BBNSM_INT_EN_TA_INT_EN(0x1)) == 0U)
    {
    }

    /* Set alarm in seconds*/
    base->BBNSM_TA = alarmSeconds;

    /* Enable RTC alarm interrupt */
    base->BBNSM_INT_EN = tmp | BBNSM_BBNSM_INT_EN_TA_INT_EN(0x2);

    /* Time alarm enable */
    tmp =
        base->BBNSM_CTRL &
        ~BBNSM_BBNSM_CTRL_TA_EN(0x3); /* Clear TA_EN field to avoid writing an invalid value(0b11) to the TA_EN field */
    base->BBNSM_CTRL = tmp | BBNSM_BBNSM_CTRL_TA_EN(0x2);

    return kStatus_Success;
}

/*!
 * brief Returns the BBNSM RTC alarm time.
 *
 * param base     BBNSM peripheral base address
 */
uint32_t BBNSM_RTC_GetAlarm(BBNSM_Type *base)
{
    /* Get alarm in seconds  */
    return base->BBNSM_TA;
}

/*!
 * @brief Disable the BBNSM RTC alarm.
 *
 * @param base     BBNSM peripheral base address
 */
void BBNSM_RTC_DisableAlarm(BBNSM_Type *base)
{
    uint32_t tmp;

    /* Time alarm disable */
    tmp =
        base->BBNSM_CTRL &
        ~BBNSM_BBNSM_CTRL_TA_EN(0x3); /* Clear TA_EN field to avoid writing an invalid value(0b11) to the TA_EN field */
    base->BBNSM_CTRL = tmp | BBNSM_BBNSM_CTRL_TA_EN(0x1);
}

/*!
 * brief Gets the BBNSM status flags.
 *
 * param base BBNSM peripheral base address
 *
 * return The status flags. This is the logical OR of members of the
 *         enumeration ::bbnsm_status_flags_t
 */
uint32_t BBNSM_GetStatusFlags(BBNSM_Type *base)
{
    return base->BBNSM_EVENTS;
}

/*!
 * brief Gets the enabled BBNSM interrupts.
 *
 * param base BBNSM peripheral base address
 *
 * return The enabled interrupts. This is the logical OR of members of the
 *         enumeration ::bbnsm_interrupt_enable_t
 */
uint32_t BBNSM_GetEnabledInterrupts(BBNSM_Type *base)
{
    return base->BBNSM_INT_EN;
}

uint64_t BBNSM_RTC_GetTicks(BBNSM_Type * base)
{
    uint32_t ls, ms, ls2;

    /* Do consecutive reads of RTC_MS to guard against RTC_LS ripple */
    ls2 = base->BBNSM_RTC_LS;
    do
    {
        ls = ls2;
        ms = base->BBNSM_RTC_MS;
        ls2 = base->BBNSM_RTC_LS;
    } while ((ls & 0x80000000U) != (ls2 & 0x80000000U));

    uint64_t ticks = ms;
    ticks = (ticks << 32U) | ls;

   return ticks;
}

void BBNSM_RTC_SetTicks(BBNSM_Type *base, uint64_t ticks)
{
    uint32_t origCtrl = base->BBNSM_CTRL;
    uint32_t clrCtrl = origCtrl & ~BBNSM_BBNSM_CTRL_RTC_EN(0x3); 

    /* Disable RTC */
    base->BBNSM_CTRL = clrCtrl | BBNSM_BBNSM_CTRL_RTC_EN(0x1);
    while ((base->BBNSM_CTRL & (BBNSM_BBNSM_CTRL_RTC_EN(0x1))) == 0U)
    {
    }

    base->BBNSM_RTC_MS = (uint32_t)(ticks >> 32U);
    base->BBNSM_RTC_LS = (uint32_t)(ticks & 0xFFFFFFFFU);

    /* Reenable RTC in case that it was enabled before */
    if ((origCtrl & BBNSM_BBNSM_CTRL_RTC_EN(0x2)) != 0U)
    {
        base->BBNSM_CTRL = clrCtrl | BBNSM_BBNSM_CTRL_RTC_EN(0x2);
        while ((base->BBNSM_CTRL & BBNSM_BBNSM_CTRL_RTC_EN(0x2)) == 0U)
        {
        }
    }
}
bool BBNSM_GprGetValue(BBNSM_Type *base, uint8_t gprIdx, uint32_t *gprVal)
{
    uint32_t rc = false;

    if (gprIdx < (sizeof(base->GPR) / sizeof(base->GPR[0])))
    {
        *gprVal = base->GPR[gprIdx];
        rc = true;
    }

    return rc;
}

bool BBNSM_GprSetValue(BBNSM_Type *base, uint8_t gprIdx, uint32_t gprVal)
{
    bool rc = false;

    if (gprIdx < (sizeof(base->GPR) / sizeof(base->GPR[0])))
    {
        base->GPR[gprIdx] = gprVal;
        rc = true;
    }

    return rc;
}

void BBNSM_ButtonGetDefaultConfig(bbnsm_button_config_t *btnConfig)
{
    assert(btnConfig != NULL);

    /* Initializes the configure structure to zero. */
    (void)memset(btnConfig, 0, sizeof(*btnConfig));

    btnConfig->turnOnTime = 0U;     /* 500 msec */
    btnConfig->turnOffTime = 0U;    /* 5 sec */
    btnConfig->debounceTime = 0U;   /* 50 msec */
}

void BBNSM_ButtonSetConfig(BBNSM_Type *base, bbnsm_button_config_t *btnConfig)
{
    assert(btnConfig != NULL);

    uint32_t ctrl = base->BBNSM_CTRL;

    ctrl &= (~(BBNSM_BBNSM_CTRL_TURN_ON_TIME_MASK |
               BBNSM_BBNSM_CTRL_BTN_TIMEOUT_MASK |
               BBNSM_BBNSM_CTRL_DEBOUNCE_MASK));

    ctrl |= (BBNSM_BBNSM_CTRL_TURN_ON_TIME(btnConfig->turnOnTime) |
             BBNSM_BBNSM_CTRL_BTN_TIMEOUT(btnConfig->turnOffTime) |
             BBNSM_BBNSM_CTRL_DEBOUNCE(btnConfig->debounceTime));

    base->BBNSM_CTRL = ctrl;
}

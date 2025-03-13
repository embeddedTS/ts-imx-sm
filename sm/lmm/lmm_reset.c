/*
** ###################################################################
**
** Copyright 2023 NXP
**
** Redistribution and use in source and binary forms, with or without modification,
** are permitted provided that the following conditions are met:
**
** o Redistributions of source code must retain the above copyright notice, this list
**   of conditions and the following disclaimer.
**
** o Redistributions in binary form must reproduce the above copyright notice, this
**   list of conditions and the following disclaimer in the documentation and/or
**   other materials provided with the distribution.
**
** o Neither the name of the copyright holder nor the names of its
**   contributors may be used to endorse or promote products derived from this
**   software without specific prior written permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
** ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
** WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
** DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
** ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
** (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
** LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
** ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
** SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**
**
** ###################################################################
*/

/*==========================================================================*/
/* File containing the implementation of the Logical Machine Manager        */
/* reset domains.                                                           */
/*==========================================================================*/

/* Includes */

#include "sm.h"
#include "lmm.h"
#include "dev_sm_api.h"

/* Local defines */

/* Local types */

/* Local variables */

/*--------------------------------------------------------------------------*/
/* Return reset domain name                                                 */
/*--------------------------------------------------------------------------*/
int32_t LMM_ResetDomainNameGet(uint32_t lmId, uint32_t domainId,
    string *domainNameAddr, int32_t *len)
{
    /* Just passthru to board/device */
    return SM_RESETDOMAINNAMEGET(domainId, domainNameAddr, len);
}

/*--------------------------------------------------------------------------*/
/* Reset domain                                                             */
/*--------------------------------------------------------------------------*/
int32_t LMM_ResetDomain(uint32_t lmId, uint32_t domainId,
    uint32_t resetState, bool toggle, bool assertNegate)
{
    /* Just passthru to board/device */
    return SM_RESETDOMAIN(domainId, resetState, toggle, assertNegate);
}

/*--------------------------------------------------------------------------*/
/* Get reset domain state                                                   */
/*--------------------------------------------------------------------------*/
int32_t LMM_ResetDomainGet(uint32_t lmId, uint32_t domainId,
    bool *assertNegate)
{
    /* Just passthru to board/device */
    return SM_RESETDOMAINGET(domainId, assertNegate);
}


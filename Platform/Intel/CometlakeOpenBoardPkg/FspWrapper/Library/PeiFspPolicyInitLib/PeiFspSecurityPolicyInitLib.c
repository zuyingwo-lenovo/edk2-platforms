/** @file
  Implementation of Fsp Security Policy Initialization.


  Copyright (c) 2020, Intel Corporation. All rights reserved.<BR>
  SPDX-License-Identifier: BSD-2-Clause-Patent
**/

#include <PeiFspPolicyInitLib.h>
#include <Library/PeiServicesLib.h>
#include <Ppi/SiPolicy.h>

/**
  Performs FSP Security PEI Policy initialization.

  @param[in][out]  FspmUpd             Pointer to FSP UPD Data.

  @retval          EFI_SUCCESS         FSP UPD Data is updated.
  @retval          EFI_NOT_FOUND       Fail to locate required PPI.
  @retval          Other               FSP UPD Data update process fail.
**/
EFI_STATUS
EFIAPI
PeiFspSecurityPolicyInitPreMem (
  IN OUT FSPM_UPD    *FspmUpd
  )
{
  EFI_STATUS                    Status;
  SI_PREMEM_POLICY_PPI          *SiPreMemPolicyPpi;

  DEBUG ((DEBUG_INFO | DEBUG_INIT, "FSP Update SecurityPolicy Pre-Mem Start\n"));

  //
  // Locate SiPreMemPolicyPpi
  //
  SiPreMemPolicyPpi = NULL;
  Status = PeiServicesLocatePpi (
             &gSiPreMemPolicyPpiGuid,
             0,
             NULL,
             (VOID **) &SiPreMemPolicyPpi
             );
  if (EFI_ERROR (Status)) {
    return EFI_NOT_FOUND;
  }

  DEBUG ((DEBUG_INFO | DEBUG_INIT, "FSP Update SecurityPolicy Pre-Mem End\n"));

  return EFI_SUCCESS;
}

/**
  Performs FSP Security PEI Policy post memory initialization.

  @param[in][out]  FspsUpd             Pointer to FSP UPD Data.

  @retval          EFI_SUCCESS         FSP UPD Data is updated.
  @retval          EFI_NOT_FOUND       Fail to locate required PPI.
  @retval          Other               FSP UPD Data update process fail.
**/
EFI_STATUS
EFIAPI
PeiFspSecurityPolicyInit (
  IN OUT FSPS_UPD    *FspsUpd
  )
{

  return EFI_SUCCESS;
}


## @file
# DSC file of Aowanda platform
#
# @copyright
# Copyright 2008 - 2021 Intel Corporation. <BR>
# Copyright (c) 2022, American Megatrends International LLC. <BR>
#
# SPDX-License-Identifier: BSD-2-Clause-Patent
##

################################################################################
#
# Defines Section - statements that will be processed to create a Makefile.
#
################################################################################
[Defines]
  PEI_ARCH                            = IA32
  DXE_ARCH                            = X64

  !include WhitleyOpenBoardPkg/PlatformPkg.dsc

[PcdsFixedAtBuild]
  gMinPlatformPkgTokenSpaceGuid.PcdBootStage|6

[PcdsFeatureFlag]
!if $(gMinPlatformPkgTokenSpaceGuid.PcdBootStage) >= 5
  gIpmiFeaturePkgTokenSpaceGuid.PcdIpmiFeatureEnable        |TRUE
  gNetworkFeaturePkgTokenSpaceGuid.PcdNetworkFeatureEnable  |TRUE
!else
  gIpmiFeaturePkgTokenSpaceGuid.PcdIpmiFeatureEnable        |FALSE
  gNetworkFeaturePkgTokenSpaceGuid.PcdNetworkFeatureEnable  |FALSE
!endif

  !include AdvancedFeaturePkg/Include/AdvancedFeatures.dsc

[Defines]
  BOARD_NAME                = Aowanda
  PLATFORM_NAME             = $(BOARD_NAME)
  PLATFORM_GUID             = 240D6B04-AFED-47E7-AB05-64B621A1112D
  FLASH_DEFINITION          = $(RP_PKG)/$(BOARD_NAME)/PlatformPkg.fdf

[PcdsFixedAtBuild]

!if $(TARGET) == "RELEASE"
  gEfiMdePkgTokenSpaceGuid.PcdDebugPropertyMask|0x0
  gEfiMdePkgTokenSpaceGuid.PcdReportStatusCodePropertyMask|0x03
  gEfiMdeModulePkgTokenSpaceGuid.PcdStatusCodeUseSerial|FALSE
!else
  gEfiMdePkgTokenSpaceGuid.PcdDebugPropertyMask|0x2F                   # Enable asserts, prints, code, clear memory, and deadloops on asserts.
  gEfiMdePkgTokenSpaceGuid.PcdReportStatusCodePropertyMask|0x07
  gEfiMdeModulePkgTokenSpaceGuid.PcdStatusCodeUseSerial|TRUE
  gEfiMdePkgTokenSpaceGuid.PcdFixedDebugPrintErrorLevel|0x80200047      # Built in messages:  Error, MTRR, info, load, warn, init
  gEfiSourceLevelDebugPkgTokenSpaceGuid.PcdDebugLoadImageMethod|0x2     # This is set to INT3 (0x2) for Simics source level debugging
!endif
  gPlatformTokenSpaceGuid.PcdBoardId|0x26

[PcdsFixedAtBuild.X64]
  gPcAtChipsetPkgTokenSpaceGuid.PcdMinimalValidYear|1900
  gPcAtChipsetPkgTokenSpaceGuid.PcdMaximalValidYear|9999

[PcdsDynamicExHii]
  gEfiMdePkgTokenSpaceGuid.PcdPlatformBootTimeOut|L"Timeout"|gEfiGlobalVariableGuid|0x0|5 # Variable: L"Timeout"

[LibraryClasses.Common.PEI_CORE, LibraryClasses.Common.PEIM]
  PeiPlatformHookLib|$(RP_PKG)/$(BOARD_NAME)/Library/PeiPlatformHookLib/PeiPlatformHooklib.inf

!if gIpmiFeaturePkgTokenSpaceGuid.PcdIpmiFeatureEnable == TRUE
  IpmiPlatformHookLib| $(RP_PKG)/$(BOARD_NAME)/Library/IpmiPlatformHookLib/IpmiPlatformHookLib.inf
!endif

[Components.IA32]
  $(RP_PKG)/Uba/BoardInit/Pei/BoardInitPei.inf {
    <LibraryClasses>
      NULL|$(RP_PKG)/$(BOARD_NAME)/Uba/TypeAowanda/Pei/PeiBoardInitLib.inf
      NULL|$(RP_PKG)/Uba/UbaMain/Common/Pei/PeiCommonBoardInitLib.inf
  }

[Components.X64]
  $(RP_PKG)/$(BOARD_NAME)/Uba/TypeAowanda/Dxe/UsbOcUpdateDxe/UsbOcUpdateDxe.inf
  $(RP_PKG)/$(BOARD_NAME)/Uba/TypeAowanda/Dxe/IioCfgUpdateDxe/IioCfgUpdateDxe.inf
  $(RP_PKG)/$(BOARD_NAME)/Uba/TypeAowanda/Dxe/SlotDataUpdateDxe/SlotDataUpdateDxe.inf
  MdeModulePkg/Bus/Pci/SataControllerDxe/SataControllerDxe.inf

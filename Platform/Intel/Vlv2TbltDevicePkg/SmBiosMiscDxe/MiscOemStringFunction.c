/*++

Copyright (c) 2009 - 2020, Intel Corporation. All rights reserved.<BR>
                                                                                   

  SPDX-License-Identifier: BSD-2-Clause-Patent

                                                                                   


Module Name:

  MiscOemStringFunction.c

Abstract:

  boot information boot time changes.
  SMBIOS type 11.

--*/


#include "CommonHeader.h"

#include "MiscSubclassDriver.h"

/**
  This function makes boot time changes to the contents of the
  MiscOemString (Type 11).

  @param  RecordData                 Pointer to copy of RecordData from the Data Table.

  @retval EFI_SUCCESS                All parameters were valid.
  @retval EFI_UNSUPPORTED            Unexpected RecordType value.
  @retval EFI_INVALID_PARAMETER      Invalid parameter was found.

**/
MISC_SMBIOS_TABLE_FUNCTION(OemString)
{
  UINTN                    OemStrLen;
  CHAR8                    *OptionalStrStart;
  EFI_STATUS               Status;
  EFI_STRING               OemStr;
  STRING_REF               TokenToGet;
  EFI_SMBIOS_HANDLE        SmbiosHandle;
  SMBIOS_TABLE_TYPE11      *SmbiosRecord;

  //
  // First check for invalid parameters.
  //
  if (RecordData == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  TokenToGet = STRING_TOKEN (STR_MISC_OEM_EN_US);
  OemStr = SmbiosMiscGetString (TokenToGet);
  OemStrLen = StrLen(OemStr);
  if (OemStrLen > SMBIOS_STRING_MAX_LENGTH) {
    return EFI_UNSUPPORTED;
  }

  //
  // Two zeros following the last string.
  //
  SmbiosRecord = AllocatePool(sizeof (SMBIOS_TABLE_TYPE11) + OemStrLen + 1 + 1);
  ZeroMem(SmbiosRecord, sizeof (SMBIOS_TABLE_TYPE11) + OemStrLen + 1 + 1);

  SmbiosRecord->Hdr.Type = EFI_SMBIOS_TYPE_OEM_STRINGS;
  SmbiosRecord->Hdr.Length = sizeof (SMBIOS_TABLE_TYPE11);

  //
  // Make handle chosen by smbios protocol.add automatically.
  //
  SmbiosRecord->Hdr.Handle = 0;
  SmbiosRecord->StringCount = 1;
  OptionalStrStart = (CHAR8 *)(SmbiosRecord + 1);
  UnicodeStrToAsciiStrS (OemStr, OptionalStrStart, OemStrLen + 1 + 1);

  //
  // Now we have got the full smbios record, call smbios protocol to add this record.
  //
  SmbiosHandle = SMBIOS_HANDLE_PI_RESERVED;
  Status = Smbios-> Add(
                      Smbios,
                      NULL,
                      &SmbiosHandle,
                      (EFI_SMBIOS_TABLE_HEADER *) SmbiosRecord
                      );
  FreePool(SmbiosRecord);
  return Status;
}

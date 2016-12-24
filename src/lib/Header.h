/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/*
 * This file is part of the libone project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef INCLUDED_LIBONE_HEADER_H
#define INCLUDED_LIBONE_HEADER_H

#include <string>
#include <cstdint>
#include <librevenge-stream/librevenge-stream.h>

namespace libone {
class Header {
  public:
    void parse(librevenge::RVNGInputStream *input);
    GUID guidFileType = GUID();
    GUID guidFile = GUID();
    GUID guidLegacyFileVersion = GUID();
    GUID guidFileFormat = GUID();
    uint32_t ffvLastCodeThatWroteToThisFile = 0;
    uint32_t ffvOldestCodeThatHasWrittenToThisFile = 0;
    uint32_t ffvNewestCodeThatHasWrittenToThisFile = 0;
    uint32_t ffvOldestCodeThatMayReadThisFile = 0;

    FileChunkReference fcrLegacyFreeChunkList = FileChunkReference();
    FileChunkReference fcrLegacyTransactionLog = FileChunkReference();

    uint32_t cTransactionsInLog = 0;

    uint32_t cbLegacyExpectedFileLength = 0;

    uint64_t rgbPlaceholder = 0;

    FileChunkReference fcrLegacyFileNodeListRoot = FileChunkReference();

    uint32_t cbLegacyFreeSpaceInFreeChunkList = 0;

    uint32_t ignored = 0;

    GUID guidAncestor = GUID();

    uint32_t crcName = 0;

    FileChunkReference fcrHashedChunkList = FileChunkReference();

    FileChunkReference fcrTransactionLog = FileChunkReference();

    FileChunkReference fcrFileNodeListRoot = FileChunkReference();

    FileChunkReference fcrFreeChunkList = FileChunkReference();

    uint64_t cbExpectedFileLength = 0;

    uint64_t cbFreeSpaceInFreeChunkList = 0;

    GUID guidFileVersion = GUID();

    uint64_t nFileVersionGeneration = 0;

    GUID guidDenyReadFileVersion = GUID();

    uint32_t grfDebugLogFlags = 0;

    FileChunkReference fcrDebugLog = FileChunkReference();

    FileChunkReference fcrAllocVerificationFreeChunkList = FileChunkReference();

    uint32_t bnCreated = 0;

    uint32_t bnLastWroteToThisFile = 0;

    uint32_t bnOldestWritten = 0;

    uint32_t bnNewestWritten = 0;


};


}

#endif
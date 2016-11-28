/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/*
 * This file is part of the libone project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include <cstddef>
#include <cstring>
#include <iostream>
#include <iomanip>
#include <libone/libone.h>
#include "libone_utils.h"

using std::stringstream;

namespace libone {

//	FileChunkReference::FileChunkReference() {}
//	FileChunkReference::~FileChunkReference() {}

	void FileChunkReference32::parse(librevenge::RVNGInputStream *input) {
		stp = libone::readU32(input, false);
		cb = readU32(input, false);
	}
	uint32_t FileChunkReference32::get_location() {
		return stp;
	}
	uint32_t FileChunkReference32::get_size() {
		return cb;
	}

	string FileChunkReference32::to_string() {
		std::stringstream stream;
		stream << std::hex << "stp32 " << stp << " cb32 " << cb;
		return stream.str();
	}

	void FileChunkReference32::location8() {
		stp *= 8;
	}

	void FileChunkReference32::set_all(uint32_t location, uint32_t size) {
		stp = location;
		cb = size;
	}

	void FileChunkReference64::parse(librevenge::RVNGInputStream *input) {
		stp = libone::readU64(input, false);
		cb = libone::readU64(input, false);
	}
	uint64_t FileChunkReference64::get_location() {
		return stp;
	}
	uint64_t FileChunkReference64::get_size() {
		return cb;
	}

	string FileChunkReference64::to_string() {
		std::stringstream stream;
		stream << "stp64 "  << stp << " cb64 " << cb;
		return stream.str();
	}

	void FileChunkReference64::set_all(uint64_t location, uint64_t size) {
		stp = location;
		cb = size;
	}


	void FileChunkReference64x32::parse(librevenge::RVNGInputStream *input) {
		stp = readU64(input, false);
		cb = readU32(input, false);
	}
	uint64_t FileChunkReference64x32::get_location() {
		return stp;
	}
	uint32_t FileChunkReference64x32::get_size() {
		return cb;
	}

	void FileChunkReference64x32::location8() {
		stp *= 8;
	}

	void FileChunkReference64x32::set_all(uint64_t location, uint32_t size) {
		stp = location;
		cb = size;
	}

	string FileChunkReference64x32::to_string() {
		std::stringstream stream;
		stream << std::hex << "stp64 " << stp << " cb32 " << cb;
		return stream.str();
	}

	bool FileChunkReference64x32::is_nil() {
	  if ((stp == 0xffffffffffffffff) && (cb == 0))
	    return true;
	  return false;
	}

}

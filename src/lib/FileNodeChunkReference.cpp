/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/*
 * This file is part of the libone project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include <libone/libone.h>
#include "FileNodeChunkReference.h"
#include "libone_utils.h"

namespace libone {

	FileNodeChunkReference::FileNodeChunkReference(enum stp_format format_stp, enum cb_format format_cb, long offset) :
		m_offset(offset),
		m_stp(0),
		m_cb(0),
		m_format_stp(format_stp),
		m_format_cb(format_cb)
	{}

	bool FileNodeChunkReference::is_fcrNil() {
    bool cbval = (m_cb == 0);
    switch (m_format_stp) {
      case stp_uncompressed_8:
        return (cbval && (m_stp & 0xFFFFFFFFFFFFFFFF));

      case stp_uncompressed_4:
			case stp_compressed_4:
        return (cbval && (m_stp & 0xFFFFFFFF));

			case stp_compressed_2:
				return (cbval && (m_stp & 0xFFFF));

      default:
        return false;
    }
	}

	bool FileNodeChunkReference::is_fcrZero() {
    return ((m_stp == 0) && (m_cb == 0));
	}

	uint64_t FileNodeChunkReference::get_location() {
		return m_stp;
	}

	uint64_t FileNodeChunkReference::get_size() {
		return m_cb;
	}

	void FileNodeChunkReference::parse(librevenge::RVNGInputStream *input) {
		input->seek(m_offset, librevenge::RVNG_SEEK_SET);

		switch (m_format_stp) {
			case stp_uncompressed_8:
				m_stp = readU64(input, false);
				break;
			case stp_uncompressed_4:
				m_stp = readU32(input, false);
				break;
			case stp_compressed_2:
				m_stp = readU16(input, false) * 8;
				break;
			case stp_compressed_4:
				m_stp = readU32(input, false) * 8;
				break;
			case stp_invalid:
			default:
				assert(false);
				break;
		}

		switch (m_format_cb) {
			case cb_uncompressed_4:
				m_cb = readU32(input, false);
				break;
			case cb_uncompressed_8:
				m_cb = readU64(input, false);
				break;
			case cb_compressed_1:
				m_cb = readU8(input) * 8;
				break;
			case cb_compressed_2:
				m_cb = readU16(input, false);
				break;
			case cb_invalid:
			default:
				assert(false);
				break;
		}

		return;
	}

	void FileNodeChunkReference::set_zero() {
		m_stp = 0;
    m_cb = 0;
		m_format_stp = stp_invalid;
    m_format_cb = cb_invalid;
	}

}
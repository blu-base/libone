/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/*
 * This file is part of the libone project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include <cstring>
#include <iostream>
#include <iomanip>
#include <libone/libone.h>


#include "FileNodeList.h"
#include "libone_utils.h"
using namespace std;
using std::string;

namespace libone {

  FileNodeList::FileNodeList(uint64_t new_location, uint64_t new_size) {
    location = new_location;
    size = new_size;
  }

  void FileNodeList::parse_header(librevenge::RVNGInputStream *input) {
    uint32_t expected_fragment_sequence;
		std::cout << "fragment position begin " << std::hex << input->tell() << '\n';
		next_fragment_location = input->tell() + size - 8 - 12;
		std::cout << "next fragment @ " << next_fragment_location << "\n";
		uintMagic = readU64 (input, false);
		if (uintMagic != 0xa4567ab1f5f7f4c4) {
		  cout << "uintMagic not correct; position " << input->tell() << '\n';
		  end = true;
		}
		FileNodeListID = readU32 (input, false);
		expected_fragment_sequence = readU32 (input, false);
		if (expected_fragment_sequence != nFragmentSequence) {
		  cout << "expected fragment " << nFragmentSequence << ", got " << expected_fragment_sequence << "\n";
		}
		else nFragmentSequence++;

		std::cout << "fragment position end " << input->tell() << " nFragmentSequence " << nFragmentSequence << '\n';
  }

	string FileNodeList::to_string() {
		std::stringstream stream;
		stream << std::hex << "uintMagic " << uintMagic << '\n';
		stream << std::dec << "FileNodeListID " << FileNodeListID << '\n';
		stream << "nFragmentSequence " << nFragmentSequence << '\n';
		for (FileNode i: rgFileNodes)
			stream << i.to_string() << '\n';
		return stream.str();
	}

	FileNode FileNodeList::get_next_node(librevenge::RVNGInputStream *input) {
	  FileChunkReference next_fragment;
	  FileNode node;
	  if (!header_parsed) {
	    parse_header(input);
	    header_parsed = true;
	  }
	  node.parse(input);
    std::cout << node.to_string();
	  std::cout << "next fragment? " << next_fragment_location << "\n";
	  if (node.isEnd()) {
      input->seek(next_fragment_location, librevenge::RVNG_SEEK_SET);
      std::cout << "what's up in here? " << input->tell();
      next_fragment.parse(input, FileChunkReference::mode::Type64x32);

      if (readU64(input, false) != 0x8BC215C38233BA4B) {
        cout << "footer not correct, position " << input->tell() << "\n";
        end = true;
      }

      if (next_fragment.is_fcrNil()) end = true;
      else {
        location = next_fragment.get_location();
        size = next_fragment.get_size();
        input->seek(location, librevenge::RVNG_SEEK_SET);
        parse_header(input);
        node.parse(input);
      }
	  }

	  return node;
	}

	bool FileNodeList::is_end() {
	  return end;
	}
}



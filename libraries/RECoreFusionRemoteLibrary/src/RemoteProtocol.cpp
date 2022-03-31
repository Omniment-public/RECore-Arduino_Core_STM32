/* RECore-PyRECore --- A Python library for control of RECore

   Copyright (c) 2021 Omniment, Inc.

   Permission is hereby granted, free of charge, to any person obtaining a copy
   of this software and associated documentation files (the "Software"), to deal
   in the Software without restriction, including without limitation the rights
   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
   copies of the Software, and to permit persons to whom the Software is
   furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in
   all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
   SOFTWARE. */

#include "RemoteProtocol.h"
#include "Arduino.h"
#include <string.h>

namespace PyRECore {

uint8_t RemoteProtocol::_buffer[RemoteProtocol::BUFFER_SIZE] = {};

Packet::Error RemoteProtocol::read(Packet::Request **req) {
  // Receives a header.
  _link.read_sync(_buffer, 1);
  auto header = static_cast<Packet::Header>(_buffer[0]);

  if (header != Packet::Header::REQ) {
    return Packet::Error::INVALID_HEADER; // This is NOT a packet.
  }

  // Receives the length of a payload.
  _link.read_sync(_buffer + 1, 1);
  auto payload_length = _buffer[1];

  if (payload_length > BUFFER_SIZE - sizeof(Packet::Request)) {
    return Packet::Error::TOO_LARGE_DATA; // Too large data
  }

  // Receives the body of a packet.
  auto remaining_length = sizeof(Packet::Request) - 2 + payload_length;
  _link.read_sync(_buffer + 2, remaining_length);

  *req = reinterpret_cast<Packet::Request *>(_buffer);

  // Receives a CRC code.
  uint8_t actual_crc;
  _link.read_sync(&actual_crc, 1);

  // Checks CRC codes.
  uint8_t expected_crc = (*req)->get_crc8();
  if (actual_crc != expected_crc) {
    return Packet::Error::INVALID_CRC; // CRC verification failure.
  }

  return Packet::Error::OK;
}

bool RemoteProtocol::write(Packet::Header header, const void *src, size_t len) {
  if (len > BUFFER_SIZE - sizeof(Packet::Response)) {
    return false; // Too large data
  }

  const Packet::Response resp = {.header = header, .payload_length = len};

  // Copies a response header
  memcpy(_buffer, &resp, sizeof(resp));
  // Copies payload
  if (src != nullptr) {
    memcpy(_buffer + sizeof(resp), src, len);
  }

  _link.write_sync(_buffer, sizeof(Packet::Response) + len);

  auto crc = reinterpret_cast<Packet::Response *>(_buffer)->get_crc8();
  _link.write_sync(&crc, sizeof(crc));

  return true;
}

} // namespace PyRECore

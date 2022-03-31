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

#ifndef OMNIMENT_PYRECORE_PACKET_H_
#define OMNIMENT_PYRECORE_PACKET_H_

#include "Crc.h"

namespace PyRECore {
namespace Packet {

/**
 * The kind of a packet.
 */
enum class Header : uint8_t {
  REQ = 0x3C,  /// Requests
  ACK = 0xFC,  /// Successful responses
  NACK = 0x3F, /// Failed responses
};

enum class Error : uint8_t {
  OK = 0x00, /// Not an error
  INVALID_HEADER = 0x01,
  INVALID_OPCODE = 0x02,
  INVALID_CRC = 0x03,
  TOO_LARGE_DATA = 0x04,
};

struct Request {
  Header header;
  uint8_t payload_length;
  uint16_t opcode;   /// The identifier of a function
  uint8_t payload[]; /// An array of arguments of a function

  inline uint8_t get_crc8() const {
    return PyRECore::get_crc8(reinterpret_cast<const uint8_t *>(this),
                              sizeof(Request) + payload_length);
  }
};

struct Response {
  Header header;
  uint8_t payload_length;
  uint8_t payload[]; /// A returned value

  inline uint8_t get_crc8() const {
    return PyRECore::get_crc8(reinterpret_cast<const uint8_t *>(this),
                              sizeof(Response) + payload_length);
  }
};

} // namespace Packet
} // namespace PyRECore

#endif // !OMNIMENT_PYRECORE_PACKET_H_

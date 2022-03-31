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

#ifndef OMNIMENT_PYRECORE_REMOTE_PROTOCOL_H_
#define OMNIMENT_PYRECORE_REMOTE_PROTOCOL_H_

#include "DataLink.h"
#include "Packet.h"

namespace PyRECore {

class RemoteProtocol {
public:
  static constexpr size_t BUFFER_SIZE = sizeof(Packet::Request) + 256;

  explicit RemoteProtocol(DataLink &link) : _link(link) {}

  Packet::Error read(Packet::Request **req);

  bool write(Packet::Header header, const void *src, size_t len);

private:
  static uint8_t _buffer[BUFFER_SIZE];
  DataLink &_link;
};

} // namespace PyRECore

#endif // !OMNIMENT_PYRECORE_REMOTE_PROTOCOL_H_

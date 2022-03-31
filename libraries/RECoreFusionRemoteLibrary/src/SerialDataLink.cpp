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

#ifndef OMNIMENT_PYRECORE_SERIAL_DATALINK_H_
#define OMNIMENT_PYRECORE_SERIAL_DATALINK_H_

#include "SerialDataLink.h"
#include "HardwareSerial.h"

namespace PyRECore {

void SerialDataLink::read_sync(void *buf, size_t len) {
  int8_t *p = reinterpret_cast<int8_t *>(buf);

  for (size_t i = 0; i < len; ++i) {
    while (_serial.available() == 0) {
      // busy wait
    }
    p[i] = _serial.read();
  }
}

void SerialDataLink::write_sync(const void *data, size_t len) {
  _serial.write(reinterpret_cast<const uint8_t *>(data), len);
  _serial.flush();
}

} // namespace PyRECore

#endif // !OMNIMENT_PYRECORE_SERIAL_DATALINK_H_

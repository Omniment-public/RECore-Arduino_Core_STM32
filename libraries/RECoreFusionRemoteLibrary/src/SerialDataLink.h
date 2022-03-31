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

#ifndef OMNIMENT_PYRECORE_SERIAL_DATA_LINK_H_
#define OMNIMENT_PYRECORE_SERIAL_DATA_LINK_H_

#include "DataLink.h"
#include "HardwareSerial.h"

namespace PyRECore {

class SerialDataLink : public DataLink {
public:
  explicit SerialDataLink(HardwareSerial &serial) : _serial(serial) {}

  virtual void read_sync(void *buf, size_t len) override;

  virtual void write_sync(const void *src, size_t len) override;

private:
  HardwareSerial &_serial;
};

} // namespace PyRECore

#endif // !OMNIMENT_PYRECORE_SERIAL_DATA_LINK_H_

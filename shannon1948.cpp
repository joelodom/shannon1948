// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include "shannon1948.hpp"
#include "gtest/gtest.h"
#include <cstdlib>

/* static */ int shannon1948::EntropySource::s_memory_allocations_ = 0;
/* static */ int shannon1948::EntropySource::s_memory_deallocations_ = 0;

/* static */ shannon1948::MESSAGE
   shannon1948::EntropySource::GenerateBinaryMessage(double p, int length)
{
   // allocate the message
   MESSAGE message = new SYMBOL[length];
   ++s_memory_allocations_;

   // populate the message
   for (int i = 0; i < length; i++)
   {
      // TODO: Switch to a better random number generator / experiment with
      // different generators.  Any experiment here is highly dependent on
      // having a true random number source, so experiments may really only
      // be measuring the entropy of the PRNG.

      int r = rand(); // 0 to RAND_MAX, inclusive of both endpoints
      while (r == RAND_MAX) // don't allow RAND_MAX
         r = rand();
      message[i] = rand() < p*RAND_MAX ? 'A' : 'B';
   }

   return message;
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  int rv = RUN_ALL_TESTS();
  return rv;
}

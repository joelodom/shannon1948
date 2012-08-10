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

#include <string>

namespace shannon1948
{
   // EntropySource is a class to generate messages that have an expected amount
   // of entropy.

   class EntropySource
   {
   public:

      // GenerateBinaryMessage generates a very simple message with two possible
      // symbols.  p is the probability of generating the first symbol, so the
      // probability of generating the second symbol is (1-p).  See Fig. 7 in
      // Shannon's paper for a graph of how p will affect H.
      static void GenerateBinaryMessage(
         double p, size_t length, std::string& output);
   };

   // EntropyCalculator uses statistical methods based on the section of
   // Shannon's paper "The Entropy of an Information Source" to estimate
   // the entropy contained in a message.

   class EntropyCalculator
   {
   public:

      // G_N uses the simpler, but less precise formula to calculate entropy.
      // G_N = -(1/N)*sum(p(B_i)*log2(p(B_i))), where the sum is over all
      // sequences B_i containing N symbols.  As N grows, the limit approaches
      // the entropy, H.
      static double G_N(std::string message, size_t N);
   };
}

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

namespace shannon1948
{
   typedef char SYMBOL;
   typedef SYMBOL* MESSAGE; // an array of symbols

   // EntropySource is a class to generate messages that have an expected amount
   // of entropy.

   class EntropySource
   {
   public:
      // GenerateBinaryMessage generates a very simple message with two possible
      // symbols.  p is the probability of generating the first symbol, so the
      // probability of generating the second symbol is (1-p).  See Fig. 7 in
      // Shannon's paper for a graph of how p will affect H.  The returned
      // message should be freed with FreeMessage.
      static MESSAGE GenerateBinaryMessage(double p, int length);

      // Use FreeMessage to free a previously allocated message.
      static void FreeMessage(MESSAGE message)
      {
         delete[] message;
         ++s_memory_deallocations_;
      }

      // Use MemoryCheck to check that all allocated messages have been freed.
      static bool MemoryCheck()
      {
         return s_memory_allocations_ == s_memory_deallocations_;
      }

   private:
      static int s_memory_allocations_;
      static int s_memory_deallocations_;
   };
}

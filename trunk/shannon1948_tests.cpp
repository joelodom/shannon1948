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

using namespace shannon1948;

TEST(overall_tests, gtest_test)
{
   EXPECT_TRUE(true) << "Simple test of GTest failed.";
}

TEST(entropy_source_tests, test_p_zero)
{
   // p = 0.0 means that messages should be entirely Bs
   const int LENGTH = 100;
   std::string message;
   EntropySource::GenerateBinaryMessage(0.0, LENGTH, message);
   for (int i = 0; i < LENGTH; i++)
      ASSERT_TRUE(message[i] == 'B') << "Expected all Bs.";
}

TEST(entropy_source_tests, test_p_one)
{
   // p = 1.0 means that messages should be entirely As
   const int LENGTH = 100;
   std::string message;
   EntropySource::GenerateBinaryMessage(1.0, LENGTH, message);
   for (int i = 0; i < LENGTH; i++)
      ASSERT_TRUE(message[i] == 'A') << "Expected all As.";
}

TEST(entropy_source_tests, test_p_half)
{
   // p = 0.5 means that messages should contain As and Bs
   const int LENGTH = 256;
   std::string message;
   EntropySource::GenerateBinaryMessage(0.5, LENGTH, message);

   bool found_a = false;
   bool found_b = false;

   for (int i = 0; i < LENGTH; i++)
   {
      if (message[i] == 'A')
         found_a = true;
      if (message[i] == 'B')
         found_b = true;
      if (found_a && found_b)
         break;
   }

   EXPECT_TRUE(found_a && found_b) << "If all works as expected, "
      "the probability of this test failing is negligible.";
}

TEST(entropy_source_tests, test_p_tenth)
{
   // p = 0.1 means that messages should contain mostly Bs
   const int LENGTH = 256;
   std::string message;
   EntropySource::GenerateBinaryMessage(0.1, LENGTH, message);

   int a_count = 0;
   int b_count = 0;

   for (int i = 0; i < LENGTH; i++)
   {
      if (message[i] == 'A')
         ++a_count;
      if (message[i] == 'B')
         ++b_count;
   }

   EXPECT_TRUE(b_count > a_count) << "If all works as expected, "
      "the probability of this test failing is negligible.";
}

TEST(entropy_calculator_tests, test_zero_entropy_message)
{
   // p = 0.0 means that messages should be entirely Bs
   const int LENGTH = 100;
   std::string message;
   EntropySource::GenerateBinaryMessage(0.0, LENGTH, message);
   double entropy = EntropyCalculator::G_N(message, 4);
   EXPECT_TRUE(entropy == 0.0) << "Expected no entropy.";
}

TEST(entropy_calculator_tests, test_max_entropy_message_1)
{
   // p = 0.5 means that messages should contain As and Bs
   const int LENGTH = 1024;
   std::string message;
   EntropySource::GenerateBinaryMessage(0.5, LENGTH, message);
   double entropy = EntropyCalculator::G_N(message, 1);
   EXPECT_NEAR(entropy, 1.0, 0.05) << "If all works as expected, "
      "the probability of this test failing is small.";
}

TEST(entropy_calculator_tests, test_max_entropy_message_8)
{
   // p = 0.5 means that messages should contain As and Bs
   const int LENGTH = 8192;
   std::string message;
   EntropySource::GenerateBinaryMessage(0.5, LENGTH, message);
   double entropy = EntropyCalculator::G_N(message, 8);
   EXPECT_NEAR(entropy, 1.0, 0.1) << "If all works as expected, "
      "the probability of this test failing is small.";
}

TEST(entropy_calculator_tests, test_max_entropy_message_16)
{
   // p = 0.5 means that messages should contain As and Bs
   const int LENGTH = 1024*1024; // 1 MB
   std::string message;
   EntropySource::GenerateBinaryMessage(0.5, LENGTH, message);
   double entropy = EntropyCalculator::G_N(message, 16);
   EXPECT_NEAR(entropy, 1.0, 0.1) << "If all works as expected, "
      "the probability of this test failing is small.";
}

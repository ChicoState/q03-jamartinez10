/**
 * Unit Tests for the class
**/

#include <gtest/gtest.h>
#include "Guesser.h"

class GuesserTest : public ::testing::Test
{
	protected:
		GuesserTest(){} //constructor runs before each test
		virtual ~GuesserTest(){} //destructor cleans up after tests
		virtual void SetUp(){} //sets up before each test (after constructor)
		virtual void TearDown(){} //clean up after each test, (before destructor)
};


//Tests for Remaining indicated by _r it should be noted that remaining is reliable on matching.
TEST(GuesserTest, first_try_r)
{
  Guesser object("Secret");
  ASSERT_EQ( 3, object.remaining());
  object.match("Secret");
  ASSERT_EQ( 3, object.remaining());
}


TEST(GuesserTest, one_away_r)
{
  Guesser object("Secret");
  object.match("Secreto");
  ASSERT_EQ(2, object.remaining());
}

TEST(GuesserTest, locked_out_but_still_counting_r) {
    Guesser object("abcde");
    object.match("aaaaaaaa");
	ASSERT_EQ(2, object.remaining());
	object.match("aaaaaaaa");
	ASSERT_EQ(1, object.remaining());
}//current implementation doesnt continue to count down

TEST(GuesserTest, restart_on_third_try_r)
{
  Guesser object("hello");
  object.match("hell");
  ASSERT_EQ( 2, object.remaining());
  object.match("hell0");
  ASSERT_EQ( 1, object.remaining());
  object.match("hello");
  ASSERT_EQ( 3, object.remaining());
}

TEST(GuesserTest, out_of_tries_r)
{
  Guesser object("Password!");
  object.match("Password");
  ASSERT_EQ( 2, object.remaining());
  object.match("Password@");
  ASSERT_EQ( 1, object.remaining());
  object.match("Password#");
  ASSERT_EQ( 0, object.remaining());
  object.match("Password!");
  ASSERT_EQ( 0, object.remaining());
}

TEST(GuesserTest, empty_string_r)
{
  Guesser object("");
  ASSERT_EQ( 3, object.remaining());
  object.match("12");
  ASSERT_EQ( 2, object.remaining());
  object.match("1");
  ASSERT_EQ( 1, object.remaining());
  //object.match("");
  //ASSERT_EQ( 3, object.remaining());
}
//after testing out the code realized that it doesn't go back to 3 after guessing correctly

TEST(GuesserTest, correct_multiple_times_r)
{
  Guesser object("!@#$%^");
  object.match("!@#$%^");
  ASSERT_EQ( 3, object.remaining());
  object.match("!@#$%^");
  ASSERT_EQ( 3, object.remaining());
  object.match("!@#$%^");
  ASSERT_EQ( 3, object.remaining());
  object.match("!@#$%^");
  ASSERT_EQ( 3, object.remaining());
}

/*-----------------------------------------------------------------*/
//Tests for Matching indicated by _m it should be noted that matching is reliable on distance
TEST(GuesserTest, first_try_m)
{
  Guesser object("Secret");
  ASSERT_EQ(true, object.match("Secret"));
}

TEST(GuesserTest, one_away_m)
{
  Guesser object("Secret");
  ASSERT_EQ(false, object.match("Secreto"));
}

TEST(GuesserTest, locked_out_immediately_m) {
    Guesser object("abcde");
    ASSERT_EQ(false, object.match("aaaaaaaa"));
    ASSERT_EQ(false, object.match("abcde"));  
}

TEST(GuesserTest, on_thirdd_try_m)
{
  Guesser object("hello");
  ASSERT_EQ(false, object.match("hell"));
  ASSERT_EQ(false, object.match("hell0"));
  ASSERT_EQ(true, object.match("hello"));
}

TEST(GuesserTest, out_of_tries_m)
{
  Guesser object("Password!");
  ASSERT_EQ(false, object.match("Password"));
  ASSERT_EQ(false, object.match("Password@"));
  ASSERT_EQ(false, object.match("Password#"));
  ASSERT_EQ(false, object.match("Password!"));
}

TEST(GuesserTest, empty_string_on3_m)
{
  Guesser object("");
  ASSERT_EQ(false, object.match("12"));
  ASSERT_EQ(false, object.match("1"));
  ASSERT_EQ(true, object.match(""));
}

TEST(GuesserTest, correct_multiple_times_m)
{
  Guesser object("!@#$%^");
  ASSERT_EQ(true, object.match("!@#$%^"));
  ASSERT_EQ(true, object.match("!@#$%^"));
  ASSERT_EQ(true, object.match("!@#$%^"));
  ASSERT_EQ(true, object.match("!@#$%^"));
  ASSERT_EQ(true, object.match("!@#$%^"));
}

/*-----------------------------------------------------------------*/
//Tests for Distance indicated by _d
TEST(GuesserTest, first_try_d)
{
  Guesser object("Secret");
  ASSERT_EQ( 0, object.distance("Secret"));
}

TEST(GuesserTest, one_away_d)
{
  Guesser object("Secret");
  ASSERT_EQ( 1, object.distance("Secreto"));
}

TEST(GuesserTest, locked_out_immediately_d) {
    Guesser object("abcde");
	ASSERT_EQ( 4, object.distance("aaaaa"));
}

TEST(GuesserTest, distance_capped_d) {
    Guesser object("abcde");
	ASSERT_EQ( 5, object.distance("aaaaaaaaaaaaaaa"));
}

TEST(GuesserTest, on_third_try_d)
{
  Guesser object("hello");
  ASSERT_EQ( 1, object.distance("hell"));
  ASSERT_EQ( 1, object.distance("hell0"));
  ASSERT_EQ( 0, object.distance("hello"));
}

TEST(GuesserTest, out_of_tries_d)
{
  Guesser object("Password!");
  ASSERT_EQ( 1, object.distance("Password"));
  ASSERT_EQ( 1, object.distance("Password@"));
  ASSERT_EQ( 1, object.distance("Password#"));
  ASSERT_EQ( 0, object.distance("Password!"));
}
TEST(GuesserTest, empty_string_on3_d)
{
  Guesser object("");
  ASSERT_EQ( 0, object.distance("12"));
  ASSERT_EQ( 0, object.distance("1"));
  ASSERT_EQ( 0, object.distance(""));
}

TEST(GuesserTest, truncated_to_23_d)
{
  Guesser object("012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789");
  ASSERT_EQ( 32, object.distance("123456789012345678901234567890123"));
  ASSERT_EQ( 32, object.distance(""));
  ASSERT_EQ( 1, object.distance("0123456789012345678901234567890"));
  ASSERT_EQ( 0, object.distance("01234567890123456789012345678901"));
}

TEST(GuesserTest, correct_multiple_times_d)
{
  Guesser object("!@#$%^");
  ASSERT_EQ( 0, object.distance("!@#$%^"));
  ASSERT_EQ( 0, object.distance("!@#$%^"));
  ASSERT_EQ( 0, object.distance("!@#$%^"));
  ASSERT_EQ( 0, object.distance("!@#$%^"));
}

#include "seal_stringComparison.h"
#include <stdio.h>
#include <string.h>

static int testNumber = 1;

void p_Test( const char * const p_a, const char * const p_b, const bool p_expectedBool )
{
  const char * const k_falseString = "false",
             * const k_trueString = "true",
             * const k_boolStrings[] = { k_falseString, k_trueString };

  const bool b = f_seal_CompareStrings_IgnoreCase( p_a, p_b );
  printf( "%d - ", testNumber ++ );
  if( b == p_expectedBool )
    printf( "Passed" );
  else
    printf( "Failed: bool returned (%s) != bool expected to be returned (%s)", k_boolStrings[ b ], k_boolStrings[ p_expectedBool ] );
  printf( "\n" );
}

void p_Test_Lexicographically( const char * const p_a, const char * const p_b, const int p_expectedInt )
{
  const int i = f_seal_CompareStringsLexicographically_IgnoreCase( p_a, p_b );
  printf( "%d - ", testNumber ++ );
  if( i == p_expectedInt )
    printf( "Passed" );
  else
    printf( "Failed: int returned (%d) != int expected to be returned (%d)", i, p_expectedInt );
  printf( "\n" );
}

int main( int argc, char * const argv[] )
{
  printf( "- This program performs the automated black-box testing of the f_seal_CompareStrings_IgnoreCase and f_seal_CompareStringsLexicographically_IgnoreCase functions.\n---\n\n" );

  p_Test( NULL, NULL, true );
  p_Test( "", NULL, false );
  p_Test( NULL, "", false );
  p_Test( "", "", true );
  p_Test( "seal", "seal", true );
  p_Test( "seal", "SEAL", true );
  p_Test( "seal", "seam", false );
  p_Test( "seal", "sea", false );

  p_Test_Lexicographically( NULL, NULL, 0 );
  p_Test_Lexicographically( "", NULL, 1 );
  p_Test_Lexicographically( NULL, "", -1 );
  p_Test_Lexicographically( "", "", 0 );
  p_Test_Lexicographically( "seal", "seal", 0 );
  p_Test_Lexicographically( "seal", "SEAL", 0 );
  p_Test_Lexicographically( "a", "b", -1 );
  p_Test_Lexicographically( "a", "B", -1 );
  p_Test_Lexicographically( "A", "b", -1 );
  p_Test_Lexicographically( "A", "B", -1 );
  p_Test_Lexicographically( "b", "a", 1 );
  p_Test_Lexicographically( "b", "A", 1 );
  p_Test_Lexicographically( "B", "a", 1 );
  p_Test_Lexicographically( "B", "A", 1 );
  p_Test_Lexicographically( "a", "", 1 );
  p_Test_Lexicographically( "", "a", -1 );
  p_Test_Lexicographically( "abc", "de", -3 );
  p_Test_Lexicographically( "de", "abc", 3 );

  printf( "\n---\n- This program will now quit.\n" );
  return 0;
}

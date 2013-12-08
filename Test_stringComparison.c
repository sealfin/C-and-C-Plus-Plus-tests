#include "seal_stringComparison.h"
#include <stdio.h>

void p_Test( const char * const p_a, const char * const p_b, const bool p_expectedBool )
{
  const char * const k_falseString = "false",
             * const k_trueString = "true",
             * const k_boolStrings[] = { k_falseString, k_trueString };

  static int testNumber = 1;
  const bool b = f_seal_CompareStrings_IgnoreCase( p_a, p_b );
  printf( "%d - ", testNumber ++ );
  if( b == p_expectedBool )
    printf( "Passed" );
  else
    printf( "Failed: bool returned (%s) != bool expected to be returned (%s)", k_boolStrings[ b ], k_boolStrings[ p_expectedBool ] );
  printf( "\n" );
}

int main( int argc, char * const argv[] )
{
  printf( "- This program performs the automated black-box testing of the f_seal_CompareStrings_IgnoreCase function.\n---\n\n" );

  p_Test( NULL, NULL, true );
  p_Test( "", NULL, false );
  p_Test( NULL, "", false );
  p_Test( "", "", true );
  p_Test( "seal", "seal", true );
  p_Test( "seal", "SEAL", true );
  p_Test( "seal", "seam", false );
  p_Test( "seal", "sea", false );

  printf( "\n---\n- This program will now quit.\n" );
  return 0;
}

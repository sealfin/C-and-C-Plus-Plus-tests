#include "seal_intToHexString.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void p_Test( const int p_int, const bool p_uppercase, const bool p_prefix, const bool p_uppercasePrefix, const bool p_explicitSign, const char * const p_expectedString )
{
  static int testNumber = 1;
  char *s = f_seal_IntToHexString( p_int, p_uppercase, p_prefix, p_uppercasePrefix, p_explicitSign );
  printf( "%d - ", testNumber ++ );
  if( strcmp( s, p_expectedString ) == 0 )
    printf( "Passed" );
  else
    printf( "Failed: string returned (\"%s\") != string expected to be returned (\"%s\")", s, p_expectedString );
  printf( "\n" );
  free( s );
}

int main( int argc, const char *argv[] )
{
  printf( "- This program performs the automated black-box testing of the f_seal_IntToHexString function.\n---\n\n" );

  p_Test( 0, false, false, false, false, "0" );
  p_Test( 0, false, false, false, true, "0" );
  p_Test( 0, true, false, false, false, "0" );
  p_Test( 0, true, false, false, true, "0" );
  p_Test( 0, false, true, false, false, "0x0" );
  p_Test( 0, false, true, false, true, "0x0" );
  p_Test( 0, true, true, false, false, "0x0" );
  p_Test( 0, true, true, false, true, "0x0" );
  p_Test( 0, false, false, true, false, "0" );
  p_Test( 0, false, false, true, true, "0" );
  p_Test( 0, false, true, true, false, "0X0" );
  p_Test( 0, false, true, true, true, "0X0" );
  p_Test( 0, true, true, true, false, "0X0" );
  p_Test( 0, true, true, true, true, "0X0" );
  p_Test( 0, true, false, true, false, "0" );
  p_Test( 0, true, false, true, true, "0" );

  p_Test( 1983, false, false, false, false, "7bf" );
  p_Test( 1983, false, false, false, true, "+7bf" );
  p_Test( 1983, true, false, false, false, "7BF" );
  p_Test( 1983, true, false, false, true, "+7BF" );
  p_Test( 1983, false, true, false, false, "0x7bf" );
  p_Test( 1983, false, true, false, true, "+0x7bf" );
  p_Test( 1983, true, true, false, false, "0x7BF" );
  p_Test( 1983, true, true, false, true, "+0x7BF" );
  p_Test( 1983, false, false, true, false, "7bf" );
  p_Test( 1983, false, false, true, true, "+7bf" );
  p_Test( 1983, false, true, true, false, "0X7bf" );
  p_Test( 1983, false, true, true, true, "+0X7bf" );
  p_Test( 1983, true, true, true, false, "0X7BF" );
  p_Test( 1983, true, true, true, true, "+0X7BF" );
  p_Test( 1983, true, false, true, false, "7BF" );
  p_Test( 1983, true, false, true, true, "+7BF" );

  p_Test( -1983, false, false, false, false, "-7bf" );
  p_Test( -1983, false, false, false, true, "-7bf" );
  p_Test( -1983, true, false, false, false, "-7BF" );
  p_Test( -1983, true, false, false, true, "-7BF" );
  p_Test( -1983, false, true, false, false, "-0x7bf" );
  p_Test( -1983, false, true, false, true, "-0x7bf" );
  p_Test( -1983, true, true, false, false, "-0x7BF" );
  p_Test( -1983, true, true, false, true, "-0x7BF" );
  p_Test( -1983, false, false, true, false, "-7bf" );
  p_Test( -1983, false, false, true, true, "-7bf" );
  p_Test( -1983, false, true, true, false, "-0X7bf" );
  p_Test( -1983, false, true, true, true, "-0X7bf" );
  p_Test( -1983, true, true, true, false, "-0X7BF" );
  p_Test( -1983, true, true, true, true, "-0X7BF" );
  p_Test( -1983, true, false, true, false, "-7BF" );
  p_Test( -1983, true, false, true, true, "-7BF" );

  printf( "\n---\n- This program will now quit.\n" );
  return 0;
}

#ifdef __cplusplus
extern "C"
{
#endif

#include "seal_intToString.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void p_Test( const int p_int, const bool p_explicitSign, const char * const p_expectedString )
{
  static int testNumber = 1;
  char *s = f_seal_IntToString( p_int, p_explicitSign );
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
  printf( "- This program performs the automated black-box testing of the f_seal_IntToString function.\n---\n\n" );

  p_Test( 0, false, "0" );
  p_Test( 0, true, "0" );
  p_Test( 1983, false, "1983" );
  p_Test( 1983, true, "+1983" );
  p_Test( -1983, false, "-1983" );
  p_Test( -1983, true, "-1983" );

  printf( "\n---\n- This program will now quit.\n" );
  return 0;
}

#ifdef __cplusplus
}
#endif

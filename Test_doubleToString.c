#ifdef __cplusplus
extern "C"
{
#endif

#include "seal_doubleToString.h"
#include <stdio.h>
#include <string.h>

void p_Test( const double p_double, const size_t p_numberOfFractionalPartDigits, const bool p_explicitSign, const char * const p_expectedString )
{
  static int testNumber = 1;
  char *s = f_seal_DoubleToString( p_double, p_numberOfFractionalPartDigits, p_explicitSign );
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
  printf( "- This program performs the automated black-box testing of the f_seal_DoubleToString function.\n---\n\n" );

  p_Test( 0, 0, false, "0" );
  p_Test( 0, 0, true, "0" );
  p_Test( 0, 3, false, "0.000" );
  p_Test( 0, 3, true, "0.000" );

  p_Test( 19.83, 0, false, "19" );
  p_Test( 19.83, 0, true, "+19" );
  p_Test( 19.83, 1, false, "19.8" );
  p_Test( 19.83, 1, true, "+19.8" );
  p_Test( 19.83, 3, false, "19.830" );
  p_Test( 19.83, 3, true, "+19.830" );

  p_Test( -19.83, 0, false, "-19" );
  p_Test( -19.83, 0, true, "-19" );
  p_Test( -19.83, 1, false, "-19.8" );
  p_Test( -19.83, 1, true, "-19.8" );
  p_Test( -19.83, 3, false, "-19.830" );
  p_Test( -19.83, 3, true, "-19.830" );

  printf( "\n---\n- This program will now quit.\n" );
  return 0;
}

#ifdef __cplusplus
}
#endif

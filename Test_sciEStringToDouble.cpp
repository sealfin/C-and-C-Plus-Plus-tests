#include "seal_sciEStringToDouble_C.h"
#ifdef __cplusplus
#include "seal_sciEStringToDouble.h"
#endif

static int testNumber = 1;

#ifdef __cplusplus
#define M_C_PLUS_PLUS( p ) p
#else
#define M_C_PLUS_PLUS( p )
#endif

void p_PrintSpaces( signed int p )
{
  for( ; p > 0; p -- )
    printf( " " );
}

void p_Test( const char * const p_string, const bool p_errorExpected, const double p_doubleExpected )
{
  const char * const k_falseString = "false",
             * const k_trueString = "true",
             * const k_boolStrings[] = { k_falseString, k_trueString };

  signed int spaces;
  bool passed = true;
  double d = f_seal_SciEStringToDouble_C( p_string );
  bool error = f_seal_SciEStringToDouble_Error_C();
  printf( "%d%n - ", testNumber ++, &spaces );
  if( error != p_errorExpected )
  {
    passed = false;
    printf( "Failed" );
    M_C_PLUS_PLUS( printf( " (C)" ); )
    printf( ": error (%s) != error expected (%s)", k_boolStrings[ error ], k_boolStrings[ p_errorExpected ] );
  }
  else
    if( !error )
      if( d != p_doubleExpected )
      {
        passed = false;
        printf( "Failed" );
        M_C_PLUS_PLUS( printf( " (C)" ); )
        printf( ": double (%f) != double expected (%f)", d, p_doubleExpected );
      }
  if( passed )
  {
    printf( "Passed" );
    M_C_PLUS_PLUS( printf( " (C)" ); )
  }
  printf( "\n" );

  #ifdef __cplusplus
  passed = true;
  p_PrintSpaces( spaces );
  printf( " - " );
  try
  {
    d = f_seal_SciEStringToDouble( p_string );
    if( p_errorExpected )
    {
      passed = false;
      printf( "Failed (C++): exception expected" );
    }
    else
      if( d != p_doubleExpected )
      {
        passed = false;
        printf( "Failed (C++): double (%f) != double expected (%f)", d, p_doubleExpected );
      }
  }
  catch( const char *ip_thrown )
  {
    if( !p_errorExpected )
    {
      passed = false;
      printf( "Failed (C++): exception not expected" );
    }
  }
  if( passed )
    printf( "Passed (C++)" );
  printf( "\n" );
  #endif
}

int main( int argc, const char *argv[] )
{
  signed int spaces;

  printf( "- This program peforms the (semi-)automated black-box testing of the f_seal_SciEStringToDouble(_C) function(s).\n---\n\n" );

  p_seal_SciEStringToDouble_PrintErrorsTo_C( NULL );

  p_Test( NULL, true, 0 );

  p_Test( "", true, 0 );

  p_Test( "e", true, 0 );
  p_Test( "E", true, 0 );

  p_Test( "e0", true, 0 );
  p_Test( "E0", true, 0 );

  p_Test( "0e", true, 0 );
  p_Test( "0E", true, 0 );

  p_Test( "0e+", true, 0 );
  p_Test( "0E+", true, 0 );
  p_Test( "0e-", true, 0 );
  p_Test( "0E-", true, 0 );

  p_Test( "0eX", true, 0 );
  p_Test( "0EX", true, 0 );
  p_Test( "0e+X", true, 0 );
  p_Test( "0E+X", true, 0 );
  p_Test( "0e-X", true, 0 );
  p_Test( "0E-X", true, 0 );

  p_Test( "+e0", true, 0 );
  p_Test( "+E0", true, 0 );
  p_Test( "-e0", true, 0 );
  p_Test( "-E0", true, 0 );

  p_Test( "+.e0", true, 0 );
  p_Test( "+.E0", true, 0 );
  p_Test( "-.e0", true, 0 );
  p_Test( "-.E0", true, 0 );

  p_Test( ".e0", true, 0 );
  p_Test( ".E0", true, 0 );

  p_Test( "Xe0", true, 0 );
  p_Test( "XE0", true, 0 );
  p_Test( "+Xe0", true, 0 );
  p_Test( "+XE0", true, 0 );
  p_Test( "-Xe0", true, 0 );
  p_Test( "-XE0", true, 0 );

  p_Test( "1983e0", false, 1983 );
  p_Test( "1983e+0", false, 1983 );
  p_Test( "1983e-0", false, 1983 );
  p_Test( "+1983e0", false, 1983 );
  p_Test( "+1983e+0", false, 1983 );
  p_Test( "+1983e-0", false, 1983 );
  p_Test( "-1983e0", false, -1983 );
  p_Test( "-1983e+0", false, -1983 );
  p_Test( "-1983e-0", false, -1983 );

  p_Test( "19.83e2", false, 1983 );
  p_Test( "19.83e+2", false, 1983 );
  p_Test( "+19.83e2", false, 1983 );
  p_Test( "+19.83e+2", false, 1983 );
  p_Test( "-19.83e2", false, -1983 );
  p_Test( "-19.83e+2", false, -1983 );

  p_Test( ".1983e4", false, 1983 );
  p_Test( ".1983e+4", false, 1983 );
  p_Test( "+.1983e4", false, 1983 );
  p_Test( "+.1983e+4", false, 1983 );
  p_Test( "-.1983e4", false, -1983 );
  p_Test( "-.1983e+4", false, -1983 );

  p_Test( "1983.e0", false, 1983 );
  p_Test( "1983.e+0", false, 1983 );
  p_Test( "+1983.e0", false, 1983 );
  p_Test( "+1983.e+0", false, 1983 );
  p_Test( "-1983.e0", false, -1983 );
  p_Test( "-1983.e+0", false, -1983 );

  p_Test( "19830e-1", false, 1983 );
  p_Test( "+19830e-1", false, 1983 );
  p_Test( "-19830e-1", false, -1983 );
  p_Test( "19830.e-1", false, 1983 );
  p_Test( "+19830.e-1", false, 1983 );
  p_Test( "-19830.e-1", false, -1983 );

  p_Test( "0", false, 0 );
  p_Test( "+0", false, 0 );
  p_Test( "-0", false, 0 );
  p_Test( "0.0", false, 0 );
  p_Test( "+0.0", false, 0 );
  p_Test( "-0.0", false, 0 );
  p_Test( "0.", false, 0 );
  p_Test( "+0.", false, 0 );
  p_Test( "-0.", false, 0 );
  p_Test( ".0", false, 0 );
  p_Test( "+.0", false, 0 );
  p_Test( "-.0", false, 0 );

  p_Test( "1983", false, 1983 );
  p_Test( "+1983", false, 1983  );
  p_Test( "-1983", false, -1983 );
  p_Test( "19.83", false, 19.83 );
  p_Test( "+19.83", false, 19.83 );
  p_Test( "-19.83", false, -19.83 );
  p_Test( "1983.", false, 1983 );
  p_Test( "+1983.", false, 1983 );
  p_Test( "-1983.", false, -1983 );
  p_Test( ".1983", false, 0.1983 );
  p_Test( "+.1983", false, 0.1983 );
  p_Test( "-.1983", false, -0.1983 );

  p_seal_SciEStringToDouble_PrintErrorsTo_C( stdout );
  printf( "%d%n - ", testNumber ++, &spaces );
  M_C_PLUS_PLUS( printf( "(C) " ); )
  printf( "To pass this test, an error message must be printed to stdout:\n" );
  p_PrintSpaces( spaces );
  printf( "   " );
  f_seal_SciEStringToDouble_C( NULL );

  #ifdef __cplusplus
  p_PrintSpaces( spaces );
  printf( " - (C++) To pass this test, an error message must be printed to stdout:\n" );
  p_PrintSpaces( spaces );
  printf( "   " );
  try
  {
    f_seal_SciEStringToDouble( NULL );
  }
  catch( const char *ip_thrown )
  {
  }
  #endif

  printf( "\n---\n- This program will now quit.\n" );
  return 0;
}

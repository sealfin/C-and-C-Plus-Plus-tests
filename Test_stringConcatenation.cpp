#include "seal_stringConcatenation_C.h"
#ifdef __cplusplus
#include "seal_stringConcatenation.h"
#endif
#include "seal_bool.h"
#include <string.h>
#include <stdlib.h>

#ifdef __cplusplus
#define M_C_PLUS_PLUS( p ) p
#else
#define M_C_PLUS_PLUS( p )
#endif

#define M_C_PLUS_PLUS_TEST( p_stringExpected )                                                           \
  passed = true;                                                                                         \
  p_PrintSpaces( spaces );                                                                               \
  printf( " - " );                                                                                       \
  try                                                                                                    \
  {                                                                                                      \
    string = f_seal_ConcatenateStrings( P );                                                             \
    if( errorExpected != k_seal_STRING_CONCATENATION_ERROR_C__NONE )                                     \
    {                                                                                                    \
      passed = false;                                                                                    \
      printf( "Failed (C++): exception expected" );                                                      \
    }                                                                                                    \
    else                                                                                                 \
      if( strcmp( string, p_stringExpected ) != 0 )                                                      \
      {                                                                                                  \
        passed = false;                                                                                  \
        printf( "Failed (C++): string (\"%s\") != string expected (\"%s\")", string, p_stringExpected ); \
      }                                                                                                  \
    free( string );                                                                                      \
  }                                                                                                      \
  catch( const char *ip_thrown )                                                                         \
  {                                                                                                      \
    if( errorExpected == k_seal_STRING_CONCATENATION_ERROR_C__NONE )                                     \
    {                                                                                                    \
      passed = false;                                                                                    \
      printf( "Failed (C++): exception not expected" );                                                  \
    }                                                                                                    \
  }                                                                                                      \
  if( passed )                                                                                           \
    printf( "Passed (C++)" );                                                                            \
  printf( "\n" );

#define M_TEST( p_errorExpected, p_stringExpected )                                                                          \
  passed = true;                                                                                                             \
  printf( "%d%n - ", testNumber ++, &spaces );                                                                               \
  string = f_seal_ConcatenateStrings_C( P );                                                                                 \
  error = f_seal_StringConcatenation_Error_C();                                                                              \
  errorExpected = k_seal_STRING_CONCATENATION_ERROR_C__ ## p_errorExpected;                                                  \
  if( error != errorExpected )                                                                                               \
  {                                                                                                                          \
    passed = false;                                                                                                          \
    printf( "Failed" );                                                                                                      \
    M_C_PLUS_PLUS( printf( " (C)" ); )                                                                                       \
    printf( ": error (k_seal_STRING_CONCATENATION_ERROR_C__%s) != error expected (k_seal_STRING_CONCATENATION_ERROR_C__%s)", \
            k_errorStrings[ error ], k_errorStrings[ errorExpected ] );                                                      \
  }                                                                                                                          \
  else                                                                                                                       \
    if( error == k_seal_STRING_CONCATENATION_ERROR_C__NONE )                                                                 \
      if( strcmp( string, p_stringExpected ) != 0 )                                                                          \
      {                                                                                                                      \
        passed = false;                                                                                                      \
        printf( "Failed" );                                                                                                  \
        M_C_PLUS_PLUS( printf( " (C)" ); )                                                                                   \
        printf( ": string (\"%s\") != string expected (\"%s\")", string, p_stringExpected );                                 \
      }                                                                                                                      \
  if( passed )                                                                                                               \
  {                                                                                                                          \
    printf( "Passed" );                                                                                                      \
    M_C_PLUS_PLUS( printf( " (C)" ); )                                                                                       \
  }                                                                                                                          \
  printf( "\n" );                                                                                                            \
  free( string );                                                                                                            \
  M_C_PLUS_PLUS( M_C_PLUS_PLUS_TEST( p_stringExpected ))

void p_PrintSpaces( signed int p )
{
  for( ; p > 0; p -- )
    printf( " " );
}

int main( int argc, const char *argv[] )
{
  bool passed;
  int testNumber = 1;
  signed int spaces;
  char *string;
  t_seal_STRING_CONCATENATION_ERROR_C error, errorExpected;
  const char *k_errorString_none = "NONE",
             *k_errorString_pIsNULL = "P_IS_NULL",
             *k_errorString_concatenatedStringTooLong = "CONCATENATED_STRING_TOO_LONG",
             *k_errorStrings[] = { k_errorString_none, k_errorString_pIsNULL, k_errorString_concatenatedStringTooLong };

  printf( "- This program performs the (semi-)automated black-box testing of the f_seal_ConcatenateStrings(_C) function(s).\n---\n\n" );

  #define P NULL
  M_TEST( P_IS_NULL, "" )
  #undef P

  #define P ( char* )"", NULL
  M_TEST( NONE, "" )
  #undef P

  #define P ( char* )"Hello", ( char* )" ", ( char* )"world!", NULL
  M_TEST( NONE, "Hello world!" )
  #undef P

  #define P ( char* )"Hel", ( char* )"", ( char* )"lo!", NULL
  M_TEST( NONE, "Hello!" )
  #undef P

  p_seal_StringConcatenation_PrintErrorsTo_C( stdout );
  printf( "%d%n - ", testNumber ++, &spaces );
  #ifdef __cplusplus
  printf( "(C) " );
  #endif
  printf( "To pass this test, an error message must be printed to stdout:\n" );
  p_PrintSpaces( spaces );
  printf( "   " );
  free( f_seal_ConcatenateStrings_C( NULL ));
  #ifdef __cplusplus
  p_PrintSpaces( spaces );
  printf( " - (C++) To pass this test, an error message must be printed to stdout:\n" );
  p_PrintSpaces( spaces );
  printf( "   " );
  try
  {
    f_seal_ConcatenateStrings( NULL );
  }
  catch( const char *ip_thrown )
  {
  }
  #endif

  printf( "\n---\n- This program will now quit.\n" );
  return 0;
}

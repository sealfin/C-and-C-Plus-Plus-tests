#include "seal_stringToInt_C.h"
#ifdef __cplusplus
#include "seal_stringToInt.h"
#endif
#include "seal_bool.h"

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

void p_Test( const char * const p_string, const t_seal_STRING_TO_INT_ERROR_C p_errorExpected, const int p_intExpected )
{
  const char *k_errorString_none = "NONE",
             *k_errorString_pIsNULL = "P_IS_NULL",
             *k_errorString_pIsZeroCharactersLong = "P_IS_ZERO_CHARACTERS_LONG",
             *k_errorString_pContainsOnlyASignCharacter = "P_CONTAINS_ONLY_A_SIGN_CHARACTER",
             *k_errorString_signCharacterIsNotFirstCharacter = "SIGN_CHARACTER_IS_NOT_FIRST_CHARACTER",
             *k_errorString_pContainsANonNumericalCharacter = "P_CONTAINS_A_NON_NUMERICAL_CHARACTER",
             *k_errorStrings[] = { k_errorString_none, k_errorString_pIsNULL, k_errorString_pIsZeroCharactersLong, k_errorString_pContainsOnlyASignCharacter, k_errorString_signCharacterIsNotFirstCharacter, k_errorString_pContainsANonNumericalCharacter };

  signed int spaces;
  int i = f_seal_StringToInt_C( p_string );
  t_seal_STRING_TO_INT_ERROR_C error = f_seal_StringToInt_Error_C();
  bool passed = true;
  printf( "%d%n - ", testNumber ++, &spaces );
  if( error != p_errorExpected )
  {
    passed = false;
    printf( "Failed" );
    M_C_PLUS_PLUS( printf( " (C)" ); )
    printf( ": error (k_seal_STRING_TO_INT_ERROR_C__%s) != error expected (k_seal_STRING_TO_INT_ERROR_C__%s)", k_errorStrings[ error ], k_errorStrings[ p_errorExpected ] );
  }
  else
    if( error == k_seal_STRING_TO_INT_ERROR_C__NONE )
      if( i != p_intExpected )
      {
        passed = false;
        printf( "Failed" );
        M_C_PLUS_PLUS( printf( " (C)" ); )
        printf( ": int (%d) != int expected (%d)", i, p_intExpected );
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
    i = f_seal_StringToInt( p_string );
    if( p_errorExpected != k_seal_STRING_TO_INT_ERROR_C__NONE )
    {
      passed = false;
      printf( "Failed (C++): exception expected" );
    }
    else
      if( i != p_intExpected )
      {
        passed = false;
        printf( "Failed (C++): int (%d) != int expected (%d)", i, p_intExpected );
      }
  }
  catch( const char *ip_thrown )
  {
    if( p_errorExpected == k_seal_STRING_TO_INT_ERROR_C__NONE )
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

#define M_TEST( p_string, p_errorExpected, p_intExpected ) p_Test( p_string, k_seal_STRING_TO_INT_ERROR_C__ ## p_errorExpected, p_intExpected );

int main( int argc, const char *argv[] )
{
  signed int spaces;

  printf( "- This program performs the (semi-)automated black-box testing of the f_seal_StringToInt(_C) function(s).\n---\n\n" );

  M_TEST( NULL, P_IS_NULL, 0 )
  M_TEST( "", P_IS_ZERO_CHARACTERS_LONG, 0 )
  M_TEST( "+", P_CONTAINS_ONLY_A_SIGN_CHARACTER, 0 )
  M_TEST( "-", P_CONTAINS_ONLY_A_SIGN_CHARACTER, 0 )

  M_TEST( "0", NONE, 0 )
  M_TEST( "+0", NONE, 0 )
  M_TEST( "-0", NONE, 0 )
  M_TEST( "0+", SIGN_CHARACTER_IS_NOT_FIRST_CHARACTER, 0 )
  M_TEST( "0-", SIGN_CHARACTER_IS_NOT_FIRST_CHARACTER, 0 )

  M_TEST( "X", P_CONTAINS_A_NON_NUMERICAL_CHARACTER, 0 )
  M_TEST( "+X", P_CONTAINS_A_NON_NUMERICAL_CHARACTER, 0 )
  M_TEST( "-X", P_CONTAINS_A_NON_NUMERICAL_CHARACTER, 0 )
  M_TEST( "X+", SIGN_CHARACTER_IS_NOT_FIRST_CHARACTER, 0 )
  M_TEST( "X-", SIGN_CHARACTER_IS_NOT_FIRST_CHARACTER, 0 )

  M_TEST( "1983", NONE, 1983 )
  M_TEST( "+1983", NONE, 1983 )
  M_TEST( "-1983", NONE, -1983 )
  M_TEST( "1983+", SIGN_CHARACTER_IS_NOT_FIRST_CHARACTER, 0 )
  M_TEST( "1983-", SIGN_CHARACTER_IS_NOT_FIRST_CHARACTER, 0 )
  M_TEST( "19+83", SIGN_CHARACTER_IS_NOT_FIRST_CHARACTER, 0 )
  M_TEST( "19-83", SIGN_CHARACTER_IS_NOT_FIRST_CHARACTER, 0 )

  p_seal_StringToInt_PrintErrorsTo_C( stdout );
  printf( "%d%n - ", testNumber ++, &spaces );
  M_C_PLUS_PLUS( printf( "(C) " ); )
  printf( "To pass this test, an error message must be printed to stdout:\n" );
  p_PrintSpaces( spaces );
  printf( "   " );
  f_seal_StringToInt_C( NULL );
  #ifdef __cplusplus
  p_PrintSpaces( spaces );
  printf( " - (C++) To pass this test, an error message must be printed to stdout:\n" );
  p_PrintSpaces( spaces );
  printf( "   " );
  try
  {
    f_seal_StringToInt( NULL );
  }
  catch( const char *ip_thrown )
  {
  }
  #endif

  printf( "\n---\n- This program will now quit.\n" );
  return 0;
}

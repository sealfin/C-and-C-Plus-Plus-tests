#include "seal_stringToDouble_C.h"
#ifdef __cplusplus
#include "seal_stringToDouble.h"
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

void p_Test( const char * const p_string, const double p_doubleExpected, const t_seal_STRING_TO_DOUBLE_ERROR_C p_errorExpected )
{
  const char *k_errorString_none = "NONE",
             *k_errorString_pIsNULL = "P_IS_NULL",
             *k_errorString_pIsZeroCharactersLong = "P_IS_ZERO_CHARACTERS_LONG",
             *k_errorString_pContainsOnlyASignCharacter = "P_CONTAINS_ONLY_A_SIGN_CHARACTER",
             *k_errorString_pContainsOnlyADecimalPoint = "P_CONTAINS_ONLY_A_DECIMAL_POINT",
             *k_errorString_pContainsNoNonSignNonDecimalPointCharacters = "P_CONTAINS_NO_NON_SIGN_NON_DECIMAL_POINT_CHARACTERS",
             *k_errorString_pContainsANonNumericalCharacterInTheIntegerPart = "P_CONTAINS_A_NON_NUMERICAL_CHARACTER_IN_THE_INTEGER_PART",
             *k_errorString_pContainsANonNumericalCharacterInTheFractionalPart = "P_CONTAINS_A_NON_NUMERICAL_CHARACTER_IN_THE_FRACTIONAL_PART",
             *k_errorStrings[] = { k_errorString_none, k_errorString_pIsNULL, k_errorString_pIsZeroCharactersLong, k_errorString_pContainsOnlyASignCharacter, k_errorString_pContainsOnlyADecimalPoint, k_errorString_pContainsNoNonSignNonDecimalPointCharacters, k_errorString_pContainsANonNumericalCharacterInTheIntegerPart, k_errorString_pContainsANonNumericalCharacterInTheFractionalPart };

  signed int spaces;
  double d = f_seal_StringToDouble_C( p_string );
  t_seal_STRING_TO_DOUBLE_ERROR_C error = f_seal_StringToDouble_Error_C();
  bool passed = true;
  printf( "%d%n - ", testNumber ++, &spaces );
  if( error != p_errorExpected )
  {
    passed = false;
    printf( "Failed" );
    M_C_PLUS_PLUS( printf( " (C)" ); )
    printf( ": error (k_seal_STRING_TO_DOUBLE_ERROR_C__%s) != error expected (k_seal_STRING_TO_DOUBLE_ERROR_C__%s)", k_errorStrings[ error ], k_errorStrings[ p_errorExpected ] );
  }
  else
    if( error == k_seal_STRING_TO_DOUBLE_ERROR_C__NONE )
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
    d = f_seal_StringToDouble( p_string );
    if( p_errorExpected != k_seal_STRING_TO_DOUBLE_ERROR_C__NONE )
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
    if( p_errorExpected == k_seal_STRING_TO_DOUBLE_ERROR_C__NONE )
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

#define M_TEST( p_string, p_doubleExpected, p_errorExpected ) p_Test( p_string, p_doubleExpected, k_seal_STRING_TO_DOUBLE_ERROR_C__ ## p_errorExpected );

int main( int argc, const char *argv[] )
{
  signed int spaces;

  printf( "- This program performs the (semi-)automated black-box testing of the f_seal_StringToDouble(_C) function(s).\n---\n\n" );

  M_TEST( NULL, 0, P_IS_NULL )
  M_TEST( "", 0, P_IS_ZERO_CHARACTERS_LONG )
  M_TEST( "+", 0, P_CONTAINS_ONLY_A_SIGN_CHARACTER )
  M_TEST( "-", 0, P_CONTAINS_ONLY_A_SIGN_CHARACTER )
  M_TEST( ".", 0, P_CONTAINS_ONLY_A_DECIMAL_POINT )
  M_TEST( "+.", 0, P_CONTAINS_NO_NON_SIGN_NON_DECIMAL_POINT_CHARACTERS )
  M_TEST( "-.", 0, P_CONTAINS_NO_NON_SIGN_NON_DECIMAL_POINT_CHARACTERS )
  M_TEST( ".+", 0, P_CONTAINS_A_NON_NUMERICAL_CHARACTER_IN_THE_FRACTIONAL_PART )
  M_TEST( ".-", 0, P_CONTAINS_A_NON_NUMERICAL_CHARACTER_IN_THE_FRACTIONAL_PART )

  M_TEST( "X", 0, P_CONTAINS_A_NON_NUMERICAL_CHARACTER_IN_THE_INTEGER_PART )
  M_TEST( "+X", 0, P_CONTAINS_A_NON_NUMERICAL_CHARACTER_IN_THE_INTEGER_PART )
  M_TEST( "-X", 0, P_CONTAINS_A_NON_NUMERICAL_CHARACTER_IN_THE_INTEGER_PART )
  M_TEST( "X.", 0, P_CONTAINS_A_NON_NUMERICAL_CHARACTER_IN_THE_INTEGER_PART )
  M_TEST( "+X.", 0, P_CONTAINS_A_NON_NUMERICAL_CHARACTER_IN_THE_INTEGER_PART )
  M_TEST( "-X.", 0, P_CONTAINS_A_NON_NUMERICAL_CHARACTER_IN_THE_INTEGER_PART )
  M_TEST( ".X", 0, P_CONTAINS_A_NON_NUMERICAL_CHARACTER_IN_THE_FRACTIONAL_PART )
  M_TEST( "+.X", 0, P_CONTAINS_A_NON_NUMERICAL_CHARACTER_IN_THE_FRACTIONAL_PART )
  M_TEST( "-.X", 0, P_CONTAINS_A_NON_NUMERICAL_CHARACTER_IN_THE_FRACTIONAL_PART )

  M_TEST( "0", 0, NONE )
  M_TEST( "+0", 0, NONE )
  M_TEST( "-0", 0, NONE )
  M_TEST( "0.0", 0, NONE )
  M_TEST( "+0.0", 0, NONE )
  M_TEST( "-0.0", 0, NONE )
  M_TEST( "0.", 0, NONE )
  M_TEST( "+0.", 0, NONE )
  M_TEST( "-0.", 0, NONE )
  M_TEST( ".0", 0, NONE )
  M_TEST( "+.0", 0, NONE )
  M_TEST( "-.0", 0, NONE )

  M_TEST( "1983", 1983, NONE )
  M_TEST( "+1983", 1983, NONE )
  M_TEST( "-1983", -1983, NONE )
  M_TEST( "19.83", 19.83, NONE )
  M_TEST( "+19.83", 19.83, NONE )
  M_TEST( "-19.83", -19.83, NONE )
  M_TEST( "1983.", 1983, NONE )
  M_TEST( "+1983.", 1983, NONE )
  M_TEST( "-1983.", -1983, NONE )
  M_TEST( ".1983", 0.1983, NONE )
  M_TEST( "+.1983", 0.1983, NONE )
  M_TEST( "-.1983", -0.1983, NONE )

  p_seal_StringToDouble_PrintErrorsTo_C( stdout );
  printf( "%d%n - ", testNumber ++, &spaces );
  M_C_PLUS_PLUS( printf( "(C) " ); )
  printf( "To pass this test, an error message must be printed to stdout:\n" );
  p_PrintSpaces( spaces );
  printf( "   " );
  f_seal_StringToDouble_C( NULL );
  #ifdef __cplusplus
  p_PrintSpaces( spaces );
  printf( " - (C++) To pass this test, an error message must be printed to stdout:\n" );
  p_PrintSpaces( spaces );
  printf( "   " );
  try
  {
    f_seal_StringToDouble( NULL );
  }
  catch( const char *ip_thrown )
  {
  }
  #endif

  printf( "\n---\n- This program will now quit.\n" );
  return 0;
}

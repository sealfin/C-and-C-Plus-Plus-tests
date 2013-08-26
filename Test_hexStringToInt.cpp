#include "seal_hexStringToInt_C.h"
#ifdef __cplusplus
#include "seal_hexStringToInt.h"
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

void p_Test( const char * const p_string, const t_seal_HEX_STRING_TO_INT_ERROR_C p_errorExpected, const int p_intExpected )
{
  const char *k_errorString_none = { "NONE" },
             *k_errorString_pIsNULL = { "P_IS_NULL" },
             *k_errorString_pIsZeroCharactersLong = { "P_IS_ZERO_CHARACTERS_LONG" },
             *k_errorString_pContainsOnlyASignCharacter = { "P_CONTAINS_ONLY_A_SIGN_CHARACTER" },
             *k_errorString_pContainsOnlyAPrefix = { "P_CONTAINS_ONLY_A_PREFIX" },
             *k_errorString_pContainsANonZeroCharacterAsTheFirstCharacterInThePrefix = { "P_CONTAINS_A_NON_ZERO_CHARACTER_AS_THE_FIRST_CHARACTER_IN_THE_PREFIX" },
             *k_errorString_pContainsNoNonSignNonPrefixCharacters = { "P_CONTAINS_NO_NON_SIGN_NON_PREFIX_CHARACTERS" },
             *k_errorString_pContainsANonHexadecimalCharacter = { "P_CONTAINS_A_NON_HEXADECIMAL_CHARACTER" },
             *k_errorStrings[] = { k_errorString_none, k_errorString_pIsNULL, k_errorString_pIsZeroCharactersLong, k_errorString_pContainsOnlyASignCharacter, k_errorString_pContainsOnlyAPrefix, k_errorString_pContainsANonZeroCharacterAsTheFirstCharacterInThePrefix, k_errorString_pContainsNoNonSignNonPrefixCharacters, k_errorString_pContainsANonHexadecimalCharacter };

  signed int spaces;
  int i = f_seal_HexStringToInt_C( p_string );
  t_seal_HEX_STRING_TO_INT_ERROR_C error = f_seal_HexStringToInt_Error_C();
  bool passed = true;
  printf( "%d%n - ", testNumber ++, &spaces );
  if( error != p_errorExpected )
  {
    passed = false;
    printf( "Failed" );
    M_C_PLUS_PLUS( printf( " (C)" ); )
    printf( ": error (k_seal_HEX_STRING_TO_INT_ERROR_C__%s) != error expected (k_seal_HEX_STRING_TO_INT_ERROR_C__%s)", k_errorStrings[ error ], k_errorStrings[ p_errorExpected ] );
  }
  else
    if( error == k_seal_HEX_STRING_TO_INT_ERROR_C__NONE )
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
    i = f_seal_HexStringToInt( p_string );
    if( p_errorExpected != k_seal_HEX_STRING_TO_INT_ERROR_C__NONE )
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
    if( p_errorExpected == k_seal_HEX_STRING_TO_INT_ERROR_C__NONE )
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

#define M_TEST( p_string, p_errorExpected, p_intExpected ) p_Test( p_string, k_seal_HEX_STRING_TO_INT_ERROR_C__ ## p_errorExpected, p_intExpected );

int main( int argc, const char *argv[] )
{
  signed int spaces;

  printf( "- This program performs the (semi-)automated black-box testing of the f_seal_HexStringToInt(_C) function(s).\n---\n\n" );

  M_TEST( NULL, P_IS_NULL, 0 )
  M_TEST( "", P_IS_ZERO_CHARACTERS_LONG, 0 )
  M_TEST( "+", P_CONTAINS_ONLY_A_SIGN_CHARACTER, 0 )
  M_TEST( "-", P_CONTAINS_ONLY_A_SIGN_CHARACTER, 0 )
  M_TEST( "0x", P_CONTAINS_ONLY_A_PREFIX, 0 )
  M_TEST( "0X", P_CONTAINS_ONLY_A_PREFIX, 0 )
  M_TEST( "+0x", P_CONTAINS_NO_NON_SIGN_NON_PREFIX_CHARACTERS, 0 )
  M_TEST( "+0X", P_CONTAINS_NO_NON_SIGN_NON_PREFIX_CHARACTERS, 0 )
  M_TEST( "-0x", P_CONTAINS_NO_NON_SIGN_NON_PREFIX_CHARACTERS, 0 )
  M_TEST( "-0X", P_CONTAINS_NO_NON_SIGN_NON_PREFIX_CHARACTERS, 0 )

  M_TEST( "gx0", P_CONTAINS_A_NON_ZERO_CHARACTER_AS_THE_FIRST_CHARACTER_IN_THE_PREFIX, 0 )
  M_TEST( "gX0", P_CONTAINS_A_NON_ZERO_CHARACTER_AS_THE_FIRST_CHARACTER_IN_THE_PREFIX, 0 )
  M_TEST( "+gx0", P_CONTAINS_A_NON_ZERO_CHARACTER_AS_THE_FIRST_CHARACTER_IN_THE_PREFIX, 0 )
  M_TEST( "+gX0", P_CONTAINS_A_NON_ZERO_CHARACTER_AS_THE_FIRST_CHARACTER_IN_THE_PREFIX, 0 )
  M_TEST( "-gx0", P_CONTAINS_A_NON_ZERO_CHARACTER_AS_THE_FIRST_CHARACTER_IN_THE_PREFIX, 0 )
  M_TEST( "-gX0", P_CONTAINS_A_NON_ZERO_CHARACTER_AS_THE_FIRST_CHARACTER_IN_THE_PREFIX, 0 )

  M_TEST( "g", P_CONTAINS_A_NON_HEXADECIMAL_CHARACTER, 0 )
  M_TEST( "+g", P_CONTAINS_A_NON_HEXADECIMAL_CHARACTER, 0 )
  M_TEST( "-g", P_CONTAINS_A_NON_HEXADECIMAL_CHARACTER, 0 )
  M_TEST( "0xg", P_CONTAINS_A_NON_HEXADECIMAL_CHARACTER, 0 )
  M_TEST( "0Xg", P_CONTAINS_A_NON_HEXADECIMAL_CHARACTER, 0 )
  M_TEST( "+0xg", P_CONTAINS_A_NON_HEXADECIMAL_CHARACTER, 0 )
  M_TEST( "+0Xg", P_CONTAINS_A_NON_HEXADECIMAL_CHARACTER, 0 )
  M_TEST( "-0xg", P_CONTAINS_A_NON_HEXADECIMAL_CHARACTER, 0 )
  M_TEST( "-0Xg", P_CONTAINS_A_NON_HEXADECIMAL_CHARACTER, 0 )

  M_TEST( "0", NONE, 0 )
  M_TEST( "0x0", NONE, 0 )
  M_TEST( "0X0", NONE, 0 )
  M_TEST( "+0", NONE, 0 )
  M_TEST( "-0", NONE, 0 )
  M_TEST( "+0x0", NONE, 0 )
  M_TEST( "+0X0", NONE, 0 )
  M_TEST( "-0x0", NONE, 0 )
  M_TEST( "-0X0", NONE, 0 )

  M_TEST( "7bf", NONE, 1983 )
  M_TEST( "7BF", NONE, 1983 )
  M_TEST( "0x7bf", NONE, 1983 )
  M_TEST( "0X7bf", NONE, 1983 )
  M_TEST( "+7bf", NONE, 1983 )
  M_TEST( "-7bf", NONE, -1983 )
  M_TEST( "+0x7bf", NONE, 1983 )
  M_TEST( "+0X7bf", NONE, 1983 )
  M_TEST( "-0x7bf", NONE, -1983 )
  M_TEST( "-0X7bf", NONE, -1983 )

  p_seal_HexStringToInt_PrintErrorsTo_C( stdout );
  printf( "%d%n - ", testNumber ++, &spaces );
  M_C_PLUS_PLUS( printf( "(C) " ); )
  printf( "To pass this test, an error message must be printed to stdout:\n" );
  p_PrintSpaces( spaces );
  printf( "   " );
  f_seal_HexStringToInt_C( NULL );
  #ifdef __cplusplus
  p_PrintSpaces( spaces );
  printf( " - (C++) To pass this test, an error message must be printed to stdout:\n" );
  p_PrintSpaces( spaces );
  printf( "   " );
  try
  {
    f_seal_HexStringToInt( NULL );
  }
  catch( const char *ip_thrown )
  {
  }
  #endif

  printf( "\n---\nThis program will now quit.\n" );
  return 0;
}

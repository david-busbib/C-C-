#include "tests.h"

#define K_1 3
#define K_2 2
#define K_MINOS_1 -1
#define K_MINOS_3 -3
#define K_29 29

#include <stdio.h>
#include <string.h>
// See full documentation in header file
int test_encode_non_cyclic_lower_case_positive_k ()
{
  char in[] = "abc";
  char out[] = "def";
  encode (in, K_1);
  return strcmp (in, out) != 0;
}

// See full documentation in header file
int test_encode_cyclic_lower_case_special_char_positive_k ()
{
    char in[] = "bay****%%";
    char out[] = "dca****%%";
    encode (in, K_2);
    return strcmp (in, out) != 0;

}

// See full documentation in header file
int test_encode_non_cyclic_lower_case_special_char_negative_k ()
{
    char in[] = "cby**%,,,";
    char out[] = "bax**%,,,";
    encode (in, K_MINOS_1);
    return strcmp (in, out) != 0;

}

// See full documentation in header file
int test_encode_cyclic_lower_case_negative_k ()
{
    char in[] = "bbay";
    char out[] = "yyxv";
    encode (in, K_MINOS_3);
    return strcmp (in, out) != 0;

}

// See full documentation in header file
int test_encode_cyclic_upper_case_positive_k ()

{
    char in[] = "CDZB";
    char out[] = "FGCE";
    encode (in, K_29);
    return strcmp (in, out) != 0;

}

// See full documentation in header file
int test_decode_non_cyclic_lower_case_positive_k ()
{
  char in[] = "def";
  char out[] = "abc";
  decode (in, K_1);
  return strcmp (in, out) != 0;
}

// See full documentation in header file
int test_decode_cyclic_lower_case_special_char_positive_k ()
{
    char out[] = "bay****%%";
    char in[] = "dca****%%";
    decode (in, K_2);
    return strcmp (in, out) != 0;

}

// See full documentation in header file
int test_decode_non_cyclic_lower_case_special_char_negative_k ()
{
    char out[] = "cby**%,,,";
    char in[] = "bax**%,,,";
    decode (in, K_MINOS_1);
    return strcmp (in, out) != 0;

}

// See full documentation in header file
int test_decode_cyclic_lower_case_negative_k ()
{
    char out[] = "bbay";
    char in[] = "yyxv";
    decode (in, K_MINOS_3);
    return strcmp (in, out) != 0;

}

// See full documentation in header file
int test_decode_cyclic_upper_case_positive_k ()
{
    char out[] = "CDZB";
    char in[] = "FGCE";
    decode(in, K_29);
    return strcmp (in, out) != 0;


}

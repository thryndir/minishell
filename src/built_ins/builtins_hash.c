/* ANSI-C code produced by gperf version 3.1 */
/* Command-line: gperf -t -N htable_get -K key builtins.gp  */
/* Computed positions: -k'2' */

#if !((' ' == 32) && ('!' == 33) && ('"' == 34) && ('#' == 35) \
      && ('%' == 37) && ('&' == 38) && ('\'' == 39) && ('(' == 40) \
      && (')' == 41) && ('*' == 42) && ('+' == 43) && (',' == 44) \
      && ('-' == 45) && ('.' == 46) && ('/' == 47) && ('0' == 48) \
      && ('1' == 49) && ('2' == 50) && ('3' == 51) && ('4' == 52) \
      && ('5' == 53) && ('6' == 54) && ('7' == 55) && ('8' == 56) \
      && ('9' == 57) && (':' == 58) && (';' == 59) && ('<' == 60) \
      && ('=' == 61) && ('>' == 62) && ('?' == 63) && ('A' == 65) \
      && ('B' == 66) && ('C' == 67) && ('D' == 68) && ('E' == 69) \
      && ('F' == 70) && ('G' == 71) && ('H' == 72) && ('I' == 73) \
      && ('J' == 74) && ('K' == 75) && ('L' == 76) && ('M' == 77) \
      && ('N' == 78) && ('O' == 79) && ('P' == 80) && ('Q' == 81) \
      && ('R' == 82) && ('S' == 83) && ('T' == 84) && ('U' == 85) \
      && ('V' == 86) && ('W' == 87) && ('X' == 88) && ('Y' == 89) \
      && ('Z' == 90) && ('[' == 91) && ('\\' == 92) && (']' == 93) \
      && ('^' == 94) && ('_' == 95) && ('a' == 97) && ('b' == 98) \
      && ('c' == 99) && ('d' == 100) && ('e' == 101) && ('f' == 102) \
      && ('g' == 103) && ('h' == 104) && ('i' == 105) && ('j' == 106) \
      && ('k' == 107) && ('l' == 108) && ('m' == 109) && ('n' == 110) \
      && ('o' == 111) && ('p' == 112) && ('q' == 113) && ('r' == 114) \
      && ('s' == 115) && ('t' == 116) && ('u' == 117) && ('v' == 118) \
      && ('w' == 119) && ('x' == 120) && ('y' == 121) && ('z' == 122) \
      && ('{' == 123) && ('|' == 124) && ('}' == 125) && ('~' == 126))
/* The character set is not based on ISO-646.  */
#error "gperf generated tables don't work with this execution character set. Please report a bug to <bug-gperf@gnu.org>."
#endif

#line 1 "builtins.gp"

	#include <minishell.h>
#line 5 "builtins.gp"
typedef struct s_builtin
{
	const char* key;
	void *(*builtin_func)(void *);
}	t_builtin;

#define TOTAL_KEYWORDS 7
#define MIN_WORD_LENGTH 2
#define MAX_WORD_LENGTH 6
#define MIN_HASH_VALUE 2
#define MAX_HASH_VALUE 9
/* maximum key range = 8, duplicates = 0 */

#ifdef __GNUC__
__inline
#else
#ifdef __cplusplus
inline
#endif
#endif
static unsigned int
hash (register const char *str, register size_t len)
{
  static unsigned char asso_values[] =
    {
     10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,
     10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,
     10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,
     10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,
     10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10, 5,
      0,10,10,10,10,10,10,10,10,10,0,10,10,10,10,10,10,10,10, 5,
      0,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,
     10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,
     10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,
     10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,
     10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,
     10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,
     10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10
    };
  return len + asso_values[(unsigned char)str[1]];
}

typedef struct s_builtin *
htable_get (register const char *str, register size_t len)
{
  static typedef struct s_builtin wordlist[] =
    {
      {""}, {""},
#line 12 "builtins.gp"
      {"cd", cd_builtin},
#line 13 "builtins.gp"
      {"env", env_builtin},
#line 14 "builtins.gp"
      {"exit", exit_builtin},
#line 15 "builtins.gp"
      {"unset", unset_builtin},
#line 16 "builtins.gp"
      {"export", export_builtin},
      {""},
#line 17 "builtins.gp"
      {"pwd", pwd_builtin},
#line 18 "builtins.gp"
      {"echo", echo_builtin}
    };

  if (len <= MAX_WORD_LENGTH && len >= MIN_WORD_LENGTH)
    {
      register unsigned int key = hash (str, len);

      if (key <= MAX_HASH_VALUE)
        {
          register const char *s = wordlist[key].key;

          if (*str == *s && !strcmp (str + 1, s + 1))
            return &wordlist[key];
        }
    }
  return 0;
}

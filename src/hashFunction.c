#include <R.h>
#include <Rinternals.h>
#include "Platform.h"
/* #include <stdint.h> */
/* #include <stddef.h> */

/**
 * Convert 32bit integer to uint8 array
 */
void sexp_to_uint8(SEXP x, uint8_t a[4]) {
  int i = INTEGER(x)[0];
  a[0] = i && 0xff;
  i >>= 8;
  a[1] = i && 0xff;
  i >>= 8;
  a[2] = i && 0xff;
  i >>= 8;
  a[3] = i && 0xff;
}

/**
 * Convert string to uint8 array
 */
const char* sexp_to_str(SEXP x, int* len) {
  const char* ret = CHAR(STRING_ELT(x,0));
  *len = 0;
  while (ret[*len]) {
    (*len) ++;
  }
  return ret;
}

/**
 * Convert uint8 to string
 */
SEXP uint8_to_sexp(const uint8_t out) {
  SEXP s;
  PROTECT(s = allocVector(INTSXP, 1));
  INTEGER(s)[0] = out;
  UNPROTECT(1);
  return s;
}

/**
 * Convert uint32 to string
 */
SEXP uint32_to_sexp(const uint32_t out) {
  SEXP s;
  PROTECT(s = allocVector(INTSXP, 1));
  INTEGER(s)[0] = out;
  UNPROTECT(1);
  return s;
}

/**
 * Convert uint64 to string
 */
SEXP uint64_to_sexp(const uint64_t out) {
  /* Rprintf("[0] = %d\n", out & 0xffffffff); */
  /* Rprintf("[1] = %d\n", out >> 32); */
  uint64_t mask = 0xffffffff;
  SEXP s;
  PROTECT(s = allocVector(INTSXP, 2));
  INTEGER(s)[0] = out >> 32;        // higher bits
  INTEGER(s)[1] = out & mask;       // lower bits
  UNPROTECT(1);
  return s;
}

/**
 * Convert uint128 to string
 */
SEXP uint128_to_sexp(const uint32_t out[4]) {
  const uint32_t mask = 0xffffffff;
  SEXP s;
  PROTECT(s = allocVector(INTSXP, 4));
  INTEGER(s)[0] = out[0];
  INTEGER(s)[1] = out[1];
  INTEGER(s)[2] = out[2];
  INTEGER(s)[3] = out[3];
  UNPROTECT(1);
  return s;
}

// Spooky hash
extern void SpookyHash32_test(const void *key, int len, uint32_t seed, void *out);

SEXP spooky32int(SEXP x) {
  uint8_t key[4];
  int len = 4;
  uint32_t seed = 0;
  sexp_to_uint8(x, key);

  uint32_t out;
  SpookyHash32_test(key, len, seed, &out);
  return uint32_to_sexp(out);
}

SEXP spooky32str(SEXP x) {
  const char* s;
  int len = 0;
  s = sexp_to_str(x, &len);
  uint32_t seed = 0;

  uint32_t out;
  SpookyHash32_test(s, len, seed, &out);
  return uint32_to_sexp(out);
}

// City hash
extern void CityHash64_test(const void *key, int len, uint32_t seed, void *out);

SEXP cityhash64int(SEXP x) {
  uint8_t key[4];
  int len = 4;
  uint32_t seed = 0;
  sexp_to_uint8(x, key);

  uint64_t out = 0;
  CityHash64_test(key, len, seed, &out);
  return uint64_to_sexp(out);
}

SEXP cityhash64str(SEXP x) {
  const char* s;
  int len = 0;
  s = sexp_to_str(x, &len);
  uint32_t seed = 0;

  uint64_t out;
  CityHash64_test(s, len, seed, &out);
  return uint64_to_sexp(out);
}

// Murmur hash
extern void MurmurHash3_x86_32_test(const void *key, int len, uint32_t seed, void *out);

SEXP murmur3_32int(SEXP x) {
  uint8_t key[4];
  int len = 4;
  uint32_t seed = 0;
  sexp_to_uint8(x, key);

  uint32_t out;
  MurmurHash3_x86_32_test(key, len, seed, &out);
  return uint32_to_sexp(out);
}

SEXP murmur3_32str(SEXP x) {
  const char* s;
  int len = 0;
  s = sexp_to_str(x, &len);
  uint32_t seed = 0;

  uint32_t out;
  MurmurHash3_x86_32_test(s, len, seed, &out);
  return uint32_to_sexp(out);
}



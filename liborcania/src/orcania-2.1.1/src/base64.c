/*
 * Base64 encoding/decoding (RFC1341)
 * Copyright (c) 2005-2011, Jouni Malinen <j@w1.fi>
 * Copyright (c) 2017-2020, Nicolas Mora <mail@babelouest.org>
 *
 * This software may be distributed under the terms of the BSD license.
 */

#include <string.h>
#include <math.h>
#include "orcania.h"

static const unsigned char base64_table[65] =
  "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

/**
 * o_base64_encode - Base64 encode
 * @src: Data to be encoded
 * @len: Length of the data to be encoded
 * @out: Pointer to output variable
 * @out_len: Pointer to output length variable
 * Returns: 1 on success, 0 on failure
 *
 * The nul terminator is not included in out_len.
 */
int o_base64_encode(const unsigned char * src, size_t len, unsigned char * out, size_t * out_len) {
  unsigned char * pos;
  const unsigned char * end, * in;
  size_t olen;
  int line_len;

  olen = len * 4 / 3 + 4; /* 3-byte blocks to 4-byte */
  olen += olen / 72; /* line feeds */
  olen++; /* nul termination */
  if (olen < len || src == NULL || out_len == NULL) {
    return 0;
  }

  end = src + len;
  in = src;
  pos = out;
  line_len = 0;
  *out_len = 0;
  while (end - in >= 3) {
    if (pos != NULL) {
      *pos++ = base64_table[in[0] >> 2];
      *pos++ = base64_table[((in[0] & 0x03) << 4) | (in[1] >> 4)];
      *pos++ = base64_table[((in[1] & 0x0f) << 2) | (in[2] >> 6)];
      *pos++ = base64_table[in[2] & 0x3f];
    }
    (*out_len) += 4;
    in += 3;
    line_len += 4;
    if (line_len >= 72) {
      line_len = 0;
    }
  }

  if (end - in) {
    if (pos != NULL) {
      *pos++ = base64_table[in[0] >> 2];
    }
    (*out_len)++;
    if (end - in == 1) {
      if (pos != NULL) {
        *pos++ = base64_table[(in[0] & 0x03) << 4];
        *pos++ = '=';
      }
      (*out_len) += 2;
    } else {
      if (pos != NULL) {
        *pos++ = base64_table[((in[0] & 0x03) << 4) | (in[1] >> 4)];
        *pos++ = base64_table[(in[1] & 0x0f) << 2];
      }
      (*out_len) += 2;
    }
    if (pos != NULL) {
      *pos++ = '=';
    }
    (*out_len)++;
  }

  if (pos != NULL) {
    *pos = '\0';
  }
  return 1;
}

/**
 * o_base64_decode - Base64 decode
 * @src: Data to be decoded
 * @len: Length of the data to be decoded
 * @out: Pointer to output variable
 * @out_len: Pointer to output length variable
 * Returns: 1 on success, 0 on failure
 *
 * The nul terminator is not included in out_len.
 */
int o_base64_decode(const unsigned char *src, size_t len, unsigned char * out, size_t * out_len) {
  unsigned char dtable[256], *pos = out, block[4], tmp;
  size_t i, count;
  int pad = 0;
  
  if (src == NULL || !len || out_len == NULL) {
    return 0;
  }

  memset(dtable, 0x80, 256);
  for (i = 0; i < sizeof(base64_table) - 1; i++) {
    dtable[base64_table[i]] = (unsigned char) i;
  }
  dtable['='] = 0;

  count = 0;
  for (i = 0; i < len; i++) {
    if (dtable[src[i]] != 0x80) {
      count++;
    }
  }

  if (count == 0 || count % 4) {
    return 0;
  }

  count = 0;
  *out_len = 0;
  for (i = 0; i < len; i++) {
    if (!o_strchr((const char *)base64_table, src[i]) && src[i] != '=' && src[i] != '\n' && src[i] != '\t' && src[i] != ' ') {
      // character invalid
      return 0;
    }
    tmp = dtable[src[i]];
    if (tmp == 0x80) {
      continue;
    }

    if (src[i] == '=') {
      pad++;
    }
    block[count] = tmp;
    count++;
    if (count == 4) {
      if (pos != NULL) {
        *pos++ = (block[0] << 2) | (block[1] >> 4);
        *pos++ = (block[1] << 4) | (block[2] >> 2);
        *pos++ = (block[2] << 6) | block[3];
      }
      (*out_len)+=3;
      count = 0;
      if (pad) {
        if (pad == 1) {
          if (pos != NULL) {
            pos--;
          }
          (*out_len)--;
        } else if (pad == 2) {
          if (pos != NULL) {
            pos -= 2;
          }
          (*out_len) -= 2;
        } else {
          /* Invalid padding */
          return 0;
        }
        break;
      }
    }
  }

  return 1;
}

/**
 * o_base64url_encode - Base64url encode (url format)
 * @src: Data to be encoded
 * @len: Length of the data to be encoded
 * @out: Pointer to output variable
 * @out_len: Pointer to output length variable
 * Returns: 1 on success, 0 on failure
 *
 * The nul terminator is not included in out_len.
 */
int o_base64url_encode(const unsigned char * src, size_t len, unsigned char * out, size_t * out_len) {
  int res = 0;
  size_t index;
  double calc;
  
  if (out != NULL) {
    res = o_base64_encode(src, len, out, out_len);
    if (res) {
      if (*out_len >= 2 && out[*out_len - 2] == '=') {
        out[*out_len - 2] = '\0';
        (*out_len) -= 2;
      } else if (*out_len && out[*out_len - 1] == '=') {
        out[*out_len - 1] = '\0';
        (*out_len)--;
      }
      for (index = 0; index < *out_len; index++) {
        if (out[index] == '+') {
          out[index] = '-';
        } else if (out[index] == '/') {
          out[index] = '_';
        }
      }
    }
  } else if (len && out_len != NULL) {
    calc = (4 * (double)len) / 3;
    if (calc != floor(calc)) {
      calc = floor(calc)+1;
    }
    *out_len = calc;
    res = 1;
  }
  return res;
}

/**
 * o_base64url_decode - Base64 decode (url format)
 * @src: Data to be decoded
 * @len: Length of the data to be decoded
 * @out: Pointer to output variable
 * @out_len: Pointer to output length variable
 * Returns: 1 on success, 0 on failure
 *
 * The nul terminator is not included in out_len.
 */
int o_base64url_decode(const unsigned char *src, size_t len, unsigned char * out, size_t * out_len) {
  int res = 0;
  size_t src_cpy_len;
  unsigned char * src_cpy;
  
  if (src) {
    src_cpy = o_malloc(len+3);
    if (src_cpy != NULL) {
      if (o_base64url_2_base64(src, len, src_cpy, &src_cpy_len)) {
        res = o_base64_decode(src_cpy, src_cpy_len, out, out_len);
      } else {
        res = 1;
      }
      o_free(src_cpy);
    } else {
      res = 0;
    }
  }
  return res;
}

/**
 * o_base64url_2_base64 - Convert a base64 url format to base64 format
 * @src: Data to be decoded
 * @len: Length of the data to be decoded
 * @out: Pointer to output variable
 * @out_len: Pointer to output length variable
 * Returns: 1 on success, 0 on failure
 *
 * The nul terminator is not included in out_len.
 * out must be at least len+2
 */
int o_base64url_2_base64(const unsigned char *src, size_t len, unsigned char * out, size_t * out_len) {
  int res = 0;
  size_t index;
  
  if (src) {
    memcpy(out, src, len);
    *out_len = len;
    for (index = 0; index < len; index++) {
      if (out[index] == '-') {
        out[index] = '+';
      } else if (out[index] == '_') {
        out[index] = '/';
      }
    }
    if (len % 4 == 2) {
      out[len] = '=';
      out[len+1] = '=';
      (*out_len) += 2;
    } else if (len % 4 == 3) {
      out[len] = '=';
      (*out_len)++;
    }
    res = 1;
  }
  return res;
}

/**
 * o_base64url_2_base64 - Convert a base64 format to base64 url format
 * @src: Data to be decoded
 * @len: Length of the data to be decoded
 * @out: Pointer to output variable
 * @out_len: Pointer to output length variable
 * Returns: 1 on success, 0 on failure
 *
 * The nul terminator is not included in out_len.
 * out must be at least len+2
 */
int o_base64_2_base64url(const unsigned char *src, size_t len, unsigned char * out, size_t * out_len) {
  int res = 0;
  size_t index;
  
  if (src) {
    memcpy(out, src, len);
    *out_len = len;
    for (index = 0; index < len; index++) {
      if (out[index] == '+') {
        out[index] = '-';
      } else if (out[index] == '/') {
        out[index] = '_';
      }
    }
    while (out[(*out_len)-1] == '=') {
      (*out_len)--;
    }
    res = 1;
  }
  
  return res;
}

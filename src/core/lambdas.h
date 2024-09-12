#pragma once


#define l_eq(a, b) (a == b)
#define l_str_eq(a, b) (strcmp(a, b))
#define l_hex_fmt(str, value) sprintf(str, "0x%X", value)
#define l_int_fmt(str, value) sprintf(str, "%d", value)
#define l_ptr_fmt(str, value) sprintf(str, "%ld", value)

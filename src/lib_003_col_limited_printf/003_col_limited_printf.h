#ifndef C_RANDOM_003_COL_LIMITED_PRINTF_H
#define C_RANDOM_003_COL_LIMITED_PRINTF_H

/*
 * Automatically linebreaks at 80 cols;
 * Treats tabs as 8 spaces
 */
void col_limited_printf(int cols, int offset, const char *fmt, ...);

#endif /* C_RANDOM_003_COL_LIMITED_PRINTF_H */

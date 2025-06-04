#ifndef BASIC_H
#define BASIC_H

#include <ncurses.h>

/* Helper macro to get size of a static array */
#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))

/* 
 * Top‐level entry point. 
 * Returns 0 on normal exit. 
 */
int basic_mode(void);

/* Example “sub‐mode” that shows a small menu */
void menu_section(void);

/* Example “sub‐mode” that asks the user for text input */
void input_section(void);

/* 
 * Generic helper: draw a vertical menu at (row 0, col 0) with a title, 
 * let user move ↑/↓ and press Enter. 
 * - title: a null‐terminated string to print at row 0 
 * - choices: array of null‐terminated strings 
 * - n_choices: number of entries in choices[] 
 * Returns the index (0..n_choices–1) that the user selects.
 */
int draw_menu(const char *title, char *choices[], int n_choices);

/* 
 * Generic helper: prompt for text at the bottom of the screen. 
 * - prompt: null‐terminated string to print (e.g. "Enter name: ") 
 * - buffer: caller‐provided char buf 
 * - bufsize: size of buffer in bytes 
 * After returning, buffer contains the user’s input (no trailing newline).
 */
void get_input(const char *prompt, char *buffer, int bufsize);

#endif
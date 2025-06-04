#include "basic.h"
#include <string.h>
#include <time.h>

/******************************************************************************
 * basic_mode()
 *
 * This is the “main menu” that lets you choose among multiple sections.
 * You can add more entries to `sections[]` and write new functions to support
 * additional screens easily.
 ******************************************************************************/
int basic_mode(void) {
    /* 1) Initialize ncurses */
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);

    /* 2) Define top‐level sections */
    char *sections[] = {
        "Section 1 - Menu Example",
        "Section 2 - Text Input Example",
        "Quit"
    };
    int n_sec = ARRAY_SIZE(sections);

    /* 3) Let user pick one */
    int choice = draw_menu("=== Main Sections ===", sections, n_sec);

    /* 4) Dispatch to the chosen section */
    switch (choice) {
        case 0:
            menu_section();
            break;
        case 1:
            input_section();
            break;
        case 2:
        default:
            /* do nothing */
            break;
    }

    /* 5) Cleanup and exit */
    endwin();
    return 0;
}

/******************************************************************************
 * menu_section()
 *
 * Demonstrates a submenu with 3 simple options. Mimics your original code.
 ******************************************************************************/
void menu_section(void) {
    clear();

    char *choices[] = {
        "Option 1 - Say Hello",
        "Option 2 - Show Time",
        "Option 3 - Back to Main"
    };
    int n_choices = ARRAY_SIZE(choices);

    int highlight = 0;
    int c, sel = -1;

    /* Loop until user presses Enter */
    while (1) {
        clear();
        mvprintw(0, 0, "Use ^/v to move; Enter to select. (Press 'q' to go back.)");
        mvprintw(1, 0, "----------------------------------------------");

        for (int i = 0; i < n_choices; i++) {
            if (i == highlight) {
                attron(A_REVERSE);
            }
            mvprintw(2 + i, 2, "%s", choices[i]);
            if (i == highlight) {
                attroff(A_REVERSE);
            }
        }
        refresh();

        c = getch();
        if (c == KEY_UP) {
            highlight = (highlight == 0) ? n_choices - 1 : highlight - 1;
        } else if (c == KEY_DOWN) {
            highlight = (highlight == n_choices - 1) ? 0 : highlight + 1;
        } else if (c == 10) { /* Enter */
            sel = highlight;
            break;
        } else if (c == 'q' || c == 'Q') {
            /* Immediately go back to main */
            return;
        }
    }

    /* Handle user’s selection */
    clear();
    switch (sel) {
        case 0:
            mvprintw(0, 0, "Hello there!");
            break;
        case 1: {
            time_t now = time(NULL);
            char timestr[64];
            strftime(timestr, sizeof(timestr), "%Y-%m-%d %H:%M:%S", localtime(&now));
            mvprintw(0, 0, "Current time: %s", timestr);
            break;
        }
        case 2:
        default:
            /* Back to main – just return */
            return;
    }
    mvprintw(2, 0, "Press any key to return...");
    refresh();
    getch();
}

/******************************************************************************
 * input_section()
 *
 * Demonstrates how to prompt the user for arbitrary text input in ncurses.
 ******************************************************************************/
void input_section(void) {
    clear();

    /* 1) Show instructions */
    mvprintw(0, 0, "This section will ask you to type some text.");
    mvprintw(1, 0, "After typing, press Enter. Press ESC at any time to cancel.");
    mvprintw(2, 0, "----------------------------------------------");
    refresh();

    /* 2) Prepare a buffer and call our helper */
    char buf[128];
    get_input("Enter your name: ", buf, sizeof(buf));

    /* 3) If user pressed ESC (empty string), treat as “cancel” */
    if (buf[0] == '\0') {
        mvprintw(4, 0, "No input entered or cancelled. Press any key to return...");
    } else {
        mvprintw(4, 0, "You typed: \"%s\"", buf);
        mvprintw(6, 0, "Press any key to return...");
    }
    refresh();
    getch();
}

/******************************************************************************
 * draw_menu()
 *
 * Draw a menu starting at row 0/col 0. Return the index the user selects.
 ******************************************************************************/
int draw_menu(const char *title, char *choices[], int n_choices) {
    int highlight = 0;
    int c;

    while (1) {
        clear();
        mvprintw(0, 0, "%s", title);
        mvprintw(1, 0, "----------------------------------------------");

        for (int i = 0; i < n_choices; i++) {
            if (i == highlight) {
                attron(A_REVERSE);
            }
            mvprintw(2 + i, 2, "%s", choices[i]);
            if (i == highlight) {
                attroff(A_REVERSE);
            }
        }
        refresh();

        c = getch();
        switch (c) {
            case KEY_UP:
                highlight = (highlight == 0) ? n_choices - 1 : highlight - 1;
                break;
            case KEY_DOWN:
                highlight = (highlight == n_choices - 1) ? 0 : highlight + 1;
                break;
            case 10:  /* Enter */
                return highlight;
            default:
                break;
        }
    }
}

/******************************************************************************
 * get_input()
 *
 * Print a prompt at the bottom, enable echo, let user type text, then return.
 * - If the user presses ESC as the very first character, we return an empty
 *   string (buffer[0] = '\0'). Otherwise buffer[] holds whatever was typed.
 ******************************************************************************/
void get_input(const char *prompt, char *buffer, int bufsize) {
    int maxy, maxx;
    getmaxyx(stdscr, maxy, maxx);

    /* 1) Show prompt near bottom */
    int prompt_row = maxy - 3;
    mvprintw(prompt_row, 0, "%s", prompt);
    clrtoeol();

    /* 2) Enable echo & show cursor */
    echo();
    curs_set(1);

    /* 3) Use wgetnstr to read up to (bufsize-1) chars */
    /* If user presses ESC (27) first, treat as “cancel.” */
    int ch = wgetch(stdscr);
    if (ch == 27) {
        /* Cancel: return empty string */
        buffer[0] = '\0';
    } else {
        /* Put first char back into the input queue, then read the rest */
        ungetch(ch);
        mvgetnstr(prompt_row, strlen(prompt), buffer, bufsize - 1);
    }

    /* 4) Disable echo & hide cursor again */
    noecho();
    curs_set(0);

    /* 5) Clear prompt line */
    mvprintw(prompt_row, 0, "");
    clrtoeol();
    refresh();
}

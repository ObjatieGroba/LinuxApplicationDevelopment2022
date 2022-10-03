#include <ncurses.h>
#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>


#define DX 3

char * nxt(char * data, char * data_end) {
    while (*data != '\n' && data != data_end) {
        ++data;
    }
    if (data != data_end) {
        ++data;
    }
    return data;
}


int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s filename", argv[0]);
    }
    FILE *file = fopen(argv[1], "r");
    if (!file) {
       fprintf(stderr, "File does not exist");
    }

    struct stat statbuf;
    if (fstat(file->_fileno, &statbuf) < 0) {
        fprintf(stderr, "Can not stat");
    }

    char * data_begin = mmap(NULL, statbuf.st_size, PROT_READ, MAP_SHARED, file->_fileno, 0);
    if (!data_begin) {
        fprintf(stderr, "Can not open file");
    }
    char * data_end = data_begin + statbuf.st_size;
    char * end = data_begin;
    size_t end_line = 1;

    initscr();
    noecho();
    cbreak();
    printw("File: %s; size: %ld", argv[1], statbuf.st_size);
    refresh();

    WINDOW *win = newwin(LINES-2*DX, COLS-2*DX, DX, DX);
    keypad(win, TRUE);
    scrollok (win, TRUE);
    box(win, 0, 0);
    wmove(win, 1, 0);

    for (size_t i = 0; i != LINES-2*DX - 2; ++i) {
        if (end == data_end) {
            break;
        }
        char * new_end = nxt(end, data_end);
//        wprintw(win, "\t%ld: %3s", end_line, end);
        wprintw(win, "%5ld: %.*s", end_line, (int)(new_end - end), end);
        end = new_end;
        ++end_line;
    }
    box(win, 0, 0);
    wrefresh(win);

    int c;
    while((c = wgetch(win)) != 27) {
        if (c == ' ') {
            if (end != data_end) {
                char * new_end = nxt(end, data_end);
                wprintw(win, "%5ld: %.*s", end_line, (int)(new_end - end), end);
                end = new_end;
                ++end_line;
                box(win, 0, 0);
                wrefresh(win);
            }
        }
    }
    endwin();

    munmap(data_begin, statbuf.st_size);
    fclose(file);
}

#ifndef BOYER_MOORE_SEARCH_H
#define BOYER_MOORE_SEARCH_H

#define NO_OF_CHARS 256

void bad_char_heuristic(char* substr, int size, int badchar[NO_OF_CHARS]);

char* boyer_moore_search(char* str, char* substr);

#endif
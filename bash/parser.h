//
// Created by 86158 on 2024/6/2.
//

#ifndef ZEARO_BASH_PARSER_H
#define ZEARO_BASH_PARSER_H

/**
 * @brief Parse a line to args.
 * @param line char* line. The line we input.
 * @return char**. We parse a line to args.
 */
extern char** zbash_parse_line(char* line);

#endif //ZEARO_BASH_PARSER_H

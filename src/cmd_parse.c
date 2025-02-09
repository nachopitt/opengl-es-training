#include <string.h>

#include "cmd_parse.h"

int cmd_parse_init(cmd_parse_state* state, int argc, char* argv[], ) {
    if (state == NULL) {
        return -1;
    }

    state->argc = argc;
    state->argv = argv;
    state->parsing_index = 1;

    return 0;
}

int cmd_parse(cmd_parse_state* state) {
    if (state->parsing_index < state->argc) {

        return 0
    }
    else {
        return -1;
    }
}

int cmd_parse_option(cmd_parse_state* state, char* option, int option_buffer_size) {

}

int cmd_parse_option_arg(cmd_parse_state* state char* option_arg, int option_arg_buffer_size) {

}


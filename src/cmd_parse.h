#ifndef CMD_PARSE_H
#define CMD_PARSE_H

typedef struct cmd_parse_arg {

} cmd_parse_arg;

typedef int(*cmd_parse_config)(cmd_parse_arg args[], int args_size);

typedef struct cmd_parse_state {
    int argc;
    char* argv[];
    int parsing_index;
} cmd_parse_state;

void cmd_parse_init(cmd_parse_state* state, int argc, char* argv[]);
int cmd_parse(cmd_parse_state* state);
void cmd_parse_option(cmd_parse_state* state, char* option, int option_buffer_size);
void cmd_parse_option_arg(cmd_parse_state* state char* option_arg, int option_arg_buffer_size);

#endif // CMD_PARSE_H

#include <stdio.h>
#include <stdio_ext.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include "Util.h"
#include "Command.h"
#include "Table.h"
#include "SelectState.h"

///
/// Allocate State_t and initialize some attributes
/// Return: ptr of new State_t
///
State_t* new_State() {
    State_t *state = (State_t*)malloc(sizeof(State_t));
    state->saved_stdout = -1;
    return state;
}

///
/// Print shell prompt
///
void print_prompt(State_t *state) {
    if (state->saved_stdout == -1) {
        printf("db > ");
    }
}

///
/// Print the user in the specific format
///
void print_user(User_t *user, SelectArgs_t *sel_args) {
    size_t idx;
    printf("(");
    for (idx = 0; idx < sel_args->fields_len; idx++) {
        if (!strncmp(sel_args->fields[idx], "*", 1)) {
            printf("%d, %s, %s, %d", user->id, user->name, user->email, user->age);
        } else {
            if (idx > 0) printf(", ");

            if (!strncmp(sel_args->fields[idx], "id", 2)) {
                printf("%d", user->id);
            } else if (!strncmp(sel_args->fields[idx], "name", 4)) {
                printf("%s", user->name);
            } else if (!strncmp(sel_args->fields[idx], "email", 5)) {
                printf("%s", user->email);
            } else if (!strncmp(sel_args->fields[idx], "age", 3)) {
                printf("%d", user->age);
            }
        }
    }
    printf(")\n");
}

///
/// Print the users for given offset and limit restriction
///
void print_users(Table_t *table, int *idxList, size_t idxListLen, Command_t *cmd) {
    size_t idx;
    int limit = cmd->cmd_args.sel_args.limit;
    int offset = cmd->cmd_args.sel_args.offset;

    if (offset == -1) {
        offset = 0;
    }

    if (idxList) {
        for (idx = offset; idx < idxListLen; idx++) {
            if (limit != -1 && (idx - offset) >= limit) {
                break;
            }
	    if(handle_where_cond(get_User(table, idxList[idx]), &(cmd->whe_args)))
            print_user(get_User(table, idxList[idx]), &(cmd->cmd_args.sel_args));
        }
    } else {
        for (idx = offset; idx < table->len; idx++) {
            if (limit != -1 && (idx - offset) >= limit) {
                break;
            }
	    if(handle_where_cond(get_User(table, idx), &(cmd->whe_args)))
            print_user(get_User(table, idx), &(cmd->cmd_args.sel_args));
        }
    }
}

///
/// This function received an output argument
/// Return: category of the command
///
int parse_input(char *input, Command_t *cmd) {
    char *token;
    int idx;
    token = strtok(input, " ,\n");
    for (idx = 0; strlen(cmd_list[idx].name) != 0; idx++) {
        if (!strncmp(token, cmd_list[idx].name, cmd_list[idx].len)) {
            cmd->type = cmd_list[idx].type;
        }
    }
    while (token != NULL) {
        add_Arg(cmd, token);
        token = strtok(NULL, " ,\n");
    }
    return cmd->type;
}

///
/// Handle built-in commands
/// Return: command type
///
void handle_builtin_cmd(Table_t *table, Command_t *cmd, State_t *state) {
    if (!strncmp(cmd->args[0], ".exit", 5)) {
        archive_table(table);
        exit(0);
    } else if (!strncmp(cmd->args[0], ".output", 7)) {
        if (cmd->args_len == 2) {
            if (!strncmp(cmd->args[1], "stdout", 6)) {
                close(1);
                dup2(state->saved_stdout, 1);
                state->saved_stdout = -1;
            } else if (state->saved_stdout == -1) {
                int fd = creat(cmd->args[1], 0644);
                state->saved_stdout = dup(1);
                if (dup2(fd, 1) == -1) {
                    state->saved_stdout = -1;
                }
                __fpurge(stdout); //This is used to clear the stdout buffer
            }
        }
    } else if (!strncmp(cmd->args[0], ".load", 5)) {
        if (cmd->args_len == 2) {
            load_table(table, cmd->args[1]);
        }
    } else if (!strncmp(cmd->args[0], ".help", 5)) {
        print_help_msg();
    }
}

///
/// Handle query type commands
/// Return: command type
///
int handle_query_cmd(Table_t *table, Command_t *cmd) {
    
    if (!strncmp(cmd->args[0], "insert", 6)) {
	if (!strncmp(cmd->args[1], "into", 4)){
	/*      if (!strncmp(cmd->args[2], "user", 4)){	
        */	
		handle_insert_cmd(table, cmd);
		return INSERT_CMD;
		}
	return UNRECOG_CMD;
	/*}
	return UNRECOG_CMD;*/
    } else if (!strncmp(cmd->args[0], "select", 6)) {
        handle_select_cmd(table, cmd);
        return SELECT_CMD;
    }else if (!strncmp(cmd->args[0], "delete", 6)) {
	handle_delete_cmd(table, cmd);
        return DELETE_CMD;
    } else {
        return UNRECOG_CMD;
    }
}

///
/// The return value is the number of rows insert into table
/// If the insert operation success, then change the input arg
/// `cmd->type` to INSERT_CMD
///
int handle_insert_cmd(Table_t *table, Command_t *cmd) {
    int ret = 0;
    User_t *user = command_to_User(cmd);
    if (user) {
        ret = add_User(table, user);
        if (ret > 0) {
            cmd->type = INSERT_CMD;
        }
    }
    return ret;
}

///
/// The return value is the number of rows select from table
/// If the select operation success, then change the input arg
/// `cmd->type` to SELECT_CMD
///
int handle_select_cmd(Table_t *table, Command_t *cmd) {
    cmd->type = SELECT_CMD;
    field_state_handler(cmd, 1);

    print_users(table, NULL, 0, cmd);
    return table->len;
}

int handle_where_cond(User_t *user, WhereArgs_t *whe_args){
    size_t condition_size = whe_args->fields_len;
    if (condition_size == 0) return 1;
    int count = 0;
    int op = -1; 
    for(size_t idx = 0; idx < condition_size; idx++){
	if(!strncmp(whe_args->fields[idx], "or", 2)){
            op= 0;
	    continue;
        }
	else if(!strncmp(whe_args->fields[idx], "and", 3)){
            op=1;
            continue;
        }
	
	if(!strncmp(whe_args->fields[idx], "id", 2)){
            int a = user->id;
	    double b = atof(whe_args->fields[idx + 2]);
	    count += handle_num_cmp(a, b, whe_args->fields[idx + 1]);
	    idx += 2;
	    continue;
        }
	else if(!strncmp(whe_args->fields[idx], "name", 4)){
            char a[256];
	    memcpy(a, user->name, sizeof(a));
	    char b[256];
	    memset(b, 0, sizeof(b));
	    strcpy(b, whe_args->fields[idx + 2]);
	    count += handle_str_cmp(a, b, whe_args->fields[idx + 1]);
	    idx += 2;
	    continue;
        }
	else if(!strncmp(whe_args->fields[idx], "email", 5)){
            char a[256];
	    memcpy(a, user->email, sizeof(a));
	    char b[256];
	    memset(b, 0, sizeof(b));
	    strcpy(b, whe_args->fields[idx + 2]);
	    count += handle_str_cmp(a, b, whe_args->fields[idx + 1]);
	    idx += 2;
	    continue;
        }
	else if(!strncmp(whe_args->fields[idx], "age", 3)){
            int a = user->age;
	    double b = atof(whe_args->fields[idx + 2]);
	    count += handle_num_cmp(a, b, whe_args->fields[idx + 1]);
	    idx += 2;
	    continue;
        }

    }
    if(op == -1)
	return count;
    else if(op == 0) return (count > 0);
	else if(op == 1) return( count == 2);
    else return 1;	
}

int handle_delete_cmd(Table_t *table, Command_t *cmd) {
    cmd->type = DELETE_CMD;
    field_state_handler(cmd, 1);
    Table_t *new_tb = new_Table(NULL);
    for(int i = 0; i < table->len; i++)
    {
        if (handle_where_cond(get_User(table, i), &(cmd->whe_args)) == 0)
        {
            add_User(new_tb, get_User(table, i));
        }
    }
    table->capacity = new_tb->capacity;
    table->len = new_tb->len;
    table->users = new_tb->users;
    table->cache_map = new_tb->cache_map;
    table->fp = new_tb->fp;
    table->file_name = new_tb->file_name;
    return table->len;
}

int handle_num_cmp(int a, double b, char *condition){
	if(!strncmp(condition, "!=", 2)){
		if(a != b) return 1;
		return 0;
	}
	else if(!strncmp(condition, ">=", 2)){
		if(a >= b) return 1;
		return 0;
	}
	else if(!strncmp(condition, "<=", 2)){
		if(a <= b) return 1;
		return 0;
	}
	else if(!strncmp(condition, ">", 1)){
		if(a > b) return 1;
		return 0;
	}
	else if(!strncmp(condition, "<", 1)){
		if(a < b) return 1;
		return 0;
	}
	else if(!strncmp(condition, "=", 1)){
		if(a == b) return 1;
		return 0;
	}
	else 
		return 0;
}
int handle_str_cmp(char* a, char* b, char *condition){
	if(!strncmp(condition, "!=", 2)){
		if(strcmp(a, b) != 0) return 1;
		return 0;
	}
	else if(!strncmp(condition, "=", 1)){
		if(strcmp(a, b) == 0) return 1;
		return 0;
	}
	else 
		return 0;
}
///
/// Show the help messages
///
void print_help_msg() {
    const char msg[] = "# Supported Commands\n"
    "\n"
    "## Built-in Commands\n"
    "\n"
    "  * .exit\n"
    "\tThis cmd archives the table, if the db file is specified, then exit.\n"
    "\n"
    "  * .output\n"
    "\tThis cmd change the output strategy, default is stdout.\n"
    "\n"
    "\tUsage:\n"
    "\t    .output (<file>|stdout)\n\n"
    "\tThe results will be redirected to <file> if specified, otherwise they will display to stdout.\n"
    "\n"
    "  * .load\n"
    "\tThis command loads records stored in <DB file>.\n"
    "\n"
    "\t*** Warning: This command will overwrite the records already stored in current table. ***\n"
    "\n"
    "\tUsage:\n"
    "\t    .load <DB file>\n\n"
    "\n"
    "  * .help\n"
    "\tThis cmd displays the help messages.\n"
    "\n"
    "## Query Commands\n"
    "\n"
    "  * insert\n"
    "\tThis cmd inserts one user record into table.\n"
    "\n"
    "\tUsage:\n"
    "\t    insert <id> <name> <email> <age>\n"
    "\n"
    "\t** Notice: The <name> & <email> are string without any whitespace character, and maximum length of them is 255. **\n"
    "\n"
    "  * select\n"
    "\tThis cmd will display all user records in the table.\n"
    "\n";
    printf("%s", msg);
}



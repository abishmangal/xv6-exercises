#include "types.h"
#include "user.h"
#include "fcntl.h"


int strcspn(char *string, char *chars)
{
  char *s, *p;
  for (s = string; *s; s++) {
    for (p = chars; *p; p++) {
      if (*s == *p)
        return s - string;
    }
  }
  return s - string;
}

char *strtok(char *s, char *delim)
{
  static char *last;
  char *start;

  if (s == 0)
    s = last;

  while (*s && strchr(delim, *s))
    s++;

  if (*s == 0)
    return 0;

  start = s;
  s += strcspn(s, delim);

  if (*s) {
    *s = 0;
    last = s + 1;
  } else {
    last = s;
  }

  return start;
}


/*
  Function Declarations for builtin shell commands:
 */
int lsh_cd(char **args);
int lsh_help(char **args);
int lsh_exit(char **args);

/*
  List of builtin commands, followed by their corresponding functions.
 */
char *builtin_str[] = {
  "cd",
  "help",
  "exit"
};

int (*builtin_func[]) (char **) = {
  &lsh_cd,
  &lsh_help,
  &lsh_exit
};

int lsh_num_builtins() {
  return sizeof(builtin_str) / sizeof(char *);
}

/*
  Builtin function implementations.
*/

/**
   @brief Bultin command: change directory.
   @param args List of args.  args[0] is "cd".  args[1] is the directory.
   @return Always returns 1, to continue executing.
 */
int lsh_cd(char **args)
{
  if (args[1] == 0) {
    printf(2, "lsh: expected argument to \"cd\"\n");
  } else {
    if (chdir(args[1]) != 0) {
      printf(2,"lsh : cd failed\n");
    }
  }
  return 1;
}

/**
   @brief Builtin command: print help.
   @param args List of args.  Not examined.
   @return Always returns 1, to continue executing.
 */
int lsh_help(char **args)
{
  int i;
  printf(1,"xv6 Shell\n");
  printf(1,"Type program names and arguments, and hit enter.\n");
  printf(1,"The following are built in:\n");

  for (i = 0; i < lsh_num_builtins(); i++) {
    printf(1,"  %s\n", builtin_str[i]);
  }

  printf(1,"Use the man command for information on other programs.\n");
  return 1;
}

/**
   @brief Builtin command: exit.
   @param args List of args.  Not examined.
   @return Always returns 0, to terminate execution.
 */
int lsh_exit(char **args)
{
  return 0;
}

/**
  @brief Launch a program and wait for it to terminate.
  @param args Null terminated list of arguments (including program).
  @return Always returns 1, to continue execution.
 */

int lsh_launch(char **args)
{
  int pid = fork();
  if (pid == 0) {
    exec(args[0], args);
    printf(2, "lsh: exec failed\n");
    exit();
  } else if (pid > 0) {
    wait();
  } else {
    printf(2, "lsh: fork failed\n");
  }
  return 1;
}

/**
   @brief Execute shell built-in or launch program.
   @param args Null terminated list of arguments.
   @return 1 if the shell should continue running, 0 if it should terminate
 */
int lsh_execute(char **args)
{
  int i;

  if (args[0] == 0) {
    // An empty command was entered.
    return 1;
  }

  for (i = 0; i < lsh_num_builtins(); i++) {
    if (strcmp(args[0], builtin_str[i]) == 0) {
      return (*builtin_func[i])(args);
    }
  }

  return lsh_launch(args);
}

#define LSH_RL_BUFSIZE 1024
/**
   @brief Read a line of input from stdin.
   @return The line from stdin.
 */
char *lsh_read_line(void)
{
  static char buffer[1024];
  int n = read(0, buffer, sizeof(buffer) - 1);
  if (n <= 0)
    exit();
  buffer[n] = 0;
  return buffer;
}


#define LSH_TOK_BUFSIZE 64
#define LSH_TOK_DELIM " \t\r\n\a"
/**
   @brief Split a line into tokens (very naively).
   @param line The line.
   @return Null-terminated array of tokens.
 */

char **lsh_split_line(char *line)
{
  static char *tokens[LSH_TOK_BUFSIZE];
  int position = 0;
  char *token;

  token = strtok(line, LSH_TOK_DELIM);
  while (token != 0 && position < LSH_TOK_BUFSIZE - 1) {
    tokens[position++] = token;
    token = strtok(0, LSH_TOK_DELIM);
  }
  tokens[position] = 0;
  return tokens;
}

/**
   @brief Loop getting input and executing it.
 */
void lsh_loop(void)
{
  char *line;
  char **args;
  int status;

  do {
    printf(1,"> ");
    line = lsh_read_line();
    args = lsh_split_line(line);
    status = lsh_execute(args);
  } while (status);
}

/**
   @brief Main entry point.
   @param argc Argument count.
   @param argv Argument vector.
   @return status code
 */
int main(int argc, char **argv)
{
  // Load config files, if any.

  // Run command loop.
  lsh_loop();

  // Perform any shutdown/cleanup.

  return 0;
}
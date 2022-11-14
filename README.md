# Minishell
Minishell : 

Authorized functions overview : 

- readline : prototype : char *readline (const char *prompt);
	      function : read a line from the terminal and return it, using the char * given as prompt.
	     return value : the line read without the final '\n'.

- rl_clear_history : prototype : void rl_clear_history (void);
		      function : Clear the history list by deleting all of the entries, in the same manner as the History library’s clear_history() function. This differs from clear_history because it frees private data Readline saves in the history list.

-  rl_on_new_line : prototype : int rl_on_new_line (void);
		     function : Tell the update functions that we have moved onto a new (empty) line, usually after outputting a newline.
		    return value : ?
		    
- rl_replace_line : prototype : void rl_replace_line (const char *text, int clear_undo);
		     function : Replace the contents of rl_line_buffer with text. The point and mark are preserved, if possible. If clear_undo is non-zero, the undo list associated with the current line is cleared.
		    
- rl_redisplay : prototype : void rl_redisplay (void);
		  function : Change what’s displayed on the screen to reflect the current contents of rl_line_buffer.
		 
- add_history : prototype : void add_history (const char *string);
		 function : Place string at the end of the history list. The associated data field (if any) is set to NULL.
		
- signal : prototype : void (*signal(int sig, void (*func)(int)))(int);
	    function : sets a function to handle signal i.e. a signal handler with signal number sig.
	   	sig is the signal number to which a handling function is set. ex : SIGINT, SIGSSEGV, SIGTERM etc...
	   	
- sigaction : prototype : int sigaction(int signum, const struct sigaction *restrict act, struct sigaction *restrict oldact);
	       function : The sigaction() system call is used to change the action taken by a process on receipt of a specific signal.

- sigemptyset : prototype : int sigemptyset(sigset_t *set);
		 function : initializes the signal set given by set to empty, with all signals excluded from the set.
		return value : returns 1 if set contains no signals, and 0 otherwise.

- sigaddset : prototype : int sigaddset(sigset_t *set, int signum);
	       function : add signal signum to set.
	      return value : returns 0 on success and -1 on error.
	      
- kill : prototype : int kill(pid_t pid, int sig);
	  function : sends a signal to a process or process group specified by pid. The signal to be sent is specified by sig and is either 0 or one of the signals from the list in the <sys/signal.h> header file.
	 return value : Returns 0 on success (at least one signal was sent). Returns -1 on error, and errno is set to indicate the error.

-  stat : prototype : int stat(const char *path, struct stat *buf);
	   function : gets status information about a specified file and places it in the area of memory pointed to by the buf argument.
	  return value : returns 0 on success and -1 on error.
	  
- lstat : prototype : int lstat(const char *path, struct stat *buf);
	   function : gets status information about a specified file and places it in the area of memory pointed to by buf. If the named file is not a symbolic link, lstat() updates the time-related fields before putting information in the stat structure.
	  return value : returns 0 on success and -1 on error.

- fstat : prototype :  int fstat(int descriptor, struct stat *buffer);
	   function : The fstat() function gets status information about the object specified by the open descriptor descriptor and stores the information in the area of memory indicated by the buffer argument. The status information is returned in a stat structure, as defined in the <sys/stat.h> header file.
           return value : returns 0 on success and -1 on error.

- printf, malloc, free, write, access, open, read, close, fork, wait, waitpid, wait3, wait4, exit, getcwd, chdir, unlink, execve, dup, dup2, pipe, opendir, readdir, closedir, strerror, perror.
Le reste (isatty, ttyname, ttyslot, ioctl, getenv, tcsetattr, tcgetattr, tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs) c’est pour les bonus a priori.

Liens utiles :

https://github.com/vportens/minishell

https://brennan.io/2015/01/16/write-a-shell-in-c/
# Get-Next-Line

The goal of this project is to code a function that returns a line ending with a newline, read from a file descriptor.

### Instructions
* You must only submit two files : `get_next_line.c` and `get_next_line.h`
* What we call a “line” is a succession of characters that end with `\n` (ascii code 0x0a) or with End Of File(EOF).
* Your function must be prototyped as follow : `int get_next_line(const int fd, char **line);`
* The first parameter is the file descriptor that will be used to read.
* The second parameter is the address of a pointer to a character that will be used to save the line read from the file descriptor.
* The return value can be `1`, `0` or `-1` depending on whether a line has been read, when the reading has been completed, or if an error has happened respectively.
* Your function get_next_line must return its result without `\n`.
* Calling your function get_next_line in a loop will then allow you to read the texta vailable on a file descriptor one line at a time until the end of the text, no matter the size of either the text or one of its lines.
* Make sure that your function behaves well when it reads from a file, from the standard output, from a redirection etc.
* In you header file `get_next_line.h` you must have at least the prototype of the function get_next_line and a macro that allows to choose the size of the reading buffer for the read function. This value will be modified during the defense to evaluate the strength of your function. That macro must be named `BUFF_SIZE`.
* We consider that get_next_line has an undefined behavior if, between two calls, the same file descriptor designs two distinct files although the reading from the first file was not completed.
* We consider also that a call to lseek(2) will never take place between two calls ofthe function get_next_line on the same file descriptor.
* Finally we consider that get_next_line has an undefined behavior when reading from a binary file. However, if you wish, you can make this behavior coherent.
* Global variables are forbidden.
* Static variables are allowed.

### Bonus part
The project get_next_line is straight forward and leaves very little room for bonuses. 
* Succeed get_next_line with a single static variable.
* Manage multiple file descriptor with your get_next_line. 

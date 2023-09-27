# NOTES

## unistd allows you to check if you have permissions for a dir:

```c
 #include <unistd.h>

 if (access(directory, W_OK) == -1) {
     printf("You do not have write permissions for this directory.\n");
 }

```

## sys/stat.h allows you to check if a directory exists:

```c
 #include <sys/stat.h>

 struct stat buffer;
 if (stat(directory, &buffer) == -1) {
     printf("Directory does not exist.\n");
}
```

I want to have a folder in the .config directory where I can store info on where the user is storing their database.



Small example of how you might use the ncurses library to handle arrow keys:

```c
#include <ncurses.h>

int main()
{
    initscr(); // Initialize the window
    keypad(stdscr, TRUE); // Enable special keys

    int ch;
    while ((ch = getch()) != 'q') // Quit on 'q'
    {
        switch (ch)
        {
            case KEY_UP:
                // Handle up arrow
                break;
            case KEY_DOWN:
                // Handle down arrow
                break;
            // Add cases for KEY_LEFT, KEY_RIGHT if needed
        }
    }

    endwin(); // End the window
    return 0;
}
```
This is a very basic example. You would replace the comments with the code to handle each arrow key. Remember to link the ncurses library when compiling (-lncurses).

------------------------------------------------------

In C, you can use the functions provided by the dirent.h library to scan for files in a directory. Here's a general idea of how you can do it:

Use opendir() to open the directory.
Use readdir() in a loop to read the files in the directory. This function returns a pointer to a struct dirent, which has a member called d_name that contains the name of the file.
Don't forget to use closedir() to close the directory when you're done.
Remember to check for errors at each step, as these functions will return NULL or -1 if something goes wrong.
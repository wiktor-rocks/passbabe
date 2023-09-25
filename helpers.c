#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#define ARRAY_SIZE 1024

typedef struct
{
    char entry[ARRAY_SIZE];
    char username[ARRAY_SIZE];
    char password[ARRAY_SIZE];
} Entries;

bool quit_stuff()
{
    char quit[1];

    while (1)
    {
        // Prompt user for database name
        printf("Enter 'q' to quit\n>>: ");
        scanf(" %c", quit);

        if (quit[0] == 'q')
        {
            printf("\n");
            return true;
        }
    }
}

void create_db_dir()
{
    return;
}


void list_entries()
{
    FILE *file;

    file = fopen("bob.pbdb", "r");

    if (file == NULL)
    {
        printf("error opening file.\n");
        return;
    }

    Entries entries[ARRAY_SIZE];

    int read = 0;
    int records = 0;

    do
    {
        read = fscanf(file, "%999[^,],%999[^,],%999[^\n]", entries[records].entry, entries[records].username,
                      entries[records].password);

        if (read == 3)
            records++;

        if (read != 3 && !feof(file))
        {
            printf("file format incorrect.\n");
            return;
        }

        if (ferror(file))
        {
            printf("error reading file");
            return;
        }
    }
    while (!feof(file));

    fclose(file);

    for (int i = 0; i < records; i++)
    {
        printf("%s | %s | %s \n", entries[i].entry, entries[i].username, entries[i].password);

        printf("\n");
    }

    if (quit_stuff())
    {
        return;
    }
}

void add_entry()
{
    char entry_name[ARRAY_SIZE];
    char username[ARRAY_SIZE];
    char password[ARRAY_SIZE];

    FILE *file = fopen("bob.pbdb", "a");

    printf("Provide name for entry (or enter 'q' to quit)\n>>: ");
    scanf("%s[^\n]", entry_name);

    if (entry_name[0] == 'q')
    {
        return;
    }

    printf("Provide username (or enter 'q' to quit)\n>>: ");
    scanf("%s[^\n]", username);

    if (username[0] == 'q')
    {
        return;
    }

    printf("Provide password(or enter 'q' to quit)\n>>: ");
    scanf("%s[^\n]", password);

    if (password[0] == 'q')
    {
        return;
    }

    fprintf(file, "\n%s,%s,%s",entry_name, username, password);

    fclose(file);
    return;
}

void add_database()
{
    char title[50];
    char ext[] = ".pbdb";

    // Prompt user for database title
    printf("Provide title for database (or enter 'q' to quit)\n>>: ");
    scanf("%49s[^\n]", title);

    // If user enters q, exit
    if (title[0] == 'q')
    {
        return;
    }

    strcat(title, ext);

    FILE *database = fopen(title, "w");

    if (database == NULL)
    {
        printf("Failed to add database.\n");
        return;
    }

    if (fclose(database) == EOF)
    {
        printf("Failed to close the database file.\n");
        return;
    }

    printf("Database added: %s\n\n", title);
    return;
}

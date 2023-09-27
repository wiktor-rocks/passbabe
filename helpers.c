#include <dirent.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
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
        printf("Enter 'q' to quit\n>>: ");
        scanf(" %c", quit);

        if (quit[0] == 'q')
        {
            printf("\n");
            return true;
        }
    }
}

char *read_config()
{

    char *home_dir = getenv("HOME");

    char full_path[ARRAY_SIZE];
    snprintf(full_path, sizeof(full_path), "%s/.config/passbabe/", home_dir);

    strcat(full_path, "passbabe.conf");
    // read the database name from config file
    FILE *config_file = fopen(full_path, "r");

    char *buffer = malloc(ARRAY_SIZE * sizeof(char));
    int i = 0;
    char ch;
    while ((ch = fgetc(config_file)) != EOF && i < ARRAY_SIZE - 1)
    {
        buffer[i] = ch;
        i++;
    }
    buffer[i] = '\0';
    fclose(config_file);

    return buffer;
}

void create_db_dir()
{

    char *home_dir = getenv("HOME");

    char full_path[ARRAY_SIZE];
    snprintf(full_path, sizeof(full_path), "%s/.config/passbabe", home_dir);

    mkdir(full_path, 0777);

    snprintf(full_path, sizeof(full_path), "%s/.config/passbabe/passbabe.conf", home_dir);

    snprintf(full_path, sizeof(full_path), "%s/.config/passbabe/databases", home_dir);

    mkdir(full_path, 0777);

    FILE *config_file = fopen(full_path, "r");

    if (config_file != NULL)
    {
        fclose(config_file);
    }
    else
    {
        config_file = fopen(full_path, "w");
        if (config_file == NULL)
        {
            fclose(config_file);
            return;
        }
    }
    return;
}

void list_entries()
{

    char *config_file_stuff = read_config();

    printf("%s\n", config_file_stuff);

    FILE *file;

    file = fopen(config_file_stuff, "r");

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

        if (read == 3){
            fgetc(file);
            records++;
        }

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
        printf("%i| %s | %s | %s",i, entries[i].entry, entries[i].username, entries[i].password);

        printf("\n");
    }

    if (quit_stuff())
    {
        return;
    }
}

void add_entry()
{

    char *config_file_stuff = read_config();

    char entry_name[ARRAY_SIZE];
    char username[ARRAY_SIZE];
    char password[ARRAY_SIZE];

    FILE *file = fopen(config_file_stuff, "a");

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

    fprintf(file, "%s,%s,%s", entry_name, username, password);
    fprintf(file, "\n");

    fclose(file);
    return;
}


void delete_entry()
{
    char *config_file_stuff = read_config();

    printf("%s\n", config_file_stuff);

    FILE *file;

    file = fopen(config_file_stuff, "r");

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

        if (read == 3){
            fgetc(file);
            records++;
        }

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
        printf("%i | %s | %s | %s \n",i, entries[i].entry, entries[i].username, entries[i].password);

    }

    char entry_number[ARRAY_SIZE];
    printf("Provide entry number to delete (or enter 'q' to quit)\n>>: ");
    scanf("%49s[^\n]", entry_number);

    int entry_number_int = atoi(entry_number);

    // If user enters q, exit
    if (entry_number[0] == 'q')
    {
        return;
    }


    FILE *new_file= fopen(config_file_stuff, "w");

    if (new_file!= NULL)
    {
        for (int i = 0; i < records; i++)
        {
            if (i != entry_number_int)
            {
                fprintf(new_file, "%s,%s,%s", entries[i].entry, entries[i].username, entries[i].password);
                fprintf(new_file, "\n");
            }
            else{
                continue;
            }
        }
    }
    fclose(new_file);
}

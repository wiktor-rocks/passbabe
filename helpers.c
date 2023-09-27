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

enum Option {
    DATABASE_FILE,
    DATABASE_DIR,
    CONFIG,
    PB_DIR,
    HOME
} Option;

char *get_location(enum Option option)
{
    char *home_dir = getenv("HOME");

    char* location = malloc(ARRAY_SIZE * sizeof(char)); 

    if (location == NULL)
    {
        return NULL;
    } 

    switch(option) {
        case DATABASE_FILE:
            snprintf(location, ARRAY_SIZE, "%s/.config/passbabe/databases/database.pbdb", home_dir);
            break;
        case DATABASE_DIR:
            snprintf(location, ARRAY_SIZE, "%s/.config/passbabe/databases", home_dir);
            break;
        case CONFIG:
            snprintf(location, ARRAY_SIZE, "%s/.config/passbabe/passbabe.conf", home_dir);
            break;
        case PB_DIR:
            snprintf(location, ARRAY_SIZE, "%s/.config/passbabe", home_dir);
            break;
        case HOME:
            snprintf(location, ARRAY_SIZE, "%s", home_dir);
            break;
        default:
            free(location);
            return NULL;
    }

    return location;
        
}

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


void create_db_dir()
{

    char *full_path = get_location(PB_DIR);
    char *database_dir = get_location(DATABASE_DIR);  
    char *database_file_name = get_location(DATABASE_FILE);
    char *config_location = get_location(CONFIG);

    mkdir(full_path, 0777);
    mkdir(database_dir, 0777);
    
    free(full_path);

    FILE *database_file = fopen(database_file_name, "r");

    if (database_file != NULL)
    {
        fclose(database_file);
        free(database_file_name);
    }
    else
    {
        database_file= fopen(database_file_name, "w");
        free(database_file_name);
        if (database_file == NULL)
        {
            return;
        }
    }

    FILE *config_file = fopen(config_location, "r");

    if (config_file != NULL)
    {
        free(config_location);
        fclose(config_file);
    }
    else
    {
        config_file = fopen(config_location, "w");
        fclose(config_file);
        if (config_file == NULL)
        {
            return;
        }
    }

    return;
}



void list_entries()
{
    char *database_location = get_location(DATABASE_FILE);

    FILE* file = fopen(database_location, "r");

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

    char *database_location = get_location(DATABASE_FILE);

    char entry_name[ARRAY_SIZE];
    char username[ARRAY_SIZE];
    char password[ARRAY_SIZE];

    FILE *file = fopen(database_location, "a");

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
    char *database_location = get_location(DATABASE_FILE);

    FILE* file = fopen(database_location, "r");

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


    FILE *new_file= fopen(database_location, "w");

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

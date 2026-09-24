/*
 * Simple Line Editor in C
 *
 * Features:
 * 1. Insert a line
 * 2. Delete a line
 * 3. Display document
 * 4. Save document to a file
 * 5. Load document from a file
 * 6. Quit
 *
 * Data structure:
 * Fixed-size array of strings
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINES 100
#define MAX_LEN 256

char lines[MAX_LINES][MAX_LEN];
int line_count = 0;

/* Insert a new line */
void insert_line(int pos, const char *text)
{
    if (line_count >= MAX_LINES)
    {
        printf("Error: Document is full. Maximum %d lines allowed.\n",
               MAX_LINES);
        return;
    }

    if (pos < 1 || pos > line_count + 1)
    {
        printf("Error: Invalid line number.\n");
        return;
    }

    /* Shift lines down */
    for (int i = line_count; i >= pos; i--)
    {
        strcpy(lines[i], lines[i - 1]);
    }

    /* Add new line */
    strncpy(lines[pos - 1], text, MAX_LEN - 1);
    lines[pos - 1][MAX_LEN - 1] = '\0';

    line_count++;

    printf("Line inserted successfully at line %d.\n", pos);
}

/* Delete a line */
void delete_line(int pos)
{
    if (line_count == 0)
    {
        printf("Error: Document is empty.\n");
        return;
    }

    if (pos < 1 || pos > line_count)
    {
        printf("Error: Invalid line number.\n");
        return;
    }

    /* Shift lines up */
    for (int i = pos - 1; i < line_count - 1; i++)
    {
        strcpy(lines[i], lines[i + 1]);
    }

    line_count--;

    printf("Line %d deleted successfully.\n", pos);
}

/* Display the document */
void display_document()
{
    if (line_count == 0)
    {
        printf("\nDocument is empty.\n");
        return;
    }

    printf("\n----- DOCUMENT -----\n");

    for (int i = 0; i < line_count; i++)
    {
        printf("%d: %s\n", i + 1, lines[i]);
    }

    printf("--------------------\n");
}

/* Save document to file */
void save_file(const char *filename)
{
    FILE *file = fopen(filename, "w");

    if (file == NULL)
    {
        printf("Error: Could not open file for saving.\n");
        return;
    }

    for (int i = 0; i < line_count; i++)
    {
        fprintf(file, "%s\n", lines[i]);
    }

    fclose(file);

    printf("Document saved successfully to %s\n", filename);
}

/* Load document from file */
void load_file(const char *filename)
{
    FILE *file = fopen(filename, "r");

    if (file == NULL)
    {
        printf("Error: Could not open file for loading.\n");
        return;
    }

    line_count = 0;

    while (line_count < MAX_LINES &&
           fgets(lines[line_count], MAX_LEN, file) != NULL)
    {
        /* Remove newline character */
        lines[line_count][strcspn(lines[line_count], "\n")] = '\0';

        line_count++;
    }

    fclose(file);

    printf("Document loaded successfully from %s\n", filename);
    printf("Total lines loaded: %d\n", line_count);
}

/* Display menu */
void display_menu()
{
    printf("\n========== LINE EDITOR ==========\n");
    printf("1. Insert Line\n");
    printf("2. Delete Line\n");
    printf("3. Display Document\n");
    printf("4. Save Document\n");
    printf("5. Load Document\n");
    printf("6. Quit\n");
    printf("=================================\n");
}

int main()
{
    int choice;
    int line_no;
    char text[MAX_LEN];
    char filename[100];

    printf("=================================\n");
    printf("       SIMPLE LINE EDITOR\n");
    printf("=================================\n");

    while (1)
    {
        display_menu();

        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1)
        {
            printf("Error: Please enter a valid number.\n");

            while (getchar() != '\n')
            {
                /* Clear invalid input */
            }

            continue;
        }

        getchar(); /* Remove newline */

        switch (choice)
        {
            case 1:
                printf("Enter line number: ");

                if (scanf("%d", &line_no) != 1)
                {
                    printf("Error: Invalid line number.\n");

                    while (getchar() != '\n')
                    {
                        /* Clear input */
                    }

                    break;
                }

                getchar();

                printf("Enter text: ");
                fgets(text, MAX_LEN, stdin);

                text[strcspn(text, "\n")] = '\0';

                insert_line(line_no, text);
                break;

            case 2:
                printf("Enter line number to delete: ");

                if (scanf("%d", &line_no) != 1)
                {
                    printf("Error: Invalid line number.\n");

                    while (getchar() != '\n')
                    {
                        /* Clear input */
                    }

                    break;
                }

                getchar();

                delete_line(line_no);
                break;

            case 3:
                display_document();
                break;

            case 4:
                printf("Enter filename to save: ");
                fgets(filename, sizeof(filename), stdin);

                filename[strcspn(filename, "\n")] = '\0';

                save_file(filename);
                break;

            case 5:
                printf("Enter filename to load: ");
                fgets(filename, sizeof(filename), stdin);

                filename[strcspn(filename, "\n")] = '\0';

                load_file(filename);
                break;

            case 6:
                printf("\nExiting Line Editor...\n");
                printf("Thank you!\n");
                return 0;

            default:
                printf("Error: Invalid choice. Please select 1-6.\n");
        }
    }

    return 0;
}
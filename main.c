#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define MAX_PATH_LENGTH 1024

int main()
{
    char source[MAX_PATH_LENGTH], destination[MAX_PATH_LENGTH];
    printf("Entrez le chemin source: ");
    scanf("%s", source);
    printf("Entrez le chemin destination: ");
    scanf("%s", destination);

    char* extensions[] = { ".txt", ".png", ".doc", ".pdf" };
    int num_extensions = sizeof(extensions) / sizeof(char*);

    for (int i = 0; i < num_extensions; i++)
    {
        char search_path[MAX_PATH_LENGTH];
        sprintf(search_path, "%s\\*%s", source, extensions[i]);

        WIN32_FIND_DATA find_data;
        HANDLE find_handle = FindFirstFile(search_path, &find_data);

        if (find_handle != INVALID_HANDLE_VALUE)
        {
            do
            {
                if (!(find_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
                {
                    char source_file[MAX_PATH_LENGTH], dest_file[MAX_PATH_LENGTH];
                    sprintf(source_file, "%s\\%s", source, find_data.cFileName);
                    sprintf(dest_file, "%s\\%s", destination, find_data.cFileName);
                    CopyFile(source_file, dest_file, FALSE);
                }
            } while (FindNextFile(find_handle, &find_data));
            FindClose(find_handle);
        }
    }

    return 0;
}

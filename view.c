#include <stdio.h>
#include "view.h"
#include <string.h>
#include "types.h"

// This function is used to open the mp3 file and check if it is opened successfully or not
Status open_files(ToviewInfo *toview)
{
    // mp3 file
    toview->fptr_mp3_file = fopen(toview->mp3_fname, "r");

    // Do Error handling
    if (toview->fptr_mp3_file == NULL)
    {
        perror("fopen");
        fprintf(stderr, "ERROR: Unable to open file %s\n", toview->mp3_fname);

        return e_failure;
    }
    return e_success; // No failure return e_success
}

// this function is used to read the command line arguments and validate them
Status read_and_validate_view_args(char *argv[], ToviewInfo *toview)
{
    if (argv[2] == NULL)
    {
        return e_failure; // if the file name is not present return e_failure
    }

    // check .mp3 is present or not
    if (strstr(argv[2], ".mp3") != NULL)
    {
        // update into the structure
        toview->mp3_fname = argv[2];
        return e_success; // if yes return e_success
    }
    else
    {
        return e_failure; // if np return e_failure
    }
}

// This function is used to perform the view operation on the mp3 file
Status to_view(ToviewInfo *toview)
{
    // open the files
    if (open_files(toview) == e_failure)
    {
        // if open files fails return e_failure
        return e_failure;
    }

    // check the ID3 tag
    if (check_ID3_tag(toview) == e_failure)
    {
        // if check ID3 tag fails return e_failure
        return e_failure; // if check ID3 tag fails return e_failure
    }

    // check the version
    if (check_version(toview) == e_failure)
    {
        // if check version fails return e_failure
        return e_failure;
    }

    // View the mp3 file
    if (mp3_view(toview) == e_failure)
    {
        return e_failure; // if mp3 view fails return e_failure
    }

    // if all the above functions are successful return e_success
    return e_success;
}

// This function is used to check ID3 tag is present or not in the mp3 file
Status check_ID3_tag(ToviewInfo *toview)
{
    char tag[4];

    // read the first 3 bytes of the mp3 file
    fread(tag, 3, 1, toview->fptr_mp3_file);

    tag[3] = '\0'; // add null character at the end of the tag

    // check the tag is ID3 or not
    if (strcmp(tag, "ID3") == 0)
    {
        printf("ID3 tag is present\n\n"); // if yes print message
        return e_success;                 // if yes return e_success
    }
    else
    {
        printf("ID3 tag is not present\n\n"); // if no print message
        return e_failure;                     // if no return e_failure
    }
}

/*Check Version*/
Status check_version(ToviewInfo *toview)
{
    char version[2];

    // read the next 2 bytes of the mp3 file
    fread(version, 2, 1, toview->fptr_mp3_file);

    // check the version is 3 or not
    if (version[0] == 3)
    {
        printf("Version: 2.3\n\n"); // if yes print message
        return e_success;           // if yes return e_success
    }
    else
    {
        printf("Version: 2.%d\n\n", version[0]); // if no print message
        return e_failure;                        // if no return e_failure
    }
}

// This function is used to skip the header of the mp3 file which is 10 bytes long
Status skip_header(ToviewInfo *toview)
{
    // skip the first 10 bytes of the mp3 file
    fseek(toview->fptr_mp3_file, 10, SEEK_SET);

    return e_success;
}

// read tag print the message
Status read_tag(ToviewInfo *toview)
{
    char buffer[4];

    // read 4 bytes from mp3 file
    fread(buffer, 4, 1, toview->fptr_mp3_file);

    // buffer[4] = '\0';//add null character at the end of the buffer

    if (strcmp(buffer, "TIT2") == 0) // check the tag is TIT2 or not
    {
        printf("Title:      ");
        return e_success; // if yes return e_success
    }

    else if (strcmp(buffer, "TPE1") == 0) // check the tag is TPE1 or not
    {
        printf("Artist:     ");
        return e_success; // if yes return e_success
    }

    else if (strcmp(buffer, "TALB") == 0) // check the tag is TALB or not
    {
        printf("Album:      ");
        return e_success; // if yes return e_success
    }

    else if (strcmp(buffer, "TYER") == 0) // check the tag is TYER or not
    {
        printf("Year:       ");
        return e_success;
    }

    else if (strcmp(buffer, "TCON") == 0) // check the tag is TCON or not
    {
        printf("Genre:      ");
        return e_success;
    }

    else if (strcmp(buffer, "COMM") == 0) // check the tag is COMM or not
    {
        printf("Comment:     ");
        return e_success;
    }

    else
    {
        return e_failure; // if the tag is not present return e_failure
    }
}

// This function is used to read the size of the mp3 file and convert it from big endian to little endian
Status read_size(ToviewInfo *toview)
{
    int num;

    // read 4 bytes from mp3 file
    fread(&num, 4, 1, toview->fptr_mp3_file);

    // convert the size from big endian to little endian
    convert_big_to_little_endian(&num);

    toview->loop = num; // update the size in the structure
    // printf("Size: %d\n", toview->size);//print the size of the mp3 file

    return e_success; // return e_success
}

// This function is used to read the contents of the mp3 file and print it
Status read_contents(ToviewInfo *toview)
{
    char ch[100];

    // read the contents of the mp3 file until loop-1
    fread(ch, toview->loop - 1, 1, toview->fptr_mp3_file);

    ch[toview->loop - 1] = '\0'; // add null character at the end of the contents

    printf("%s\n", ch); // print the contents of the mp3 file

    return e_success; // return e_success
}

// This function is used to convert the size from big endian to little endian
Status convert_big_to_little_endian(int *num)
{
    // convert 4-byte integer from big endian to little endian
    *num =
        ((*num >> 24) & 0x000000FF) | // Extract the first byte and shift it to the last position

        ((*num << 8) & 0x00FF0000) | // Extract the second byte and shift it to the third position

        ((*num >> 8) & 0x0000FF00) | // Extract the third byte and shift it to the second position

        ((*num << 24) & 0xFF000000); // Extract the fourth byte and shift it to the first position

    // return success after converting the size from big endian to little endian
    return e_success; //
}

// This function is used to view the mp3 file and print the tags and contents of the mp3 file
Status mp3_view(ToviewInfo *toview)
{
    skip_header(toview);

    // run loop 6 times to read the tags and contents of the mp3 file
    for (int i = 0; i < 6; i++)
    {
        read_tag(toview);

        // read the size of the mp3 file
        if (read_size(toview) == e_failure)
        {
            return e_failure;
        }

        // skip the 3 bytes of flags
        fseek(toview->fptr_mp3_file, 3, SEEK_CUR);

        // read the contents of the mp3 file
        if (read_contents(toview) == e_failure)
        {
            return e_failure;
        }
    }
    return e_success; // if all the above functions are successful return e_success
}

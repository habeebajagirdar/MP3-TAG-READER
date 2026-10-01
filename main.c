#include <stdio.h>
#include <string.h>
#include "view.h"
#include "types.h"

int main(int argc, char *argv[])
{
    ToviewInfo toview;
    //  ToeditInfo toedit;

    int ret = check_operation_type(argv);

    // check the ret is e_view or not
    if (ret == e_view)
    {
        // if the read and validate view args function returns e_failure then print error
        if (read_and_validate_view_args(argv, &toview) == e_failure)
        {
            printf("Error : Invalid Arguments for View\n"); // printf error message and return 0
            return 0;
        }

        if (to_view(&toview) == e_failure)
        {
            printf("ERROR: Unable to read tag information\n");
            return 0;
        }
        printf("Viewing completed successfully!!!!!\n"); // success message
    }

    // check the ret is e_edit or not
    //  else if(ret == e_edit)
    
    else
    {
        printf("Error : Invalid arguments\n"); // printf error message and return 0
        return 0;
    }
    return 0;
}

// This function is used to check the tag of the mp3 file and print the corresponding message
OperationType check_operation_type(char *argv[])
{
    // check the argv[1] is NULL or not
    if (argv[1] == NULL)
    {
        return e_unsupported;
    }

    // check the argv[1] is -v or not
    if (strcmp(argv[1], "-v") == 0)
    {
        return e_view; // if yes return e_view
    }

    // check the argv[1] is -e or not
    else if (strcmp(argv[1], "-e") == 0)
    {
        return e_edit; // if yes return e_edit
    }
    else
    {
        return e_unsupported;
    }
}

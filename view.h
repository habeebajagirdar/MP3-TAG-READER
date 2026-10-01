#ifndef ENCODE_H
#define ENCODE_H

#include "types.h" //contains user defined types

// Structure to store the information required for encoding
typedef struct _toview
{
    /*mp3 file*/
    char *mp3_fname;
    FILE *fptr_mp3_file;
    unsigned int size;
    uint loop;

} ToviewInfo;

/*Check Operation type*/
OperationType check_operation_type(char *argv[]);

/*Get File Pointer*/
Status open_files(ToviewInfo *toview);

/*read and validate with extension*/
Status read_and_validate_view_args(char *argv[], ToviewInfo *toview);

/*Perform to view function*/
Status to_view(ToviewInfo *toview);

/*Check ID3 Tag*/
Status check_ID3_tag(ToviewInfo *toview);

/*Check Version*/
Status check_version(ToviewInfo *toview);

/*Skip the header of the mp3 file*/
Status skip_header(ToviewInfo *toview);

/*View the mp3 file*/
Status mp3_view(ToviewInfo *toview);

/*Read the tag of the mp3 file*/
Status read_tag(ToviewInfo *toview);

/*Read the size of the mp3 file*/
Status read_size(ToviewInfo *toview);

/*Read the contents of the mp3 file*/
Status read_contents(ToviewInfo *toview);

// Convert the size from big endian to little endian
Status convert_big_to_little_endian(int *num);

#endif

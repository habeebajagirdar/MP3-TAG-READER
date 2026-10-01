# MP3 Tag Reader

### 1. Read / View Tags (`-v`)
Reads the ID3v2 header and frames from an MP3 file and displays the
metadata in a formatted layout. It extracts:
- Title
- Artist
- Album
- Year
- Genre
- Comment

The program opens the file in binary mode, verifies the "ID3" signature,
reads the tag version and frame sizes, and prints the content of each
frame (TIT2, TPE1, TALB, TYER, TCON, COMM).

### 2. Edit Tags (`-e`)
Modifies a selected tag in the MP3 file. The user chooses which field to
change, and the program writes the new value into the matching frame
while keeping all other tags intact.

| Option | Field   |
|--------|---------|
| -t     | Title   |
| -a     | Artist  |
| -A     | Album   |
| -y     | Year    |
| -g     | Genre   |
| -c     | Comment |

## Files
- `main.c` - program entry point and argument handling
- `view.c / view.h` - reads and displays the tags
- `types.h` - common type definitions
- `sample.mp3` - sample file for testing

## Build
gcc main.c view.c -o mp3tag

## Usage
Read tags:
./mp3tag -v sample.mp3

Edit tags:
./mp3tag -e -t "New Title" sample.mp3

## Sample Output
Title   : Sunny Sunny - Yo Yo Honey Singh - [SongsPk.CC]
Artist  : Yo Yo Honey Singh - [SongsPk.CC]
Album   : Yaariyan
Year    : 2013
Genre   : Bollywood Music - [SongsPk.CC]
Comment :  eng
Viewing completed successfully!!!!!

#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE (1024 * 1024)


int print_file_contents(char *filename) {

	FILE* fileopen = fopen(filename, "r"); 
	
	if (fileopen == NULL) {
	    perror("fopen");
	    return 1;
	}
	
	char buffer[BUFFER_SIZE];

	while (fgets(buffer, sizeof(buffer), fileopen) != NULL) {
	    printf("%s", buffer);
	}   	
}


void copy_stdin_stdout() {
	char c[BUFFER_SIZE];

	while (1) {
    	fgets(c, sizeof(c), stdin);
    	printf("%s", c);
	}
}


void concatenate(FILE* openfile1, FILE* openfile2, char *contents_file1, char *contents_file2) {
	
	while (fgets(contents_file1, sizeof(contents_file1), openfile1) != NULL) { // Get the first file's content
	   printf("%s", contents_file1); // Print the first file content
	} 

	while (fgets(contents_file2, sizeof(contents_file2), openfile2) != NULL) { // Get the second file's content
		printf("%s", contents_file2); // Print the second file content
	}
	
}

/* Prediction for what the user wants here needs to be improved, This program may include bugs that 
can corrupt the user's data, Use with caution. Do not write important files with this program unless you verified
that it works. Based on our tests, The program is doing everything correctly and writing everything correctly. But don't trust our tests
They may be a specific case that you trigger that might corrupt your data or make unexpected actions
Again, Our tests showed nothing wrong. So you should be fine with using this tool
But still use with caution. We are not responsible for any loss of data or problems that may
happen with this program. If you found a bug, report it on GitHub or send it to the e-mail
(rpmiteam@proton.me) without brackets.
*/

int main (int argc, char *argv[]) {    
	if (argc == 1) { // If there is no specified files or options, copy stdin to standard output
	    copy_stdin_stdout();
	}

	if (argc == 3) {
		char *file1 = argv[1];
		char *file2 = argv[2];
	
		FILE* openfile1 = fopen(file1, "r");
		FILE* openfile2 = fopen(file2, "r");
		
		char contents_file1[BUFFER_SIZE];
		char contents_file2[BUFFER_SIZE];


		if (fopen(file1, "r") != NULL && fopen(file2, "r") != NULL) {
			concatenate(openfile1, openfile2, contents_file1, contents_file2);
		}

		if (fopen(file1, "r") == NULL || fopen(file2, "r") == NULL) {
			perror("fopen");
			printf("USAGE: %s <first_file> <second_file>", argv[0]);
			return 1;
		}				
	}
	
    if (argc == 2) {
    	char *filename = argv[1];
		print_file_contents(filename);
    }

    if (argc > 3) {
    	printf("USAGE: %s <options> <file> (Will change depending on the options)", argv[0]);
    	return 1;
    }	 

    return 0;
}

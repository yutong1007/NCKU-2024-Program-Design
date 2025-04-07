#include <stdio.h>
#include <string.h>

int main() {
	char input1[100],input2[100];
    FILE *read_file;
	while (1) {
		printf("Please enter the name of the file to read from.\n");
        fgets(input1, sizeof(input1), stdin); // input file name (read)
        input1[strcspn(input1, "\n")] = 0;

        if (strcmp(input1, "exit") == 0) {
            break;
       	}
        	
        read_file = fopen(input1, "r");
		if(read_file == NULL ) { // the file name of input is not exist
            printf("The file name does not exist.\n");
			continue;
        }
        fclose(read_file);
		
        printf("Please enter the name of the file to write the output to.\n");
        fgets(input2, sizeof(input2), stdin); // input file name (write)
        input2[strcspn(input2, "\n")] = 0;
        	
        // calculate
		read_file = fopen(input1, "r");
		int a, b, c, d;
        fscanf(read_file,"%d %d %d %d", &a, &b, &c, &d);
        fclose(read_file);
		

        // output
        int son, mom;
        son = a * d + c * b;
        mom = b * d;

        FILE *answer_file;
        answer_file = fopen(input2,"w");
        fprintf(answer_file, "%d/%d\n", son, mom);
        fclose(answer_file);
		printf("Calculation complete!\n");
	}	
	return 0;
}
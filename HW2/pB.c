#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]){
	// reading file
	FILE *read_file;
	read_file = fopen(argv[1], "r");
	int a, b, c, d;
	// 讀檔案要用fscanf
	fscanf(read_file,"%d %d %d %d", &a, &b, &c, &d);
	
	// 記得關檔案
	fclose(read_file);
	/*
	我一開始以為要約分
	// calculate
	// b d找最小公倍數
	int small;
	
	// b or d是最小公倍數
	if (b > d){
		if (b % d == 0){
		       small = b;	
		}
		else {
			int i = 1;
			while(1){
				int test = b * i;
				if (test % d == 0){
					small = test;
					break;
				}
				i++;
			}
		}
	}
	else if (d > b){
		if (d % b == 0){
			small = d;
		}
		else {
                        int i = 1;
                        while(1){
                                int test = d * i;
                                if (test % b == 0){
                                        small = test;
                                        break;
                                }
                                i++;
                        }
                }
	}
	else {
		small = b;
	}
	*/


	// 輸出
	int son, mom;
	son = a * d + c * b;
	mom = b * d;
	
	FILE *answer_file;
	answer_file = fopen("answer.txt","w");
	
	// 輸出在檔案要用fprintf
	fprintf(answer_file, "%d/%d\n", son, mom);
	fclose(answer_file);

	return 0;
}
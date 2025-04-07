#include <stdio.h>

void print_month_calendar(int days_in_month,int start_day) {
    for (int i = 0; i < start_day - 1; i++) {
        printf("   "); // Output spaces until the dates start.
    }

    for (int day = 1; day <= days_in_month; day++) {
        printf("%2d",day); // 用%2d確保每次輸出的整數都是兩位數寬
        if ( ( day + start_day - 1 ) % 7 == 0) {
            printf("\n"); // This line has already output up to Sunday, print a newline.
        }
	else {
	    printf(" ");
	}
    }
    printf("\n");
}

int main() {
    int days_in_month,start_day;
    scanf("%d %d",&days_in_month,&start_day);
    // Enter the number of days in the month and the starting day of the week.
    print_month_calendar(days_in_month,start_day);
    return 0;
}
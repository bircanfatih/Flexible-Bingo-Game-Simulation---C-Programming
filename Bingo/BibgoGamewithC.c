#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

typedef struct Cards {      
	
    int card[15];       // Bingo cards and line holder structure 
    int line[3];
    
} cards;

void print(int *array, int numRows, int numCols) {  
	
    int i, j;											// To print generared cards
    
    for (i = 0; i < numRows; i++) {
        for (j = 0; j < numCols; j++) {
            printf("%d ", array[i * numCols + j]);
        }
        printf("\n");
    }
}

void bubbleSortRows(int array[], int size) {
    
	int i, j;
	
    for (i = 0; i < size - 1; i++) {                   //In a Bingo card, each row is sorted within itself. We use the Bubble Sort function for this sorting process.
        for (j = 0; j < size - i - 1; j++) {
            if (array[j] > array[j + 1]) {
                int temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }
}

void cardgenerate(struct Cards *p1) {
    int i, j;
    
    for (i = 0; i < 15; i++) {
            p1->card[i] = 1 + rand() % 91;
            for (j = 0; j < i; j++) {
                if (p1->card[i] == p1->card[j]) {
                    i--;
                    break;
                }
            }
        }

    bubbleSortRows(p1->card, 5);
    bubbleSortRows(p1->card + 5, 5);
    bubbleSortRows(p1->card + 10, 5);
}
    
void game(struct Cards *p2, int num, int oy, int *win, int *lin1, int *lin2 ) {
   
    int k, j;

    for (k = 0; k < oy; k++) {
        for (j = 0; j < 15; j++) {                                  //In the Game function, each drawn number is compared sequentially with the card numbers to determine Line 1, Line 2, and Full House
            if (num == p2[k].card[j] && j < 5)
                p2[k].line[0]++;
            if (num == p2[k].card[j] && j < 10 && j >= 5)
                p2[k].line[1]++;
            if (num == p2[k].card[j] && j < 15 && j >= 10)
                p2[k].line[2]++;

            if ((p2[k].line[0] == 5 || p2[k].line[1] == 5 || p2[k].line[2] == 5) && *lin1 == 0) {
                if(*lin1==0){
                printf("\n\nLine 1: Player %d\n\n", k + 1);
                *lin1 = 1;
				}
               
            } else if ((p2[k].line[0] == 5 && p2[k].line[2] != 5 && p2[k].line[1] == 5 && *lin2 == 0) ||
                       (p2[k].line[0] == 5 && p2[k].line[1] != 5 && p2[k].line[2] == 5 && *lin2 == 0) ||
                       (p2[k].line[0] != 5 && p2[k].line[1] == 5 && p2[k].line[2] == 5 && *lin2 == 0)) {
						
						if(*lin2==0){
							printf("\n\nLine 2: Player %d\n\n", k + 1);
                		*lin2 = 1;
						}
                	
            } else if (p2[k].line[0] == 5 && p2[k].line[1] == 5 && p2[k].line[2] == 5) {
                *win = 1;
                printf("\n\nFull House: Player %d\n\n", k + 1);
                break;
            }
        }
        if (*win == 1)
            break;
    }
}

int main() {
    
    srand(time(NULL));
    int i, playernum, j, line1=0, line2=0,timer;
    int drawn[91];
	int winner=0;
	
    printf("Enter the number of players:\n");                   // You can select the number of player
    scanf("%d", &playernum);
    
    printf("Enter the timer in second:\n");                   // The number generation process slows down according to the entered duration
    scanf("%d", &timer);
    
    cards *player = (struct Cards*) malloc(playernum * sizeof(struct Cards));  // To make the number of players flexible, the dynamic array method was used
    
    for (i = 0; i < playernum; i++) {
        cardgenerate(&player[i]);
        printf("Player %d\n", i + 1);
        printf("*************\n");
        print(player[i].card, 3, 5);
        printf("*************\n\n");
        player[i].line[0] = 0;
        player[i].line[1] = 0;
        player[i].line[2] = 0;
	}
    
	printf("Numbers:\n");
	for(i=0;i<91;i++){
		drawn[i]=1+rand()%91;              //Bingo numbers are generated using the random function in such a way that they are not the same and fall between 1 and 99               
		int break1=0;
		for(j=0;j<i;j++){
		
			if(drawn[j]==drawn[i]){
				i--;
				break1=1;
				break;
			}	
		}
		if(break1==1)
		continue;
		
		printf(" %d ",drawn[i]);
		game(player, drawn[i], playernum, &winner,&line1,&line2);
		if(winner==1)                                              //When there is a winner, the number generation process is stopped
		break;
		sleep(timer);
	} 
    
    free(player);
    return 0;
}
    

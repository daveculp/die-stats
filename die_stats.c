#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#define FALSE 0
#define TRUE 1

// Function to roll a die with a specified number of sides
int rollDie(int sides, int reroll_1) 
{
	int num;
	
	num = 1;
	if (reroll_1 == FALSE)
	{
		num = rand() % sides + 1;
	}
	else 
	{
		while (num == 1)
		{
			num = rand() % sides + 1;
		}
	}
	return num;
}

// Function to generate the "old school" D&D stats for 6 ability scores
// dieType = number of sides on the die
// numRolls = number of times to roll the die
// dropLowest = if true, drop the lowest die roll
// Returns an array of the six numbers generated in ascending order
void getStats(int dieType, int numRolls, int dropLowest, int reroll_1, int* stats) {
    int i, j;
    for (i = 0; i < 6; i++) {
        int dice[numRolls];
        for (j = 0; j < numRolls; j++) {
            dice[j] = rollDie(dieType, reroll_1);
            //printf("%d\n", dice[j]);
        }

        // Sort the dice rolls
        for (j = 0; j < numRolls - 1; j++) {
            for (int k = 0; k < numRolls - j - 1; k++) {
                if (dice[k] > dice[k + 1]) {
                    int temp = dice[k];
                    dice[k] = dice[k + 1];
                    dice[k + 1] = temp;
                }
            }
        }

        // Drop the lowest roll if needed
        if (dropLowest) {
            int sum = 0;
            for (j = 1; j < numRolls; j++) {
                sum += dice[j];
            }
            stats[i] = sum;
        } else {
            int sum = 0;
            for (j = 0; j < numRolls; j++) {
                sum += dice[j];
            }
            stats[i] = sum;
        }
    }
}

int main() {
    setlocale(LC_NUMERIC, "");
    srand(time(NULL));

    unsigned long count = 0;
    unsigned long totals[7] = {0}; // Keeps track of the total number of characters with this number of 18s (0-6)

    int num_die,die,drop_low, reroll;

    num_die = 3;
    die = 6;
    drop_low = FALSE;
    reroll = TRUE;

    while (count < 1000000000000) {
        int stats[6];
        getStats(die, num_die, drop_low, reroll, stats);

        // Count the number of 18s and increment the corresponding total
        int num18s = 0;
        for (int i = 0; i < 6; i++) {
            if (stats[i] == 18) {
                num18s++;
            }
        }

        totals[num18s]++;
        count++;

        if (count % 10000000 == 0) {
            printf("%'lu\n", count);
        }
    }

    printf("%id%i Drop lowest:%i  Reroll 1's:%i\n",num_die,die,drop_low, reroll);

    printf("\nTotal number of characters generated: %lu\n", count);
    for (int i = 0; i < 7; i++) {
        printf("Total number of characters with %d 18's: %lu. ", i, totals[i]);
        if (totals[i] > 0) {
            printf("Ratio is 1 in %.18lf or %.18lf%%\n", (double)count / totals[i], ((double)totals[i] / count) * 100);
        } else {
            printf("\n");
        }
    }

    return 0;
}


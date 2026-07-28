#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

/*
 A simple console "Number Gambling Game" in C.
 Behavior modeled after the HTML/JS version:
 - Start with a balance (1000)
 - Each round: player places a bet (1..balance) and guesses a number 1..10
 - If guess matches random target (1..10), player wins the bet (balance += bet)
 - Otherwise player loses the bet (balance -= bet)
 - Round counter increments each play
 - Player can quit by entering 'q' when prompted for a bet
*/

long read_long(const char *prompt) {
    char buf[128];
    long val;

    while (1) {
        printf("%s", prompt);
        if (!fgets(buf, sizeof(buf), stdin)) {
            clearerr(stdin);
            continue;
        }
        // allow quitting by entering 'q' or 'Q' alone
        if ((buf[0] == 'q' || buf[0] == 'Q') && (buf[1] == '\n' || buf[1] == '\0')) {
            return LONG_MIN; // sentinel for quit
        }
        char *endptr;
        val = strtol(buf, &endptr, 10);
        if (endptr == buf || (*endptr != '\n' && *endptr != '\0')) {
            printf("Please enter a valid number or 'q' to quit.\n");
            continue;
        }
        return val;
    }
}

int main(void) {
    long balance = 1000;
    int round = 1;
    srand((unsigned)time(NULL));

    printf("Number Gambling Game (console)\n");
    printf("Starting balance: %ld\n", balance);
    printf("Type 'q' at any bet prompt to quit and save progress.\n\n");

    while (balance > 0) {
        printf("--- Round %d ---\n", round);
        printf("Balance: %ld\n", balance);

        long bet = read_long("Enter bet amount (1..balance): ");
        if (bet == LONG_MIN) break;
        if (bet < 1 || bet > balance) {
            printf("Invalid bet. Bet must be between 1 and %ld.\n\n", balance);
            continue;
        }

        long guess = read_long("Guess a number (1..10): ");
        if (guess == LONG_MIN) break;
        if (guess < 1 || guess > 10) {
            printf("Invalid guess. Please choose a number between 1 and 10.\n\n");
            continue;
        }

        int target = (rand() % 10) + 1;
        if (guess == target) {
            balance += bet;
            printf("Correct! The number was %d. You won %ld.\n", target, bet);
        } else {
            balance -= bet;
            printf("Wrong! The number was %d. You lost %ld.\n", target, bet);
        }

        round++;
        printf("\n");
    }

    if (balance <= 0) {
        printf("You are out of funds. Game over.\n");
    } else {
        printf("You quit the game. Final balance: %ld\n", balance);
    }

    return 0;
}

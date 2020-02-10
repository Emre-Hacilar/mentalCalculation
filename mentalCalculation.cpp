#include <iostream>
#include <ctime>
#include <string>
#include <vector>
#include <map>


// Prints the intro in the terminal
void PrintIntroduction() {
    // Game intro logs
    std::cout << "\n******************************************************\n";
    std::cout << "You are a secret agent breaking into a vault full of information.\n";
    std::cout << "You need to enter the correct codes to continue...\n";
    std::cout << "******************************************************\n";
}

// The level selection of the digits (easy: 2, medium: 3, hard: 4)
int SelectLevel() {
    std::cout << "\nSelect your level for the doors\n";
    std::cout << "Easy:     2 Digit code\n";
    std::cout << "Medium:   3 Digit code\n";
    std::cout << "Hard:     4 Digit code\n\n";

    // Variable for the user input
    std::string UserAnswer = "";

    // Reads the whole input of the user and initializes the value in the UserAnswer variable
    std::getline(std::cin, UserAnswer);

    // The 3 difficulties regarding the digit length of code as map
    std::map<std::string,int> DigitLengthDifficulty = {
        { "easy", 2},
        { "medium", 3},
        { "hard", 4}
    };

    // If the userinput was not given, we recall the function with a notification for the user
    if (DigitLengthDifficulty[UserAnswer] == 0) {
        std::cout << "Please provide a strength (easy, medium, hard)";
        return SelectLevel();
    }

    return DigitLengthDifficulty[UserAnswer];
}

// Returns the summary of an int vector
int GetSum(std::vector<int> DigitList) {
    int Summary = 0;

    for (int& digit : DigitList) {
        Summary += digit;
    }

    return Summary;
}

// Returns the product of an int vector
int GetProduct(std::vector<int> DigitList) {
    int Product = 1;

    for (int& digit : DigitList) {
        Product *= digit;
    }

    return Product;
}

/*
    The actual game where the random digits are generated on each call,
    afterwards an input from the player is expected (amount of inputs depend on the previously selected digit length difficulty) then, 
    when all the input from the player is given, we compare the randomly generated numbers with the user input.
    This is done by comparing the sum and the product of both number sequences.
    Important to know, since we compare the sum and product, the order of the digits doesn't really matter here.
*/
bool PlayGame(int Difficulty, int CodeLength) {
    ++Difficulty;

    // The vector which will contain the random digits
    std::vector<int> RandomDigits;

    // Generate random numbers and push into the vector -> amount is depending on CodeLength
    for (int i = 0; i < CodeLength; i++) {
        RandomDigits.push_back(rand() % Difficulty + Difficulty);
    }

    // Summary and product of the randomly generated numbers
    int DigitsSummary = 0;
    int DigitsProduct = 1;

    // Initializing the declared variables for summary and product of the random numbers
    DigitsSummary = GetSum(RandomDigits);
    DigitsProduct *= GetProduct(RandomDigits);

    // Printing hints about the code 
    std::cout << "\n- The code is a " << CodeLength << " digit number";
    std::cout << "\n- The code adds up to: " << DigitsSummary;
    std::cout << "\n- The code multiplies to: " << DigitsProduct << std::endl; // Extra line break so the user input is on a new line

    // User related variables (guessed numbers, input, sum, product)
    std::vector<int> GuessedNumbers;
    int UserInput;
    int GuessSummary = 0;
    int GuessProduct = 1;

    // Takes user input - how many is depending on the CodeLength (the selected difficulty)
    for (int i = 0; i < CodeLength; i++) {
        std::cin >> UserInput;

        // For if the user enters "bad" character
        std::cin.clear();
        std::cin.ignore();

        GuessedNumbers.push_back(UserInput);
    }

    // Initializing the declared variables for summary and product of the user guess
    GuessSummary = GetSum(GuessedNumbers);
    GuessProduct = GetProduct(GuessedNumbers);

    // Compare results
    return (GuessSummary == DigitsSummary) && (GuessProduct == DigitsProduct);
}

// Logs the remaining doors
void PrintRemainingDoors(int level) {
    const int remainingDoors = 10 - level;

    std::cout << remainingDoors << " more doors left!\n";
}

bool IsGameFinished(int MaxDifficulty, int LevelDifficulty, int AttemptsLeft) {
    // Check if it was the last level
    if (LevelDifficulty == MaxDifficulty) {
        std::cout << "\nYou did it! you are in the secret room full of information!";
        return true;
    }

    // Check if user has no attempts left
    if (AttemptsLeft == 0) {
        std::cout << "\nYou triggered the alarm...";
        return true;
    }

    return false;
}

int main() {
    // Creates a sequence of random numbers based on the current time
    srand(time(NULL)); 

    PrintIntroduction();

    // Determines how many digits can be in the code (easy = 2 | medium = 3 | hard = 4)
    const int DigitsCount = SelectLevel();

    const int MaxDifficulty = 10;
    int LevelDifficulty = 0;
    int AttemptsLeft = 3;

    while (true) {
        if (PlayGame(LevelDifficulty, DigitsCount)) {
            std::cout << "\nCorrect!\n\n";

            ++LevelDifficulty;

            PrintRemainingDoors(LevelDifficulty);
            
            // Reset attempts on the new level
            AttemptsLeft = 3;
        } else {
            std::cout << "\nWrong code...\n\n";

            --AttemptsLeft;

            std::cout << AttemptsLeft << " Attempts left\n";
        }

        if (IsGameFinished(MaxDifficulty, LevelDifficulty, AttemptsLeft)) {
            return false;
        }
    }

    return 0;
}
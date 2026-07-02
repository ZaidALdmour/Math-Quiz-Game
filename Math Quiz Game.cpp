#include <iostream>   // Include iostream for input/output operations.
#include <cstdlib>    // Include cstdlib for system functions like clearing the screen.
#include <ctime>      // Include ctime for random number seeding.

using namespace std;  // Use the standard namespace to avoid prefixing std:: before standard functions.

// Enumeration: enQuestionsLevel
// Purpose: Defines the difficulty levels available for quiz questions.
enum enQuestionsLevel { EasyLevel = 1, MedLevel = 2, HardLevel = 3, Mix = 4 };

// Enumeration: enOperationType
// Purpose: Defines the types of arithmetic operations used in the quiz.
enum enOperationType { Add = 1, Mult = 2, Sub = 3, Div = 4, MixOp = 5 };

// Function: RandomNumber
// Purpose: Generates a random number within the given range [From, To].
int RandomNumber(int From, int To)
{
    return rand() % (To - From + 1) + From;
}

// Function: GetOpTypeSymbol
// Purpose: Converts an operation type to its corresponding symbol.
string GetOpTypeSymbol(enOperationType OpType)
{
    switch (OpType)
    {
    case enOperationType::Add:
        return "+";
    case enOperationType::Mult:
        return "x";
    case enOperationType::Sub:
        return "-";
    case enOperationType::Div:
        return "/";
    default:
        return "Mix";
    }
}

// Function: GetRandomOperationType
// Purpose: Generates a random arithmetic operation type.
enOperationType GetRandomOperationType()
{
    return (enOperationType)RandomNumber(1, 4);
}

// Function: GetQuestionLevelText
// Purpose: Converts an enQuestionsLevel enum to a string representation.
string GetQuestionLevelText(enQuestionsLevel QuestionLevel)
{
    string arrQuestionLevelText[4] = { "Easy","Medium","Hard","Mixed" };
    return arrQuestionLevelText[QuestionLevel - 1];
}

// Function: SetScreenColor
// Purpose: Changes the console screen color based on answer correctness.
void SetScreenColor(bool Right)
{
    if (Right)
        system("color 2F"); // Green for correct answers.
    else
    {
        system("color 4F"); // Red for incorrect answers.
        cout << "\a"; // Plays an alert sound.
    }
}

// Function: SimpleCalculator
// Purpose: Performs the selected arithmetic operation on two numbers.
int SimpleCalculator(int Number1, int Number2, enOperationType OpType)
{
    switch (OpType)
    {
    case enOperationType::Add:
        return Number1 + Number2;
    case enOperationType::Mult:
        return Number1 * Number2;
    case enOperationType::Sub:
        return Number1 - Number2;
    case enOperationType::Div:
        return (Number2 != 0) ? (Number1 / Number2) : 0;  // Avoid division by zero.
    default:
        return Number1 + Number2;
    }
}

// Structure: stQuestion
// Purpose: Stores information for a single quiz question.
struct stQuestion
{
    int Number1 = 0;
    int Number2 = 0;
    enOperationType OperationType;
    enQuestionsLevel QuestionLevel;
    int CorrectAnswer = 0;
    int PlayerAnswer = 0;
    bool AnswerResult = false;
};

// Structure: stQuizz
// Purpose: Stores details of the entire quiz session.
struct stQuizz
{
    stQuestion QuestionList[100];
    short NumberOfQuestions;
    enQuestionsLevel QuestionsLevel;
    enOperationType OpType;
    short NumberOfWrongAnswers = 0;
    short NumberOfRightAnswers = 0;
    bool isPass = false;
};

// Function: ReadHowManyQuestions
// Purpose: Prompts the user to choose the number of questions.
short ReadHowManyQuestions()
{
    short NumberOfQuestions = 1;
    do
    {
        cout << "How many questions do you want to answer (1 to 10)? ";
        cin >> NumberOfQuestions;
    } while (NumberOfQuestions < 1 || NumberOfQuestions > 10);

    return NumberOfQuestions;
}

// Function: ReadOperationType
// Purpose: Prompts the user to choose the operation type.
enOperationType ReadOperationType()
{
    short OpType;
    do
    {
        cout << "Enter Opration Tybe : Add [1] Mult [2] Sub [3] Div [4] Mix [5] : ";
        cin >> OpType;
    } while (OpType < 1 || OpType > 5);

    return (enOperationType)OpType;
}

// Function: ReadQuestionsLevel
// Purpose: Prompts the user to choose the difficulty level.
enQuestionsLevel ReadQuestionsLevel()
{
    short Level;
    do
    {
        cout << "Enter qustions level : Easy[1] Mid[2] Hard [3] Mix [4] : ";
        cin >> Level;
    } while (Level < 1 || Level > 4);

    return (enQuestionsLevel)Level;
}

// Function: GenerateQuestion
// Purpose: Creates a random math question based on difficulty and operation type.
stQuestion GenerateQuestion(enQuestionsLevel QuestionLevel, enOperationType OpType)
{
    stQuestion Question;

    if (QuestionLevel == enQuestionsLevel::Mix)
        QuestionLevel = (enQuestionsLevel)RandomNumber(1, 3);

    if (OpType == enOperationType::MixOp)
        OpType = GetRandomOperationType();

    Question.OperationType = OpType;
    Question.QuestionLevel = QuestionLevel;

    switch (QuestionLevel)
    {
    case enQuestionsLevel::EasyLevel:
        Question.Number1 = RandomNumber(1, 10);
        Question.Number2 = RandomNumber(1, 10);
        break;
    case enQuestionsLevel::MedLevel:
        Question.Number1 = RandomNumber(10, 50);
        Question.Number2 = RandomNumber(10, 50);
        break;
    case enQuestionsLevel::HardLevel:
        Question.Number1 = RandomNumber(50, 100);
        Question.Number2 = RandomNumber(50, 100);
        break;
    }

    Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OperationType);
    return Question;
}

// Function: GenerateQuizzQuestions
// Purpose: Fills the quiz structure with generated questions.
void GenerateQuizzQuestions(stQuizz& Quizz)
{
    for (short QuestionNumber = 0; QuestionNumber < Quizz.NumberOfQuestions; QuestionNumber++)
    {
        Quizz.QuestionList[QuestionNumber] = GenerateQuestion(Quizz.QuestionsLevel, Quizz.OpType);
    }
}

// Function: AskAndCorrectQuestionListAnswers
// Purpose: Iterates through quiz questions, evaluates answers, and provides feedback.
void AskAndCorrectQuestionListAnswers(stQuizz& Quizz)
{
    for (short QuestionNumber = 0; QuestionNumber < Quizz.NumberOfQuestions; QuestionNumber++)
    {
        cout << "\nQuestion [" << QuestionNumber + 1 << "/" << Quizz.NumberOfQuestions << "]\n";
        cout << Quizz.QuestionList[QuestionNumber].Number1 << " "
            << GetOpTypeSymbol(Quizz.QuestionList[QuestionNumber].OperationType) << " "
            << Quizz.QuestionList[QuestionNumber].Number2 << " = ";

        cin >> Quizz.QuestionList[QuestionNumber].PlayerAnswer;

        if (Quizz.QuestionList[QuestionNumber].PlayerAnswer == Quizz.QuestionList[QuestionNumber].CorrectAnswer)
        {
            cout << "Correct!\n";
            Quizz.QuestionList[QuestionNumber].AnswerResult = true;
            Quizz.NumberOfRightAnswers++;
        }
        else
        {
            cout << "Wrong! Correct Answer: " << Quizz.QuestionList[QuestionNumber].CorrectAnswer << endl;
            Quizz.QuestionList[QuestionNumber].AnswerResult = false;
            Quizz.NumberOfWrongAnswers++;
        }

        SetScreenColor(Quizz.QuestionList[QuestionNumber].AnswerResult);
    }

    Quizz.isPass = (Quizz.NumberOfRightAnswers >= Quizz.NumberOfWrongAnswers);
}

// Function: PrintQuizzResults
// Purpose: Displays the final stats of the quiz.
void PrintQuizzResults(stQuizz Quizz)
{
    cout << "\n\n____________________________________________________\n";
    if (Quizz.isPass)
    {
        cout << "                 +++ QUIZZ PASSED +++\n";
        system("color 2F"); // Screen remains Green on pass
    }
    else
    {
        cout << "                 +++ QUIZZ FAILED +++\n";
        system("color 4F"); // Screen remains Red on fail
    }
    cout << "____________________________________________________\n\n";

    cout << "Total Questions    : " << Quizz.NumberOfQuestions << endl;
    cout << "Questions Level    : " << GetQuestionLevelText(Quizz.QuestionsLevel) << endl;
    cout << "Operation Type     : " << (Quizz.OpType == enOperationType::MixOp ? "Mix" : GetOpTypeSymbol(Quizz.OpType)) << endl;
    cout << "Number of Right    : " << Quizz.NumberOfRightAnswers << endl;
    cout << "Number of Wrong    : " << Quizz.NumberOfWrongAnswers << endl;
    cout << "____________________________________________________\n";
}

// Function: PlayMathGame
// Purpose: Initializes the quiz, generates questions, and manages the quiz flow.
void PlayMathGame()
{
    stQuizz Quizz;

    Quizz.NumberOfQuestions = ReadHowManyQuestions();
    Quizz.OpType = ReadOperationType();
    Quizz.QuestionsLevel = ReadQuestionsLevel();

    GenerateQuizzQuestions(Quizz);
    AskAndCorrectQuestionListAnswers(Quizz);
    PrintQuizzResults(Quizz);
}

// Function: StartGame
// Purpose: Main loop that allows playing the game multiple times.
void StartGame()
{
    char PlayAgain = 'Y';
    do
    {
        system("cls");
        system("color 0F"); // Reset to default black background
        PlayMathGame();

        cout << "\nDo you want to play again? (Y/N): ";
        cin >> PlayAgain;
    } while (PlayAgain == 'Y' || PlayAgain == 'y');
}

// Main Function
int main()
{
    srand((unsigned)time(NULL));  // Seed the random number generator.
    StartGame();  // Start the quiz game loop.
    return 0;  // Exit the program successfully.
}
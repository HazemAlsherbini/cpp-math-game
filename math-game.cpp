#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

enum enQuestionsLevel { Easy = 1, Medium = 2, Hard = 3, Mix = 4 };

enum enQuestionsType { Add = 1, Sub = 2, Mul = 3, Div = 4, MixOp = 5 };

struct strQuestionInfo
{
    int FirstNumber = 0;
    int SecondNumber = 0;
    enQuestionsType OpType;
    enQuestionsLevel QuestionLevel;
    int CorrectAnswer = 0;
    int PlayerAnswer = 0;
    bool RightAnswer;
};

struct strQuizInfo
{
    strQuestionInfo Questions[100]; 
    enQuestionsType QuizOpType;
    enQuestionsLevel QuizLevel;
    short NumberOfQuestions;
    short NumberOfRightAnswers = 0;
    short NumberOfWrongAnswers = 0;
};

int RandomNumbersInRange(int from, int to)
{
    int random = rand() % (to - from + 1) + from;
    return random;
}

short ReadNumberOfQuestions()
{
    short NumberOfQuestions;

    cout << "\nHow many Question Do you want to answer? ";
    cin >> NumberOfQuestions;

    return NumberOfQuestions;
}

enQuestionsLevel ReadLevel()
{
    short Choice = -1;

    while (Choice < 1 || Choice > 4)
    {
        cout << "\nEnter Questions Level : [1] Easy ,[2] Medium ,[3] Hard ,[4] Mix ? ";
        cin >> Choice;
    }

    return (enQuestionsLevel)Choice;
}

enQuestionsType ReadType()
{
    short Choice = -1;

    while (Choice < 1 || Choice > 5)
    {
        cout << "\nEnter Questions Type : [1] Add ,[2] Sub ,[3] Mul ,[4] Div ,[5] Mix ? ";
        cin >> Choice;
    }

    return (enQuestionsType)Choice;
}

string PrintOperator(short OperatorNum)
{
    const string Op[] = { "+" ,"-","x","/" ,"Mix"};
    return Op[OperatorNum - 1];
}

string PrintLevel(short LevelNum)
{
    const string Level[] = { "Easy" , "Med" , "Hard" , "Mix" };
    return Level[LevelNum - 1];
}

int ReadStudentAnswer()
{
    int Answer;
    cin >> Answer;
    return Answer;
}

char ReadYESorNO(string message)
{
    char Choice;
    do {
        cout << message;
        cin >> Choice;
        Choice = tolower(Choice);

    } while (Choice != 'y' && Choice != 'n');
    return Choice;
}

void ClearScreen() {
    system("cls");
}

bool MoreQuiz()
{
    char Choice = ReadYESorNO("\nDo you Want To Solve More? [Y] or [N] : ");

    if (Choice == 'y')
    {
        ClearScreen();
        return true;
    }
    else
        return false;
}

void RingBell()
{
    cout << "\a";
}

void ScreenColor(bool IsPass)
{
    if (IsPass)
    {
        cout << "Right Answer :-)\n";
        system("color 2F");
    }
    else
    {
        cout << "Wrong Answer :-)\n";
        RingBell();
        system("color 4F");
    }
}

int CalculateAnswer(const strQuestionInfo & Question)
{
    switch (Question.OpType)
    {
    case enQuestionsType::Add :
        return Question.FirstNumber + Question.SecondNumber ;

    case enQuestionsType::Sub:
        return Question.FirstNumber - Question.SecondNumber;

    case enQuestionsType::Mul:
        return Question.FirstNumber * Question.SecondNumber;

    case enQuestionsType::Div:
        return ( Question.SecondNumber != 0 ) ? (Question.FirstNumber / Question.SecondNumber) : 0 ;

    default:
        return Question.FirstNumber + Question.SecondNumber;
    }

}

void GenerateQuestionNumbers(strQuestionInfo & Question)
{
    switch (Question.QuestionLevel)
    {
    case enQuestionsLevel::Easy:
        Question.FirstNumber = RandomNumbersInRange(1, 10);
        Question.SecondNumber = RandomNumbersInRange(1, 10);
        break;

    case enQuestionsLevel::Medium:
        Question.FirstNumber = RandomNumbersInRange(10, 50);
        Question.SecondNumber = RandomNumbersInRange(10, 50);
        break;

    case enQuestionsLevel::Hard:
        Question.FirstNumber = RandomNumbersInRange(50, 100);
        Question.SecondNumber = RandomNumbersInRange(50, 100);
        break;
    }
}

strQuestionInfo GenerateQuestion(const strQuizInfo &  QuizInfo)
{
    enQuestionsLevel Level = QuizInfo.QuizLevel;
    enQuestionsType Type = QuizInfo.QuizOpType;

    strQuestionInfo QuestionInfo;

    if (Level == enQuestionsLevel::Mix)
        Level = (enQuestionsLevel)RandomNumbersInRange(1, 3);

    if (Type == enQuestionsType::MixOp)
        Type = (enQuestionsType)RandomNumbersInRange(1, 4);

    QuestionInfo.QuestionLevel = Level;
    QuestionInfo.OpType = Type;

    GenerateQuestionNumbers(QuestionInfo);

    QuestionInfo.CorrectAnswer = CalculateAnswer(QuestionInfo);
    
    return QuestionInfo;
}

void GenerateQuestions (strQuizInfo & QuizInfo )
{
    for (short Question = 0 ; Question < QuizInfo.NumberOfQuestions ; Question++)
    {
        QuizInfo.Questions[Question] = GenerateQuestion(QuizInfo);
    }
}

void ConductQuiz(strQuizInfo& QuizInfo)
{
    for (short Question = 0; Question < QuizInfo.NumberOfQuestions; Question++)
    {
        cout << "Question [" << Question + 1 << "/" << QuizInfo.NumberOfQuestions << "]\n\n";
        cout << QuizInfo.Questions[Question].FirstNumber << "\n" <<
            QuizInfo.Questions[Question].SecondNumber << PrintOperator(QuizInfo.Questions[Question].OpType)
            << "\n-------------\n";
        QuizInfo.Questions[Question].PlayerAnswer = ReadStudentAnswer();

        if (QuizInfo.Questions[Question].PlayerAnswer == QuizInfo.Questions[Question].CorrectAnswer)
        {
            QuizInfo.Questions[Question].RightAnswer = true;
            QuizInfo.NumberOfRightAnswers++;
        }
        else
        {
            QuizInfo.Questions[Question].RightAnswer = false;
            QuizInfo.NumberOfWrongAnswers++;
        }

        ScreenColor(QuizInfo.Questions[Question].RightAnswer);
        
    }
}

strQuizInfo StartQuiz()
{
    strQuizInfo QuizInfo;
    QuizInfo.NumberOfQuestions = ReadNumberOfQuestions();
    QuizInfo.QuizLevel = ReadLevel();
    QuizInfo.QuizOpType = ReadType();

    GenerateQuestions(QuizInfo);
    ConductQuiz(QuizInfo);

    return QuizInfo;
}

string GetQuizResult(const strQuizInfo & QuizInfo)
{
    if (QuizInfo.NumberOfRightAnswers >= QuizInfo.NumberOfWrongAnswers)
        return "PASS";
    else
        return "FAIL";
}

void FinalResults(const strQuizInfo& QuizInfo)
{
    cout << "\n\n";

    cout << "--------------------------------------------------\n";
    cout << " Final Result is " << GetQuizResult(QuizInfo) << "\n";
    cout << "__________________________________________________\n\n";

    cout << "__________________________________________________\n";
    cout << "Questions   Number   : " << QuizInfo.NumberOfQuestions << endl;
    cout << "Questions   Level    : " << PrintLevel(QuizInfo.QuizLevel) << endl;
    cout << "Operator    Type     : " << PrintOperator(QuizInfo.QuizOpType) << endl;
    cout << "Right  Answers       : " << QuizInfo.NumberOfRightAnswers << endl;
    cout << "Wrong  Answers       : " << QuizInfo.NumberOfWrongAnswers << endl;

    cout << "__________________________________________________\n";

}

void StartGame()
{
    do
    {
        system("color 0F");

        strQuizInfo QuizResults = StartQuiz();

        FinalResults(QuizResults);

    } while (MoreQuiz());
}

int main()
{
    srand((unsigned)time(NULL));
    StartGame();
}


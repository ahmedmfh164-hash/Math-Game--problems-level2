#include <iostream>
#include<cstdlib>
#include<ctime>
using namespace std;

enum enQuesitionLevel { EasyLevel = 1, MedLevel = 2, HardLevel = 3, Mix = 4 };
enum enOperationType { Add = 1, Sub = 2, Mult = 3, Div = 4, MixOp = 5 };

int ReadNumberOfQuesition(string Message)
{
	int Number;
	do {
		cout << Message<<endl;
		cin >> Number;
	} while (Number < 0);
	return Number;
}

int RandomNumber(int From,int To)
{
	int RandomNum = rand() % (To - From + 1) + From;
	return RandomNum;
}

string GetOpTypeSymbol(enOperationType OpType)
{
	switch (OpType)
	{
	case enOperationType::Add:
		return "+";
		break;
	case enOperationType::Sub:
		return "-";
		break;
	case enOperationType::Mult:
		return "x";
		break;
	case enOperationType::Div:
		return "/";
		break;
	default:
		return "Mix";
	}	
}

enOperationType GetRandomOperationType()
{
	return (enOperationType)RandomNumber(1, 4);
}

string GetQuesitionLevelText(enQuesitionLevel QuesitionLevel)
{
	string arrQuesitionLevelText[4] = { "Easy","Medium","Hard","Mixed" };
	return arrQuesitionLevelText[QuesitionLevel - 1];
}

void SetScreenColor(bool Right)
{
	if (Right)
		system("color 2F");
	else
		system("color 4F");
	cout << "\a";
}

int SimpleCalculator(int Number1, int Number2, enOperationType OpType)
{
	switch (OpType)
	{
	case enOperationType::Add:
		return Number1 + Number2;
	case enOperationType::Sub:
		return Number1 - Number2;
	case enOperationType::Mult:
		return Number1 * Number2;
	case enOperationType::Div:
		return (Number2 != 0) ? (Number1 / Number2) : 0;
	default:
		return Number1 + Number2;
	}
}

struct stQuesition
{
	int Number1 = 0;
	int Number2 = 0;
	enOperationType OperationType;
	enQuesitionLevel QuesitionLevel;
	int CorrectAnswer = 0;
	int PlayerAnswer = 0;
	bool AnswerResult = false;
};

struct stQuiz
{
	stQuesition QuestionList[100];
	short NumberOfQuesition;
	enQuesitionLevel QuesitionLevel;
	enOperationType OpType;
	short NumberOfWrongAnswers = 0;
	short NumberOfRightAnswers = 0;
	bool IsPass = false;
};

stQuesition GenerateQuesition(enQuesitionLevel QuesitionLevel, enOperationType OpType)
{
	stQuesition Quesition;
	if (QuesitionLevel == enQuesitionLevel::Mix)
		QuesitionLevel = (enQuesitionLevel)RandomNumber(1, 3);

	if (OpType == enOperationType::MixOp)
		OpType = GetRandomOperationType();

	Quesition.OperationType = OpType;

	switch (QuesitionLevel)
	{
	case enQuesitionLevel::EasyLevel:
		Quesition.Number1 = RandomNumber(1, 10);
		Quesition.Number2 = RandomNumber(1, 10);
		break;
	case enQuesitionLevel::MedLevel:
		Quesition.Number1 = RandomNumber(10, 50);
		Quesition.Number2 = RandomNumber(10, 50);
		break;
	case enQuesitionLevel::HardLevel:
		Quesition.Number1 = RandomNumber(50, 100);
		Quesition.Number2 = RandomNumber(50, 100);
		break;
	}

	Quesition.CorrectAnswer = SimpleCalculator(Quesition.Number1, Quesition.Number2, Quesition.OperationType);
		Quesition.QuesitionLevel = QuesitionLevel;

		return Quesition;
}

void AskAndCorrectQuestionListAnswers(stQuiz& Quiz)
{
	for (short QuesitionNumber = 0;QuesitionNumber < Quiz.NumberOfQuesition;QuesitionNumber++)
	{
		cout << "\nQuestion [" << QuesitionNumber + 1 << "/" << Quiz.NumberOfQuesition << "]\n\n";
		cout << Quiz.QuestionList[QuesitionNumber].Number1 << " " << GetOpTypeSymbol(Quiz.QuestionList[QuesitionNumber].OperationType) << " \n"
			<< Quiz.QuestionList[QuesitionNumber].Number2 << "\n----\n";

		cin >> Quiz.QuestionList[QuesitionNumber].PlayerAnswer;

		if (Quiz.QuestionList[QuesitionNumber].PlayerAnswer == Quiz.QuestionList[QuesitionNumber].CorrectAnswer)
		{
			cout << "Correct!\n";
			Quiz.NumberOfRightAnswers++;
		}
		else
		{
			cout << "Wrong Correct Answer : " << Quiz.QuestionList[QuesitionNumber].CorrectAnswer << endl;
			Quiz.NumberOfWrongAnswers++;
		}
	}

	Quiz.IsPass = (Quiz.NumberOfRightAnswers >= Quiz.NumberOfWrongAnswers);

}

void PlayMathGame()
{
	stQuiz Quiz;
	Quiz.NumberOfQuesition = ReadNumberOfQuesition("How Many Quesition do you want to answer ?");
	Quiz.QuesitionLevel = enQuesitionLevel::EasyLevel;
	Quiz.OpType = enOperationType::MixOp;

	for (short QuesitionNumber = 0;QuesitionNumber < Quiz.NumberOfQuesition;QuesitionNumber++)
	{
		Quiz.QuestionList[QuesitionNumber] = GenerateQuesition(Quiz.QuesitionLevel, Quiz.OpType);
	}

	AskAndCorrectQuestionListAnswers(Quiz);

	cout << "\nQiuz Completed! Right Answers : " << Quiz.NumberOfRightAnswers << ",Wrong Answers: " << Quiz.NumberOfWrongAnswers << "\n";

	cout << (Quiz.IsPass ? "You Passed the Quiz !\n " : "you Failed the Quiz!\n");
}

int main()
{
	srand((unsigned)time(NULL));

	PlayMathGame();
}


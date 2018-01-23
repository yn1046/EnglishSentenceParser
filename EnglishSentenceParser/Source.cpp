#define _CRT_SECURE_NO_WARNINGS
#define PATTERN_LENGTH sizeof(Pattern)/sizeof(Pattern[0]) - 1
#include <iostream>

enum Type
{
	noun, verb, article
};
Type Pattern[] = { noun, verb, article, noun };

struct Word
{
	char value[100];
	Type type;
} WordList[11];

int Search(char* value)
{
	int i, len = 11;
	for (i = 0; i < len; i++)
		if (strcmp(WordList[i].value, value) == 0) return i;
	return -1;
}

bool Match(Type *type, char* lexem)
{
	int i = Search(lexem);
	if (i != -1 && WordList[i].type == *type)
	{
		printf("%s is correct\n", lexem);
		char* nextLexem = strtok(NULL, " ,.");
		if (nextLexem != NULL) return Match(type + 1, nextLexem);
		if (&Pattern[PATTERN_LENGTH] == type) return true;
		puts("Probably the string is too short.");
		return false;
	}
	return false;
}

bool Scan(char* sentence) {
	printf("text: ");
	puts(sentence);
	
	Type* pPattern = &Pattern[0];
	char* lexem = strtok(sentence, " ,.");
	if (Match(pPattern, lexem)) return true;
	return false;
}

bool ScanAscending(char* sentence)
{
	printf("text: ");
	puts(sentence);

	Type* pPattern = &Pattern[0];
	char* lexem = strtok(sentence, " ,.");
	while (lexem != NULL)
	{
		int i = Search(lexem);
		if (i != -1 && WordList[i].type == *pPattern)
		{
			printf("%s is correct\n", lexem);
			lexem = strtok(NULL, " ,.");
			pPattern++;
		}
		else return false;
	}
	if (&Pattern[PATTERN_LENGTH+1] == pPattern) return true;
	puts("Probably the string is too short.");
	return false;
}

bool Parse(char *sentence)
{
	WordList[0] = { "a", article };
	WordList[1] = { "the", article };
	WordList[2] = { "Linus", noun };
	WordList[3] = { "Charlie", noun };
	WordList[4] = { "Snoopy", noun };
	WordList[5] = { "blanket", noun };
	WordList[6] = { "dog", noun };
	WordList[7] = { "song", noun };
	WordList[8] = { "holds", verb };
	WordList[9] = { "pets", verb };
	WordList[10]= { "sings", verb };

	bool res;
	char resString[100], input[100];
	puts("How'd you like to scan? 1 - descending, 2 - ascending\n");
	gets_s(input);
	while (strcmp(input, "1") != 0 && strcmp(input, "2") != 0)
	{
		puts("Wrong input. Enter only \"1\" or \"2\".\n");
		gets_s(input);
	}
	if (strcmp(input, "1") == 0)
	{
		res = Scan(sentence);
		strcpy(resString, "Descent parsing returned ");
		strcat(resString, (res ? "True" : "False"));
		puts(resString);
	}
	else
	{
		res = ScanAscending(sentence);
		strcpy(resString, "Ascent parsing returned ");
		strcat(resString, (res ? "True" : "False"));
		puts(resString);
	}

	return res;
}

int main()
{
	char inputString[100];
	puts("Please enter a string.");
	gets_s(inputString);

	if (Parse(inputString)) puts("String matches the pattern, everything is OK.");
	else puts("String doesn't match the pattern.");

	system("pause");
	return 0;
}
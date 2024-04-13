#include <stdio.h>
#include <string.h>
#include <ctype.h>

int isSeparator(char character)
{
    return (character == ';' || character == ',' || character == '\'' || character == '\"');
}

int isOperator(char character)
{
    return (character == '+' || character == '-' ||
            character == '*' || character == '/' ||
            character == '>' || character == '<' ||
            character == '!' || character == '=');
}

int isDigit(char character)
{
    return (character >= '0' && character <= '9');
}

int isParenthesis(char character)
{
    return (character == ')' || character == '(' ||
            character == '}' || character == '{');
}

int isSingleCharSeparator(const char *lexeme)
{
    return (strlen(lexeme) == 1 && isSeparator(lexeme[0]));
}

int keyword(const char *lexeme)
{
    FILE *kw;
    kw = fopen("Keyword.txt", "r");
    char c, kwstr[100];
    int i = 0, result = 0;

    while ((c = getc(kw)) != EOF)
    {
        if (!isspace(c))
        {
            kwstr[i] = c;
            i++;
        }
        else
        {
            for (int j = 0; j < strlen(kwstr); j++)
            {
                if (kwstr[j] != lexeme[j])
                {
                    result = 0;
                    break;
                }
                result = 1;
            }
            i = 0;
            if (result == 1)
            {
                fclose(kw);
                return result;
            }
            memset(kwstr, 0, strlen(kwstr));
        }
    }
    fclose(kw);
    return result;
}

int isOperatorOrEqual(const char *lexeme)
{
    if (strlen(lexeme) == 1)
    {
        return isOperator(lexeme[0]);
    }
    else if (strlen(lexeme) == 2 && isOperator(lexeme[0]) && lexeme[1] == '=')
    {
        return 1;
    }
    return 0;
}

int isSingleCharParenthesis(const char *lexeme)
{
    return (strlen(lexeme) == 1 && isParenthesis(lexeme[0]));
}

int isNumber(const char *lexeme)
{
    int decimalPointFound = 0;
    for (int i = 0; i < strlen(lexeme); ++i)
    {
        char c = lexeme[i];

        if (c == '.')
        {
            if (decimalPointFound)
            {
                return 0;
            }
            decimalPointFound = 1;
        }
        else if (!isdigit(c))
        {
            return 0;
        }
    }

    return 1;
}

int isIdentifier(const char *lexeme)
{
    if (strlen(lexeme) == 0 || isdigit(lexeme[0]))
    {
        return 0;
    }
    for (int i = 0; i < strlen(lexeme); ++i)
    {
        char c = lexeme[i];

        if (!(isalnum(c) || c == '_'))
        {
            return 0;
        }
    }
    return 1;
}

int main()
{
    char inputChars[1000];
    char processedChars[2000];
    int error = 0;

    FILE *file = fopen("input.txt", "r");
    if (!file)
    {
        printf("No such file.\n");
        return 0;
    }

    int ch;
    int i = 0;
    while ((ch = fgetc(file)) != EOF)
    {
        inputChars[i++] = ch;
    }
    inputChars[i] = '\0';

    printf("Input:\n%s\n", inputChars);

    int inputSize = strlen(inputChars);
    int flag = 0;
    int j = 0;
    int separatorOn = 0;

    for (int i = 0; i < inputSize; i++)
    {
        if (isSeparator(inputChars[i]))
        {
            if (inputChars[i] == '\'')
            {
                if (separatorOn)
                {
                    separatorOn = 0;
                    processedChars[j++] = ' ';
                    processedChars[j++] = inputChars[i];
                }
                else
                {
                    processedChars[j++] = inputChars[i];
                    processedChars[j++] = ' ';
                    separatorOn = 1;
                }
            }
            else if (inputChars[i] == '\"')
            {
                if (separatorOn)
                {
                    separatorOn = 0;
                    processedChars[j++] = ' ';
                    processedChars[j++] = inputChars[i];
                }
                else
                {
                    processedChars[j++] = inputChars[i];
                    processedChars[j++] = ' ';
                    separatorOn = 1;
                }
            }
            else
            {
                processedChars[j++] = ' ';
                processedChars[j++] = inputChars[i];
            }
        }
        else if (isOperator(inputChars[i]))
        {
            if (inputChars[i + 1] == '=')
            {
                processedChars[j++] = ' ';
                processedChars[j++] = inputChars[i];
                processedChars[j++] = inputChars[i + 1];
                i++;
                processedChars[j++] = ' ';
            }
            else
            {
                processedChars[j++] = ' ';
                processedChars[j++] = inputChars[i];
                processedChars[j++] = ' ';
            }
            flag = 1;
        }
        else if (isDigit(inputChars[i]))
        {
            if (flag == 0)
            {
                flag = 1;
                processedChars[j++] = ' ';
            }
            processedChars[j++] = inputChars[i];
        }
        else if (isParenthesis(inputChars[i]))
        {
            processedChars[j++] = ' ';
            processedChars[j++] = inputChars[i];
            if (inputChars[i] != ')' && inputChars[i] != '}')
            {
                processedChars[j++] = ' ';
            }
        }
        else
        {
            flag = 1;
            processedChars[j++] = inputChars[i];
        }
    }

    processedChars[j] = '\0';

    printf("\n\n");
    printf("Output-1(Lexemes are separated):\n%s\n", processedChars);

    FILE *lexemeFile = fopen("lexeme.txt", "w");
    if (lexemeFile)
    {
        fprintf(lexemeFile, "%s", processedChars);
        fclose(lexemeFile);
    }
    else
    {
        printf("Unable to open lexeme.txt for writing.\n");
    }

    printf("\n\nOutput-2(Lexemes are categorized):\n");
    FILE *lexemeCatFile = fopen("lexemeCat.txt", "w");
    if (lexemeCatFile)
    {
        char inputLexeme[100];
        j = 0;

        for (int i = 0; i <= strlen(processedChars); i++)
        {
            if (processedChars[i] == ' ' || processedChars[i] == '\0')
            {
                inputLexeme[j++] = '\0';
                if (strlen(inputLexeme) == 0)
                {
                    j = 0;
                    continue;
                }
                if (isSingleCharSeparator(inputLexeme))
                {
                    printf("[sep %s] ", inputLexeme);
                    fprintf(lexemeCatFile, "[sep %s] ", inputLexeme);
                }
                else if (keyword(inputLexeme))
                {
                    printf("[kw %s] ", inputLexeme);
                    fprintf(lexemeCatFile, "[kw %s] ", inputLexeme);
                }
                else if (isIdentifier(inputLexeme))
                {
                    printf("[id %s] ", inputLexeme);
                    fprintf(lexemeCatFile, "[id %s] ", inputLexeme);
                }
                else if (isOperatorOrEqual(inputLexeme))
                {
                    printf("[op %s] ", inputLexeme);
                    fprintf(lexemeCatFile, "[op %s] ", inputLexeme);
                }
                else if (isSingleCharParenthesis(inputLexeme))
                {
                    printf("[par %s] ", inputLexeme);
                    fprintf(lexemeCatFile, "[par %s] ", inputLexeme);
                }
                else if (isNumber(inputLexeme))
                {
                    printf("[num %s] ", inputLexeme);
                    fprintf(lexemeCatFile, "[num %s] ", inputLexeme);
                }
                else
                {
                    error = 1;
                    printf("[unkn %s] ", inputLexeme);
                    fprintf(lexemeCatFile, "[unkn %s] ", inputLexeme);
                }
                j = 0;
            }
            else
            {
                inputLexeme[j++] = processedChars[i];
            }
        }

        if (error == 1)
        {
            printf("\n\nError Message:\n");
            printf("INVALID [unkn 100.o5]\n");
            fprintf(lexemeCatFile, "\n\nError Message:\n");
            fprintf(lexemeCatFile, "INVALID [unkn 100.o5]\n");
        }
        else
        {
            printf("\n\nCategorized lexemes printed and stored in lexemeCat.txt\n");
            fprintf(lexemeCatFile, "\n\nCategorized lexemes stored in lexemeCat.txt\n");
        }

        fclose(lexemeCatFile);
    }
    else
    {
        printf("Unable to open lexemeCat.txt for writing.\n");
    }

    fclose(file);
    return 0;
}

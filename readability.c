#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

string get_user_input();
float count_letters(string user_input, float letter_count, int input_length);
float count_words(string user_input, float word_count, int input_length);
float count_sentences(string user_input, float sentence_count, int input_length);
int count_input_length(int input_length, string user_input);
float answer_of_liau(float letter_count, float word_count, float sentence_count, float index);
float get_average_letters(float letter_count, float word_count, float average_letter);
float get_average_sentences(float sentence_count, float word_count, float average_words);
float calculate_index(float letter_count, float word_count, float sentence_count, float average_letters, float average_sentences, float index);
int calculate_grade(float index, int grade);
void output_grade(int grade);

int main(void) //all function description comments are at functions code
{
    float letter_count = 0;
    float word_count = 1;
    float sentence_count = 0;
    string user_input;
    float index = 0;
    int input_length = 0;
    float average_letter = 0;
    float average_sentences = 0;
    int grade = 0;

    user_input = get_user_input();
    input_length = count_input_length(input_length, user_input);
    letter_count = count_letters(user_input, letter_count, input_length);
    word_count = count_words(user_input, word_count, input_length);
    sentence_count = count_sentences(user_input, sentence_count, input_length);
    average_letter = get_average_letters(letter_count, word_count, average_letter);
    average_sentences = get_average_sentences(sentence_count, word_count, average_sentences);
    index = calculate_index(letter_count, word_count, sentence_count, average_letter, average_sentences, index);
    grade = calculate_grade(index, grade);
    output_grade(grade);
}

string get_user_input() // gets the text to be graded
{
    string user_input = get_string("Text: ");
    return user_input;
}

int count_input_length (int input_length, string user_input) // how many chars long is the user input text, all characters included no exclusions
{
    input_length = strlen(user_input);
    return input_length;
}

float count_letters (string user_input, float letter_count, int input_length) //upper case 63-90, lower case 67-122 (ascii values)
{
    int asci_value; // ascii value of the char thats pointed to in the string "user_input"

    for (int i = 0; i < input_length; i++)
    {
        asci_value = user_input[i];
        if ((asci_value > 64 && asci_value < 91) || (asci_value > 96 && asci_value < 123))
        {
            letter_count++;
        }
    }

    return letter_count;
}

float count_words (string user_input, float word_count, int input_length) //counts amount of spcaes ascii value 32, spaces starts at 1
{
    int asci_value; // ascii value of the char thats pointed to in the string "user_input"

    for (int i = 0; i < input_length; i++)
    {
        asci_value = user_input[i];
        if (asci_value == 32)    //if a space is detected add 1 to word_count
        {
            word_count++;
        }
    }

    return word_count;
}

float count_sentences (string user_input, float sentence_count, int input_length) //count sentences, if . or ? or ! detecteds, add 1 to sentence count
{
    int asci_value;

    for (int i = 0; i < input_length; i++)
    {
        asci_value = user_input[i];
        if ((asci_value == 46) || (asci_value == 33) || (asci_value == 63))
        {
            sentence_count++;
        }
    }

    return sentence_count;
}

float get_average_letters(float letter_count, float word_count, float average_letter) //average letters per 100 words
{
    //(letters/words)*100
    average_letter = letter_count / word_count * 100;
    return average_letter;
}

float get_average_sentences(float sentence_count, float word_count, float average_sentences) //averege sentences per 100 words
{
    //(sentences/words)*100
    average_sentences = (sentence_count / word_count) * 100;
    return average_sentences;
}

float calculate_index (float letter_count, float word_count, float sentence_count, float average_letters, float average_sentences, float index) //calculates index
{
    // index = 0.0588 * average_letters - 0.296 * average_sentences - 15.8
    index = 0.0588 * average_letters - 0.296 * average_sentences - 15.8;
    return index; //
}

int calculate_grade (float index, int grade) //turns the float index into a rounded int
{
    index = round(index);
    grade = index;
    return grade;
}

void output_grade (int grade)
{
    if ((grade > 0 && grade < 16)) //grade 1 - 15
    {
        printf("Grade %i\n", grade);
    }
    else if (grade > 15) //grade 16 or higher
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Before Grade 1\n"); //grade less than 1
    }
}

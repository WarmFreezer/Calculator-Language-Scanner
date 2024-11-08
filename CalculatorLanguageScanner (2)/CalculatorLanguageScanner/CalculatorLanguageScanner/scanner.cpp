#include <fstream>
#include <iostream> 
using namespace std;

int main() 
{
	ifstream inputFile("input.txt");
	ofstream outputFile("output.txt");

	char current;
	int i = 0;
	string input;
	
	while (inputFile.get(current))
	{
		input += current;
	}

	current = input[i];
	
	while (true)
	{
		
		if (current == ' ' || current == '\n' || current == '\t')	//Clear whitespace, tabs, new lines
		{
			i++; current = input[i];
		}
		
		else if (current == '/')		//Checks for comments and '/'
		{
			i++; current = input[i];
			if (current == '/')			//Clears single line comments
			{
				while (current != '\n')
				{
					i++; current = input[i]; 
				}
				i++; current = input[i];
			}

			else if (current == '*')	//Clears multi-line comments
			{
				i++; current = input[i];
				 do 
				 {		
					if (current == '*') 
					{
						while (current == '*')
						{
							i++; current = input[i]; 
						}

						if (current == '/')
						{
							break;
						}
					}

					i++; current = input[i];
				 } while (current != '*');

				 i++; current = input[i];		
				 i++; current = input[i];
			}
			
			else						//Checks if current is the single character token '/'
			{
				outputFile << "/\n";
			}
		}

		else if (current == '(')		//Checks if current is open parenthesis
		{
			outputFile << current << "\n";
			i++; current = input[i];
		}

		else if (current == ')')		//Checks if current is closing parenthesis
		{
			outputFile << current << "\n";
			i++; current = input[i];

		}

		else if (current == '*')		//Checks if current is an asterisk/multiplication operator
		{
			outputFile << current << "\n";
			i++; current = input[i];
		}

		else if (current == '+' || current == '-')	//Checks if current is an addition operator
		{
			outputFile << current << "\n";
			i++; current = input[i];
		}

		else if (current == ':')		//Checks for assignment operator ':='
		{
			i++; current = input[i];
			if (current == '=')
			{
				outputFile << ":=\n";
			}

			else
			{
				cout << "Lexical Error: Not a token \n" << current;
			}

			i++; current = input[i];
		}

		else if (current == '.')		//Checks for numbers starting with a decimal
		{
			string num = ".";
			i++; current = input[i];
			if (!isdigit(current))
			{
				cout << "Lexical Error: Not a token \n" << current;
				break;
			}

			while (isdigit(current))
			{
				num += current; 
				i++; current = input[i];
			}
			outputFile << num << "\tnumber\n";
		}

		else if (isdigit(current))		//Checks for numbers starting with digits
		{
			string num = "";
			num += current;
			i++; current = input[i];
			while (isdigit(current))
			{
				num += current;
				i++; current = input[i];
			}
			
			if (current == '.')
			{
				i++; current = input[i];
				num += '.';

				while (isdigit(current))
				{
					num += current;
					i++; current = input[i];
				}
				outputFile << num << "\tnumber\n";
			}
			
			else
			{
				outputFile << num << "\tnumber\n";
			}
		}

		else if (isalpha(current) || current == '_')		//Checks for ids or keywords
		{
			string phrase = "";
			phrase += current;
			i++; current = input[i];
			while (isalpha(current) || isdigit(current) || current == '_')
			{
					phrase += current;
					i++; current = input[i];
			} 
			
			if (phrase == "read")		//Checks for keywords
			{
				outputFile << "read\tkeyword\n";
			}
		
			else if (phrase == "write")
			{
				outputFile << "write\tkeyword\n";
			}
			
			else						//Checks for ids
			{
				outputFile << phrase << "\tid\n";
			}
			
		}

		else if (current == '\0')		//Detects end of file
		{
			break;
		}
		
		else							//Returns an error if current is not a valid token
		{
			cout << "Lexical Error: Not a token \n" << current;
			break;
		}
	}
	
	outputFile.close();					//Close output file, save changes
	inputFile.close();					//Close input file

	return 0;
}

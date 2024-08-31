#include <iostream>
#include <fstream>
#include <string>
#include <cstddef>
using namespace std;
void compressFile(const std::string& inputFileName, const std::string& outputFileName)
 {
    ifstream inputFile(inputFileName, ios::binary);
    ofstream outputFile(outputFileName,ios::binary);

    if (!inputFile) 
	{
        cout << "Error: Unable to open input file " << inputFileName << ".\n";
        return;
    }
    if (!outputFile) 
	{
        cout << "Error: Unable to open output file " << outputFileName << ".\n";
        return;
    }

    char currentChar, prevChar;
    int count = 0;

    if (inputFile.get(prevChar)) 
	{
        count = 1;

        while (inputFile.get(currentChar)) 
		{
            if (currentChar == prevChar) 
			{
                ++count;
            } 
			else 
			{
                outputFile.put(prevChar);
                outputFile.write(reinterpret_cast<const char*>(&count), sizeof(count));
                prevChar = currentChar;
                count = 1;
            }
        }

        outputFile.put(prevChar);
        outputFile.write(reinterpret_cast<const char*>(&count), sizeof(count));
    }

    inputFile.close();
    outputFile.close();
}

void decompressFile(const string& inputFileName, const string& outputFileName)
 {
    ifstream inputFile(inputFileName,ios::binary);
    ofstream outputFile(outputFileName,ios::binary);

    if (!inputFile) 
	{
        cout<< "Error: Unable to open input file " << inputFileName << ".\n";
        return;
    }
    if (!outputFile) 
	{
        cout<< "Error: Unable to open output file " << outputFileName << ".\n";
        return;
    }

    char currentChar;
    int count;

    while (inputFile.get(currentChar)) 
	{
        if (inputFile.read(reinterpret_cast<char*>(&count), sizeof(count))) 
		{
            for (int i = 0; i < count; ++i) 
			{
                outputFile.put(currentChar);
            }
        } 
		else
		 {
           cout << "Error: Invalid file format or incomplete data.\n";
            break;
        }
    }

    inputFile.close();
    outputFile.close();
}

int main()
 {
    string fileName = "file.txt";
    string compressedFileName = "compressed.txt";
    string decompressedFileName = "decompressed.txt";

    int choice;
    std::cout << "Choose an option:\n";
    std::cout << "1. Compress file\n";
    std::cout << "2. Decompress file\n";
    std::cout << "Enter your choice (1 or 2): ";
    std::cin >> choice;

    if (choice == 1) 
	{
        compressFile(fileName, compressedFileName);
        cout << "File compressed successfully.\n";
    } 
	else if (choice == 2) 
	{
        decompressFile(compressedFileName, decompressedFileName);
        cout << "File decompressed successfully.\n";
    } 
	else 
	{
       cerr << "Invalid choice.\n";
    }

    return 0;
}

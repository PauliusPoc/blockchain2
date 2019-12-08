#include <iostream>
#include <string.h>
#include <fstream>
#include <bitset>
#include <sstream>
#include <time.h>


#include <random>
#include <algorithm>
#include <cmath>
const int BITSET_LENGTH = 32;

const int HASH_LENGTH = 64;


std::string bitsetToHex(std::bitset<HASH_LENGTH> bs[4]) {
    std::string hashStr = "";
    for(int i = 0; i < 4; i++) {
        std::string str;
        std::stringstream ss;
        ss << std::hex << bs[i].to_ullong();
        ss >> str;
        str = std::string((HASH_LENGTH / 4) - str.length(), '0').append(str);
        hashStr.append(str);
    }
    return hashStr;
}

std::string HexToBin(std::string hexdec)
{
    long int i = 0;
    std::string binStr = "";

    while (hexdec[i]) {
        switch (hexdec[i]) {
            case '0':
                binStr += "0000";
                break;
            case '1':
                binStr += "0001";
                break;
            case '2':
                binStr += "0010";
                break;
            case '3':
                binStr += "0011";
                break;
            case '4':
                binStr += "0100";
                break;
            case '5':
                binStr += "0101";
                break;
            case '6':
                binStr += "0110";
                break;
            case '7':
                binStr += "0111";
                break;
            case '8':
                binStr += "1000";
                break;
            case '9':
                binStr += "1001";
                break;
            case 'a':
                binStr += "1010";
                break;
            case 'b':
                binStr += "1011";
                break;
            case 'c':
                binStr += "1100";
                break;
            case 'd':
                binStr += "1101";
                break;
            case 'e':
                binStr += "1110";
                break;
            case 'f':
                binStr += "1111";
                break;
            default:
                break;
        }
        i++;
    }
    return binStr;
}


long getCharsSum(std::string str) {
	long sum = 0;
	for (int i = 0; i < str.length(); i++) {
		sum += abs(int(str[i])) * (i + 8);
	}
	long val = sum * str.length() / 3;
	val = val / 2 * (val / 3);
	long randm = val % abs((int(str[0])) + abs(int(str[str.length() - 1])) / 2);
	for (int j = 1; j < randm; ++j) {
		val = val + sin(int(str[0])) + sin(j) * cos(int(str[str.length() - 1])) + ((abs(int(str[0])) + abs(int(str[str.length() - 1]))) / 2) - abs(int(str[str.length() % j]));
	}
	return val / 2;
}

std::string hash(std::string input) {
	std::bitset<BITSET_LENGTH> bs[8];
	for (auto & b : bs) {
		b = std::bitset<BITSET_LENGTH>{}.set();
	}

	long test = getCharsSum(input);

	std::stringstream res;
	std::string tmp_str;

	for (int i = 0; i < 8; i++) {
		int sk = 0;
		long val = std::abs(test * (i + 3));

		//std::cout << val << std::endl;
		while (val >= BITSET_LENGTH) {
			int index = val % BITSET_LENGTH;
			val = val / 1.05 - (i * 2) - bs[i].count();
			bs[i].flip(index);
			int test = index - bs[i].count();
			bs[i].flip(abs(test));
			if (index % 2 == 0) {
				bs[i].flip();
			}
		}
	}
	std::string hex_str;

	for (int i = 0; i < 8; i++) {
		std::stringstream res;
		std::string tmp_str;
		res << std::hex << bs[i].to_ullong();
		res >> tmp_str;
		int diff = 8 - tmp_str.length();
		if (diff < 8) {
			for (int j = 0; j < diff; ++j) {
				tmp_str.insert(0, "0");
			}
		}
		hex_str += tmp_str;
	}

	return hex_str;
}


double measureTime(std::string filename) {
    std::ifstream inFile;
    inFile.open(filename);
    std::string input;
    double timeElapsed = 0;

    while (getline(inFile, input)) {
        clock_t tStart = clock();
        hash(input);
        timeElapsed += (double)(clock() - tStart)/CLOCKS_PER_SEC;
    }
    inFile.close();
    return timeElapsed;
}
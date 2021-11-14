#include <algorithm>
#include <iostream>
#include <map>
#include <utility>
#include <string>
#include <fstream>
#include <exception>
#include <sstream>
#include <vector>

size_t fact(size_t a){
    size_t r = 1;
    for(size_t i = 1; i <= a; ++i)
        r *= i;
    return r;
}

std::vector<std::pair<std::string, int>> sortDict(std::map<std::string, int>& dict){
    std::vector<std::pair<std::string, int>> values{
        std::make_move_iterator(begin(dict)), std::make_move_iterator(end(dict))
    };
    sort(values.begin(), values.end(), [](std::pair<std::string, int> l, std::pair<std::string, int> r)
    {
        return l.second > r.second;
    });
    dict.clear();
    return values;
}

std::vector<std::pair<std::string, int>> readDict(char* fileName){
    std::map<std::string, int> dict;
    std::ifstream dict_f;
    try {
        dict_f.open("dictionary.txt");
    }
    catch(std::exception& e){
        std::cerr << "Dictionary is not open" << std::endl;
        std::cerr << e.what() << std::endl; 
    }
    std::string row;
    std::istringstream line;
    int value;
    while (getline(dict_f, row)){
        std::istringstream line(row);
        row.clear();
        line >> row >> value;
        row = row.substr(0, row.size() - 1);
        dict.emplace(std::make_pair(row, value));
    }
    dict_f.close();
    std::vector<std::pair<std::string, int>> sortedDict(sortDict(dict));
    return sortedDict;
}

size_t countWords(const std::string& line) {
    size_t count = 0, pos = 0;
    do{
        ++count;
        pos = line.find(" ", pos + 1);
    } while (pos != std::string::npos);
    return count;
}

void writeStr(std::vector<std::string>& str, size_t b, size_t a = 0){
    size_t i = 1;
    do {
        for(size_t it = 0; it < str.size(); ++it)
            std::cout << str[it] << " ";
        std::cout << std::endl;
        std::next_permutation(str.begin(), str.end());
    } while(i++ != fact(str.size()));
    std::cout << std::endl;
}

void iterat(std::vector<std::vector<std::string>>& words, size_t numbWort, std::vector<std::string>& str){
    for(int i = 0; i < words[numbWort].size(); ++i){
        str.at(numbWort) = words[numbWort][i];
        if (numbWort != str.size() - 1){
            //++numbWort;
            iterat(words, numbWort + 1, str);
        }
        else{
            writeStr(str, str.size() - 1);
        }
    }
}

void writeAnnogram(std::vector<std::pair<std::string, int>>& dict, std::string line) {
    std::vector<std::vector<std::string>> words;
    std::istringstream row(line);
    //считаем количество слов
    size_t count = countWords(line);
    words.resize(count + 1);
    std::string word;
    for (size_t i = 0; i < count; ++i){
        row >> word;
        words.at(count).push_back(word);
    }
    // смотрим совпадения по таблице
    for(size_t i = 0; i < words[count].size(); ++i){
        word = words[count][i];
        for(auto j = dict.begin(); j != dict.end(); ++j){
            if ((std::is_permutation(word.begin(), word.end(), j->first.begin())) && (word.size() == j->first.size())){
                words.at(i).push_back(j->first);
            }
        }
    }
    //нужно пересостыковать слова в предложении
    iterat(words, 0, words[count]);
}

int main(int argc, char* argv[]) {
    //const char* const dictionary = "dictionary.txt";
    //std::ifstream input(dictionary);
    std::ifstream input("input.txt");
    //std::ifstream input(argv[1]);
    try {
        input.is_open();
    }
    catch(std::exception e){
        std::cerr << "Input file is not open" << std::endl;
        std::cerr << e.what() << std::endl; 
    }

    //readDict(argv[2]);
    std::vector<std::pair<std::string, int>> dict = readDict("dictionary.txt");
    std::string line;
    while(getline(input, line)){
        writeAnnogram(dict, line);
    }
    input.close();
   std::cout << "wse" << std::endl;
    return 0;
}
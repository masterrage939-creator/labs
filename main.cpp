#include <iostream>
#include <string>
#include <vector>


int  task1(){
    std::string shortt;
    int n_words;
    std::vector<std::string>words;
    std::cout<<"Enter acronym: ";
    std::cin>>shortt;
    size_t n_shortt = shortt.size();
    std::cout<<"Enter count of words: ";
    std::cin>>n_words;
    if ((size_t)n_words != n_shortt){  std::cout<<"false"; return 0;}
    std::cout<<"Enter words: ";
    for (int i=0;i<n_words; i++){
        std::string word;
        std::cin>>word;
        words.push_back(word);
    }
    for (int i=0; i<n_words;i++){
        if (words[i][0] != shortt[i]) {
            std::cout<<"false"; 
            return 0;
        }
    }
    std::cout<<"true"; return 0;

}

void task2(){
    std::string sentence;
    std::cout<<"Enter sentence: ";
    std::cin.ignore(); 
    std::getline(std::cin, sentence);
    size_t n_sntc = sentence.size();
    std::string reverse;
    int cnt_space = 0;
    for (int i =0 ; i<n_sntc;i++){
        if(sentence[i] != ' '){
            reverse.push_back(sentence[i]);
        }
        else{
            cnt_space++;
        }
    }
    std::string normal (reverse.rbegin(), reverse.rend());
    if (normal == reverse){
        std::cout<<"true";
    }
    else{
        std::cout<<"false";
    }
}

void task3(const std::vector<int>&score){
    int n_words, n_letters;
    std::vector<std::string>words;
    std::vector<char>letters;
    
    std::cout<<"Enter count of words: ";
    std::cin>>n_words;
    std::cout<<"Enter count of letters: ";
    std::cin>>n_letters;
    std::cout<<"Enter words: ";
    for (int i =0; i<n_words;i++){
        std::string word;
        std::cin>>word;
        words.push_back(word);
    }
    std::cout<<"Enter letters: ";
    for (int i =0; i<n_letters;i++){
        char letter;
        std::cin>>letter;
        letters.push_back(letter);
    }
    std::vector<int> available(26, 0);
    for (char ch : letters) {
        available[ch - 'a']++;
    }
    std::vector<std::vector<int>> wordCount(n_words, std::vector<int>(26, 0));
    std::vector<int> wordScore(n_words, 0);
    for (int i = 0; i < n_words; ++i) {
        for (char ch : words[i]) {
            int idx = ch - 'a';
            wordCount[i][idx]++;
            wordScore[i] += score[idx];
        }
    }
        int best = 0;
    int totalMasks = 1 << n_words; 
    for (int mask = 0; mask < totalMasks; ++mask) {
        std::vector<int> used(26, 0);
        int currentScore = 0;
        bool possible = true;

        for (int i = 0; i < n_words; ++i) {
            if (mask & (1 << i)) { 
                for (int j = 0; j < 26; ++j) {
                    used[j] += wordCount[i][j];
                    if (used[j] > available[j]) {
                        possible = false;
                        break;
                    }
                }
                if (!possible) break;
                currentScore += wordScore[i];
            }
        }

        if (possible && currentScore > best) {
            best = currentScore;
        }
    }
    std::cout<<best;
}




int main(){
    int n;
    std::vector<int> score(26);
    std::cout<<"Enter the task number(1-3): ";
    std::cin>>n;
    switch (n)
    {
    case 1:
        task1();
        break;
    case 2:
        task2();
        break;
    case 3:
        
        for (int i = 0; i < 26; ++i) {
        score[i] = i + 1; 
    }
        task3(score);
        break;
    default:
        break;
    }
}
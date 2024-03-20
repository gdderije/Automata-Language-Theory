/*
CMSC 141 - Exercise 1
Gisselle Derije and Leandrei Sagun
April 2, 2021
*/

#include<iostream>
#include<string>
#include<vector>

std::vector<std::string> L(std::vector<std::string> &words){
	bool swapped = true;								//boolean that determines if at least two strings are swapped
	std::vector<std::string> w = words;					
	std::string u, v;
	while(swapped){
		swapped = false;
		for(int i = 0; i < words.size() - 1; i++){
			u = words[i];					//set u as the current string
			v = words[i+1];					//set v as the next string
			if(u.size() > v.size()){		//swaps the consecutive strings if the current string is longer than the next string
				words[i] = v;
				words[i+1] = u;
				swapped = true;
				break;
			}
			else if(u.size() == v.size()){
				for(int j = 0; j < u.size(); j++){	//iterates the characters of both strings
					if(u.at(j) > v.at(j)){			//swaps the consecutive strings if the current string has a larger character at the jth index
						words[i] = v;
						words[i+1] = u;
						swapped = true;
						break;
					}
					else if(u.at(j) < v.at(j)){		//ends the iteration if the current string has a smaller character at the jth index
						break;
					}
				}
			}
		}
	}
	return words;

}
int main(){
	std::vector<std::string> words = {"quick", "brown", "fox", "jumps", "over", "the", "lazy", "dog"};
	
	std::cout << "Original list of strings:" << std::endl;
	for(std::string word : words){
		std::cout << word << std::endl;
	}
	std::cout << std::endl;
	words = L(words);
	std::cout << "List of strings in shortlex order:" << std::endl;
	for(std::string word : words){
		std::cout << word << std::endl;
	}
	std::cout << std::endl;
	
}
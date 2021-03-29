#include <iostream>
#include "enigma_code.h"
#include <vector>

using namespace std;
//string plaintext = "INTELLIGENCEPOINTSTOATTACKONTHEEASTWALLOFTHECASTLEATDAWN";
//string ciphertext = "RZHAOZZUPQAALDBEPVWXBNQNSMBFWDRDLUYLGEVEIESGZEKPIVGWPROD";


void cryptanalysis_function(EnigmaText &text){
	
		//Possible Key or Rotor Combination in Array all
	//display();

	string all[17576];
	int l = 0;
	for(int i=0;i<26;++i){
		for(int j=0;j<26;++j){
			for(int k=0;k<26;++k){
				all[l] += all[l] + alphabet[i] + alphabet[j] + alphabet[k];
				++l;
			}
		}
	}	
	
	string key, ring_setting;
	double counter {min_quadgram_score};
	vector<int> old_text_score_result;

	for(int i=0;i<17576;++i){//Used for Varying Ring Setting
		
		for(int j=0;j<17576;++j){//Used for Varying Rotor Setting
			
			key = all[j];
			ring_setting = all[i];
			text.decrypt(key, ring_setting);
			text.quadgram_score();
			if(text.score>=counter){
				old_text_score_result.push_back(text.score);
				counter = text.score;
				text.print_status();
				
				if((old_text_score_result.size() > 3) 
					&& (old_text_score_result.at(old_text_score_result.size()-1) == old_text_score_result.at(old_text_score_result.size()-2)) 
					&& (old_text_score_result.at(old_text_score_result.size()-1) == old_text_score_result.at(old_text_score_result.size()-3))) 
						return; 
			}	
		}
	}
}

int main(){
	
	clock_t start, end; 
	EnigmaText ciphertext;
	cout << "Ciphertext: ";
	ciphertext.read_encrypted();
	
	start = clock(); 
	cryptanalysis_function(ciphertext);
	
	cout << endl;
	cout << "Rotor Setting: " << ciphertext.rotor_setting() << endl;
	cout << "Ring Setting: " << ciphertext.ring_setting() << endl;
	
	end = clock(); 
	double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
	cout << "Elapsed cryptanalysis time: " << time_taken << " s" << endl;
	
	return 0;
}

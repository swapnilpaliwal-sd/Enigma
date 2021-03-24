#include "enigma_code.h"
#include "qgr.h"
#include<vector>
#include <bits/stdc++.h> 
using namespace std;
//string plaintext = "INTELLIGENCEPOINTSTOATTACKONTHEEASTWALLOFTHECASTLEATDAWN";

double scoreText(string text,int len){
	
	int i;
    char temp[4];
    double score = 0;
    for (i=0;i<len-3;i++){
        temp[0]=text[i]-'A';
        temp[1]=text[i+1]-'A';
        temp[2]=text[i+2]-'A';
        temp[3]=text[i+3]-'A';
        score += qgram[17576*temp[0] + 676*temp[1] + 26*temp[2] + temp[3]];
        
    }
    return score;
    
    /*int i;
    double score = 0;
    for (i=0;i<len;i++){
        if((plaintext[i])==(text[i])){
        	score++;
		}
    }
    return score;*/
}


string cryptanalysis_function(){
	
	string result;
	string key,text,output_text;
	short location_on_initialization_array,plugboard_input_count=0;
	
	//Initializing Rotor1
	struct enigma_rotor rotor_one;
	//Initializing Rotor 2
	struct enigma_rotor rotor_two;
	//Initializing Rotor 3
	struct enigma_rotor rotor_three;
	//Initializing input characters in array
	initialize_input(rotor_one.input_character);
	//Intitializing output characters in array
	rotor_one_output(rotor_one.output_character);

	
	//Repeating the same steps
	initialize_input(rotor_two.input_character);
	rotor_two_output(rotor_two.output_character);
	
	initialize_input(rotor_three.input_character);
	rotor_three_output(rotor_three.output_character);
	
	
	//CRYPTANALYSIS
	
	text = "RZHAOZZUPQAALDBEPVWXBNQNSMBFWDRDLUYLGEVEIESGZEKPIVGWPROD";
	string ring_setting;
	double counter = -1000000000000000000;
	double scoring;
		//Possible Key or Rotor Combination in Array all
	display();
	char list[26] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
	string all[17576];
	int l = 0;
	for(int i=0;i<26;i++){
		for(int j=0;j<26;j++){
			for(int k=0;k<26;k++){
				all[l] = all[l] + list[i] + list[j] + list[k];
				l++;
			}
		}
	}	
	
	
	
	
	vector<int> old_text_score_result;
	int counter_same = 0;
	
	
	
	
		for(int i=0;i<17576;i++){//Used for Varying Ring Setting
		
		for(int j=0;j<17576;j++){//Used for Varying Rotor Setting
			
			key = all[j];
			ring_setting = all[i];
	
	
			//Get the character location on the input character array for rotor1
			location_on_initialization_array=character_location(rotor_one.output_character,ring_setting[0]);	
			rotor_shift(rotor_one.output_character,location_on_initialization_array);
			
			//Initialize with ring setting location 
			location_on_initialization_array = character_location(rotor_one.input_character,key[0]);
			rotor_shift(rotor_one.input_character,location_on_initialization_array);
			
			//Get the character location on the input character array for rotor2
			location_on_initialization_array=character_location(rotor_two.output_character,ring_setting[1]);
			rotor_shift(rotor_two.output_character,location_on_initialization_array);
			
			//Initialize with ring setting location 
			location_on_initialization_array = character_location(rotor_two.input_character,key[1]);
			rotor_shift(rotor_two.input_character,location_on_initialization_array);
			
			//Get the character location on the input character array for rotor3
			location_on_initialization_array=character_location(rotor_three.output_character,ring_setting[2]);
			rotor_shift(rotor_three.output_character,location_on_initialization_array);
			
			//Initialize with ring setting location 
			location_on_initialization_array = character_location(rotor_three.input_character,key[2]);
			rotor_shift(rotor_three.input_character,location_on_initialization_array);
			
			
			//PERMUTATIONS
			//text = plugboard_redirect(text,plugboard_input_count);
			++plugboard_input_count;
			//text = plugboard_redirect(text);
			//ENCRYPTION
			output_text=encryption_decryption(rotor_one,rotor_two,rotor_three,text);
			//output_text = plugboard_redirect(output_text,plugboard_input_count);
			//delay();
			scoring = scoreText(output_text,text.length());
			if(scoring>=counter){
				
				old_text_score_result.push_back(scoring);
				
				counter = scoring;
				cout<<"The Highest Counter: "<<counter<<" Rotor Setting: "<<rotor_one.input_character[0]<<rotor_two.input_character[0]<<rotor_three.input_character[0]<<" Ring Setting: "<<rotor_one.output_character[0]<<rotor_two.output_character[0]<<rotor_three.output_character[0]<<endl;
				cout<<"Potential Plaintext: "<<output_text<<endl;
				
				
				if(old_text_score_result.size() > 3) {
				
					if((old_text_score_result.at(old_text_score_result.size()-1) == old_text_score_result.at(old_text_score_result.size()-2)) && (old_text_score_result.at(old_text_score_result.size()-1) == old_text_score_result.at(old_text_score_result.size()-3))) {
						
						cout<<"The Highest Counter: "<<counter<<" Rotor Setting: "<<rotor_one.input_character[0]<<rotor_two.input_character[0]<<rotor_three.input_character[0]<<" Ring Setting: "<<rotor_one.output_character[0]<<rotor_two.output_character[0]<<rotor_three.output_character[0]<<endl;
						cout<<"Potential Plaintext: "<<output_text<<endl;
						result += rotor_one.input_character[0];
				result += rotor_two.input_character[0];
				result += rotor_three.input_character[0];
				
				result += rotor_one.output_character[0];
				result += rotor_two.output_character[0];
				result += rotor_three.output_character[0];
				
				return result;	
			
						
					}
				
				}
			
			}
			
	
		}
}
}

int main(){
	
	clock_t start, end; 
	
	start = clock(); 
	string final_result = cryptanalysis_function();
	
	
	string rotor_setting, ring_setting;
	
	
	rotor_setting +=  final_result[0];
	rotor_setting +=  final_result[1];
	rotor_setting +=  final_result[2];
	
	ring_setting +=  final_result[3];
	ring_setting +=  final_result[4];
	ring_setting +=  final_result[5];
	cout << endl;
	cout << "Rotor Setting: " << rotor_setting << endl;
	cout << "Ring Setting: " << ring_setting << endl;
	end = clock(); 
	double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
	
	
	cout << "Elapsed cryptanalysis time: " << time_taken << " s" << endl;
	
	
	
	
	
	return 0;
}

//Project:Enigma
//Free for Distribution and use
#include <iostream>
#include "quadgram_analysis.h"
#include <string>
#include <cstring>
#include <algorithm>

using namespace std;

constexpr char alphabet[26] {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
constexpr char rotor_one_cred[26] {'E','K','M','F','L','G','D','Q','V','Z','N','T','O','W','Y','H','X','U','S','P','A','I','B','R','C','J'};
constexpr char rotor_two_cred[26] {'A','J','D','K','S','I','R','U','X','B','L','H','W','T','M','C','Q','G','Z','N','P','Y','F','V','O','E'};
constexpr char rotor_three_cred[26] {'B','D','F','H','J','L','C','P','R','T','X','V','Z','N','Y','E','I','W','G','A','K','M','U','S','Q','O'};
constexpr char reflector[26] {'A','B','C','D','E','F','G','D','I','J','K','G','M','K','M','I','E','B','F','T','C','V','V','J','A','T'};

constexpr double min_quadgram_score {-10000000000};


double scoreText(const string &text, const int len){
	
	int i;
    char temp[4];
    double score = 0;
    for (i=0;i<len-3;++i){
        temp[0]=text[i]-'A';
        temp[1]=text[i+1]-'A';
        temp[2]=text[i+2]-'A';
        temp[3]=text[i+3]-'A';
        score += qgram[17576*temp[0] + 676*temp[1] + 26*temp[2] + temp[3]];       
    }
    return score;
}


class Rotor {
	public:
	//input element on the rotor
	char input_character[26];
	//output element from the rotor
	char output_character[26];
	Rotor(char const r[]): input_character{}, output_character{} {
		strncpy(input_character, alphabet, 26);
		strncpy(output_character, r, 26);
	}
	Rotor(): input_character{}, output_character{} {
		strncpy(input_character, alphabet, 26);
	}
};


short character_location(const char rotor_input[], const char character_input){
	return distance(rotor_input, find(rotor_input, rotor_input+26, character_input));
}

void rotor_shift(char rotor_input[], const int position){
	char character_holder=rotor_input[0];
	for(int i=0;i<position;++i){
		character_holder=rotor_input[0];
		for(int j=0;j<25;++j){
			rotor_input[j]=rotor_input[j+1];
			if(j==24){
				rotor_input[25]=character_holder;
			}
		}
	}
}

void display(){
	
	
	//Banner
	cout<<"#######################################################################################################"<<endl;
	cout<<"#          ######   ######   ######  ######  ######  ######  ######     ######     ######       #     #"<<endl;
	cout<<"#          #    #   #    #   #    #    #     #       #         #        #   $      #    #        #    #"<<endl;
	cout<<"#          #    #   #    #   #    #    #     #       #         #        # $        #    #         #   #"<<endl;
	cout<<"# ######## # ## #   # ## #   #    #    #     ######  #         #        ######     ######  #########  #"<<endl;
	cout<<"#          #        #  #     #    #    #     #       #         #         $   #     #              #   #"<<endl;
	cout<<"#          #        #   #    #    #  # #     #       #         #           $ #     #             #    #"<<endl;
	cout<<"#          #        #    #   ######    #     ######  ######    #        ######     #            #     #"<<endl;
	cout<<"#######################################################################################################"<<endl;
	
	
	
	
}
void delay(){
	display();
	for(int i=0;i<15000;++i){
		//delay
		
		cout<<"\r"<<"[+]Processing the request";
	}
}


class EnigmaText {
public:
	string encrypted, decrypted;
	Rotor rotor_one, rotor_two, rotor_three;
	size_t length;
	double score;
	EnigmaText(string t): encrypted{t}, decrypted{t}, rotor_one {rotor_one_cred}, rotor_two {rotor_two_cred}, rotor_three {rotor_three_cred}, length{t.length()}, score{min_quadgram_score} {}
	EnigmaText(): encrypted{}, decrypted{}, rotor_one {rotor_one_cred}, rotor_two {rotor_two_cred}, rotor_three {rotor_three_cred}, length{0}, score{min_quadgram_score} {}
	void read_decrypted() {cin >> decrypted; encrypted=decrypted; length=decrypted.length();}
	void read_encrypted() {cin >> encrypted; decrypted=encrypted; length=encrypted.length();}
	short rotor_direction_output(const short input_output_char_loc);
	string encryption_decryption(string key, string ring_setting, bool decryption);
	void encrypt(string key, string ring_setting) {encrypted = encryption_decryption(key, ring_setting, false);}
	void decrypt(string key, string ring_setting) {decrypted = encryption_decryption(key, ring_setting, true);}
	void quadgram_score(size_t l) {score = scoreText(decrypted,l);}
	void quadgram_score() {score = scoreText(decrypted,length);}
	string rotor_setting() {string s {rotor_one.input_character[0],rotor_two.input_character[0],rotor_three.input_character[0]}; return s;}
	string ring_setting() {string s {rotor_one.output_character[0],rotor_two.output_character[0],rotor_three.output_character[0]}; return s;}
	void print_status() {
		cout<<"Score: "<<score<<" Rotor Setting: "<<rotor_setting()<<" Ring Setting: "<<ring_setting()<<'\n';
		cout<<"Potential Plaintext: "<<decrypted<<'\n';
	}
};

short EnigmaText::rotor_direction_output(const short input_output_char_loc){
		
		short characher_location_holder {input_output_char_loc};
		short characher_location_holder_two;
		
		//Getting character on rotor3 input tray
		characher_location_holder=character_location(rotor_three.input_character,rotor_three.output_character[characher_location_holder]);
		//Getting character on rotor2 input tray
		characher_location_holder=character_location(rotor_two.input_character,rotor_two.output_character[characher_location_holder]);
		//Getting character on rotor1 input tray
		characher_location_holder=character_location(rotor_one.input_character,rotor_one.output_character[characher_location_holder]);
		//Getting the reflected elment and the other reflected value
	
		for(int i=0;i<26;++i){
			if(characher_location_holder!=i && reflector[characher_location_holder]==reflector[i]){
				characher_location_holder_two=i;
			}
		}
		
		//Getting character on rotor1 output tray
		characher_location_holder=character_location(rotor_one.output_character,rotor_one.input_character[characher_location_holder_two]);
		//Getting character on rotor2 output tray
		characher_location_holder=character_location(rotor_two.output_character,rotor_two.input_character[characher_location_holder]);
		//Getting character on rotor3 output tray
		characher_location_holder=character_location(rotor_three.output_character,rotor_three.input_character[characher_location_holder]);
		//Cipher Character
		return characher_location_holder;
		
}

string EnigmaText::encryption_decryption(string key, string ring_setting, bool decryption) {
	
	short location_on_initialization_array;
	
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
	
	//Creating Input/Output Array
	string output_text;
	short char_loc_holder;
	int count_rotor_one {0}, count_rotor_two {0}, count_rotor_three {0};
	
	for(int i=0;i<length;++i){
		
		//Finding the location of the character on the input output tray
		if(decryption) {char_loc_holder=character_location(alphabet,encrypted[i]);}
		else {char_loc_holder=character_location(alphabet,decrypted[i]);}
		//Step1
		//shifting the rotor3 by one place
		rotor_shift(rotor_three.input_character,1);
		rotor_shift(rotor_three.output_character,1);
		++count_rotor_three;
		//if we complete a complete rotation move second rotor
		if((count_rotor_three>0)&&(count_rotor_three%26==0)){
			rotor_shift(rotor_two.input_character,1);
			rotor_shift(rotor_two.output_character,1);
			++count_rotor_two;
			//if we complete a complete rotation move first rotor
			if((count_rotor_two>0)&&(count_rotor_two%26==0)){
				rotor_shift(rotor_one.input_character,1);
				rotor_shift(rotor_one.output_character,1);
				++count_rotor_one;
			}
		}
		char_loc_holder=rotor_direction_output(char_loc_holder);
		output_text += alphabet[char_loc_holder];
	}
	return output_text;
}

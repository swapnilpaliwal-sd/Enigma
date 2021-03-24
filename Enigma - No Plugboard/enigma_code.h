//Project:Enigma
//Free for Distribution and use
#include<iostream>
#include<conio.h>
#include<string>
using namespace std;
struct enigma_rotor{
	//input element on the rotor
	char input_character[26];
	//output element from the rotor
	char output_character[26];
};
void initialize_input(char rotor_input_initialization[]){
	char alphabet[26]={'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
	for(int i=0;i<26;i++){
		rotor_input_initialization[i]=alphabet[i];
	}
	
}
void rotor_one_output(char rotor_one_input[]){
	char rotor_one_cred[26]={'E','K','M','F','L','G','D','Q','V','Z','N','T','O','W','Y','H','X','U','S','P','A','I','B','R','C','J'};
	for(int i=0;i<26;i++){
		rotor_one_input[i]=rotor_one_cred[i];
	}
	
}
void rotor_two_output(char rotor_two_input[]){
	char rotor_one_cred[26]={'A','J','D','K','S','I','R','U','X','B','L','H','W','T','M','C','Q','G','Z','N','P','Y','F','V','O','E'};
	for(int i=0;i<26;i++){
		rotor_two_input[i]=rotor_one_cred[i];
	}
	
}
void rotor_three_output(char rotor_three_input[]){
	char rotor_one_cred[26]={'B','D','F','H','J','L','C','P','R','T','X','V','Z','N','Y','E','I','W','G','A','K','M','U','S','Q','O'};
	for(int i=0;i<26;i++){
		rotor_three_input[i]=rotor_one_cred[i];
	}
	
}
short character_location(char rotor_input[],char character_input){
	short location;
	for(int i=0;i<26;i++){
		if(rotor_input[i]==character_input){
			location=i;
		}
	}
	return location;
}
void rotor_shift(char rotor_input[],int position){
	char character_holder=rotor_input[0];
	for(int i=0;i<position;i++){
		character_holder=rotor_input[0];
		for(int j=0;j<25;j++){
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
	for(int i=0;i<15000;i++){
		//delay
		
		cout<<"\r"<<"[+]Processingtherequest";
	}
}
short rotor_direction_output(int input_output_char_loc,struct enigma_rotor rotor_one_input,struct enigma_rotor rotor_two_input,struct enigma_rotor rotor_three_input){
		
		short characher_location_holder=input_output_char_loc;
		short characher_location_holder_two;
		char reflector[26]={'A','B','C','D','E','F','G','D','I','J','K','G','M','K','M','I','E','B','F','T','C','V','V','J','A','T'};
		
		//Getting character on rotor3 input tray
		characher_location_holder=character_location(rotor_three_input.input_character,rotor_three_input.output_character[characher_location_holder]);
		//Getting character on rotor2 input tray
		characher_location_holder=character_location(rotor_two_input.input_character,rotor_two_input.output_character[characher_location_holder]);
		//Getting character on rotor1 input tray
		characher_location_holder=character_location(rotor_one_input.input_character,rotor_one_input.output_character[characher_location_holder]);
		//Getting the reflected elment and the other reflected value
	
		for(int i=0;i<26;i++){
			if(characher_location_holder==i){
				
			}
			else{
				if(reflector[characher_location_holder]==reflector[i]){
					characher_location_holder_two=i;
				}
			}
		}
		//Getting character on rotor1 output tray
		characher_location_holder=character_location(rotor_one_input.output_character,rotor_one_input.input_character[characher_location_holder_two]);
		//Getting character on rotor2 output tray
		characher_location_holder=character_location(rotor_two_input.output_character,rotor_two_input.input_character[characher_location_holder]);
		//Getting character on rotor3 output tray
		characher_location_holder=character_location(rotor_three_input.output_character,rotor_three_input.input_character[characher_location_holder]);
		//Cipher Character
		return characher_location_holder;
		
		
}
string encryption_decryption(struct enigma_rotor rotor_one_input,struct enigma_rotor rotor_two_input,struct enigma_rotor rotor_three_input,string text){
	
	//Creating Input/Output Array
	string output_text;
	short char_loc_holder;
	char input_output_char[26];
	int count_rotor_one=0,count_rotor_two=0,count_rotor_three=0,text_len;
	text_len=text.length();
	initialize_input(input_output_char);

	
	for(int i=0;i<text_len;i++){
		
		//Finding the location of the character on the input output tray
		char_loc_holder=character_location(input_output_char,text[i]);
		//Step1
		//shifting the rotor3 by one place
		rotor_shift(rotor_three_input.input_character,1);
		rotor_shift(rotor_three_input.output_character,1);
		count_rotor_three++;
		//if we complete a complete rotation move second rotor
		if((count_rotor_three>0)&&(count_rotor_three%26==0)){
			rotor_shift(rotor_two_input.input_character,1);
			rotor_shift(rotor_two_input.output_character,1);
			count_rotor_two++;
			//if we complete a complete rotation move first rotor
			if((count_rotor_two>0)&&(count_rotor_two%26==0)){
				rotor_shift(rotor_one_input.input_character,1);
				rotor_shift(rotor_one_input.output_character,1);
				count_rotor_one++;
			}
		}
		char_loc_holder=rotor_direction_output(char_loc_holder,rotor_one_input,rotor_two_input,rotor_three_input);
		output_text=output_text+input_output_char[char_loc_holder];
	}
	
	return output_text;
	
}

//Project:Enigma
//Free for Distribution and use
//READ THE "README.md" FILE 
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

	cout<<endl;
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

string plugboard_redirect(string text,short count_for_input){
	//substitute a character with different character
	char list_of_char [26] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
	static char sub_list_char [26] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
		
	short temp_sub_val_holder [2];
	short loc_holder[2];
	short loc_holding_for_text,counter=0;
	
	
	//provide machine setting credentials
	while((counter!=10)&&(count_for_input==0)){
		//taking input of two credentials
		cout<<"First plug at: ";
		cin>>temp_sub_val_holder[0];
		cout<<"First plug end at: ";
		cin>>temp_sub_val_holder[1];
		loc_holder[0] = character_location(list_of_char,list_of_char[temp_sub_val_holder[0]]);
		loc_holder[1] = character_location(list_of_char,list_of_char[temp_sub_val_holder[1]]);
		sub_list_char[(loc_holder[0])] = list_of_char[(loc_holder[1])];
		sub_list_char[(loc_holder[1])] = list_of_char[(loc_holder[0])];
		++counter;
		
	}
	
	for(int i=0;i<text.length();i++){
		loc_holding_for_text = character_location(list_of_char,text[i]);
		text[i] = sub_list_char[loc_holding_for_text];
	}
	system("cls");	
	return text;
	
	
	
}
int main(){
	
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
	//Initialization complete
	
	//Input the Key
	display();
	cout<<"Enter the key (INCAPS) to establish a rotor sequence: ";
	cin>>key;
	string ring_setting;
	cout<<"Enter potential ring settings (INCAPS): ";
	cin>>ring_setting;
	//Get the character location on the input character array for rotor1
	location_on_initialization_array=character_location(rotor_one.input_character,key[0]);
	
	
	rotor_shift(rotor_one.input_character,location_on_initialization_array);
	
	location_on_initialization_array=character_location(rotor_one.output_character,ring_setting[0]);
	rotor_shift(rotor_one.output_character,location_on_initialization_array);
	
	//Get the character location on the input character array for rotor2
	location_on_initialization_array=character_location(rotor_two.input_character,key[1]);
	
	rotor_shift(rotor_two.input_character,location_on_initialization_array);
	
	location_on_initialization_array=character_location(rotor_two.output_character,ring_setting[1]);
	rotor_shift(rotor_two.output_character,location_on_initialization_array);
	
	//Get the character location on the input character array for rotor3
	location_on_initialization_array=character_location(rotor_three.input_character,key[2]);
	rotor_shift(rotor_three.input_character,location_on_initialization_array);
	
	location_on_initialization_array=character_location(rotor_three.output_character,ring_setting[2]);
	rotor_shift(rotor_three.output_character,location_on_initialization_array);
	
	
	cout<<"Enter the text: ";
	cin>>text;
	cout<<endl<<endl<<"------------------------------PLUGBOARD SETTING------------------------------"<<endl;
			
				
	//PERMUTATIONS
//	cout<<"Plaintext before: "<<text<<endl;
	text = plugboard_redirect(text,plugboard_input_count);
//	cout<<"Plaintext after: "<<text<<endl;
	++plugboard_input_count;
	//text = plugboard_redirect(text);
	//ENCRYPTION
	output_text=encryption_decryption(rotor_one,rotor_two,rotor_three,text);
//	cout<<endl<<"Output text: "<<output_text<<endl;
	output_text = plugboard_redirect(output_text,plugboard_input_count);
	
	delay();
	cout<<endl<<"Key Setting: "<<key<<endl;
	cout<<"Ring Setting: "<<ring_setting<<endl;
	cout<<endl;
	cout<<endl<<"Output text: "<<output_text<<endl;
	
	
}

/*
CMSC 141 - Exercise 1
Gisselle Derije and Leandrei Sagun
April 2, 2021
*/
#include <iostream>
#include <string>
#include <set>

// state and symbol type
using string_t = std::string;
// set of states and final states type
using set_string_t = std::set<string_t>;
// transition type
using transition_t = string_t(const string_t &, const string_t &);

// DFA (Deterministic Finite Automaton) struct
struct DFA{
	set_string_t	Q;		//states
	set_string_t	Sigma;	//alphabet
	transition_t*	delta;	//transition
	string_t 		q0;		//initial state
	set_string_t	F;		//final states
	DFA(set_string_t Q, set_string_t Sigma, transition_t* delta, string_t q0, set_string_t F){
		this->Q = Q;
		this->Sigma = Sigma;
		this->delta = delta;
		this->q0 = q0;
		this->F = F;
	}
	bool accepts(const string_t &input) const{
		string_t current_state = this->q0;									//initializes the current state to the initial state
		string_t next_state;
		//traverses the input string determines the states at each symbol
		for(int i = 0; i < input.length(); i++){
			next_state = this->delta(current_state, input.substr(i, 1));	//determines next state using the function delta with current state and the next symbol as input
			current_state = next_state;										//sets the next state as the current state for the next iteration
		}
		//checks if the last state is in the final states
		for(string_t final_state : this->F){
			if(current_state == final_state){
				return true;
			}
		}
		return false;
	}
	DFA complement() const{
		set_string_t F_bar = this->Q;			//initializes the final state of the complement equal to the entire set of states
		for(string_t state : this->F){			
			F_bar.erase(F_bar.find(state));		//removes the elements present in F from the set of states
		}
		return DFA(this->Q, this->Sigma, this->delta, this->q0, F_bar);
	}
};

//definition of delta
string_t delta(const string_t &state, const string_t &symbol){
	string_t next_state;
	if(state == "o"){
		if(symbol == "0"){
			next_state = "y";
		}
		if(symbol == "1"){
			next_state = "o";
		}
	}
	if(state == "s"){
		if(symbol == "0"){
			next_state = "z";
		}
		if(symbol == "1"){
			next_state = "o";
		}
	}
	if(state == "x"){
		if(symbol == "0"){
			next_state = "z";
		}
		if(symbol == "1"){
			next_state = "x";
		}
	}
	if(state == "y"){
		if(symbol == "0"){
			next_state = "y";
		}
		if(symbol == "1"){
			next_state = "o";
		}
	}
	if(state == "z"){
		if(symbol == "0"){
			next_state = "z";
		}
		if(symbol == "1"){
			next_state = "x";
		}
	}
	return next_state;
}

std::ostream& operator<<(std::ostream &output, const DFA &automaton){
	std::cout << "States: {";
	for(string_t state : automaton.Q){
		output << state + ", ";
	}
	output << "\b\b  \b\b}" << std::endl;
	output << "Symbols: {";
	for(string_t symbol : automaton.Sigma){
		output << symbol + ", ";
	}
	output << "\b\b  \b\b}" << std::endl;
	output << "Transition:" << std::endl;
	output << "delta\t";
	for(string_t symbol : automaton.Sigma){
		output << symbol + "\t";
	}
	output << std::endl;
	for(string_t state : automaton.Q){
		output << state + "\t";
		for(string_t symbol : automaton.Sigma){
			output << automaton.delta(state, symbol) + "\t";
		}
		output << std::endl;
	}
	output << "Start State: " + automaton.q0 << std::endl;
	output << "Final State: {";
	for(string_t final_state : automaton.F){
		output << final_state + ", ";
	}
	output << "\b\b  \b\b}";
	return output;
}


int main(){
	string_t inputs[] = {"100", "010", "1101", "001001", ""};
	DFA dfa({"o", "s", "x", "y", "z"}, {"0", "1"}, delta, "s", {"o", "z"});

	std::cout << dfa << std::endl << std::endl;
	for(string_t input : inputs){
		std::cout << "DFA accepts " + input + "? ";
		if(dfa.accepts(input)){
			std::cout << "true" << std::endl;
		}
		else{
			std::cout << "false" << std::endl;
		}
	}
	DFA comp_dfa = dfa.complement();
	std::cout << "\n\nComplemented DFA\n" << std::endl;
	std::cout << comp_dfa << std::endl << std::endl;
	for(string_t input : inputs){
		std::cout << "DFA accepts " + input + "? ";
		if(comp_dfa.accepts(input)){
			std::cout << "true" << std::endl;
		}
		else{
			std::cout << "false" << std::endl;
		}
	}
	return 0;
}
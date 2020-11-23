#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include "gui.h"

int add_new_card(int container_id, int step);
char * get_prompt();
void new_game();
void card_shuffle();
void end_game();
void higher_lower(int is_higher);
void on_click_higher();
void on_click_lower();
void on_click_pass(); // Extension part
//void on_click_hint();

static int status[3]; // step, North's score, South's score
static int card_deck[52];
const int rounds = 19;
char prompt[100];

// container_id = 0 for North, 1 for South
int add_new_card(int container_id, int step){
    int card = card_deck[step];
    add_image(container_id, card);
    return card;
}

char * get_prompt(){
    char north[] = "North";
    char south[] = "South";
    sprintf(prompt, "%s's turn\nNorth's score : %d\n South's score: %d", (status[0] % 2 == 0? north : south), status[1], status[2]);
    return prompt;
}

void new_game(){
    /************CODE HERE**************/
    // starts a new game,
    // all initialization useful for resetting should be done here
    // Start from scratch or
	// finished one game and start another one.
	
	int i;
	for (i = 0; i < 3; i ++)
	{
		status[i] = 0; // reset status to zero
	}
    clear_container(0); // reset North
    clear_container(1); // reset South
    
	char * new_prompt = get_prompt();
    set_prompt(new_prompt); // clear existing and set a blank new prompt

    card_shuffle(); // shuffle the card deck
    
	// 2. initialize two cards to be pre-shown at the start of the game
    add_new_card(0, 0); // Add card to North player
    add_new_card(1, 1); // Add card to South player
	status[0] = 2; // After two initial cards given, increment initial steps by two

    show_ingame_buttons(); // show higher, lower, pass, etc. buttons
    /************CODE END***************/
}

void card_shuffle() {
    // this method prepares all cards in card_deck
    // this is the ONLY function that should apply RANDOMNESS
    int i,irandom,temp;
    for (i = 0; i < 52; i++) {
        card_deck[i] = i;
    }
    for (i = 0; i < 51; i++) {
        irandom = i +  rand() % (52 - i);
        temp = card_deck[i];
        card_deck[i] = card_deck[irandom];
        card_deck[irandom] = temp;
    }
}


void end_game(){
    /************CODE HERE**************/
    // 1. Hide the higher and lower button
    hide_ingame_buttons();

    // 2. show match results in buffer_prompt. If North wins, Please show "North wins.\nNorth's score : %d, South's score: %d"
	char *results = malloc(60); // allocate memory to store winner message
	int score = status[1] - status[2]; // positive if North has higher score or tie with South

	if (score == 0)
	{
		sprintf(results, "Draw.\nNorth's score : %d, South's score: %d", status[1], status[2]);
	}
	else if (score > 0)
	{
		sprintf(results, "North wins.\nNorth's score : %d, South's score: %d", status[1], status[2]);
	}
	else
	{
		sprintf(results, "South wins.\nNorth's score : %d, South's score: %d", status[1], status[2]);
	}

    set_prompt(results); // update prompt with message in `results`
    /************CODE END***************/
}



void higher_lower(int is_higher){
    int step = status[0];
    int current_container = step % 2;
    int card = add_new_card(current_container, step);

    /************CODE HERE**************/
    // If current player predict correct card, he get 10 points. Otherwise, he loss 5 points.
    int last_card = card_deck[step -1];
	int card_diff = card - last_card; // negative only if current card is lower than last card
	int player = step % 2; // 0 for North, 1 for South

	switch (is_higher)
	{
		case 0: // when player press "Lower" button
			if (card_diff < 0) status[player +1] += 10;
			else status[player +1] -= 5;
			break;
		case 1: // when player press "Higher" button
			if (card_diff > 0) status[player +1] += 10;
			else status[player +1] -= 5;
			break;
		// anything besides 0 or 1, e.g. "Pass" button will have no effect on scoreboard
	}
    /************CODE END***************/

    if (status[0] == rounds){
        end_game();
        return;
    }else{
        status[0]++;
        char * prompt = get_prompt();
        set_prompt(prompt);
    }   
}

void on_click_higher(){
    higher_lower(1);
}

void on_click_lower(){
    higher_lower(0);
}

void on_click_pass(){
    higher_lower(-1);
}

//void on_click_hint(){
//    
//}
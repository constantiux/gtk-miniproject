#include <time.h>
#include <stdlib.h>
int add_new_card(int container_id, int step);
char * get_prompt();
void new_game();
void card_shuffle();
void end_game();
void higher_lower(int is_higher);
void on_click_higher();
void on_click_lower();
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
    // Hint: 
    // 1. please don't forget the situation when we finish a game and start a new one.
    // 2. We should have two cards already shown at the start of the game.
    
	status[0]=2; //Initialize steps 
    status[1]=0; //Initialize scores
    status[2]=0;
    clear_container(0); //Clear North Container
    clear_container(1); //Clear South Container
    char * init_prompt = get_prompt();
    set_prompt(init_prompt);
    card_shuffle();
    // 2. We should have two cards already shown at the start of the game.
    add_new_card(0,0); //Add card to North Container
    add_new_card(1,1); //Add card to South Container
    show_ingame_buttons();
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
    char *match_results=malloc(100);
    if (status[1]>status[2]){ // If North's score is higher than South
      sprintf(match_results, "North wins.\nNorth's score : %d, South's score: %d", status[1], status[2]);
    }
    else if (status[2]>status[1]){ // If South's score is higher than North
      sprintf(match_results, "South wins.\nNorth's score : %d, South's score: %d", status[1], status[2]);
    }
    else{ // If North's score is equal with South
      sprintf(match_results, "Draw.\nNorth's score : %d, South's score: %d", status[1], status[2]);
    }
    set_prompt(match_results); //Print match results
    /************CODE END***************/
}



void higher_lower(int is_higher){
    int step = status[0];
    int current_container = step % 2;
    int card = add_new_card(current_container, step);

    /************CODE HERE**************/
    // If current player predict correct card, he get 10 points. Otherwise, he loss 5 points.
    int prev_card = card_deck[step-1];
    if (is_higher==1){ //If player chooses higher
      if (step%2 == 0){ //If it is North's turn
        if (card > prev_card){ //If guess correctly
          status[1]=status[1]+10; //Add 10 points
        }
        else{
          status[1]=status[1]-5; //Lose 5 points
        }
      }
      else if (step%2 !=0){ //ELse if South's Turn
        if (card > prev_card){ //If guess correctly
          status[2]=status[2]+10; //Add 10 points
        }
        else{
          status[2]=status[2]-5; //Lose 5 points
        }
      }
    }
    else if (is_higher==0){ //If player chooses lower
      if (step%2 == 0){ //If it is North's turn
        if (card < prev_card){ //If guess correctly
          status[1]=status[1]+10; //Add 10 points
        }
        else{ //Else guess wrongly
          status[1]=status[1]-5; //Lose 5 points
        }
      }
      else if (step%2 !=0){ //ELse if South's Turn
        if (card < prev_card){ //If guess correctly
          status[2]=status[2]+10; //Add 10 points
        }
        else{ //Else guess wrongly
          status[2]=status[2]-5; //Lose 5 points
        }
      }
    }
    //Else if player choose to pass, no score updates
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

//della
void on_click_pass(){
    higher_lower(2);
}

//void on_click_hint(){
//    
//}
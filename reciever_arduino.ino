#include <RGBmatrixPanel.h>
#include <Vector.h>
#include <stdlib.h>

int hard_hand_decision_matrix[22][13] = {
	{-1,-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{-1,-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{-1,-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{-1,-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{-1,-1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1},
	{-1,-1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1},
	{-1,-1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1},
	{-1,-1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1},
	{-1,-1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1},
	{-1,-1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1},
	{-1,-1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1},
	{-1,-1, 1, 1, 2, 2, 2, 2, 1, 1, 1, 1, 1},
	{-1,-1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{-1,-1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{-1,-1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{-1,-1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{-1,-1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{-1,-1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{-1,-1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{-1,-1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{-1,-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{-1,-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}
};

int soft_hand_decision_matrix[22][13] = {
	{-1,-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{-1,-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{-1,-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{-1,-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{-1,-1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1},
	{-1,-1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1},
	{-1,-1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1},
	{-1,-1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1},
	{-1,-1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1},
	{-1,-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{-1,-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{-1,-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{-1,-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{-1,-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{-1,-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{-1,-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{-1,-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{-1,-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{-1,-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{-1,-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{-1,-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
	{-1,-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}
};

const byte numChars = 32;
char receivedChars[numChars];

int player_cards_array[5];
int dealer_cards_array[2];

Vector<int> player_cards(player_cards_array);
Vector<int> dealer_cards(dealer_cards_array);
int player_score = 0;


bool player_ace = false;
int dealer_score = 0;
bool dealer_ace = false;

boolean newData = false;
#define CLK  8
#define OE   9
#define LAT 10
#define A   A0
#define B   A1
#define C   A2
#define D   A3

RGBmatrixPanel matrix(A, B, C, D, CLK, LAT, OE, false);

void setup() {
    Serial1.begin(9600);
    Serial1.println("<Arduino is ready>");
    matrix.begin();
    matrix.setCursor(1, 0);   // start at top left, with one pixel of spacing
    matrix.setTextSize(1);    // size 1 == 8 pixels high
    matrix.setTextColor(matrix.Color333(4,0,7));
}

void loop() {
    matrix.print("Deal a player card:");
    recv_card();
    matrix.fillScreen(matrix.Color333(0, 0, 0));
    pushPlayerCard();
    
    matrix.setCursor(1, 0);
    matrix.print("Deal a dealer card:");
    recv_card();
    matrix.fillScreen(matrix.Color333(0, 0, 0));
    pushDealerCard();

    matrix.setCursor(1, 0);
    matrix.print("Deal a second player card:");
    recv_card();
    matrix.fillScreen(matrix.Color333(0, 0, 0));
    pushPlayerCard();

    matrix.setCursor(1, 0);
    matrix.print("Deal a second dealer card:");
    recv_card();
    matrix.fillScreen(matrix.Color333(0, 0, 0));
    pushDealerCard();

    dealer_score = dealer_cards[0];

    game_loop();

    dealer_score = dealer_cards[0] + dealer_cards[1];
    
    if(dealer_score > 21 && dealer_ace) {
        dealer_score -= 10;
    }


    if (player_score  > 21 && dealer_score > 21){
        //both bust
        matrix.setCursor(1, 0);
        matrix.print("both bust");
    }
    else if (player_score < 21 && dealer_score < player_score) {
        //player wins
        matrix.setCursor(1, 0);
        matrix.print("You win!");
    }
    else if (player_score > 21 && dealer_score < 21) {
        //player busts
        matrix.setCursor(1, 0);
        matrix.print("You lose!");
    }
    else if (player_score > 21 && dealer_score > player_score) {
        //dealer wins
        matrix.setCursor(1, 0);
        matrix.print("You lose!");
    }
    else if (dealer_score > 21 && player_score < 21) {
        //dealer busts, player wins
        matrix.setCursor(1, 0);
        matrix.print("both bust!");
    }
    
}

void recv_card() {
    static boolean recvInProgress = false;
    static byte ndx = 0;
    char startMarker = '<';
    char endMarker = '>';
    char rc;
    newData = false;
    while(true) {
      while (Serial1.available() > 0 && newData == false) {
          rc = Serial1.read();

          if (recvInProgress == true) {
              if (rc != endMarker) {
                  receivedChars[ndx] = rc;
                  ndx++;
                  if (ndx >= numChars) {
                      ndx = numChars - 1;
                  }
              }
              else {
                  receivedChars[ndx] = '\0'; // terminate the string
                  recvInProgress = false;
                  ndx = 0;
                  newData = true;
                  return;
              }
          }

          else if (rc == startMarker) {
              recvInProgress = true;
          }
      }
    }
}

void showNewData() {
    if (newData == true) {
        Serial1.println(receivedChars);
        matrix.print(receivedChars);
        newData = false;
    }
}

void pushPlayerCard() {
    if(atoi(receivedChars) <= 10) {
        player_cards.push_back(atoi(receivedChars));
        player_score += atoi(receivedChars);
    }
    else if (atoi(receivedChars) == 11) { //ace case
        if(player_score + 11 > 21) {
            player_cards.push_back(1);
            player_score += 1;
            player_ace = true;
        }
        player_cards.push_back(11);
        player_score += 11;
        player_ace = true;
    }
    else {
        player_cards.push_back(10);
    }
}

void pushDealerCard() {
    if(atoi(receivedChars) <= 10) {
        dealer_cards.push_back(atoi(receivedChars));
    }
    else if (atoi(receivedChars) == 11) { //ace case
        dealer_cards.push_back(11);
        dealer_ace = true;
    }
    else {
        dealer_cards.push_back(10);
    }  
}

void game_loop() {

    if(!player_ace) {
        switch(hard_hand_decision_matrix[player_score][dealer_score]) {
            case 0:
                matrix.setCursor(1, 0);
                matrix.print("You should stand.");
                delay(5000);
                matrix.fillScreen(matrix.Color333(0, 0, 0));
                break;
            default:
                matrix.setCursor(1, 0);
                matrix.print("You should hit.");
                delay(5000);
                matrix.fillScreen(matrix.Color333(0, 0, 0));
                recv_card();
                pushPlayerCard();
                if(player_score > 21 && !player_ace) {
                    break;
                }
                else if(player_score > 21 && player_ace) {
                    player_score -= 10;
                }
                game_loop();

        }
    }
    else {
        switch(soft_hand_decision_matrix[player_score][dealer_score]) {
            case 0:
                matrix.setCursor(1, 0);
                matrix.print("You should stand.");
                delay(5000);
                matrix.fillScreen(matrix.Color333(0, 0, 0));
                break;
            default:
                matrix.setCursor(1, 0);
                matrix.print("You should hit.");
                delay(5000);
                matrix.fillScreen(matrix.Color333(0, 0, 0));
                recv_card();
                pushPlayerCard();
                if(player_score > 21 && !player_ace) {
                    break;
                }
                else if(player_score > 21 && player_ace) {
                    player_score -= 10;
                }
                game_loop();
        }
    }
}

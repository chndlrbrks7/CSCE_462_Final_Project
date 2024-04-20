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

int player_cards_array[20];
int dealer_cards_array[20];

Vector<int> player_cards(player_cards_array);
Vector<int> dealer_cards(dealer_cards_array);

int player_cards_w[52];
int dealer_cards_w[52];
int desk_cards[52];

Vector<int> player_cards_war(player_cards_w);
Vector<int> dealer_cards_war(dealer_cards_w);
Vector<int> deskCards(desk_cards);

int player_score = 0;
int num_player_cards = 26;


bool player_ace = false;
int dealer_score = 0;
bool dealer_ace = false;
bool blackjack = true;
bool war = false;

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
    recv_card();
    blackjack_or_war();
    
    if (blackjack)
        start_blackjack();
    else {
      start_war();
    }
    
}

void start_blackjack() {
    matrix.print("Your\nturn");
    recv_card();
    matrix.fillScreen(matrix.Color333(0, 0, 0));
    pushPlayerCard();
    
    matrix.setCursor(1, 0);
    matrix.print("Dealer\nturn");
    recv_card();
    matrix.fillScreen(matrix.Color333(0, 0, 0));
    pushDealerCard();

    matrix.setCursor(1, 0);
    matrix.print("Your\nturn" + player_score);

    recv_card();
    matrix.fillScreen(matrix.Color333(0, 0, 0));
    pushPlayerCard();

    matrix.setCursor(1, 0);
    matrix.print("Dealer\nturn");
    recv_card();
    matrix.fillScreen(matrix.Color333(0, 0, 0));
    pushDealerCard();

    dealer_score = dealer_cards[0];

    game_loop();
    

    dealer_score = dealer_cards[0] + dealer_cards[1];

    while(dealer_score < 17) {
      matrix.setCursor(1, 0);
      matrix.print("Dealer\nturn");
      recv_card();
      pushDealerCard();
      matrix.fillScreen(matrix.Color333(0, 0, 0));
      delay(3000);
    }

    if(dealer_score > 21 && dealer_ace) {
        dealer_score -= 10;
    }


    if (player_score  > 21 && dealer_score > 21){
        //both bust
        matrix.setCursor(1, 0);
        matrix.print("You\nlose!");
    }
    else if (player_score < 21 && dealer_score < player_score) {
        //player wins
        matrix.setCursor(1, 0);
        matrix.print("You\nwin!");
    }
    else if (player_score > 21 && dealer_score < 21) {
        //player busts
        matrix.setCursor(1, 0);
        matrix.print("You\nlose!");
    }
    else if (player_score > 21 && dealer_score > player_score) {
        //dealer wins
        matrix.setCursor(1, 0);
        matrix.print("You\nlose!");
    }
    else if (dealer_score > 21 && player_score < 21) {
        //dealer busts, player wins
        matrix.setCursor(1, 0);
        matrix.print("You\nlose!");
    }
}

void start_war() {
    char message[30];
    for (size_t i = 0; i < 26; i++) {
        matrix.setCursor(1, 0);
        sprintf(message, "Cards\nDealt\n%d/26", (int)(i));
        matrix.print(message);
        recv_card();
        matrix.fillScreen(matrix.Color333(0, 0, 0));
        pushWarDealerCard();
    }

    while (!dealer_cards_war.empty() && num_player_cards > 0) {
        if (war) {
            matrix.setCursor(1, 0);
            matrix.print("Play your card facedown:");      
            recv_card();
            matrix.fillScreen(matrix.Color333(0, 0, 0));
            pushWarPlayerCard();
            int playerCardDown = player_cards_war.back();

            matrix.setCursor(1, 0);
            matrix.print("Play your card faceup:");      
            recv_card();
            matrix.fillScreen(matrix.Color333(0, 0, 0));
            pushWarPlayerCard();
            int playerCardUp = player_cards_war.back();

            num_player_cards -= 2;

            int dealerCardDown = dealer_cards_war.front();
            matrix.setCursor(1, 0);
            matrix.print("Dealer played facedown card");
            delay(3000);  
            matrix.fillScreen(matrix.Color333(0, 0, 0));
            dealer_cards_war.remove(0);

            int dealerCardUp = dealer_cards_war.front();
            printWarCard(playerCardUp, dealerCardUp);
            delay(3000);    
            matrix.fillScreen(matrix.Color333(0, 0, 0));
            dealer_cards_war.remove(0);

            deskCards.push_back(playerCardDown);
            deskCards.push_back(playerCardUp);
            deskCards.push_back(dealerCardDown);
            deskCards.push_back(dealerCardUp);

            if (playerCardUp != dealerCardUp) {
                if (playerCardUp > dealerCardUp) {
                    for (size_t i = 0; i < deskCards.size(); i++) {
                      player_cards_war.push_back(deskCards.at(i));
                    }
                    matrix.setCursor(1, 0);
                    matrix.print("You\nwon\nthis\nwar");      
                    delay(3000);
                    matrix.fillScreen(matrix.Color333(0, 0, 0));
                    num_player_cards += deskCards.size();
                }
                else {
                    for (size_t i = 0; i < deskCards.size(); i++) {
                      dealer_cards_war.push_back(deskCards.at(i));
                    }
                    matrix.setCursor(1, 0);
                    matrix.print("You\nlost\nthis\nwar");      
                    delay(3000);
                    matrix.fillScreen(matrix.Color333(0, 0, 0));
                }
                deskCards.clear();
                war = false;

            }
            else if (dealer_cards_war.empty()){
                matrix.setCursor(1, 0);
                matrix.print("DEALER\nEMPTY\nDECK");      
                delay(3000);
                matrix.fillScreen(matrix.Color333(0, 0, 0));
                matrix.setCursor(1, 0);
                matrix.print("YOU\nWIN!");      
                delay(3000);
                matrix.fillScreen(matrix.Color333(0, 0, 0));
                break;
            }
            else if (num_player_cards < 1) {
                matrix.setCursor(1, 0);
                matrix.print("PLAYER\nEMPTY\nDECK");      
                delay(3000);
                matrix.fillScreen(matrix.Color333(0, 0, 0));
                matrix.setCursor(1, 0);
                matrix.print("YOU\nLOSE!");      
                delay(3000);
                matrix.fillScreen(matrix.Color333(0, 0, 0));
                break;
            }
            else {
              matrix.setCursor(1, 0);
              matrix.print("WAR\nGOES\nON");      
              delay(3000);
              matrix.fillScreen(matrix.Color333(0, 0, 0));
            }
        }
        else {
            matrix.setCursor(1, 0);
            matrix.print("Play your card:");      
            recv_card();
            matrix.fillScreen(matrix.Color333(0, 0, 0));
            pushWarPlayerCard();
            int playerCardUp = player_cards_war.back();

            int dealerCardUp = dealer_cards_war.front();
            printWarCard(playerCardUp, dealerCardUp);
            delay(3000);    
            matrix.fillScreen(matrix.Color333(0, 0, 0));
            dealer_cards_war.remove(0);

            deskCards.push_back(playerCardUp);
            deskCards.push_back(dealerCardUp);

            num_player_cards--;

            if (playerCardUp != dealerCardUp)
            {
                if (playerCardUp > dealerCardUp) {
                    for (size_t i = 0; i < deskCards.size(); i++) {
                      player_cards_war.push_back(deskCards.at(i));
                    }
                    matrix.setCursor(0, 0);
                    matrix.print("You\nwin\nthis\nround");      
                    delay(3000);
                    matrix.fillScreen(matrix.Color333(0, 0, 0));
                    num_player_cards += deskCards.size();
                }
                else {
                    for (size_t i = 0; i < deskCards.size(); i++) {
                      dealer_cards_war.push_back(deskCards.at(i));
                      matrix.setCursor(0, 0);
                      matrix.print("You\nlose\nthis\nround");      
                      delay(3000);
                      matrix.fillScreen(matrix.Color333(0, 0, 0));
                    }
                }
                matrix.setCursor(1, 0);
                matrix.print("The\ngame\ngoes\non");      
                delay(3000);
                matrix.fillScreen(matrix.Color333(0, 0, 0));
                deskCards.clear();
            }
            else {
              matrix.setCursor(1, 0);
              matrix.print("IT'S\nWAR\nTIME");      
              delay(3000);
              matrix.fillScreen(matrix.Color333(0, 0, 0));
              war = true;
            }
        }
    }
    if (dealer_cards_war.empty()) {
          matrix.setCursor(1, 0);
          matrix.print("DEALER\nEMPTY\nDECK");      
          delay(3000);
          matrix.fillScreen(matrix.Color333(0, 0, 0));
          matrix.setCursor(1, 0);
          matrix.print("YOU\nWIN!");      
          delay(3000);
          matrix.fillScreen(matrix.Color333(0, 0, 0));
    }
    else {
          matrix.setCursor(1, 0);
          matrix.print("PLAYER\nEMPTY\nDECK");      
          delay(3000);
          matrix.fillScreen(matrix.Color333(0, 0, 0));
          matrix.setCursor(1, 0);
          matrix.print("YOU\nLOSE!");      
          delay(3000);
          matrix.fillScreen(matrix.Color333(0, 0, 0));
    }
    player_cards_war.clear();
    dealer_cards_war.clear();
    deskCards.clear();
    war = false;
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

void printWarCard(int player_card, int dealer_card) {
    char message[30];
    char player_bits[4];
    char dealer_bits[4];
    switch (player_card) {
        case 11: //ace
            sprintf(player_bits, "%c", 'A');
            break;
        case 12: //jack
            sprintf(player_bits, "%c", 'J');
            break;
        case 13: //queen
            sprintf(player_bits, "%c", 'Q');
            break;
        case 14: //king
            sprintf(player_bits, "%c", 'K');
            break;
        default:
            sprintf(player_bits, "%d", player_card);
    }
    switch (dealer_card) {
        case 11: //ace
            sprintf(dealer_bits, "%c", 'A');
            break;
        case 12: //jack
            sprintf(dealer_bits, "%c", 'J');
            break;
        case 13: //queen
            sprintf(dealer_bits, "%c", 'Q');
            break;
        case 14: //king
            sprintf(dealer_bits, "%c", 'K');
            break;
        default:
            sprintf(dealer_bits, "%d", dealer_card);
    }
    matrix.setCursor(1, 0);
    sprintf(message, "%d\nvs\n%d", player_bits, dealer_bits);
    matrix.print(message);
}

void pushPlayerCard() {
    if(atoi(receivedChars) <= 10) {
        player_cards.push_back(atoi(receivedChars));
        player_score += atoi(receivedChars);
    }
    else if (atoi(receivedChars) == '11') { //ace case
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
  int value = 0;
  if(atoi(receivedChars) <= 10) {
      dealer_cards.push_back(atoi(receivedChars));
      value = atoi(receivedChars);
  }
  else if (atoi(receivedChars) == '11') { //ace case
      dealer_cards.push_back(11);
      dealer_ace = true;
      value = 11;
  }
  else {
      dealer_cards.push_back(10);
      value = 10;
  }
  if(dealer_cards.size() >= 2) {
    dealer_score += value;
  }
}

void pushWarDealerCard() {
  dealer_cards_war.push_back(atoi(receivedChars));
}

void pushWarPlayerCard() {
  player_cards_war.push_back(atoi(receivedChars));
}

void blackjack_or_war() {
  if (receivedChars[0] == 'W')
      blackjack = false;
  // blackjack true by default
}

void game_loop() {

    if(!player_ace) {
        switch(hard_hand_decision_matrix[player_score][dealer_score]) {
            case 0:
                matrix.setCursor(1, 0);
                matrix.print("You\nshould\nstand");
                delay(5000);
                matrix.fillScreen(matrix.Color333(0, 0, 0));
                return;
            default:
                matrix.setCursor(1, 0);
                matrix.print("You\nshould\nhit");
                delay(5000);
                matrix.fillScreen(matrix.Color333(0, 0, 0));
                recv_card();
                pushPlayerCard();
                if(player_score > 21 && !player_ace) {
                    return;
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
                matrix.print("You\nshould\n stand");
                delay(5000);
                matrix.fillScreen(matrix.Color333(0, 0, 0));
                return;
            default:
                matrix.setCursor(1, 0);
                matrix.print("You\nshould\nhit");
                delay(5000);
                matrix.fillScreen(matrix.Color333(0, 0, 0));
                recv_card();
                pushPlayerCard();
                if(player_score > 21 && !player_ace) {
                    return;
                }
                else if(player_score > 21 && player_ace) {
                    player_score -= 10;
                }
                game_loop();
        }
    }
}

void drawHeart() {
  matrix.drawLine(6, 4, 12, 0, matrix.Color333(7, 0, 0));
  matrix.drawLine(12, 0, 18, 4, matrix.Color333(7, 0, 0));
  matrix.drawLine(18, 4, 20, 8, matrix.Color333(7, 0, 0));
  matrix.drawLine(20, 8, 20, 14, matrix.Color333(7, 0, 0));
  matrix.drawLine(20, 14, 12, 28, matrix.Color333(7, 0, 0));
  matrix.drawLine(12, 28, 4, 14, matrix.Color333(7, 0, 0));
  matrix.drawLine(4, 14, 4, 8, matrix.Color333(7, 0, 0));
  matrix.drawLine(4, 8, 6, 4, matrix.Color333(7, 0, 0));
}

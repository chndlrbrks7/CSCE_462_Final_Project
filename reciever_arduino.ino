#include <RGBmatrixPanel.h>
#include <Vector.h>
#include <stdlib.h>

int hard_hand_decision_matrix[22][13] = {
  {-1,-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
  {-1,-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
  {-1,-1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
  {-1,-1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
  {-1,-1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
  {-1,-1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
  {-1,-1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
  {-1,-1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
  {-1,-1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
  {-1,-1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
  {-1,-1, 1, 1, 2, 2, 2, 2, 1, 1, 1, 1, 1},
  {-1,-1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1},
  {-1,-1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1},
  {-1,-1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1},
  {-1,-1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1},
  {-1,-1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1},
  {-1,-1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1},
  {-1,-1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1},
  {-1,-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {-1,-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {-1,-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {-1,-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
};


int soft_hand_decision_matrix[22][13] = {
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
	{-1,-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
  {-1,-1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1},
  {-1,-1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1},
  {-1,-1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1},
  {-1,-1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1},
  {-1,-1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1},
  {-1,-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {-1,-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {-1,-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {-1,-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
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
    drawSpade();
    drawDiamond();
    drawHeart();
    drawClub();
    recv_card();
    /*blackjack_or_war();
    
    if (blackjack)
        start_blackjack();
    else {
      start_war();
    }*/
    
}

void start_blackjack() {
    matrix.fillScreen(matrix.Color333(0, 0, 0));
    matrix.setCursor(1, 0);

    matrix.print("Game:\nBlack\njack");
    delay(3000);

    matrix.fillScreen(matrix.Color333(0, 0, 0));
    matrix.setCursor(1, 0);
    matrix.print("Your\nturn");
    recv_card();
    matrix.fillScreen(matrix.Color333(0, 0, 0));
    pushPlayerCard();
    
    matrix.setCursor(1, 0);
    matrix.print("House\nturn");
    recv_card();
    matrix.fillScreen(matrix.Color333(0, 0, 0));
    pushDealerCard();

    matrix.setCursor(1, 0);
    matrix.print("Your\nturn");


    recv_card();
    matrix.fillScreen(matrix.Color333(0, 0, 0));
    pushPlayerCard();

    matrix.setCursor(1, 0);
    matrix.print("House\nturn");
    recv_card();
    matrix.fillScreen(matrix.Color333(0, 0, 0));
    pushDealerCard();

    dealer_score = dealer_cards[0];

    game_loop();
    

    dealer_score = dealer_cards[0] + dealer_cards[1];

    while(dealer_score < 17) {
      matrix.setCursor(1, 0);
      matrix.print("House\nturn");
      recv_card();
      pushDealerCard();
      matrix.fillScreen(matrix.Color333(0, 0, 0));
      delay(3000);
    }

    if(dealer_score > 21 && dealer_ace) {
        dealer_score -= 10;
    }


    if (player_score > 21){
        matrix.setCursor(1, 0);
        matrix.print("You\nlose!");
        delay(5000);
    }
    else if (player_score <= 21 && dealer_score < player_score) {
        //player wins
        matrix.fillScreen(matrix.Color333(0, 0, 0));
        matrix.setCursor(1, 0);
        matrix.print("You\nwin!");
        delay(5000);
    }
    else if (dealer_score >= 21 && player_score <= 21) {
        //dealer busts, player wins
        matrix.setCursor(1, 0);
        matrix.print("You\nwin!");
        delay(5000);
    }
    else if (player_score <= 21 && player_score < dealer_score ) {
      matrix.setCursor(1,0);
      matrix.print("You\nlose!");
      delay(5000);
    }
    else if (dealer_score == player_score) {
      matrix.setCursor(1, 0);
      matrix.print("Draw");
      delay(5000);
    }
    else {
      char message[30];
      matrix.setCursor(1, 0);
      sprintf(message, "%d\n%d", player_score, dealer_score);
      matrix.print(message);
    }
}

void start_war() {
    matrix.fillScreen(matrix.Color333(0, 0, 0));
    matrix.setCursor(1, 0);

    matrix.print("Game:\nWar");
    delay(3000);

    matrix.fillScreen(matrix.Color333(0, 0, 0));
    matrix.setCursor(1, 0);
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
            matrix.print("Play\nface\ndown");      
            recv_card();
            matrix.fillScreen(matrix.Color333(0, 0, 0));
            pushWarPlayerCard();
            int playerCardDown = player_cards_war.back();

            matrix.setCursor(1, 0);
            matrix.print("Play\nface\nup");      
            recv_card();
            matrix.fillScreen(matrix.Color333(0, 0, 0));
            pushWarPlayerCard();
            int playerCardUp = player_cards_war.back();

            num_player_cards -= 2;

            int dealerCardDown = dealer_cards_war.front();
            matrix.setCursor(1, 0);
            matrix.print("House\ndealt\nface\ndown");
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
                  if((atoi(receivedChars) < 1 || atoi(receivedChars) > 14) && (receivedChars[0] != 'W' && receivedChars[0] != 'B')) {
                    matrix.fillScreen(matrix.Color333(0, 0, 0));
                    matrix.setCursor(1, 0);
                    matrix.print("Bad\nread\ntry\nagain");
                    recv_card();
                  }
                  else if(receivedChars[0] == 'W') {
                    start_war();
                    loop();
                  }
                  else if(receivedChars[0] == 'B') {
                    start_blackjack();
                    loop();
                  }
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
        player_score += 10;
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
                matrix.print("Stand");
                delay(5000);
                matrix.fillScreen(matrix.Color333(0, 0, 0));
                return;
            default:
                matrix.setCursor(1, 0);
                matrix.print("Hit");
                delay(5000);
                matrix.fillScreen(matrix.Color333(0, 0, 0));
                matrix.setCursor(1, 0);
                matrix.println("Your\nturn");
                recv_card();
                pushPlayerCard();
                matrix.fillScreen(matrix.Color333(0, 0, 0));
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
                matrix.print("Stand");
                delay(5000);
                matrix.fillScreen(matrix.Color333(0, 0, 0));
                return;
            default:
                matrix.setCursor(1, 0);
                matrix.print("Hit");
                delay(5000);
                matrix.fillScreen(matrix.Color333(0, 0, 0));
                matrix.setCursor(1, 0);
                matrix.println("Your\nturn");
                recv_card();
                pushPlayerCard();
                matrix.fillScreen(matrix.Color333(0, 0, 0));
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

void drawSpade() {
  matrix.fillRect(0,0,16, 16, matrix.Color333(1, 0, 0));
  matrix.fillRect(3, 7, 9, 3, matrix.Color333(0, 0, 0));
  matrix.fillRect(4,5, 7, 2, matrix.Color333(0, 0, 0));
  matrix.fillRect(6, 3, 3, 2, matrix.Color333(0, 0, 0));
  matrix.drawPixel(7, 2, matrix.Color333(0, 0, 0));
  matrix.drawPixel(4, 10, matrix.Color333(0, 0, 0));
  matrix.drawPixel(5, 10, matrix.Color333(0, 0, 0));
  matrix.drawPixel(9, 10, matrix.Color333(0, 0, 0));
  matrix.drawPixel(10, 10, matrix.Color333(0, 0, 0));
  matrix.fillRect(7, 10, 1, 4, matrix.Color333(0, 0, 0));
  matrix.drawPixel(6, 12, matrix.Color333(0, 0, 0));
  matrix.drawPixel(8, 10, matrix.Color333(0, 0, 0));
  matrix.fillRect(4, 13, 5, 1, matrix.Color333(0, 0, 0));
  matrix.drawPixel(8, 12, matrix.Color333(0, 0, 0));
  matrix.drawPixel(9, 13, matrix.Color333(0, 0, 0));
  matrix.drawPixel(10, 13, matrix.Color333(0, 0, 0));
  matrix.drawPixel(6, 10, matrix.Color333(0, 0, 0));
}

void drawDiamond() {
  matrix.fillRect(16, 0, 16, 16, matrix.Color333(0, 0, 0));
  matrix.fillRect(23,3, 3, 9,  matrix.Color333(1, 0, 0));
  matrix.fillRect(22, 4, 1, 5, matrix.Color333(1, 0, 0));
  matrix.fillRect(26, 5, 1, 5, matrix.Color333(1, 0, 0));
  matrix.fillRect(27, 6, 1, 3, matrix.Color333(1, 0, 0));
  matrix.fillRect(21, 6, 1, 3, matrix.Color333(1, 0, 0));
  matrix.drawPixel(20, 7, matrix.Color333(1, 0, 0));
  matrix.drawPixel(28, 7, matrix.Color333(1, 0, 0));
  matrix.drawPixel(24, 2, matrix.Color333(1, 0, 0));
  matrix.drawPixel(24, 12, matrix.Color333(1, 0, 0));
  matrix.drawPixel(22, 10, matrix.Color333(1, 0, 0));
  matrix.drawPixel(22, 9, matrix.Color333(1, 0, 0));
  matrix.drawPixel(26, 4, matrix.Color333(1, 0, 0));
  matrix.drawPixel(26, 10, matrix.Color333(1, 0, 0));
}

void drawHeart() {
    matrix.fillRect(0, 17, 16, 15, matrix.Color333(0, 0, 0));
    matrix.fillRect(4, 19, 2, 2, matrix.Color333(1, 0, 0));
    matrix.fillRect(9, 19, 2, 2, matrix.Color333(1, 0, 0));
    matrix.fillRect(2, 21, 11, 3, matrix.Color333(1, 0, 0));
    matrix.fillRect(4, 24, 7, 2, matrix.Color333(1, 0, 0));
    matrix.fillRect(6, 26, 3, 2, matrix.Color333(1, 0, 0));

    matrix.drawPixel(3, 20, matrix.Color333(1, 0, 0));
    matrix.drawPixel(11, 20, matrix.Color333(1, 0, 0));
    matrix.drawPixel(6, 20, matrix.Color333(1, 0, 0));
    matrix.drawPixel(8, 20, matrix.Color333(1, 0, 0));

    matrix.drawPixel(3, 24, matrix.Color333(1, 0, 0));
    matrix.drawPixel(11, 24, matrix.Color333(1, 0, 0));

    matrix.drawPixel(5, 26, matrix.Color333(1, 0, 0));
    matrix.drawPixel(9, 26, matrix.Color333(1, 0, 0));

    matrix.drawPixel(7, 28, matrix.Color333(1, 0, 0));

}

void drawClub() {
    matrix.fillRect(16, 16, 17, 16, matrix.Color333(1, 0, 0));
    matrix.fillRect(23, 18, 3, 8, matrix.Color333(0, 0, 0));
    matrix.fillRect(20, 23, 3, 3, matrix.Color333(0, 0, 0));
    matrix.fillRect(26, 23, 3, 3, matrix.Color333(0, 0, 0));
    matrix.fillRect(23, 27, 3, 2, matrix.Color333(0, 0, 0));

    matrix.fillRect(22, 19, 1, 2, matrix.Color333(0, 0, 0));
    matrix.fillRect(26, 19, 1, 2, matrix.Color333(0, 0, 0));

    matrix.fillRect(21, 22, 2, 1, matrix.Color333(0, 0, 0));
    matrix.fillRect(26, 22, 2, 1, matrix.Color333(0, 0, 0));

    matrix.fillRect(21, 26, 2, 1, matrix.Color333(0, 0, 0));
    matrix.fillRect(26, 26, 2, 1, matrix.Color333(0, 0, 0));

    matrix.drawPixel(24, 26, matrix.Color333(0, 0, 0));

    matrix.drawPixel(22, 28, matrix.Color333(0, 0, 0));
    matrix.drawPixel(26, 28, matrix.Color333(0, 0, 0));
}

void printWarCard(int player_card, int dealer_card) {
    char message[30];
    char player_bits[4];
    char dealer_bits[4];
    matrix.setCursor(1, 0);
    switch (player_card) {
        case 11: //ace
            //sprintf(player_bits, "%c", 'A');
            matrix.print("Ace");
            break;
        case 12: //jack
            //sprintf(player_bits, "%c", 'J');
            matrix.print("Jack");
            break;
        case 13: //queen
            //sprintf(player_bits, "%c", 'Q');
            matrix.print("Queen");
            break;
        case 14: //king
            //sprintf(player_bits, "%c", 'K');
            matrix.print("King");
            break;
        default:
            sprintf(player_bits, "%d", player_card);
            matrix.print(player_bits);
    }
    matrix.print("\nvs\n");
    switch (dealer_card) {
        case 11: //ace
            matrix.print("Ace");
            break;
        case 12: //jack
            matrix.print("Jack");
            break;
        case 13: //queen
            matrix.print("Queen");
            break;
        case 14: //king
            matrix.print("King");
            break;
        default:
            sprintf(dealer_bits, "%d", dealer_card);
            matrix.print(dealer_bits);
    }
    matrix.setCursor(1, 0);

}

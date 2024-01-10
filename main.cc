#include <iostream>
#include "textdisplay.h"
#include "board.h"
#include "abstractcomputer.h"
#include "levelone.h"
#include "leveltwo.h"
#include "levelthree.h"
#include "levelfour.h"
#include <chrono>
typedef std::chrono::high_resolution_clock Clock;

using namespace std;

pair<int, int> getCoord(string loc) {
    // If loc is not a string a length 2, return error value
    if(loc.length() != 2) return {-1, -1};
    int row, col;
    if (isupper(loc[0])) { // Check if first letter is upper/lowercase
        col = loc[0] - 'A';
    } else {
        col = loc[0] - 'a';
    }
    
    // Extra -1 since chess board coords are 1-8
    row = loc[1] - '0' - 1;
    row = abs(loc[1] - '0' - 8);

    return {row, col};
}

PType getPType(string p) {
    char c = tolower(p[0]);
    switch (c) {
        case 'k':
            return PType::King;
        case 'q':
            return PType::Queen;
        case 'r':
            return PType::Rook;
        case 'b':
            return PType::Bishop;
        case 'n':
            return PType::Knight;
        case 'p':
            return PType::Pawn;
        default:
            return PType::Empty;
    }
    return PType::Empty;
}

int main() {
    cin.exceptions(ios::eofbit|ios::failbit);
    string cmd;
    Board b;
    bool whiteTurn = true;
    int whitePlayer, blackPlayer; // 0 = human, 1-4 = computer 1-4
    double whiteScore = 0;
    double blackScore = 0;
    bool bonus= false;
    b.init();
    LevelOne c1{};
    LevelTwo c2{};
    LevelThree c3{};
    LevelFour c4{};
    try {
    while (true) {
        cin >> cmd;
        if (cmd == "game") {
            // Setup players
            string wPlayer, bPlayer;
            cin >> wPlayer;
            if (wPlayer == "computer") {
                int level = -1;
                cin >> level;
                whitePlayer = level;
            } else if (wPlayer == "human") {
                whitePlayer = 0;
            }
            cin >> bPlayer;
            if (bPlayer == "computer") {
                int level = -1;
                cin >> level;
                blackPlayer = level;
            } else if (bPlayer == "human") {
                blackPlayer = 0;
            }
            int gameState = 0;

            // TIME CONTROL
            string time;
            double minutes = 0;
            bool hasTimeControl = false;
            if (bonus) {
                cout << "Would you like to play with time control? (y/n)" << endl;
                cin >> time;
                if (time[0] == 'Y' || time[0] == 'y') {
                    hasTimeControl = true;
                    cout << "How many minutes: ";
                    cin >> minutes;
                }
            }
            
            double totalSeconds = minutes * 60;
            double whiteTime = totalSeconds;
            double blackTime = totalSeconds;


            // Start playing
            while (true) {
                auto t1 = Clock::now();
                cin >> cmd;
                bool validMove = true;
                if (cmd == "resign") {
                    if (whiteTurn) {
                        ++blackScore;
                        cout << endl << "Black wins!" << endl;
                    } else {
                        ++whiteScore;
                        cout << endl << "White wins!" << endl;
                    }
                    b.init();
                    whiteTurn = true;
                    break;
                } else if (cmd == "move") {
                    if (whiteTurn) {
                        if (whitePlayer == 0) {
                            string l1, l2;
                            cin >> l1 >> l2;
                            pair<int, int> loc1 = getCoord(l1);
                            pair<int, int> loc2 = getCoord(l2);

                            validMove = b.makeMove(loc1.first, loc1.second, loc2.first, loc2.second, Colour::White);
                        } else if (whitePlayer == 1) {
                            if (gameState == 3) {
                                c1.nextMove(Colour::White, b, true);
                            } else {
                                c1.nextMove(Colour::White, b, false);
                            }
                            
                            
                        } else if (whitePlayer == 2) {
                            if (gameState == 3) {
                                c2.nextMove(Colour::White, b, true);
                            } else {
                                c2.nextMove(Colour::White, b, false);
                            }
                        } else if (whitePlayer == 3) {
                            if (gameState == 3) {
                                c3.nextMove(Colour::White, b, true);
                            } else {
                                c3.nextMove(Colour::White, b, false);
                            }
                        } else if (whitePlayer == 4) {
                            if (gameState == 3) {
                                c4.nextMove(Colour::White, b, true);
                            } else {
                                c4.nextMove(Colour::White, b, false);
                            }
                        }
                    } else {
                        if (blackPlayer == 0) {
                            string l1, l2;
                            cin >> l1 >> l2;
                            pair<int, int> loc1 = getCoord(l1);
                            pair<int, int> loc2 = getCoord(l2);

                            validMove = b.makeMove(loc1.first, loc1.second, loc2.first, loc2.second, Colour::Black);
                        } else if (blackPlayer == 1) {
                            if (gameState == 3) {
                                c1.nextMove(Colour::Black, b, true);
                            } else {
                                c1.nextMove(Colour::Black, b, false);
                            }
                            
                        } else if (blackPlayer == 2) {
                            if (gameState == 3) {
                                c2.nextMove(Colour::Black, b, true);
                            } else {
                                c2.nextMove(Colour::Black, b, false);
                            }
                        } else if (blackPlayer == 3) {
                            if (gameState == 3) {
                                c3.nextMove(Colour::Black, b, true);
                            } else {
                                c3.nextMove(Colour::Black, b, false);
                            }
                        } else if (blackPlayer == 4) {
                            if (gameState == 3) {
                                c4.nextMove(Colour::Black, b, true);
                            } else {
                                c4.nextMove(Colour::Black, b, false);
                            }
                        }
                    }
                } else {
                    cout << "Invalid Command, please try again" << endl;
                    continue;
                }
                cout << b;

                if (!validMove) { // If the move is invalid, don't do any checks and don't change the colour
                    cout << "Move was invalid, please try again" << endl;
                    continue;
                }

                // After a move, check if won and switch colours
                
                if (whiteTurn) {
                    gameState = b.getGameState(Colour::Black);
                } else {
                    gameState = b.getGameState(Colour::White);
                }
                
                if (gameState == 1) { // Game is won
                    if (whiteTurn) {
                        whiteScore++;
                        cout << "Checkmate! White wins!" << endl;
                    } else {
                        blackScore++;
                        cout << "Checkmate! Black wins!" << endl;
                    }
                    b.init();
                    whiteTurn = true;
                    break;
                } else if (gameState == 2) { // Game is stalemate
                    whiteScore += 0.5;
                    blackScore += 0.5;
                    b.init();
                    whiteTurn = true;
                    cout << "Stalemate!" << endl;
                    break;
                } else if (gameState == 3) {
                    if (whiteTurn) {
                        cout << "Black is in Check!" << endl;
                    } else {
                        cout << "White is in Check!" << endl;
                    }
                }

                auto t2 = Clock::now();

                if (whiteTurn && hasTimeControl) {
                    whiteTime = whiteTime - std::chrono::duration_cast<std::chrono::seconds>(t2 - t1).count();
                    cout << "You took: " << std::chrono::duration_cast<std::chrono::seconds>(t2 - t1).count() << " seconds." << endl;
                    cout << "Remaining time for White: " << whiteTime << " seconds." << endl;
                } else if (hasTimeControl){
                    blackTime = blackTime - std::chrono::duration_cast<std::chrono::seconds>(t2 - t1).count();
                    cout << "You took: " << std::chrono::duration_cast<std::chrono::seconds>(t2 - t1).count() << " seconds." << endl;
                    cout << "Remaining time for Black: " << blackTime << " seconds." << endl;
                }   

                if (whiteTurn && whiteTime < 0 && hasTimeControl) {
                    blackScore++;
                    cout << "White ran out of time! Black wins!" << endl;
                    b.init();
                    whiteTurn = true;
                    break;
                } else if (!whiteTurn && blackTime < 0 && hasTimeControl) {
                    whiteScore++;
                    cout << "Black ran out of time! White wins!" << endl;
                    b.init();
                    whiteTurn = true;
                    break;
                }

                whiteTurn = !whiteTurn;


            }
            // End of game, print scores
            cout << "GAME FINISHED, SCORES:" << endl; 
            cout << "White: " << whiteScore << endl;
            cout << "Black: " << blackScore << endl << endl; 


        } else if (cmd == "setup") {
            string option;
            string secondArg;
            while (true) {
                cin >> option;
                if (option == "+") {
                    string location;
                    cin >> secondArg >> location;
                    pair<int, int> loc = getCoord(location);
                    if (isupper(secondArg[0])) {
                        b.set(loc.first, loc.second, getPType(secondArg), Colour::White);
                    } else {
                        b.set(loc.first, loc.second, getPType(secondArg), Colour::Black);
                    }
                    cout << b;
                    cout << "Added " << secondArg << " at " << location << endl;
                } else if (option == "-") { // Delete piece (set to empty)
                    cin >> secondArg;
                    pair<int, int> loc = getCoord(secondArg);
                    b.set(loc.first, loc.second, PType::Empty, Colour::Empty);
                    cout << b;
                    cout << "removed piece at " << secondArg << endl;
                } else if (option == "=") { // Set colour to make next move
                    cin >> secondArg;
                    if (secondArg == "black") {
                        cout << "Changed turn to black" << endl;
                        whiteTurn = false;
                    } else {
                        cout << "Changed turn to white" << endl;
                        whiteTurn = true;
                    }

                } else if (option == "done") { // Exit setup mode [NEED TO CHECK IF VALID StATE OR NOT]
                    cout << b;
                    if (b.checkValid()) {
                        break;
                    } else {
                        cout << "Board is in invalid state. Board must contain exactly one white king and exactly one black king, " <<
                        "that no pawns are on the first or last row of the board, and that neither king is in check" << endl;
                    }
                    
                } else { // Invalid command, get the line to clear buffer and restart (not sure if buffer needs to be cleared)
                    getline(cin, option);
                    cout << "Please re-enter a command in setup mode:" << endl;
                }
            }
            
        } else if (cmd == "clear") {
            b.clear();
            cout << b;
        } else if (cmd == "init") {
            b.init();
            cout << b;
        } else if (cmd == "theme" && bonus) {
            int offset = 0;
            cin >> offset;
            if (offset == 0) {
                b.setTheme(0);
            } else if (offset == 1) {
                b.setTheme(1);
            } else if (offset == 2) {
                b.setTheme(4);
            } else if (offset == 3) {
                b.setTheme(6);
            } else {
                cout << "Invalid theme (0-3)" << endl;
            }
        } else if (cmd == "bonus") {
            bonus = !bonus;
        } else {
            getline(cin, cmd);
            cout << "Command not found, please re-enter a command:" << endl;
        }


    }
    } catch (...) {
        // End of game, print scores
        cout << "FINAL SCORES:" << endl; 
        cout << "White: " << whiteScore << endl;
        cout << "Black: " << blackScore << endl << endl;
    }
}

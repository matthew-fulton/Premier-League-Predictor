/*      This Program simulates the remaining English Premier League season n # of times, determining the most likely final standings, point totals,
    as well as the likelihood that each team finishes in each of the 20 possible spots, to find the probability that each team is relegated, 
    qualifies for the Euro league, Champions league, or finishes as Champions of the league

        The win probabilities are taken from fivethirtyeight.com. Unlike five-thirty-eights simulator, these win probabilities remain static 
    throughout each trial. This means that these results are slightly more concentrated to the average then five-thirty-eights, as there are
    fewer instances of a team vastly overperforming or underperforming expectations for a prolonged period. 

                                        Format for finish matrix:    finish[team][position]
*/

#include <iostream>
#include<iomanip>
#include <cmath>
#include<array>
#include<Bits.h>
using namespace std;


int main()
{

    //VARIABLES
    int a(0); int b(0); int c(0); int i; int j;                     // Counters
    int n = 1000;                                                     // Number of Iterations             **USER INPUT**
    int month = 2;                                                      // Today's date (Month)
    int day = 9;                                                        // Today's date (Day)
    
    double nn = n / 1.0;                                            // Convert to Double
    double p = 0; double diffplayed=0;                                  // counter for games played
    int nplayed = 0;                          //Number of games played since February 7th (All teams had played 25);
    int finish[21][21] = { 0 };                                                                                             // Final results for every team across all trials
    double avgPts[21] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };                                                      // Avg Pts for every team across all trials
    double played[21] = { 0,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25 };                         // MP, pts, gd, goals, and rank for every team within each trial
    double points[21] = { 0,73,51,49,41,37,36,35,35,33,31,31,31,31,30,26,26,25,24,23,18 };
    double gd[21] = { 0, 45,36,28,9,8,3,7,3,-6,-2,-10,-12,-15,-7,-7,-13,-15,-13,-16,-23 };
    double gf[21] = { 0,60,65,	54,	43,	40,	26,	36,	35,	31,	32,	28,	24,	31,	22,	30,	25,	32,	30,	23,	24 };
    double rank[21] = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20 };
    double ranktrack[21] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };                               // Tracker to determine each teams rank in any given trial
    char array[][21] = { " ","Liverpool", "Man City","Leicester","Chelsea","Spurs","Sheffield Utd","Man United","Wolves","Everton","Arsenal","Burnley","Newcastle","Southampton","Crystal Palace","Brighton","Bournemouth","Aston Villa","West Ham","Watford","Norwich" };

    const int defplayed[21] = { 0,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25 };                // Starting values for MP, pts, gd, goals, rank for each trial
    const int defpoints[21] = { 0,73,51,49,41,37,36,35,35,33,31,31,31,31,30,26,26,25,24,23,18 };
    const int defgd[21] = { 0, 45,36,28,9,8,3,7,3,-6,-2,-10,-12,-15,-7,-7,-13,-15,-13,-16,-23 };
    const int defgf[21] = { 0,60,65,	54,	43,	40,	26,	36,	35,	31,	32,	28,	24,	31,	22,	30,	25,	32,	30,	23,	24 };
    const int defrank[21] = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20 };
    const double defranktrack[21] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };





    

    //OUTER LOOP TO RUN THE SCENARIO n TIMES
    for (a = 1; a < n + 1; a = a + 1) {
        //Re-initialize ARRAYS FOR ALL 20 TEAMS FINAL PTS, GD, GF, AND FINISH FOR EACH TRIAL
        for (c = 0; c < 21; c = c + 1) {
            played[c] = defplayed[c];                                                               // Reset MP, pts, gd, goals and rank tracker to begin trial
            points[c] = defpoints[c];
            gd[c] = defgd[c];
            gf[c] = defgf[c];
            ranktrack[c] = defranktrack[c];
            p = 0;
        }


        //CREATE ARRAYS FOR HOME WIN PROBABILITY, AWAY WIN PROBABILITY FOR EVERY GAME REMAINING
        int homewin[130] = { 57,43,	49,	86,	42,	49,	10,	27,	60,	57,	55,	50,	55,	51,	46,	22,	57,	64,	41,	88,	24,	49,	35,	37,	39,	20,	14,	42,	47,	81,	89,	57,	57,	40,	55,	56,	31,	57,	22,	68,	32,	33,	87,	41,	39,	34,	19,	30,	45,	20,	63,	28,	55,	42,	42,	63,	27,	86,	59,	41,	28,	41,	46,	21,	61,	43,	44,	48,	33,	35,	66,	90,	65,	48,	40,	40,	14,	62,	49,	36,	26,	54,	91,	42,	37,	23,	55,	27,	14,	36,	41,	86,	57,	52,	45,	56,	25,	13,	41,	27,	79,	64,	24,	90,	40,	17,	33,	47,	29,	57,	32,	64,	64,	44,	58,	13,	36,	56,	38,	37,	56,	63,	9,	91,	49,	51,	42,	44,	30,	46 };
        int awaywin[130] = { 25,26,	27,	9,	27,	26,	16,	23,	23,	23,	23,	26,	23,	27,	28,	21,	24,	22,	26,	9,	24,	27,	27,	28,	25,	22,	19,	27,	26,	12,	8,	22,	24,	28,	25,	26,	26,	23,	21,	19,	26,	30,	10,	28,	26,	26,	20,	26,	25,	22,	20,	22,	26,	26,	27,	23,	25,	11,	22,	25,	25,	26,	23,	22,	22,	29,	26,	27,	26,	28,	20,	8,	21,	25,	26,	30,	17,	23,	26,	26,	24,	24,	7,	26,	25,	24,	24,	24,	18,	30,	26,	11,	24,	24,	27,	25,	24,	17,	25,	27,	15,	21,	25,	8,	25,	20,	28,	25,	27,	25,	24,	20,	21,	25,	25,	17,	26,	25,	27,	29,	24,	22,	15,	7,	23,	25,	27,	28,	26,	25 };
        //CREATE AN ARRAY FOR HOME TEAM, AWAY TEAM FOR EVERY GAME REMAINING; ASSIGN EACH TEAM A NUMBER 1-20 BASED ON STANDINGS TO DO SO
        int hometeam[130] = { 9,15,6,2,8,13,20,17,10,4,4,11,13,14,6,3,7,8,10,1,	20,	15,	17,	12,	18,	16,	19,	9,	5,	2,	1,	10,	13,	14,	8,	6,	11,	4,	7,	3,	19,	12,	2,	16,	15,	20,	17,	18,	5,	9,	5,	4,	7,	12,	11,	8,	20,	1,	3,	13,	17,	9,	2,	18,	10,	14,	19,	16,	15,	6,	4,	1,	7,	5,	12,	11,	13,	3,	8,	20,	17,	9,	2,	18,	10,	14,	19,	16,	15,	6,	17,	1,	7,	5,	8,	19,	16,	15,	20,	6,	4,	9,	12,	2,	18,	10,	11,	13,	14,	3,	17,	1,	7,	5,	8,	19,	16,	15,	20,	6,	4,	9,	12,	2,	18,	10,	11,	13,	14,	3 };
        int awayteam[130] = { 14, 19,	16,	18,	3,	11,	1,	5,	12,	7,	5,	16,	17,	12,	15,	2,	19,	20,	9,	18,	3,	14,	6,	11,	13,	4,	1,	7,	8,	10,	16,	18,	12,	19,	15,	20,	5,	9,	2,	17,	3,	6,	11,	14,	10,	13,	4,	8,	7,	1,	18,	2,	6,	17,	19,	16,	9,	14,	15,	10,	8,	3,	1,	4,	20,	11,	13,	12,	7,	5,	19,	17,	16,	9,	18,	6,	2,	14,	10,	15,	7,	13,	12,	11,	3,	4,	20,	5,	1,	8,	14,	11,	13,	10,	9,	12,	3,	2,	18,	4,	20,	17,	5,	16,	19,	1,	8,	15,	7,	6,	10,	4,	18,	3,	14,	2,	13,	12,	11,	9,	8,	16,	1,	20,	17,	19,	15,	6,	5,	7 };
        
        
        double homewp;              // Odds Home team wins game (Take from 538)
        double awaywp;              // Odds Away team wins game (Take from 538)

        double randwl;              // Random number holders for W/D/L Result, Winner/D goals scored, scoring margin
        double randgs;              
        double randgd;             

        double hpoints;             // Place holder for home points, goals for, goal difference added by game
        double hgoals;              
        double hgd;                 

        double apoints;             // Place holder for away points, goals for, goal difference added by game
        double agoals;              
        double agd;                 

        //Games already played:
        //Matchweek 26:
        //Everton 3-1 Crystal Palace
        played[9] = played[9] + 1; played[14] = played[14] + 1; points[9] = points[9] + 3; points[14] = points[14] + 0; gd[9] = gd[9] + 2; gd[14] = gd[14] - 2; gf[9] = gf[9] + 3; gf[14] = gf[14] + 1;
        //Brighton 1-1 Watford
        played[15] = played[15] + 1; played[19] = played[19] + 1; points[15] = points[15] + 1; points[19] = points[19] + 1; gd[15] = gd[15]; gd[19] = gd[19]; gf[15] = gf[15] + 1; gf[19] = gf[19] + 1;
        //Sheffield 2-1 Bournemouth
        played[6] = played[6] + 1; played[16] = played[16] + 1; points[6] = points[6] + 3; points[16] = points[16] + 0; gd[6] = gd[6] + 1; gd[16] = gd[16] = 1; gf[6] = gf[6] + 2; gf[16] = gf[16] + 1;
        //  Man City-West Ham 2-0
        played[2] = played[2] + 1; played[18] = played[18] + 1; points[2] = points[2] + 3; gf[2] = gf[2] + 2; gd[2] = gd[2] + 2; gd[18] = gd[18] - 2;
        // Wolves 0-0 Leicester
        points[8] = points[8] + 1; points[3] = points[3] + 1; played[8] = played[8] + 1; played[3] = played[3] + 1;
        // Southampton 1-2 Burnley
        played[13] = played[13] + 1; played[11] = played[11] + 1; points[11] = points[11] + 3; gf[13] = gf[13] +1 ; gf[11] = gf[11] + 2; gd[13] = gd[13] - 1; gd[11] = gd[11] + 1;
        // Norwich 0-1 Liverpool 
        played[20] = played[20] + 1; played[1] = played[1] + 1; points[1] = points[1] + 3; gf[1] = gf[1] + 1; gd[1] = gd[1] + 1;
        // Aston Villa 2-3 Tottenham
        played[17] = played[17] + 1; played[5] = played[5] + 1; points[5] = points[5] + 3; gd[17] = gd[17] - 1; gd[5] = gd[5] + 1; gf[17] = gf[17] + 2; gf[5] = gf[5] + 3;
        // Arsenal 4-0 Newcastle
        played[10] = played[10] + 1; played[12] = played[12] + 1; points[10] = points[10] + 3; gd[10] = gd[10] + 4; gd[12] = gd[12] - 4; gf[10] = gf[10] + 4;
        // Chelsea 0-2 Man United
        played[4] = played[4] + 1; played[7] = played[7] + 1; points[7] = points[7] + 3; gd[4] = gd[4] - 2; gd[7] = gd[7] + 2; gf[7] = gf[7] + 2;
        // Chelsea 2-1 Spurs 4-5
        played[4] = played[4] + 1; played[5] = played[5] + 1; points[4] = points[4] + 3; gf[4] = gf[4] + 2; gf[5] = gf[5] + 11; gd[4] = gd[4] + 1; gd[5] = gd[5] - 1;
        // Burnley 3-0 Bournemouth 11-16
        played[11] = played[11] + 1; played[16] = played[16] + 1; points[11] = points[11] + 3; gf[11] = gf[11] + 3; gd[11] = gd[11] + 3; gd[16] = gd[16] - 3;
        // Crystal Palace 1-0 Newcastle  14-12
        played[14] = played[14] + 1; played[12] = played[12] + 1; points[14] = points[14] + 3; gf[14] = gf[14] + 1; gd[14] = gd[14] + 1; gd[12] = gd[12] - 1;
        // Sheffield Utd 1-1 Brighton  6-15
        played[6] = played[6] + 1; played[15] = played[15] + 1; points[6] = points[6] + 1; points[15] = points[15] + 1; gf[6] = gf[6] + 1; gf[15] = gf[15] + 1;
        // Southampton 2-0 Aston Villa 13 17
        played[13] = played[13] + 1; played[17] = played[17] + 1; points[13] = points[13] + 3; gf[13] = gf[13] + 2; gd[13] = gd[13] + 2; gd[17] = gd[17] - 2;
        // Leicester 0-1 Man City 3-2
        played[3] = played[3] + 1; played[2] = played[2] + 1; points[2] = points[2] + 3; gf[2] = gf[2] + 1; gd[2] = gd[2] + 1; gd[3] = gd[3] - 1;
        // Man United 3-0 Watford 7 19
        played[7] = played[7] + 1; played[19] = played[19] + 1; points[7] = points[7] + 3; gf[7] = gf[7] + 3; gd[7] = gd[7] + 3; gd[19] = gd[19] - 3;
        // Wolves 3-0 Norwich 8 20
        played[8] = played[8] + 1; played[20] = played[20] + 1; points[8] = points[8] + 3; gf[8] = gf[8] + 3; gd[8] = gd[8] + 3; gd[20] = gd[20] - 3;
        // Arsenal 3-2 Everton 10 9
        played[10] = played[10] + 1; played[9] = played[9] + 1; points[10] = points[10] + 3; gf[10] = gf[10] + 3; gf[9] = gf[9] + 2; gd[10] = gd[10] + 1; gd[9] = gd[9] - 1;

        for (i = 1; i < 21;i=i+1) {
            diffplayed = played[i] - defplayed[i];
            p = p + diffplayed / 2.0;
        }
        nplayed = p;
        //INNER LOOP TO RUN THE ENGINE FOR EACH GAME:
        for (i = nplayed; i < 130; i = i + 1) {
            hpoints = 0;
            hgoals = 0;
            hgd = 0;
            apoints = 0;
            agoals = 0;
            agd = 0;

            homewp = homewin[i];                        // set the home and away win probabilities (Will eventually have program call these numbers from elsewhere)
            awaywp = awaywin[i];
            randwl = rand() % 100;              // Randomize all 3 aspects of game's result
            randgs = rand() % 100;
            randgd = rand() % 100;
            if (randwl < awaywp) {                  // Home loss
                hpoints = 0;
                apoints = 3;
                if (randgs < 18) {                  // Use weighted random # generator to predict winner (Away team) goals scored
                    agoals = 1;
                }
                else if (randgs < 65) {
                    agoals = 2;
                }
                else if (randgs < 88) {
                    agoals = 3;
                }
                else if (randgs < 96) {
                    agoals = 4;
                }
                else if (randgs < 99) {
                    agoals = 5;
                }
                else {
                    agoals = rand() % 4;
                    agoals = agoals + 6;
                }
                if (randgd < 50) {                  // Use weighted random # generator to predict margin of victory/ loser (Home) goals scored
                    hgoals = agoals - 1;
                }
                else if (randgd < 81) {
                    hgoals = agoals - 2;
                }
                else if (randgd < 93) {
                    hgoals = agoals - 3;
                }
                else if (randgd < 97) {
                    hgoals = agoals - 4;
                }
                else {
                    hgoals = agoals - (rand() % 5);
                    hgoals = hgoals - 5;
                }
            }
            else if (randwl < (100 - homewp)) {     // Draw
                hpoints = 1;
                apoints = 1;
                if (randgs < 18) {                  // Use weighted random # generator to predict goals scored
                    agoals = 1;
                }
                else if (randgs < 65) {
                    agoals = 2;
                }
                else if (randgs < 88) {
                    agoals = 3;
                }
                else if (randgs < 96) {
                    agoals = 4;
                }
                else if (randgs < 99) {
                    agoals = 5;
                }
                else {
                    agoals = rand() % 4;
                    agoals = agoals + 6;
                }
                hgoals = agoals;
            }
            else {                                  // Home win
                hpoints = 3;
                apoints = 0;
                if (randgs < 18) {                  // Use weighted random # generator to predict winner (Home team) goals scored
                    hgoals = 1;
                }
                else if (randgs < 65) {
                    hgoals = 2;
                }
                else if (randgs < 88) {
                    hgoals = 3;
                }
                else if (randgs < 96) {
                    hgoals = 4;
                }
                else if (randgs < 99) {
                    hgoals = 5;
                }
                else {
                    hgoals = rand() % 4;
                    hgoals = hgoals + 6;
                }
                if (randgd < 50) {                  // Use weighted random # generator to predict margin of victory/ loser (Away) goals scored
                    agoals = hgoals - 1;
                }
                else if (randgd < 81) {
                    agoals = hgoals - 2;
                }
                else if (randgd < 93) {
                    agoals = hgoals - 3;
                }
                else if (randgd < 97) {
                    agoals = hgoals - 4;
                }
                else {
                    agoals = hgoals - rand() % 5;
                    agoals = agoals - 5;
                }
            }
            if (agoals < 0) {
                agoals = 0;
            }
            if (hgoals < 0) {
                hgoals = 0;
            }

            hgd = hgoals - agoals;
            agd = -hgd;
            points[hometeam[i]] = points[hometeam[i]] + hpoints;
            gd[hometeam[i]] = gd[hometeam[i]] + hgd;
            gf[hometeam[i]] = gf[hometeam[i]] + hgoals;
            played[hometeam[i]] = played[hometeam[i]] + 1;

            points[awayteam[i]] = points[awayteam[i]] + apoints;
            gd[awayteam[i]] = gd[awayteam[i]] + agd;
            gf[awayteam[i]] = gf[awayteam[i]] + agoals;
            played[awayteam[i]] = played[awayteam[i]] + 1;
        }

        //COMPILE FINAL RANKINGS FOR THE TRIAL
    //cout << array[1];
        for (i = 1; i < 21; i = i + 1) {
            for (j = 1; j < 21; j = j + 1) {
                if (points[i] < points[j]) {
                    ranktrack[i] = ranktrack[i] + 1;
                }
            }
        }
        for (i = 1; i < 21; i = i + 1) {
            for (j = 1; j < 21; j = j + 1) {
                if (gd[i] > gd[j]) {
                    ranktrack[i] = ranktrack[i] - .01;
                }
            }
        }
        for (i = 1; i < 21; i = i + 1) {
            for (j = 1; j < 21; j = j + 1) {
                if (gf[i] > gf[j]) {
                    ranktrack[i] = ranktrack[i] - .0001;
                }
            }
        }
        for (i = 1; i < 21; i = i + 1) {
            rank[i] = 1;
            for (j = 1; j < 21; j = j + 1) {
                if (ranktrack[i] > ranktrack[j]) {
                    rank[i] = rank[i] + 1;
                }
            }
        }

        //COMPILE OVERALL RESULTS
        for (i = 1; i < 21; i = i + 1) {
            for (j = 1; j < 21; j = j + 1) {
                if (rank[i] == j) {
                    finish[i][j] = finish[i][j] + 1;
                }
            }
        }
        
        
        for (i = 1; i < 21; i = i + 1) {
            avgPts[i] = (avgPts[i] * a - avgPts[i] + points[i]) / a;
        }

    }
 
    int w = 11;
    float relegation; float euro; float ucl;
    for (i = 1; i < 21; i = i + 1) {
        rank[i] = 1;
        for (j = 1; j < 21; j = j + 1) {
            if (avgPts[i] < avgPts[j]) {
                rank[i] = rank[i] + 1;
            }
        }
    }

    cout << setw(15) << "Team";
    for (b = 20; b > 0; b = b - 1) {
        cout << setw(3) << b;
    }
    cout << endl;
    for (i = 1; i < 21; i = i + 1) {
        cout << setw(15) << array[i];
        for (j = 20; j > 0; j = j - 1) {
            cout << setw(3) << setprecision(0) << fixed << finish[i][j] / nn * 100;
        }
        cout << endl;
    }
    cout << endl << endl << endl << endl;
    int x = w + 5; int y = w + 2; int z = w - 2;
    cout << setw(2) << "Rk" << setw(x) << "Team" << setw(y) << "Relegation" << setw(z) << "Euro" << setw(w) << "UCL" << setw(w) << "Champions" << setw(w) << "Exp Points" << endl;
    for (i = 1; i < 21; i = i + 1) {
        relegation = finish[i][20] + finish[i][19] + finish[i][18];
        euro = finish[i][6] + finish[i][7];
        ucl = finish[i][5]+finish[i][4] + finish[i][3] + finish[i][2] + finish[i][1];
        if (i == 2) {
            euro = 0; 
            ucl = 0;
        }
        cout << setw(2) << setprecision(0) << fixed << rank[i] << setw(x) << setprecision(0) << fixed << array[i] << setw(w) << setprecision(0) << fixed << (relegation) / nn * 100 << setw(w) << setprecision(0) << fixed << (euro) / nn * 100 << setw(w) << setprecision(0) << fixed << (ucl) / nn * 100 << setw(w) << setprecision(0) << fixed << finish[i][1] / nn * 100 << setw(w) << setprecision(0) << fixed << avgPts[i] << endl;
    }
   
    cout << endl << endl << endl << endl << endl;
    cout << "Note: Points totals are shown rounded; if two teams are shown tied on expected points, they may not actually be tied" << endl;
    cout << "These expected rankings do not account for tiebreakers, therefore" << endl;
    cout << "Ensure a large enough number of iterations are run (Recommend 100+) to avoid inaccurate results";
    cout << endl << endl << endl;

    // Games played test sequence: (Should return "38.0.." for each team) 
    /*cout << endl;
    for (i = 1; i < 21; ++i) {
        cout <<setw(15)<< array[i]<<"\t"<<played[i] << endl;
    }
    */
    
    return 0;
}

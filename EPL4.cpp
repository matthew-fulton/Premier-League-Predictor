/*      This Program simulates the remaining English Premier League season n # of times, determining the most likely final standings, point totals,
    as well as the likelihood that each team finishes in each of the 20 possible spots, to find the probability that each team is relegated,
    qualifies for the Euro league, Champions league, or finishes as Champions of the league


                                        Format for finish matrix:    finish[team][position]
*/
#define _USE_MATH_DEFINES

#include <iostream>
#include <iomanip>
#include <cmath>
#include <array>
#include <Bits.h>
#include <random>
#include <fstream>
#include <iomanip>
using namespace std;
double rand_gen() {
    return((double)(rand()) + 1.) / ((double)(RAND_MAX)+1.);
}

double normalRandom() {
    // Return a normally distributed random value
    double v1 = rand_gen();
    double v2 = rand_gen();
    return cos(2 * M_PI * v2) * sqrt(-2. * log(v1));
}
int n = 10000;                        // number of simulations to run
double homefield = 0.2;             // Home field advantage used in calculations

double sigma = 1.0;
double mu = 1.0;
double x = 1.0; double y = 1.0;
double hpg = 1.0; double apg = 1.0; double hxg = 1.0; double axg = 1.0; double hg = 1.0; double ag = 1.0;
int ihg = 1; int iag = 1;
double hpoints; double apoints;
char team[][21] = { " ","Liverpool", "Man.City", "Leicester", "Chelsea", "Man.United", "Wolves", "Tottenham", "Everton", "Sheffield Utd", "Arsenal", "Crystal Palace", "Burnley", "Southampton", "Newcastle", "Brighton", "Watford", "West Ham", "Bournemouth", "Aston Villa", "Norwich" };
double played[21] = { 0, 31, 30, 31, 30, 31, 31, 31, 31, 31, 30, 31, 30, 30, 31, 31, 30, 31, 31, 31, 31 };
double w[21] = { 0, 28, 20, 16, 15, 13, 12, 12, 11, 11, 9, 11, 11, 11, 10, 7, 6, 7, 7, 7, 5 };
double d[21] = { 0, 2, 3, 7, 6, 10, 13, 9, 8, 11, 13, 9, 6, 4, 9, 12, 10, 6, 6, 6, 6 };
double l[21] = { 0, 1, 7, 8, 9, 8, 6, 10, 12, 9, 8, 11, 13, 15, 12, 12, 14, 18, 18, 18, 20 };
double gf[21] = { 0, 70, 76, 59, 53, 48, 44, 50, 38, 30, 41, 28, 34, 38, 29, 34, 28, 35, 29, 36, 25 };
double ga[21] = { 0, 21, 31, 29, 40, 31, 34, 41, 46, 31, 41, 36, 45, 52, 42, 41, 45, 54, 50, 59, 56 };
double gd[21] = { 0, 49, 45, 30, 13, 17, 10, 9, -8, -1, 0, -8, -11, -14, -13, -7, -17, -19, -21, -23, -31 };
double points[21] = { 0, 86, 63, 55, 51, 49, 49, 45, 41, 44, 40, 42, 39, 37, 39, 33, 28, 27, 27, 27, 21 };
double offense[21] = { 0, 2.9, 3.2, 2.1, 2.4, 2.4, 2, 2.2, 2, 1.7, 2.1, 1.7, 1.8, 1.9, 1.6, 1.8, 1.9, 1.9, 1.8, 1.8, 1.6 };
double defense[21] = { 0, 0.2, 0.2, 0.5, 0.5, 0.3, 0.4, 0.7, 0.6, 0.7, 0.7, 0.7, 0.8, 0.8, 0.9, 0.7, 0.7, 1, 1, 1.1, 1 };
int home[74] = { 0, 12, 13, 4, 19, 16, 11, 15, 8, 10, 18, 17, 9, 2, 20, 5, 3, 6, 4, 12, 14, 1, 13, 7, 11, 16, 10, 2, 17, 9, 15, 8, 18, 19, 16, 20, 1, 9, 15, 6, 19, 7, 18, 5, 4, 8, 14, 2, 17, 10, 12, 13, 11, 3, 19, 1, 5, 7, 6, 16, 18, 15, 20, 9, 4, 8, 14, 2, 17, 10, 12, 13, 11, 3 };
int away[74] = { 0, 16, 10, 2, 6, 13, 12, 5, 3, 20, 14, 4, 7, 1, 15, 18, 11, 10, 16, 9, 17, 19, 2, 8, 4, 20, 3, 14, 12, 6, 1, 13, 7, 5, 14, 17, 12, 4, 2, 8, 11, 10, 3, 13, 20, 19, 7, 18, 16, 1, 6, 15, 5, 9, 10, 4, 17, 3, 11, 2, 13, 14, 12, 8, 6, 18, 1, 20, 19, 16, 15, 9, 7, 5 };
double defplayed[21] = { 0, 31, 30, 31, 30, 31, 31, 31, 31, 31, 30, 31, 30, 30, 31, 31, 30, 31, 31, 31, 31 };
double defw[21] = { 0, 28, 20, 16, 15, 13, 12, 12, 11, 11, 9, 11, 11, 11, 10, 7, 6, 7, 7, 7, 5 };
double defd[21] = { 0, 2, 3, 7, 6, 10, 13, 9, 8, 11, 13, 9, 6, 4, 9, 12, 10, 6, 6, 6, 6 };
double defl[21] = { 0, 1, 7, 8, 9, 8, 6, 10, 12, 9, 8, 11, 13, 15, 12, 12, 14, 18, 18, 18, 20 };
double defgf[21] = { 0, 70, 76, 59, 53, 48, 44, 50, 38, 30, 41, 28, 34, 38, 29, 34, 28, 35, 29, 36, 25 };
double defga[21] = { 0, 21, 31, 29, 40, 31, 34, 41, 46, 31, 41, 36, 45, 52, 42, 41, 45, 54, 50, 59, 56 };
double defgd[21] = { 0, 49, 45, 30, 13, 17, 10, 9, -8, -1, 0, -8, -11, -14, -13, -7, -17, -19, -21, -23, -31 };
double defpoints[21] = { 0, 86, 63, 55, 51, 49, 49, 45, 41, 44, 40, 42, 39, 37, 39, 33, 28, 27, 27, 27, 21 };
double defoffense[21] = { 0, 2.9, 3.2, 2.1, 2.4, 2.4, 2, 2.2, 2, 1.7, 2.1, 1.7, 1.8, 1.9, 1.6, 1.8, 1.9, 1.9, 1.8, 1.8, 1.6 };
double defdefense[21] = { 0, 0.2, 0.2, 0.5, 0.5, 0.3, 0.4, 0.7, 0.6, 0.7, 0.7, 0.7, 0.8, 0.8, 0.9, 0.7, 0.7, 1, 1, 1.1, 1 };
long int finish[21][21] = {0 };
double standing[21] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
long int ucl[21] = { 0 };
long int euro[21] = { 0 };
long int relegation[21] = { 0 };
int euroCutoff = 7;
int faHome[7] = { 20,9,3,14,0,0,0 };
int faAway[7] = { 5,10,4,2,0,0,0 };
int faAdv = 0;
double randFAET = 0;
double avgPts[21] = { 0 };
int iavgPts[21] = { 0 };

int main()
{
    for (int simcount = 1; simcount <= n; ++simcount) {               // Outer loop to run the simulation n times
        for (int teamcount = 1; teamcount <= 20; ++teamcount) {
            played[teamcount] = defplayed[teamcount];                   // Reset each variable to default value at beginning of each sim
            w[teamcount] = defw[teamcount];
            d[teamcount] = defd[teamcount];
            l[teamcount] = defl[teamcount];
            gf[teamcount] = defgf[teamcount];
            ga[teamcount] = defga[teamcount];
            gd[teamcount] = defgd[teamcount];
            points[teamcount] = defpoints[teamcount];
            offense[teamcount] = defoffense[teamcount];
            defense[teamcount] = defdefense[teamcount];
        }
        for (int i = 1; i <= 7; ++i) {
            hpg = (offense[faHome[i]] + defense[faAway[i]]) / 2.0;
            apg = (offense[faAway[i]] + defense[faHome[i]]) / 2.0;
            mu = -0.01469;
            sigma = 0.422611;
            x = normalRandom() * sigma + mu;
            hxg = hpg * (x + 1.0);
            if (hxg < 0) {
                hxg = 0.0;
            }
            mu = -0.14541;
            sigma = 0.559399;
            y = normalRandom() * sigma + mu;
            hg = hxg * (y + 1.0);

            mu = 0.101226;
            sigma = 0.631447;
            x = normalRandom() * sigma + mu;
            axg = apg * (x + 1.0);
            if (axg < 0) {
                axg = 0.0;
            }
            mu = -0.22945;
            sigma = 0.624305;
            y = normalRandom() * sigma + mu;
            ag = axg * (y + 1.0);
            if (hg < 0) {
                hg = 0.0;
            }
            if (ag < 0) {
                ag = 0.0;
            }
            ihg = hg + 0.5;               // convert home/away goal variables to integers, using 0.5 to allow proper rounding
            iag = ag + 0.5;
            if (i == 1) {
                ihg = 2;
                iag = 1;
            }
            if (ihg > iag) {
                faAdv = faHome[i];
            }
            if (ihg == iag) {
                randFAET = rand() % 100;
                if (randFAET >= 50) {
                    faAdv = faHome[i];
                }
                else {
                    faAdv = faAway[i];
                }
            }
            if (ihg < iag) {
                faAdv = faAway[i];
            }
            if (i == 1) {
                faHome[5] = faAdv;
            }
            if (i == 2) {
                faAway[5] = faAdv;
            }
            if (i == 3) {
                faHome[6] = faAdv;
            }
            if (i == 4) {
                faAway[6] = faAdv;
            }
            if (i == 5) {
                faHome[7] = faAdv;
            }
            if (i == 6) {
                faAway[7] = faAdv;
            }
        }
        for (int j = 1; j <= 73; ++j) {
            played[home[j]] = played[home[j]] + 1;
            played[away[j]] = played[away[j]] + 1;
            hpg = (offense[home[j]] + defense[away[j]]) / 2.0 + 0.2;            // Calculate predicted goals for each side
            apg = (offense[away[j]] + defense[home[j]]) / 2.0 + 0.2;

            mu = -0.01469;
            sigma = 0.422611;
            x = normalRandom() * sigma + mu;
            hxg = hpg * (x + 1.0);
            if (hxg < 0) {
                hxg = 0.0;
            }
            mu = -0.14541;
            sigma = 0.559399;
            y = normalRandom() * sigma + mu;
            hg = hxg * (y + 1.0);

            mu = 0.101226;
            sigma = 0.631447;
            x = normalRandom() * sigma + mu;
            axg = apg * (x + 1.0);
            if (axg < 0) {
                axg = 0.0;
            }
            mu = -0.22945;
            sigma = 0.624305;
            y = normalRandom() * sigma + mu;
            ag = axg * (y + 1.0);
            if (hg < 0) {
                hg = 0.0;
            }
            if (ag < 0) {
                ag = 0.0;
            }
            ihg = hg + 0.5;               // convert home/away goal variables to integers, using 0.5 to allow proper rounding
            iag = ag + 0.5;
            if (j == 1) {
                ihg = 1;
                iag = 0;
                hxg = 1;
                axg = 0.5;
            }
            if (j == 2) {
                ihg = 0;
                iag = 2;
                hxg = 0.6;
                axg = 1.5;
            }
            if (j == 3) {
                ihg = 2;
                iag = 1;
                hxg = 2.5;
                axg = 1.1;
            }
            if (j == 4) {
                ihg = 0;
                iag = 1;
                hxg = 0.4;
                axg = 0.8;
            }

            if (ihg > iag) {
                hpoints = 3.0;
                apoints = 0.0;
                w[home[j]] = w[home[j]] + 1;
                l[away[j]] = l[away[j]] + 1;
            }
            if (ihg == iag) {
                hpoints = 1.0;
                apoints = 1.0;
                d[home[j]] = d[home[j]] + 1;
                d[away[j]] = d[away[j]] + 1;
            }
            if (ihg < iag) {
                hpoints = 0.0;
                apoints = 3.0;
                l[home[j]] = l[home[j]] + 1;
                w[away[j]] = w[away[j]] + 1;
            }
            points[home[j]] = points[home[j]] + hpoints*1.0;
            points[away[j]] = points[away[j]] + apoints*1.0;
            gf[home[j]] = gf[home[j]] + ihg;
            gf[away[j]] = gf[away[j]] + iag;
            ga[home[j]] = ga[home[j]] + iag;
            ga[away[j]] = ga[away[j]] + ihg;
            gd[home[j]] = gd[home[j]] + ihg - iag;
            gd[away[j]] = gd[away[j]] + iag - ihg;
            offense[home[j]] = (played[home[j]] - 1.0) / (played[home[j]]) * offense[home[j]] + 1.0 / played[home[j]] * (hxg-0.1);
            offense[away[j]] = (played[away[j]] - 1.0) / (played[away[j]]) * offense[away[j]] + 1.0 / played[away[j]] * (axg+0.1);
            defense[home[j]] = (played[home[j]] - 1.0) / (played[home[j]]) * defense[home[j]] + 1.0 / played[home[j]] * (axg+0.1);
            defense[away[j]] = (played[away[j]] - 1.0) / (played[away[j]]) * defense[away[j]] + 1.0 / played[away[j]] * (hxg-0.1);
        }
        // final count
        for (int teamcount = 1; teamcount <= 20; ++teamcount) {
            points[teamcount] = points[teamcount] + gd[teamcount]/100.00+ gf[teamcount]/10000.0;
        }
        for (int i = 1; i <= 20; ++i) {
            standing[i] = 1;
            for (int k = 1; k <= 20; ++k) {
                if (points[i] < points[k]) {
                    standing[i] = standing[i] + 1;
                }
            }

        }
        for (int i = 1; i <= 20; ++i) {
            for (int k = 1; k <= 1; ++k) {
                if (i != k) {
                    if (standing[i] == standing[k]) {
                        standing[k] = standing[k] + 1;     
                        // If 2 teams are still tied after GD & GF tiebreakers, assume team currently ranked better wins the play-off
                    }
                }
            }
        }
        for (int i = 1; i <= 20; ++i) {
            for (int k = 1; k <= 20; ++k) {
                if (k == standing[i]) {
                    finish[i][k] = finish[i][k] + 1;
                }
            }
        }
        if (standing[faAdv] <= 7) {
            euroCutoff = 7;
        }
        else {
            euroCutoff = 6;
        }
        for (int i = 1; i <= 20; ++i) {
            if (standing[i] <= 5 && i != 2) {
                ucl[i] = ucl[i] + 1;
            }
            else if (standing[i] <= euroCutoff && i != 2) {
                euro[i] = euro[i] + 1;
            }
            else if (i == faAdv && i != 2) {
                euro[i] = euro[i] + 1;
            }
            if (standing[i] >= 18) {
                relegation[i] = relegation[i] + 1;
            }
            
            if (simcount == 1) {
                avgPts[i] = points[i];
            }
            else {
                avgPts[i] = points[i] / simcount + avgPts[i] * (simcount - 1.0) / (simcount * 1.0);
            }

        }
    }
    for (int i = 1; i <= 20; ++i) {
        iavgPts[i] = avgPts[i] + 0.5;
    }

    
    cout << setw(15) << "Team" << "\t" << setw(5) << "Champ" << "\t" << "UCL" << "\t" << "Euro" << "\t" << "Relegation" << endl;
    for (int i = 1; i <= 20; ++i) {
        cout << setw(15) << team[i] << "\t"<< setw(5)<< finish[i][1]*100/n<<"\t" << ucl[i]*100/n<<"\t" << euro[i]*100/n<<"\t" << relegation[i]*100/n << "\t" << iavgPts[i]<< endl;
    }
    
    // Print a table showing each team's percent of finishes at each position
    /*
    for (int i = 1; i <= 20; ++i) {
        cout << i << " ";
        }
     cout << endl;
    for (int i = 1; i <= 20; ++i) {
        cout << team[i];
        for (int k = 1; k <= 20; ++k) {
            cout << finish[i][k]*1.0/n*100 << " ";
        }
        cout << endl;
    }
    */
    
 



    // Code to Print values to new Excel file
    /* ofstream outData;
    outData.open("outfile.csv", ios::app);
    for (int i = 1; i <= 10000; ++i) {
        x = normalRandom() * sigma + mu;
        outData << x << endl;
    }
    */
    return 0;
}

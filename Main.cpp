#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <ctime>
#include <numeric>
#include <math.h>

using namespace std;

class Team
{
public:
    string name;
    int points;
    int offenseOverall;
    int defenseOverall;
    int runFrequency;
    int passFrequency;

    Team(string name, int offenseOverall, int defenseOverall, int runFrequency, int passFrequency)
    {
        this->name = name;
        this->points = points;
        this->offenseOverall = offenseOverall;
        this->defenseOverall = defenseOverall;
        this->runFrequency = runFrequency;
        this->passFrequency = passFrequency;
    }

    int OffensivePlay()
    {
        return rand() % 50 + this->offenseOverall;
    }

    int DefensivePlay()
    {
        return rand() % 50 + this->defenseOverall;
    }

    bool PlayType()
    {
        return (rand() % 100) < runFrequency;
    }
};

static void DriveResult(Team &teamA, Team &teamB)
{
    // Offense>Defense gains yards, opposite loses yards, equal numbers means 0 yards.
    int teamAOffense = teamA.OffensivePlay();
    int teamBDefense = teamB.DefensivePlay();
    int yardsGainedOnPlay;
    int yardsGainedOnDowns = 0;
    int yardsGainedOnDrive = 0;
    int down = 1;
    bool playType;

    do
    {
        playType = (rand() % 100) < teamA.runFrequency;

        if (playType == true)
        {
            yardsGainedOnPlay = (rand() % 15) - 2;
        }
        else
        {
            yardsGainedOnPlay = (rand() % 25) - 8;
        }

        yardsGainedOnDowns += yardsGainedOnPlay;
        yardsGainedOnDrive = yardsGainedOnDrive + yardsGainedOnPlay;

        if (playType == true)
        {
            cout << "The " << teamA.name.c_str() << " run for " << yardsGainedOnPlay << " yards.\n";
        }
        else
        {
            cout << "The " << teamA.name.c_str() << " pass for " << yardsGainedOnPlay << " yards.\n";
        }

        down++;

        if ((yardsGainedOnDowns >= 10) && (yardsGainedOnDrive < 24))
        {
            //cout << "First down " << teamA.name.c_str() << "!\n";
            down = 1;
            yardsGainedOnDowns = 0;
        }

        if ((down == 4) && (teamA.points >= teamB.points))
        {
            cout << "Field goal " << teamA.name.c_str() << "!\n";
            teamA.points += 3;
        }

        if (yardsGainedOnDrive >= 25)
        {
            cout << "Touchdown " << teamA.name.c_str() << "!\n";
            teamA.points += 7;
        }

    } while ((yardsGainedOnDrive < 25) && (down != 4));

    int main()
    {
        srand(time(NULL));

        Team lsu("Tigers", 90, 90, 50, 50);
        Team alabama("Crimson Tide", 90, 90, 80, 20);

        lsu.points = 0;
        alabama.points = 0;

        do
        {
            DriveResult(lsu, alabama);
            DriveResult(alabama, lsu);
        } while (lsu.points == alabama.points);

        if (lsu.points > alabama.points)
        {
            cout << "\nTigers win!\n";
        }
        else
        {
            cout << "\nCrimson Tide win!\n";
        }

        cout << '\n';
        cout << "Final Score: \n";
        cout << "LSU " << lsu.points << endl;
        cout << "Alabama " << alabama.points;

        return 0;
    }
#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

void PopulateLists(vector<uint> &leftList, vector<uint> &rightList);
uint GetAndPopMinValue(vector<uint> &list);
ulong GetSimilarityScore(uint number, vector<uint> &rightList);

int main()
{
    ulong totalDistance = 0;
    ulong similarityScore = 0;

    vector<uint> leftList = vector<uint>(1000);
    vector<uint> rightList = vector<uint>(1000);

    PopulateLists(leftList, rightList);

    // Part 2
    for (int i = 0; i < 1000; i++)
    {
        similarityScore += GetSimilarityScore(leftList.at(i), rightList);
    }

    // Part 1
    while (leftList.size() > 0 && rightList.size() > 0)
    {
        uint minLeft = GetAndPopMinValue(leftList);
        uint minRight = GetAndPopMinValue(rightList);

        totalDistance += abs((int)(minLeft - minRight));
    }

    cout << "Total Distance (Part 1): " << totalDistance << endl;
    cout << "Similarity Score (Part 2): " << similarityScore << endl;
}

void PopulateLists(vector<uint> &leftList, vector<uint> &rightList)
{
    fstream inputFile = fstream("input.txt");

    string line;
    for (int i = 0; i < 1000; i++)
    {
        getline(inputFile, line);

        uint addToLeft = stoi(line.substr(0, 5));
        uint addToRight = stoi(line.substr(8, 5));

        leftList.at(i) = addToLeft;
        rightList.at(i) = addToRight;
    }
}

uint GetAndPopMinValue(vector<uint> &list)
{
    uint minValueIndex = 0;
    uint minValue = list.at(minValueIndex);

    // Find min value and the index of the min value
    uint listLength = list.size();
    for (int i = 0; i < listLength; i++)
    {
        if (list.at(i) < minValue)
        {
            minValueIndex = i;
            minValue = list.at(i);
        }
    }

    // Put the element at the end so it can be poped out of the list
    list.at(minValueIndex) = list.at(listLength - 1);
    list.pop_back();

    return minValue;
}

ulong GetSimilarityScore(uint number, vector<uint> &rightList)
{
    uint length = rightList.size();
    uint occurencesOfNumInRightList = 0;

    for (int i = 0; i < length; i++)
    {
        if (number == rightList.at(i))
            occurencesOfNumInRightList++;
    }

    return number * occurencesOfNumInRightList;
}
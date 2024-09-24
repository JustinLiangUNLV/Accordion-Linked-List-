#include "LL.h"
#include "LL.cpp"
#include "myStack.h"
#include "myStack.cpp"
#include <iostream>
#include <string>
using namespace std;

int main() 
{
	// reading in the cards
    LL<myStack<string>> accordian; // create a LL called accordian
    string card; // create a temp string variable for each card
    while (cin >> card) // read each string into a string variable called card
    {
        myStack<string> tempStack; // create a temporary stack
        tempStack.push(card); // push the read values into the temp stack
        accordian.tailInsert(tempStack); // populate the LL with stacks of cards, should be 52
    }

    LL<myStack<string>>::iterator it; // create an iterator
    // debugging code to see if all the cards are read in correctly
    // for(it = accordian.begin(); it != accordian.end(); it++)
    // {
    //     cout << (*it).peek() << " ";
    // }
    // cout << endl;

    // game logic
    bool cardHasMoved = true; // initialize cardHasMoved to true, start the loop
    while (cardHasMoved) 
    {
        cardHasMoved = false; // then set it to false so that we can test if it actually moved or not
        for (it = accordian.begin(); it != accordian.end(); it++) // iterate through linked list
        {
            LL<myStack<string>>::iterator j = it; // create an iterator called j and give it the value of (it)
            LL<myStack<string>>::iterator i = it; // create another iterator called i and give it the value of (it)
            bool checkThird = false; // variable to check the third card, because it is given priorty first. if checkThrid is false then we move to comparing first neighbor
            int stepsOver = 0; // create a counter to see how many steps j has taken
            for(int k = 0; k < 3; k++) // create a for loop that loops three times
            {
                if(j != accordian.begin()) // while j is not at the beginning
                {
                    j--; // decrement j three positions
                    stepsOver++; // increment the number of steps in case, j hasn't done more or less than 3
                    // to simulate j-- 3 times in the pdf
                }
            }
            if (stepsOver == 3 && ((*i).peek()[0] == (*j).peek()[0] || (*i).peek()[1] == (*j).peek()[1]))  // compares i and j which is now three steps over
            // compares if they have the same face or suit
            {
                (*j).push((*i).pop()); // push into the stack of j if the comparison is true, moved from i
                if ((*i).isEmpty()) // if the stack of cards is empty
                {
                    accordian.removeAtPosition(i); // remove that stack from the accordian, thus removing how many stack of cards there are
                }
                i = accordian.begin(); // set i to point to the beginning of the linked list
                cardHasMoved = true; // set the cardHasMoved to equal to true
                checkThird = true; // set that the third comparison was true
            }
            if (!checkThird) // if checkThird is false, meaning three steps over didn't compare then...
            {
                j = i; // set j back to i
                if (i != accordian.begin())  // as long as it is not at the beginning
                {
                    j--; // set j to be one neighbor over to the left
                    if ((*i).peek()[0] == (*j).peek()[0] || (*i).peek()[1] == (*j).peek()[1]) // compare if the first neighbor over matches in same face or suit
                    {
                        (*j).push((*i).pop()); // if it is, then put that i card into the j stack
                        if ((*i).isEmpty())  // if it is pointing to nothing, meaning the stack is not there
                        {
                            accordian.removeAtPosition(i); // remove the stack
                        }
                        i = accordian.begin(); // set it back the front
                        cardHasMoved = true; // set cardHasMoved to true
                    }
                }
            }
            if (cardHasMoved) // if card moved all the way to left
            {
                break;
            }
        }
    }

    // outputting
    int stacksOfCards = 0; // create a variable for how stacks there are
    for (it = accordian.begin(); it != accordian.end(); it++) // iterate through accordian
    {
        stacksOfCards++; // just sees how many stacks of cards have been created and store that amount to a variable
    }
    cout << stacksOfCards << " Stacks: "; // cout how many stacks of cards there are
    for (it = accordian.begin(); it != accordian.end(); it++)  // iterate through the accordian again
    {
        cout << (*it).peek() << ":" << (*it).getSize() << " "; //output the top card and how many cards are within that stack of cards
    }
    cout << endl;
    return 0;
}
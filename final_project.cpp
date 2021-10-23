/*
When the user selects the request tickets menu option, the program should prompt for the
number of seats the patron wants. A function should then be called and passed this
information so that it can handle the ticket request. If any of the requested seats do not
exist, or are not available, an appropriate message should be displayed. If the seats exist
and are available, a bill should be printed that lists the number of requested seats, the price
per seat in the requested row, and the total price for the seats. Then the user program
should ask if the patron wishes to purchase these seats.
*/



#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;



const int ROW = 15,                    // number of rows
COL = 30;                            // number of seats per row



// function prototypes
void displayMenu();
void displaySeat(char [ROW][COL]);
void fileToArray(char[ROW][COL]);        // function to read SeatAvailability.txt into an array
void writeToFile(char[ROW][COL]);                // write array into SeatAvailability.txt
void priceDisplay();                        // price display function
void requestTicket(char[ROW][COL]);                    // purchase ticket function
void salesReport();


int main()
{
    int user_choice = 0;                 // initializing user input

    char seatAvailability[ROW][COL];            // array to hold SeatAvailability file and edit,

    // getting user choice
    while(user_choice != 5)
    {
        displayMenu();

        cout << "Your option choice : ";
        cin >> user_choice;

    // user input validation
    while(user_choice > 5 || user_choice < 1)
    {
        cout << "The program only accepts 1 to 5." << endl;
        cout << "Please try again.." << endl;
        cout << "Your option choice : ";
        cin >> user_choice;
    }


    if(user_choice == 1)
    {

        //writeToFile(newShow);
        fileToArray(seatAvailability);
        displaySeat(seatAvailability);


    }
    else if(user_choice == 2)
    {
        priceDisplay();
    }
    else if(user_choice == 3)
    {
        requestTicket(seatAvailability);
    }
    else if(user_choice == 4)
    {
        salesReport();
    }

    }// while loop ends

    return 0;

} // int main() ends

void displayMenu()
{
    //menu details
    cout << "\t\tTheater ticket system\n\n";
    cout << "1. Seating Chart.\n";
    cout << "2. Ticket Price for each row.\n";
    cout << "3. Purchase ticket.\n";
    cout << "4. View total price for ticket purchased.\n";
    cout << "5. Exit Program.\n\n";
}

// void function for formatted output
void displaySeat(char array[][COL])
{
    cout  << "# = Open Seat\n" << "* = Reserved Seat\n";
    cout  << "Seats:  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30\n" ;

        for (int x = 0; x < ROW; x++)
        {

            cout  << "Row " << setfill('0') << setw(2) << (x+1) << "  ";

          for (int y = 0; y < COL; y++)
          {
              cout << array[x][y] << "  ";
          }
          cout << endl;
        }
}

// read in SeatAvailability.txt to an array array function
void fileToArray(char seats[ROW][COL])
{
    // open file to read from
    ifstream seatsIn;
    seatsIn.open("SeatAvailability.txt");

    if(seatsIn.fail())
    {
        cout << "Error opening file. " << endl;

    }
    else
    {
        for (int row = 0; row < ROW; row++)
        {
            for (int column = 0; column < COL; column++)
            {
                seats[row][column] = '#';
                seatsIn >> seats[row][column];
            }
        }
    }
    // close file
    seatsIn.close();
}


// write array back to SeatAvailabiltiy. txt funcion
void writeToFile(char seats[ROW][COL])
{
    // open file to write to
    ofstream seatsOut;
    seatsOut.open("SeatAvailability.txt");

    // write array to file
    // by row
    for (int i = 0; i < ROW; i++)
    {
        // by column
        for (int j = 0; j < COL; j++)
        {
            seatsOut << seats[i][j];
        }
        // put each row on it's own line
        seatsOut << endl;
    }

    // close file
    seatsOut.close();

}

// purchase ticket function
/*
Requirements from Final Project PDF:
When the user selects the request tickets menu option, the program should prompt for the
number of seats the patron wants. A function should then be called and passed this
information so that it can handle the ticket request. If any of the requested seats do not
exist, or are not available, an appropriate message should be displayed. If the seats exist
and are available, a bill should be printed that lists the number of requested seats, the price
per seat in the requested row, and the total price for the seats. Then the user program
should ask if the patron wishes to purchase these seats.
*/
void requestTicket(char seatAvailability[ROW][COL])
{
    int ticket;
    double total = 0.0;
    char copy[ROW][COL];
    fileToArray(copy);
    //ask number of tickets are going to purchase
    do{
        cout << "Enter the number of ticket you would like to purchase: ";
        cin >> ticket;
        //print out invalidation
        while(ticket <= 0 || ticket > 450)
        {
            cout << "Invalid number of tickets... please try again: ";
            cin >> ticket;
        }
    }while(ticket <= 0 || ticket > 450);//validation

    //ask for each ticket for different seats and rows
    for(int time = 1; time <= ticket; time++)
    {
        int row, seat;
        bool avail = false;
        double price = 20.00;


        do{
            do{
                cout << "Enter the row number for the ticket " << time << ": ";    //row
                cin >> row;
                //validation
                while(row > 15 || row <= 0)
                {
                    cout << "Invalid information, Try again: ";
                    cin >> row;
                }

                cout << "Enter the seat number for the ticket " << time << ": ";   //seat
                cin >> seat;
                while(seat > 30 || seat <= 0)
                {
                    cout << "Invalid information, Try again: ";
                    cin >> seat;
                }
            }while(row > 15 || row <= 0 || seat > 30 || seat <= 0);

            //read file
            fileToArray(seatAvailability);

            //check the availbility of original file
            if(seatAvailability[row-1][seat-1] == '#'){//seat available
                avail = true;
                copy[row-1][seat-1] = '*';

            }else{
                cout << "The seat is no longer available, please try again: ";
            }
        }while(avail == false);

        //cal. price for that one row(ticket)
        for (int i = 1; i < row; i++)
        price += 10;

        // display seat information
        cout << endl << fixed << showpoint << setprecision(2);
        cout << "Row " << row << " price per seat: $" << price << endl;
        //total price
        total += price;


    }                                                           //end of for loop
    cout << endl << fixed << showpoint << setprecision(2);
    cout << "Number of seats requested: " << ticket << endl;
    cout << "Total price for all tickets: " << total << endl;

    char purchase; // character input for customer to purchase tickets
    do
    { // user input and validation

        cout << "Would you like to purchase these tickets (Y/N)? ";
        cin >> purchase;
        purchase = toupper(purchase);
        // error message
        if (purchase != 'Y' && purchase != 'N')
            cout << "Error. Invalid input." << endl;
    } while (purchase != 'Y' && purchase != 'N');


    // process request
    // purchase tickets
    if(purchase == 'Y'){
        writeToFile(copy);
    }


    cout << "Seat Reserved." << endl << endl << endl;

}


// price function (increase by $ 10 for each row)
void priceDisplay()
{
    double ticket = 20.0;
    cout << "\n******* Ticket price chart *******" << endl;
    for (int i = 0; i < 15; i++)
    {
        cout << "\tRow " << setfill('0') << setw(2) << i + 1 << " : $ ";
        cout << ticket << "\n";                    // constant price declared at the top
        ticket += 10;

    }
}

void salesReport() {
    ifstream seatsIn;
    seatsIn.open("SeatAvailability.txt");
    if(seatsIn.fail())
    {
        cout << "Error opening file. " << endl;
    }
    else
    {
        char seats[ROW][COL];
        //read file
        ifstream seatsIn;
        seatsIn.open("SeatAvailability.txt");       //open the file
        if (seatsIn.fail())                         //validation
        {
            cout << "Error openeing file. " << endl;
        }else{
            for (int row=0; row < ROW; row++){
                for (int column=0; column < COL; column++){
                    seatsIn >> seats[row][column]; //store the file information to "seats" array
                }
            }
        }
        int sold_counter = 0;
        int money_count = 0;
        for (int row=0; row < ROW; row++) {             //count the price
            for (int column = 0; column < COL; column++){
                if (seats[row][column] == '*'){
                    sold_counter+=1;
                    money_count += ((row)*10)+20;
                }
            }
        }
        //display the information(sold seat, empty seat, total so far)
        cout << "Seats sold: " << sold_counter << endl;
        cout << "Empty Seat: " << 450-sold_counter << endl;
        cout << "Total gain: " << money_count << endl << endl << endl;
    }
}

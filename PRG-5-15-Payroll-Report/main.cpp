//
//  main.cpp
//  PRG-5-15-Payroll-Report
//
//  Created by Keith Smith on 10/7/17.
//  Copyright © 2017 Keith Smith. All rights reserved.
//
//
//  Write a program that displays a weekly payroll report. A loop in the program should
//  ask the user for the employee number, gross pay, state tax, federal tax, and FICA withholdings.
//  The loop will terminate when 0 is entered for the employee number. After the
//  data is entered, the program should display totals for gross pay, state tax, federal tax,
//  FICA withholdings, and net pay.
//
//  Input Validation: Do not accept negative numbers for any of the items entered. Do
//  not accept values for state, federal, or FICA withholdings that are greater than the
//  gross pay. If they sum of state tax + federal tax + FICA withholdings for any employee
//  is greater than gross pay, print an error message and ask the user to reenter the data
//  for that employee.

#include <iostream>
#include <iomanip>

using namespace std;

int main()
{
    int intEmployeeNumber = 999999, // Initialize
        intEmployeeNumberLast; // Set default to minimum employee identification number
    
    float fltPayGross,
          fltFICAWithholdings,
          fltPayNet,
          fltTaxStateDollar,
          fltTaxFederalDollar,
          fltRunningTotal = 0.0f; // Initialize counter
    
    // Used to prevent user from exiting the program before entering a single employee's data
    bool booHasRunOnce = false;
    
    //Set decimal and configure number output for dollar display ($0.00)
    cout << setprecision(2) << fixed << showpoint;
    
    //Whole loop ends when 0 is entered for employee number
    while(intEmployeeNumber != 0)
    {
        cout << "Please enter your employee's identification number:\n";
        cin >> intEmployeeNumber;
        
        //Determines if program has run once or not, if it hasn't,
        //it forces the user to enter information (run at least once)
        if(intEmployeeNumber == 0 && booHasRunOnce == true)
        {
            break;
        }
        else if(intEmployeeNumber == 0 && booHasRunOnce == false)
        {
            while(intEmployeeNumber == 0)
            {
                cout << "You must enter at least one employee's data,\n"
                     << "please enter an employee identification number.\n";
                cin >> intEmployeeNumber;
            }
        }
        
        //After having run, this checks to make sure that
        //duplicate information isn't being entered.
        //Compares this employee number to the last one
        while(intEmployeeNumberLast == intEmployeeNumber)
        {
            cout << "You have just entered that employee's information,\n"
                 << "please enter a new employee ID number:\n";
            cin >> intEmployeeNumber;
        }
        
        while(intEmployeeNumber < 100000 || intEmployeeNumber > 999999)
        {
            cout << "Please enter a valid 6-digit employee identification number.\n";
            cin >> intEmployeeNumber;
            // Catches first time through entering 0 and trying to quit
            if(intEmployeeNumber == 0 && booHasRunOnce == true)
            {
                cout << "You have terminated the program.\n";
                return 0;
            }
            // C
            else if(intEmployeeNumber == 0 && booHasRunOnce == false)
            {
                cout << "You must enter at least one employee's data.\n";
            }
        }
        
        //Begin: Enter Gross Pay
        cout << "Please enter the employee's gross pay, in dollars:\n";
        cin >> fltPayGross;
        
        //Ensure Gross Pay is a positive value
        while(fltPayGross <= 0.0f)
        {
            cout << "Please enter a value greater than $0.01:\n";
            cin >> fltPayGross;
        }
        //End: Enter Gross Pay
        
        
        //Begin: State Tax Amount and Check
        cout << "Please enter the state tax amount in dollars:\n";
        cin >> fltTaxStateDollar;
        
        while(fltTaxStateDollar < 0.0f || fltTaxStateDollar >= fltPayGross)
        {
            cout << "Please enter a dollar amount \n"
                 << "greater than or equal to $0.00 and less than gross pay:\n";
            cin >> fltTaxStateDollar;
        }
        //End: State Tax Amount and Check
        
        //Begin use of running total as check against gross pay
        fltRunningTotal += fltTaxStateDollar;
        
        //Begin: Federal Tax Amount and Check
        cout << "Please enter the federal tax amount in dollars:\n";
        cin >> fltTaxFederalDollar;
        
        //Add federal tax to running total (just state tax at this point)
        //For comparison against gross pay
        fltRunningTotal += fltTaxFederalDollar;
        
        while(fltTaxFederalDollar < 0.0f || fltRunningTotal > fltPayGross)
        {
            fltRunningTotal -= fltTaxFederalDollar;
            
            cout << "Please enter a dollar amount \n"
                 << "less than gross pay, less than state tax plus federal tax \n"
                 << "and an amount greater than or equal to $0.00\n";
            cin >> fltTaxFederalDollar;
            
            fltRunningTotal += fltTaxFederalDollar;
        }
        //End: Federal Tax Amount and Check
        
        
        //Begin: FICA Withholdings Amount and Check
        cout << "Please enter the employee's FICA Withholdings:\n";
        cin >> fltFICAWithholdings;
        
        fltRunningTotal += fltFICAWithholdings;
        
        while(fltFICAWithholdings < 0.0f || fltRunningTotal > fltPayGross)
        {
            fltRunningTotal -= fltFICAWithholdings;
            
            cout << "Please enter a dollar amount \n"
                 << "less than gross pay, an amount that does not push the \n"
                 << "running total over gross pay, and an amount greater than or equal to $0.00:\n";
            cin >> fltFICAWithholdings;
            
            fltRunningTotal += fltFICAWithholdings;
        }
        //End: FICA Withholdings Amount and Check
        
        
        //Having passed all the data validation and checks,
        //Net pay is simply calculated by subtracting the running total
        //(now state tax + federal tax + fica withholdings)
        fltPayNet = fltPayGross - fltRunningTotal;
        
        
        //Display information entered in formatted fashion
        cout << setw(35) << "For employee  #" << intEmployeeNumber << endl
             << setw(35) <<  "With gross pay: $" << fltPayGross << endl
             << setw(35) <<  "And state tax withholdings of: $" << fltTaxStateDollar << endl
             << setw(35) <<  "And federal tax withholdings of: $" << fltTaxFederalDollar << endl
             << setw(35) <<  "And FICA withholdings of: $" << fltFICAWithholdings << endl
             << setw(35) <<  "Their total withholdings is: $" << fltRunningTotal << endl
             << setw(35) <<  "And their net pay is: $" << fltPayNet << endl << endl;
        
        //Set that this program has run at least one time
        //So user can enter 0 for employee ID number and exit
        booHasRunOnce = true;
        
        //Set this variable to current employee id number
        //To check when this loops back to the beginning
        //To prevent the same number from being entered two times in a row.
        intEmployeeNumberLast = intEmployeeNumber;
        
        //Prompt user for data entry which will be at beginning of the loop
        cout << "Please enter another employee ID number,\n"
             << "enter 0 to quit.\n";
    }
    
    cout << "You have terminated the program.\n";
    
    return 0;
}




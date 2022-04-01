/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package sorter;

import java.io.IOException;
import java.util.*;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author Jesse
 */

/** This menu is used for handling the menu and using MenuFunctions for their 
 *  needs.
 */
public class Menu {
    
    public void intro() {
        System.out.println("Welcome to The Indexer.");
        System.out.println("What do you want to do today?");
        System.out.println("1. Add an entry.\n2. Display current file list."
                + "\n3. Display specific entry."
                + "\n4. Find based off of starting alphabet."
                + "\n5. Find by year or season."
                + "\n6. Sort your text file."
                + "\n7. Delete an entry."
                + "\n8. Edit an entry."
                + "\n9. Change file."
                + "\n10. Exit\n");
    }

    public void menu() {
        boolean token = true;
        String fileName = "anime_index.txt";
        // Token is used to check for overall input validity.  
        while (token) {
            intro();
            System.out.println("Your current file that you are working"
                    + " with is: " + fileName + "\n");
            try {
                String choiceNum;
                int actualNum = -1;
                boolean inputCheck = false;
                
                // Checks for input being an integer.
                while (!inputCheck) {
                    System.out.println("Please enter a number of choice.");
                    Scanner userInput = new Scanner(System.in);
                    choiceNum = userInput.next();
                    try {
                        actualNum = Integer.parseInt(choiceNum);
                        inputCheck = true;
                    } catch(NumberFormatException e){
                        System.out.println("Error: Input is not of number value.");
                    }
                }
                
                // Switch case for different functions 
                switch (actualNum) {
                    case 1:
                        //Add_list
                        MenuFunctions.add_entry(fileName);
                        break;
                    case 2:
                        MenuFunctions.display_list(fileName);
                        break;
                    case 3:
                        MenuFunctions.display_list_spec(fileName);
                        break;
                    case 4:
                        MenuFunctions.display_list_start(fileName);
                        break;
                    case 5:
                        MenuFunctions.find_by_seasonOrYear(fileName);
                        break;
                    case 6:
                        String userInput;
                        int input = -1;
                        boolean stringCheck = false;
                        boolean numberCheck = false;
                        System.out.println("Please choose what you want to"
                                + " sort by. Input the number.\n"
                                + "1 for names\n"
                                + "2 for seasons\n"
                                + "3 for years.");
                        
                        // Used to check the number input 
                        while (!stringCheck || !numberCheck) {
                            Scanner sortInput = new Scanner(System.in);
                            userInput = sortInput.next();
                            try {
                                input = Integer.parseInt(userInput);
                                stringCheck = true;
                            } catch(NumberFormatException e){
                                System.out.println("Error: Input is not of number value."
                                        + " Please enter a number of choice.");
                            }
                            if (input != 1 && input != 2 && input != 3) {
                                System.out.println("Error: Please only input 1, 2"
                                        + " or 3.");
                            } else {
                                numberCheck = true;
                            }
                        }
                        MenuFunctions.sort_functions(fileName, input);
                        break;
                    case 7:
                        MenuFunctions.delete_entry(fileName);
                        break;
                    case 8:
                        MenuFunctions.change_entry(fileName);
                        break;
                    case 9:
                        fileName = MenuFunctions.change_file(fileName);
                        break;
                    case 10:
                        token = false;
                        System.out.println("Exiting.");
                        break;
                    default:
                        System.out.println("Error: Invalid input. You entered a number"
                                + " that was not listed.\n");
                } 
            } catch (IOException ex) {
                Logger.getLogger(Menu.class.getName()).log(Level.SEVERE, null, ex);
            }
        }
    }
}

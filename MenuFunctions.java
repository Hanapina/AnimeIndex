/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package sorter;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.nio.charset.Charset;
import java.nio.file.Files;
import java.util.*;
import java.util.stream.Collectors;
/**
 *
 * @author Jesse
 */
public class MenuFunctions {
    
    /**
     * This method is used to extract fields from a formatted text file and 
     * generates a list from it.
     * 
     * @param fileName
     * @return A list of created objects
     * @throws FileNotFoundException
     * @throws IOException 
     */
    public static List<Entry> extract_file(String fileName) throws FileNotFoundException, IOException{
        // Entry Stuff
        File file = new File(fileName);
        List<String> list = new ArrayList<>();
        List<Entry> entryList = new ArrayList<>();
        
        // Check if file exists or not, if so read it all, otherwise create it for you.
        if (file.exists()) {
            list = Files.readAllLines(file.toPath(), Charset.defaultCharset());
        } else if(file.createNewFile()) {
            System.out.println("Error: File did not exist. Creating the file.\n");
            return entryList;
        }
        
        // Creates the array list. 
        for (String line: list) {
            String[] lineSplit = line.split(", ");
            int numToString = Integer.parseInt(lineSplit[2]);
            Entry item = new Entry(lineSplit[0], lineSplit[1], numToString);
            entryList.add(item);
        }
        return entryList;
    }
    
    /**
     * This method is created solely to write a list into a file
     * It is extended from the method "add_list"
     * 
     * @param fileName 
     * @param list 
     * @throws IOException 
     */
    public static void write_file(String fileName, List<Entry> list) throws IOException {
        // Creates each string in format: name, season, year
        FileWriter fw = new FileWriter(fileName, false);
        PrintWriter fwStream = new PrintWriter(fw);
        for (Entry entry : list) {
            fwStream.println(entry.getName() + ", " + entry.getSeason() + ", " +
                    entry.getYear());
        }
        fwStream.close();
    }
    
    /**
     * Method made to display a text file.
     * 
     * @param fileName
     * @throws FileNotFoundException
     * @throws IOException 
     */
    public static void display_list(String fileName) throws FileNotFoundException, IOException {
        // Entry stuff
        List<Entry> entryList = new ArrayList<Entry>();
        entryList = extract_file(fileName);
        if (entryList.isEmpty()) {
            return;
        }
        
        // Formatting text + print statements + uses streams to print each object
        help_print(entryList);
    }
    
    /**
     * Function to handle specific entry finding
     * @param fileName
     * @throws FileNotFoundException
     * @throws IOException 
     */
    public static void display_list_spec(String fileName) throws FileNotFoundException, IOException {
        // Entry stuff
        List<Entry> entryList = new ArrayList<Entry>();
        List<Entry> resultList = new ArrayList<Entry>();
        entryList = extract_file(fileName);
        if (entryList.isEmpty()) {
            return;
        }
        
        // Formatting text + print statements + uses streams to print each object
        System.out.println("What entry do you want to look for?");
        Scanner userInput = new Scanner(System.in);
        String stringInput = userInput.nextLine();
        System.out.println("Matching...\n");
        for (Entry entry: entryList) {
            if (stringInput.equals(entry.getName()) || entry.getName().contains(stringInput)) {
                resultList.add(entry);
            }
        }
        
        // Returns if the list itself is empty as nothing was found
        if (resultList.isEmpty()) {
            System.out.println("Name entered does not exist. Returning to menu.\n");
            return;
        }
        
        help_print(resultList);
    }
    
    /**
     * Function to find stuff to start
     * @param fileName
     * @throws FileNotFoundException
     * @throws IOException 
     */
    public static void display_list_start(String fileName) throws FileNotFoundException, IOException {
        // Entry stuff
        List<Entry> entryList = new ArrayList<Entry>();
        List<Entry> resultList = new ArrayList<Entry>();
        entryList = extract_file(fileName);
        if (entryList.isEmpty()) {
            return;
        }
        
        // Formatting text + print statements + uses streams to print each object
        System.out.println("What letters do you want to start with?");
        Scanner userInput = new Scanner(System.in);
        String stringInput = userInput.nextLine();
        System.out.println("Finding...\n");
        for (Entry entry: entryList) {
            if (entry.getName().startsWith(stringInput)) {
                resultList.add(entry);
            }
        }
        
        // Returns if the list itself is empty as nothing was found
        if (resultList.isEmpty()) {
            System.out.println("String entered does not exist. Returning to menu.\n");
            return;
        }
        
        help_print(resultList);
    }
    
    /**
     * Main function to control a find function by season or year
     * @param fileName
     * @throws IOException 
     */
    public static void find_by_seasonOrYear(String fileName) throws IOException {
        List<Entry> entryList = new ArrayList<Entry>();
        List<Entry> resultList = new ArrayList<Entry>();
        entryList = extract_file(fileName);
        if (entryList.isEmpty()) {
            return;
        }
        
        // Handling input error
        String userInput;
        int input = -1;
        boolean stringCheck = false;
        boolean numberCheck = false;
        System.out.println("Please choose what you want to"
                + " sort by. Input the number."
                + "\n1 for seasons"
                + "\n2 for years.");

        // Used to check the number input 
        while (!stringCheck || !numberCheck) {
            Scanner sortInput = new Scanner(System.in);
            userInput = sortInput.next();
            try {
                input = Integer.parseInt(userInput);
                stringCheck = true;
            } catch (NumberFormatException e) {
                System.out.println("Error: Input is not of number value."
                        + " Please enter a number of choice.");
            }
            if (input != 1 && input != 2) {
                System.out.println("Error: Please only input 1, 2");
            } else {
                numberCheck = true;
            }
        }
        
        // Case for either season or year
        switch(input) {
            case 1:
                resultList = find_season(entryList);
                if (resultList.isEmpty()) {
                    System.out.println("Error: Season not found\n");
                    return;
                }
                break;
            case 2:
                resultList = find_year(entryList);
                if (resultList.isEmpty()) {
                    System.out.println("Error: Year not found\n");
                    return;
                }
                break;
            default:
                System.out.println("Error: Only input 1 and 2 please.");
                break;
        }
        
        help_print(resultList);
    }
    
    /**
     * Function for handling years
     * @param list
     * @return 
     */
    public static List<Entry> find_year(List<Entry> list) {
        List<Entry> resultList = new ArrayList<Entry>();
        System.out.println("\nEnter a year.");
        String userInput;
        int input = -1;
        boolean stringCheck = false;
        
        // Used to check to make sure the user input is a number.
        while (!stringCheck) {
            Scanner sortInput = new Scanner(System.in);
            userInput = sortInput.next();
            try {
                input = Integer.parseInt(userInput);
                stringCheck = true;
            } catch (NumberFormatException e) {
                System.out.println("Error: Input is not of number value."
                        + " Please enter a year.");
            }
        }
        
        for (Entry entry: list) {
            if (input == entry.getYear()) {
                resultList.add(entry);
            }
        }
        return resultList;
    }
    
    // Function to find seasons. 
    public static List<Entry> find_season(List<Entry> list) {
        List<Entry> resultList = new ArrayList<Entry>();
        System.out.println("\nEnter your season.");
        String userInput = null;
        boolean stringCheck = false;
        
        // String checking via to lower case.
        while (!stringCheck) {
            Scanner sc = new Scanner(System.in);
            userInput = sc.nextLine();
            if (userInput.toLowerCase().equals("fall") || userInput.toLowerCase().equals("winter") || 
                    userInput.toLowerCase().equals("spring") || userInput.toLowerCase().equals("summer")) {
                stringCheck = true;
            } else {
                System.out.println("Error: Please enter Fall, Winter, "
                        + "Spring, or Summer");
            }
        }
        
        for(Entry entry: list) {
            if (userInput.toLowerCase().equals(entry.getSeason().toLowerCase())) {
                resultList.add(entry);
            }
        }
        
        return resultList;
    }
    
    /**
     * Method that adds to a list and sorts via name.
     * 
     * @param fileName
     * @throws FileNotFoundException
     * @throws IOException 
     */
    public static void add_entry(String fileName) throws FileNotFoundException, IOException {
        // Entry stuff
        List<Entry> entryList = new ArrayList<Entry>();
        entryList = extract_file(fileName);
        if (entryList.isEmpty()) {
            return;
        }
        
        // Name Input + Checking for name to see if it exists
        boolean entryExist = true;
        String name = "";
        String season;
        int year;
        System.out.println("Please enter the name of the anime. If it is a "
                    + "remake, please add a ':remake' at the end of the title.");
        
        while (entryExist) {
            Scanner nameInput = new Scanner(System.in);
            name = nameInput.nextLine();
            final String checkName = name;
            entryExist = entryList.stream().anyMatch(x -> x.getName().toLowerCase()
                    .equals(checkName.toLowerCase()));
            if (entryExist) {
                System.out.println("Error: This name already exists. Please reenter the name.");
            }
        }
        
        // Season + Year input
        System.out.println("Please enter the season the anime is from.");
        Scanner seasonInput = new Scanner(System.in);
        season = seasonInput.next();
        System.out.println("Please enter the year the anime is from.");
        Scanner yearInput = new Scanner(System.in);
        year = Integer.parseInt(yearInput.next());
        Entry entry = new Entry(name, season, year);
        
        // Add entry to list + sort it by name
        entryList.add(entry);
        List<Entry> resultList = entryList.stream().
                sorted((Entry o1, Entry o2) -> o1.getName().
                        compareTo(o2.getName())).
                        collect(Collectors.toList());
        
        //write to a file + overwrite
        write_file(fileName, resultList);
        System.out.println("Entry successfully added.\n");
    }
    
    /**
     * Uses a map to separate the entry between a false/true list. 
     * @param fileName
     * @throws IOException 
     */
    public static void delete_entry(String fileName) throws IOException {
        // Entry stuff
        List<Entry> entryList = new ArrayList<Entry>();
        entryList = extract_file(fileName);
        if (entryList.isEmpty()) {
            return;
        }
        
        
        String userInput;
        List<Entry> resultList = new ArrayList<>();
        List<Entry> actualList = new ArrayList<>();
        System.out.println("\nType the name of the entry that you want to delete.");
        
        // Splits into 2 lists via using maps. If entry exists, it splits. 
        while (resultList.isEmpty()) {
            Scanner sc = new Scanner(System.in);
            userInput = sc.nextLine();
            final String checkName = userInput;
            Map<Boolean, List<Entry>> partitions = entryList.stream().
                    collect(Collectors.partitioningBy(Entry -> Entry.getName().toLowerCase().
                            equals(checkName.toLowerCase())));
            resultList = partitions.get(true);
            actualList = partitions.get(false);
            if (resultList.isEmpty()) {
                System.out.println("Error: This entry does not exist. Please try again.");
            }
        }
        
        write_file(fileName, actualList);
        System.out.println("Success: Entry has been deleted.\n");
    }
    
    /**
     * This function handles all the sort methods. All of them are just stream 
     * manipulations of the array list created by extract_file. 
     * 
     * @param fileName
     * @param input
     * @throws IOException 
     */
    public static void sort_functions(String fileName, int input) throws IOException {
        // Entry stuff
        List<Entry> entryList = new ArrayList<>();
        List<Entry> resultList  = new ArrayList<>();
        entryList = extract_file(fileName);
        if (entryList.isEmpty()) {
            return;
        }
        
        // Different cases for different sorts: 1 = name, 2 = season, 3 = year
        switch (input) {
            case 1:
                resultList = entryList.stream().
                    sorted((Entry o1, Entry o2) -> o1.getName().
                        compareTo(o2.getName())).
                    collect(Collectors.toList());
                write_file(fileName, resultList);
                System.out.println("Success: List has been sorted by names.\n");
                break;
            case 2:
                resultList = entryList.stream().
                    sorted((Entry o1, Entry o2) -> o1.getSeason().
                        compareTo(o2.getSeason())).
                    collect(Collectors.toList());
                write_file(fileName, resultList);
                System.out.println("Success: List has been sorted by seasons.\n");
                break;
            case 3:
                resultList = entryList.stream().
                    sorted(Comparator.comparingInt(Entry::getYear)).
                    collect(Collectors.toList());
                write_file(fileName, resultList);
                System.out.println("Success: List has been sorted by year.\n");
                break;
            default:
                break;
        }
    }
    
    /**
     * Changes the text file that is being edited. 
     * @param fileName
     * @return
     * @throws IOException 
     */
    public static String change_file(String fileName) throws IOException {
        String newFileName;
        System.out.println("\nWhat is the name of the file you want to change"
                + " to.");
        Scanner sc = new Scanner(System.in);
        newFileName = sc.nextLine();
        newFileName = newFileName + ".txt";
        File file = new File(newFileName);
        
        // If file exists, take that new name
        if (file.isFile()) {
            System.out.println("Success: Changing your file to: " + newFileName + 
                    "\nReturning you to the menu.\n");
            return newFileName;
        }
        
        // New so ask if they want to make the new file or not
        System.out.println("\nFile is new. Attempting to creating new file.");
        System.out.println("Are you sure that this is the name you want?"
                + "\nPress the enter key if so."
                + "\nOtherwise, type anything followed be enter to return to the previous menu and cancel.");
        
        String userInput = "";
        Scanner confirmSc = new Scanner(System.in);
        userInput = confirmSc.nextLine();
        if (!userInput.equals("")){
            System.out.println("Not making a new file. Returning to the menu.\n");
            return fileName;
        }
        // Check if file exists or not, if so read it all, otherwise create it for you.
        if(file.createNewFile()) {
            System.out.println("Success: Creating the file.\n");
        }
        return newFileName;
    }
    
    /**
     * Change entry function.
     * @param fileName
     * @throws IOException 
     */
    public static void change_entry(String fileName) throws IOException {
        List<Entry> entryList = new ArrayList<>();
        entryList = extract_file(fileName);
        Entry newChangedEntry = new Entry("", "", 0);
        Entry keepTrackEntry = new Entry("", "", 0);
        
        System.out.println("\nThis is your current list.");
        display_list(fileName);
        
        // Grab entry from array list.
        boolean checkEntry = false;
        System.out.println("Which entry would you like to change?");
        while (!checkEntry) {
            Scanner userInput = new Scanner(System.in);
            String userString = userInput.nextLine();
            for (Entry entry: entryList) {
                if (entry.getName().equals(userString)) {
                    newChangedEntry.setName(entry.getName());
                    newChangedEntry.setSeason(entry.getSeason());
                    newChangedEntry.setYear(entry.getYear());
                    keepTrackEntry = entry;
                }
            }
            if (newChangedEntry.getName().equals("")) {
                System.out.println("\nWe could not find an entry with that name."
                        + " Please reenter the entry: ");
            } else {
                checkEntry = true;
            }
        }
        
        // Asking for what they want to change.
        boolean numberCheck = false;
        int actualNum = -1;
        while (!numberCheck || (actualNum != 1 && actualNum !=2 && actualNum != 3)) {
            System.out.println("\nWhat would you like to change for this entry?"
                    + "\n1. Name"
                    + "\n2. Season"
                    + "\n3. Year");

            Scanner entryChangeInput = new Scanner(System.in);
            String userInput = entryChangeInput.nextLine();
            try {
                actualNum = Integer.parseInt(userInput);
                numberCheck = true;
            } catch (NumberFormatException e) {
                System.out.println("Error: Input is not of number value."
                        + " Please enter a number of choice.");
            }
            
            if (actualNum != 1 && actualNum !=2 && actualNum != 3) {
                System.out.println("Error: Please only enter 1, 2, or 3.");
            }
        }
        
        // Switch statement to handle each case. 
        switch(actualNum) {
            case 1: 
                System.out.println("\nPlease input the new name.");
                Scanner nameInput = new Scanner(System.in);
                String stringNameInput = nameInput.nextLine();
                newChangedEntry.setName(stringNameInput);
                System.out.println("\nName changed. Fixing text file.");
                break;
            case 2: 
                System.out.println("\nPlease input the new season.");
                Scanner seasonInput = new Scanner(System.in);
                String stringSeasonInput = seasonInput.nextLine();
                newChangedEntry.setSeason(stringSeasonInput);
                System.out.println("\nSeason changed. Fixing text file.");
                break;
            case 3: 
                System.out.println("\nPlease input the new year.");
                Scanner nameYearInput = new Scanner(System.in);
                int intYearInput = Integer.parseInt(nameYearInput.nextLine());
                newChangedEntry.setYear(intYearInput);
                System.out.println("\nYear changed. Fixing text file.");
                break;
            default: 
                break;
        }
        
        // Add entry to list + sort it by name
        entryList.remove(keepTrackEntry);
        entryList.add(newChangedEntry);
        List<Entry> resultList = entryList.stream().
                sorted((Entry o1, Entry o2) -> o1.getName().
                        compareTo(o2.getName())).
                        collect(Collectors.toList());
        
        //write to a file + overwrite
        write_file(fileName, resultList);
        System.out.println("Text file fixed. Returning to menu.\n");
    }
    
    /**
     * Helper function to help print a whole list.
     * @param list 
     */
    private static void help_print(List<Entry> list){
        String format = "%-35s %-20s %d %n";
        String format2 = "%-35s %-20s %s %n";
        System.out.printf("\n");
        System.out.printf(format2, "Name:", "Season:", "Year:");
        list.stream().
                forEach(x -> System.out.printf(format, x.getName(), x.getSeason(), x.getYear()));
        System.out.printf("\n");
    }
}

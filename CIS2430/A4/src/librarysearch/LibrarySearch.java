package librarysearch;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.FlowLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.PrintWriter;
import java.util.Scanner;
import java.util.ArrayList;
import java.util.HashMap;
import javax.swing.*;
import java.awt.event.*;

/**
 * This is a simple library search where user can load existing references at
 * the start of the program. Now the user can interact with the program through
 * a GUI. The user can add, search for books\journals and are able to quit from
 * the program. The user must save and quit to save all the references that were
 * added during that session.
 *
 * @author mtran04
 */
public class LibrarySearch extends JFrame implements ActionListener, ItemListener {

    /*
     * INSTANCE VARIABLES
     */
    
    public static ArrayList<Reference> referenceList = new ArrayList<>();
    public static HashMap<String, ArrayList<Integer>> hashMap = new HashMap<>();
    Scanner keyboard = new Scanner(System.in);
    private static final String REFERENCE_TYPE = "type = ";
    private static final String REFERENCE_CALLNUMBER = "callnumber = ";
    private static final String REFERENCE_AUTHORS = "authors = ";
    private static final String REFERENCE_TITLE = "title = ";
    private static final String REFERENCE_PUBLISHER = "publisher = ";
    private static final String REFERENCE_ORGANIZATION = "organization = ";
    private static final String REFERENCE_YEAR = "year = ";
    static Scanner inputStream = null;
    static PrintWriter outputStream = null;
    
    /**
     * GUI INSTANCE VARIABLES
     */
    
    private static final int WIDTH = 600;
    private static final int HEIGHT = 500;
    
    // PANELS FOR GUI //
    JPanel addPanel = new JPanel();
    JPanel searchPanel = new JPanel();
    JPanel commandPanel = new JPanel();
    
    // LABELS FOR ADDING PANEL //
    JLabel typeLabel = new JLabel("Type: ");
    JLabel callNum = new JLabel("Call No:");
    JLabel authors = new JLabel("Authors:");
    JLabel title = new JLabel("Title:");
    JLabel publisher = new JLabel("Publisher:");
    JLabel organization = new JLabel("Organization:");
    JLabel year = new JLabel("Year:");
    
    // TEXT FIELDS FOR ADDING PANEL //
    JTextField callNumField = new JTextField();
    JTextField authorsField = new JTextField();
    JTextField titleField = new JTextField();
    JTextField publisherField = new JTextField();
    JTextField organizationField = new JTextField();
    JTextField yearField = new JTextField();
    
    // COMBO DROP BOX FOR ADDING PANEL // 
    String[] type = {"Book", "Journal"};
    JComboBox referenceType = new JComboBox(type);
    
    // MESSAGE AREA FOR ADDING PANEL //
    JTextArea messageArea = new JTextArea();
    JScrollPane scrollMessage = new JScrollPane();
    
    // BUTTONS FOR ADDING PANEL //
    JButton addReset = new JButton("Reset");
    JButton addButton = new JButton("Add");
    
    // LABELS FOR SEARCHING PANEL //
    JLabel searchCallNum = new JLabel("Call No:");
    JLabel titleKeywords = new JLabel("Title Keywords:");
    JLabel startYear = new JLabel("Start Year:");
    JLabel endYear = new JLabel("End Year:");
    
    // TEXT FIELDS FOR SEARCHING PANEL //
    JTextField searchCallNumField = new JTextField();
    JTextField searchTitle = new JTextField();
    JTextField searchStart = new JTextField();
    JTextField searchEnd = new JTextField();
    JTextArea searchArea = new JTextArea();
    JScrollPane scrollSearch = new JScrollPane();
    
    // BUTTONS FOR SEARCHING PANEL //
    JButton searchReset = new JButton("Reset");
    JButton searchButton = new JButton("Search");
    String outputFile;

    /**
     * To create the GUI in main
     *
     * @param output
     */
    public LibrarySearch(String output) {
        super();
        this.libraryGUI();
        this.outputFile = output;
    }

    /**
     * Implements the library GUI
     */
    public void libraryGUI() {
        this.setTitle("Library Search");
        this.setSize(WIDTH, HEIGHT);
        this.setDefaultCloseOperation(JFrame.DO_NOTHING_ON_CLOSE);
        this.setLayout(null);
        this.setResizable(false);
        this.getContentPane().setBackground(Color.GREEN);

        // CREATING MENU BAR //
        JMenuBar menu = new JMenuBar();
        JMenu command = new JMenu("Command");
        JMenuItem home = new JMenuItem("Home");
        JMenuItem add = new JMenuItem("Add");
        JMenuItem search = new JMenuItem("Search");
        JMenuItem saveAndExit = new JMenuItem("Save and Exit");
        JMenuItem exit = new JMenuItem("Exit");
        ImageIcon addIcon = new ImageIcon("add-icon.gif");
        ImageIcon searchIcon = new ImageIcon("icon_search_16x16.gif");
        ImageIcon exitIcon = new ImageIcon("Exit.png");
        ImageIcon saveAndExitIcon = new ImageIcon("sa_svn_save_button.png");
        ImageIcon homeIcon = new ImageIcon("538709-home_16x16.png");

        setJMenuBar(menu);
        menu.add(command);
        home.setIcon(homeIcon);
        command.add(home);
        add.setIcon(addIcon);
        command.add(add);
        search.setIcon(searchIcon);
        command.add(search);
        saveAndExit.setIcon(saveAndExitIcon);
        command.add(saveAndExit);
        exit.setIcon(exitIcon);
        command.add(exit);

        // CREATING COMMAND PANEL //
        commandPanel.setSize(WIDTH, HEIGHT);
        commandPanel.setLayout(null);
        commandPanel.setLocation(0, 0);
        commandPanel.setBackground(Color.ORANGE);
        this.add(commandPanel);
        JLabel label1 = new JLabel("Welcome to Library Search");
        label1.setLocation(10, 50);
        label1.setSize(160, 25);
        label1.setHorizontalAlignment(0);
        commandPanel.add(label1);

        JLabel label2 = new JLabel("Choose a command from the \"Commands\" menu above for adding a reference, searching a ");
        label2.setLocation(5, 200);
        label2.setSize(535, 25);
        label2.setHorizontalAlignment(0);
        commandPanel.add(label2);

        JLabel label3 = new JLabel("references, go to the home screen, save and quit or quit without saving.");
        label3.setLocation(5, 220);
        label3.setSize(420, 25);
        label3.setHorizontalAlignment(0);
        commandPanel.add(label3);
        commandPanel.setVisible(true);

        home.addActionListener(this); // action listener for home screen

        // CREATING ADD PANEL WITH LABELS, TEXT FIELD AND A COMBO BOX //
        addPanel.setSize(WIDTH, HEIGHT);
        addPanel.setLocation(0, 0);
        addPanel.setLayout(null);
        addPanel.setBackground(Color.ORANGE);
        this.add(addPanel);
        JLabel referenceLabel = new JLabel("Adding a reference");
        referenceLabel.setLocation(5, 0);
        referenceLabel.setSize(170, 25);
        addPanel.add(referenceLabel);
        typeLabel.setLocation(30, 30);
        typeLabel.setSize(100, 25);
        addPanel.add(typeLabel);

        // COMBO BOX 
        referenceType.setSelectedIndex(0);
        referenceType.setLocation(100, 30);
        referenceType.setSize(70, 20);
        addPanel.add(referenceType);

        referenceType.addItemListener(this); // action listener for combo box

        callNum.setLocation(30, 60);
        callNum.setSize(100, 25);
        addPanel.add(callNum);

        callNumField.setLocation(100, 65);
        callNumField.setSize(250, 20);
        addPanel.add(callNumField);

        authors.setLocation(30, 87);
        authors.setSize(100, 25);
        addPanel.add(authors);

        authorsField.setLocation(100, 90);
        authorsField.setSize(250, 20);
        addPanel.add(authorsField);

        title.setLocation(30, 112);
        title.setSize(90, 25);
        addPanel.add(title);

        titleField.setLocation(100, 115);
        titleField.setSize(250, 20);
        addPanel.add(titleField);

        publisher.setLocation(30, 140);
        publisher.setSize(90, 25);
        addPanel.add(publisher);

        publisherField.setLocation(100, 143);
        publisherField.setSize(250, 20);
        addPanel.add(publisherField);

        organization.setLocation(30, 140);
        organization.setSize(90, 25);
        addPanel.add(organization);
        organization.setVisible(false);

        organizationField.setLocation(120, 143);
        organizationField.setSize(230, 20);
        addPanel.add(organizationField);
        organizationField.setVisible(false);

        year.setLocation(30, 170);
        year.setSize(80, 25);
        addPanel.add(year);

        yearField.setLocation(100, 173);
        yearField.setSize(250, 20);
        addPanel.add(yearField);

        // MESSAGE AREA TO GIVE FEEDBACK TO THE USER //
        JLabel messages = new JLabel("Messages");
        messages.setLocation(30, 210);
        messages.setSize(80, 25);
        addPanel.add(messages);

        messageArea.setEditable(false);
        messageArea.setWrapStyleWord(true);
        messageArea.setBackground(Color.WHITE);
        addPanel.add(messageArea);

        scrollMessage.setLocation(20, 235);
        scrollMessage.setSize(540, 180);
        scrollMessage.setViewportView(messageArea);
        scrollMessage.setHorizontalScrollBarPolicy(JScrollPane.HORIZONTAL_SCROLLBAR_ALWAYS);
        scrollMessage.setVerticalScrollBarPolicy(JScrollPane.VERTICAL_SCROLLBAR_ALWAYS);
        addPanel.add(scrollMessage);

        // BUTTONS FOR USER TO RESET OR ADD REFERENCE //
        addReset.setLocation(425, 80);
        addReset.setSize(80, 30);
        addReset.setBackground(Color.RED);
        addPanel.add(addReset);

        addButton.setLocation(425, 150);
        addButton.setSize(80, 30);
        addButton.setBackground(Color.RED);
        addPanel.add(addButton);

        addReset.addActionListener(this);
        addButton.addActionListener(this);

        addPanel.setVisible(false);

        add.addActionListener(this); // action listener for add panel

        // SEARCH PANEL WITH LABELS AND TEXT FIELDS//
        searchPanel.setSize(WIDTH, HEIGHT);
        searchPanel.setLocation(0, 0);
        searchPanel.setLayout(null);
        searchPanel.setBackground(Color.ORANGE);
        this.add(searchPanel);

        JLabel searchLabel = new JLabel("Searching references");
        searchLabel.setLocation(5, 0);
        searchLabel.setSize(170, 25);
        searchPanel.add(searchLabel);

        searchCallNum.setLocation(30, 60);
        searchCallNum.setSize(100, 25);
        searchPanel.add(searchCallNum);

        searchCallNumField.setLocation(130, 65);
        searchCallNumField.setSize(220, 20);
        searchPanel.add(searchCallNumField);

        titleKeywords.setLocation(30, 87);
        titleKeywords.setSize(180, 25);
        searchPanel.add(titleKeywords);

        searchTitle.setLocation(130, 90);
        searchTitle.setSize(220, 20);
        searchPanel.add(searchTitle);

        startYear.setLocation(30, 112);
        startYear.setSize(100, 25);
        searchPanel.add(startYear);

        searchStart.setLocation(130, 115);
        searchStart.setSize(100, 20);
        searchPanel.add(searchStart);

        endYear.setLocation(30, 140);
        endYear.setSize(100, 25);
        searchPanel.add(endYear);

        searchEnd.setLocation(130, 143);
        searchEnd.setSize(100, 20);
        searchPanel.add(searchEnd);

        JLabel searchResult = new JLabel("Search Results");
        searchResult.setLocation(30, 210);
        searchResult.setSize(200, 25);
        searchPanel.add(searchResult);

        // MESSAGE AREA TO SHOW THE REFERENCES USER SEARCHING FOR //
        searchArea.setEditable(false);
        searchArea.setWrapStyleWord(true);
        searchArea.setBackground(Color.WHITE);
        searchPanel.add(searchArea);

        scrollSearch.setLocation(20, 235);
        scrollSearch.setSize(540, 180);
        scrollSearch.setViewportView(searchArea);
        scrollSearch.setHorizontalScrollBarPolicy(JScrollPane.HORIZONTAL_SCROLLBAR_ALWAYS);
        scrollSearch.setVerticalScrollBarPolicy(JScrollPane.VERTICAL_SCROLLBAR_ALWAYS);
        searchPanel.add(scrollSearch);

        // BUTTONS FOR USER TO RESET OR SEARCH FOR REFERENCES //
        searchReset.setLocation(425, 60);
        searchReset.setSize(80, 30);
        searchReset.setBackground(Color.RED);
        searchPanel.add(searchReset);

        searchButton.setLocation(425, 140);
        searchButton.setSize(80, 30);
        searchButton.setBackground(Color.RED);
        searchPanel.add(searchButton);

        searchReset.addActionListener(this);
        searchButton.addActionListener(this);
        searchPanel.setVisible(false);

        // ACTION LISTENERS FOR SEARCH PANEL, SAVE AND EXTI BUTTON AND EXIT BUTTON //
        search.addActionListener(this);
        saveAndExit.addActionListener(this);
        exit.addActionListener(this);

        // ADD WINDOW LISTENER TO CONFIRM USER EXITING
        addWindowListener(new CheckOnExit());

    }

    @Override
    /**
     * ActionListener to carry out what the user wants the GUI to do
     */
    public void actionPerformed(ActionEvent e) {
        if (e.getActionCommand().equalsIgnoreCase("Add") && e.getSource() instanceof JMenuItem) { // change to add panel
            commandPanel.setVisible(false);
            addPanel.setVisible(true);
            searchPanel.setVisible(false);
        } else if (e.getActionCommand().equalsIgnoreCase("Search") && e.getSource() instanceof JMenuItem) { // change to search panel
            commandPanel.setVisible(false);
            addPanel.setVisible(false);
            searchPanel.setVisible(true);
        } else if (e.getActionCommand().equalsIgnoreCase("Home")) { // change to home panel
            commandPanel.setVisible(true);
            addPanel.setVisible(false);
            searchPanel.setVisible(false);
        } else if (e.getActionCommand().contains("Save")) { // save refernces and exit
            try {
                outputStream = new PrintWriter(new FileOutputStream(outputFile));
            } catch (FileNotFoundException file) {
                System.err.println("Error opening the output file");
                System.exit(0);
            }
            saveReferences(outputStream); // save references to output file
            outputStream.close();
            System.exit(0);
        } else if (e.getActionCommand().equalsIgnoreCase("Exit")) { // exit program without saving
            System.exit(0);
        } else if (e.getActionCommand().equalsIgnoreCase("Reset")) { // reset all fields
            callNumField.setText("");
            titleField.setText("");
            authorsField.setText("");
            publisherField.setText("");
            organizationField.setText("");
            yearField.setText("");
            searchCallNumField.setText("");
            searchTitle.setText("");
            searchStart.setText("");
            searchEnd.setText("");
            messageArea.setText("");
            searchArea.setText("");
        } else if (e.getActionCommand().equalsIgnoreCase("Add") && e.getSource() instanceof JButton) { // add reference
            String type = (String) referenceType.getSelectedItem();
            if (callNumField.getText().isEmpty()) {
                messageArea.setText("Must enter a call number!");
                JOptionPane.showMessageDialog(this, "Call Number Cannot Be Blank!!\nReference Not Added!!", "Invalid Input!!", JOptionPane.ERROR_MESSAGE);
                return;
            } else if (titleField.getText().isEmpty()) {
                messageArea.setText("Must enter a title!");
                JOptionPane.showMessageDialog(this, "Title Cannot Be Blank!!\nReference Not Added!!", "Invalid Input!!", JOptionPane.ERROR_MESSAGE);
                return;
            } else if (yearField.getText().isEmpty()) {
                messageArea.setText("Must enter a year!");
                JOptionPane.showMessageDialog(this, "Year Cannot Be Blank!!\nReference Not Added!!", "Invalid Input!!", JOptionPane.ERROR_MESSAGE);
                return;
            }
            if (!callNumField.getText().isEmpty() && !titleField.getText().isEmpty() && !yearField.getText().isEmpty()) {
                messageArea.setText("");
                add(type, callNumField.getText(), titleField.getText(), yearField.getText());
            }
        } else if (e.getActionCommand().equalsIgnoreCase("Search") && e.getSource() instanceof JButton) { // search for reference
            searchArea.setText("");
            search(searchCallNumField.getText().trim(), searchTitle.getText(), searchStart.getText(), searchEnd.getText());
        }
    }

    @Override
    /**
     * Listens to what the JComboxBox is doing
     */
    public void itemStateChanged(ItemEvent e) {
        if (e.getItem().equals("Journal")) { // make the fields for journal visible
            authors.setVisible(false);
            authorsField.setVisible(false);
            publisher.setVisible(false);
            publisherField.setVisible(false);
            organization.setVisible(true);
            organizationField.setVisible(true);
            callNumField.setText("");
            titleField.setText("");
            yearField.setText("");
            publisherField.setText("");
            authorsField.setText("");
        } else { // make the fields for book visible
            authors.setVisible(true);
            authorsField.setVisible(true);
            publisher.setVisible(true);
            publisherField.setVisible(true);
            organization.setVisible(false);
            organizationField.setVisible(false);
            organizationField.setText("");
        }
    }

    /**
     * Load references at the beginning of the program from file input
     *
     * @param inputStream
     */
    public static void loadReferences(Scanner inputStream) {
        // Load existing references from input file at the start of the program
        while (inputStream.hasNextLine()) {
            String type = inputStream.nextLine();
            type = type.replaceAll(REFERENCE_TYPE, "");
            if (type.equalsIgnoreCase("book")) {
                String callNumber = inputStream.nextLine().trim();
                callNumber = callNumber.replaceAll(REFERENCE_CALLNUMBER, "");

                String authors = inputStream.nextLine();
                authors = authors.replaceAll(REFERENCE_AUTHORS, "");

                String title = inputStream.nextLine().trim();
                title = title.replaceAll(REFERENCE_TITLE, "");
                String[] tokenTitle = title.toLowerCase().split("[ ,\n]+");

                String publisher = inputStream.nextLine().trim();
                publisher = publisher.replaceAll(REFERENCE_PUBLISHER, "");

                String tempYear = inputStream.nextLine().trim();
                tempYear = tempYear.replaceAll(REFERENCE_YEAR, "");
                int year = Integer.parseInt(tempYear);

                Book newBook = new Book(callNumber, authors, title, publisher, year);
                referenceList.add(newBook);
                addTitleToHashMap(tokenTitle, referenceList.size());
            } else if (type.equalsIgnoreCase("journal")) {
                String callNumber = inputStream.nextLine().trim();
                callNumber = callNumber.replaceAll(REFERENCE_CALLNUMBER, "");

                String title = inputStream.nextLine().trim();
                title = title.replaceAll(REFERENCE_TITLE, "");
                String[] tokenTitle = title.toLowerCase().split("[ ,\n]+");

                String organization = inputStream.nextLine().trim();
                organization = organization.replaceAll(REFERENCE_ORGANIZATION, "");

                String tempYear = inputStream.nextLine().trim();
                tempYear = tempYear.replaceAll(REFERENCE_YEAR, "");
                int year = Integer.parseInt(tempYear);

                Journal newJournal = new Journal(callNumber, title, organization, year);
                referenceList.add(newJournal);
                addTitleToHashMap(tokenTitle, referenceList.size());
            }
        }
    }

    /**
     * Create a reference and adds to reference list
     */
    public void add(String type, String callNumber, String title, String year) {
        int yearTemp = 0;
        try {
            if (!yearField.getText().isEmpty()) {
                yearTemp = Integer.parseInt(yearField.getText().trim());
            }
        } catch (Exception evt) {
            messageArea.setText("Invalid Year. Year must be between 1000-9999");
            JOptionPane.showMessageDialog(this, "Invalid Year. Year must be between 1000-9999!\nReference Not Added!!", "Invalid Input!!", JOptionPane.ERROR_MESSAGE);
            return;
        }

        String[] tokenTitle = title.toLowerCase().split("[ ,\n]+"); // tokenize the title to lower case for the hashmap
        boolean duplicate = false;

        // CREATE BOOK OBJECT AND ADD TO REFERENCELIST
        if (type.equalsIgnoreCase("Book") && yearTemp > 1000 && yearTemp < 9999) {
            Book newBook = new Book(callNumber, authorsField.getText().trim(), title, publisherField.getText().trim(), yearTemp);
            for (Reference book : referenceList) { // CHECKS FOR DUPLICATE
                if (book.getCallNumber().equals(newBook.getCallNumber()) && book.getYear() == newBook.getYear()) {
                    duplicate = true;
                }
            }
            if (!duplicate) { // ADD UNIQUE BOOK
                referenceList.add(newBook);
                int sizeOfList = referenceList.size();
                addTitleToHashMap(tokenTitle, sizeOfList);
                messageArea.append("\nCallNumber: " + callNumber + "\nAuthors: " + authorsField.getText().trim() + "\nTitle: " + title + "\nPublisher: " + publisherField.getText().trim() + "\nYear: " + yearTemp + "\n\nBook was added successfully");
            } else { // DUPLICATE FOUND
                messageArea.setText("Reference already exists");
                JOptionPane.showMessageDialog(this, "Reference already exists!\nReference Not Added!!", "Duplicate Entry!", JOptionPane.ERROR_MESSAGE);
            }
        } // CREATE JOURNAL OBJECT AND ADD TO REFERENCELIST
        else if (type.equalsIgnoreCase("Journal") && yearTemp > 1000 && yearTemp < 9999) {
            Journal newJournal = new Journal(callNumber, titleField.getText(), organizationField.getText(), yearTemp);
            for (Reference journal : referenceList) { // CHECKS FOR DUPLICATE
                if (journal.getCallNumber().equals(newJournal.getCallNumber()) && journal.getYear() == newJournal.getYear()) {
                    duplicate = true;
                }
            }
            if (!duplicate) { // ADD UNIQUE JOURNAL
                referenceList.add(newJournal);
                int sizeOfList = referenceList.size();
                addTitleToHashMap(tokenTitle, sizeOfList);
                messageArea.append("\nCallNumber: " + callNumber + "\nTitle: " + title + "\nOrganization: " + organizationField.getText().trim() + "\nYear: " + yearTemp + "\n\nJournal was added successfully");
            } else { // DUPLICATE FOUND
                messageArea.setText("Reference already exists");
                JOptionPane.showMessageDialog(this, "Reference already exists!\nReference Not Added!!", "Duplicate Entry!", JOptionPane.ERROR_MESSAGE);
            }
        } else {
            messageArea.setText("Year must be between 1000-9999");
            JOptionPane.showMessageDialog(this, "Year must be between 1000-9999!\nReference Not Added!!", "Invalid Input!!", JOptionPane.ERROR_MESSAGE);
        }
    }

    /**
     * Add tokenized reference title keywords to the hash map
     *
     * @param tokenTitle
     * @param sizeOfList
     */
    public static void addTitleToHashMap(String[] tokenTitle, int sizeOfList) {
        String keyword = "";
        int counter = 0;
        while (counter < tokenTitle.length) {
            keyword = tokenTitle[counter];
            while (!hashMap.containsKey(keyword)) { // while the keyword does not exist in the hashmap, add it
                hashMap.put(keyword, new ArrayList<Integer>());
            }
            hashMap.get(keyword).add(sizeOfList - 1); // if keyword already exists, update the array associated with keyword
            counter++;
        }
    }

    /**
     * Search through reference lists to find what the user wants
     */
    public void search(String callNumber, String title, String startYear, String endYear) {
        String[] searchKeywords = null;

        if (!title.equals("")) {
            searchKeywords = title.toLowerCase().split("[ ,\n]+");
        }

        int start = 0;
        int end = 0;

        try { // try to parse year input from user
            if (!searchStart.getText().isEmpty()) {
                start = Integer.parseInt(searchStart.getText());
            }
        } catch (Exception startYearE) {
            searchArea.setText("Invalid Start Year. Year must be between 1000-9999");
            JOptionPane.showMessageDialog(this, "Invalid Start Year. Year must be between 1000-9999!\nSearch Not Performed!!", "Invalid Input!!", JOptionPane.ERROR_MESSAGE);
            return;
        }
        try {
            if (!searchEnd.getText().isEmpty()) {
                end = Integer.parseInt(searchEnd.getText());
            }
        } catch (Exception endYearE) {
            searchArea.setText("Invalid End Year. Year must be between 1000-9999");
            JOptionPane.showMessageDialog(this, "Invalid End Year. Year must be between 1000-9999!\nSearch Not Performed!!", "Invalid Input!!", JOptionPane.ERROR_MESSAGE);
            return;
        }

        if (start == 0 && end == 0) {
            start = 1000;
            end = 9999;
        } else if (start == 0 && end != 0) {
            start = 1000;
        } else if (start != 0 && end == 0) {
            end = 9999;
        }

        if (start > end) {
            searchArea.setText("Start of Year CANNOT be GREATER than End Year");
            JOptionPane.showMessageDialog(this, "Start of Year CANNOT be GREATER than End Year!\nSearch Not Performed!!", "Invalid Input!!", JOptionPane.ERROR_MESSAGE);
        } else if (start <= end) {
            if (start >= 1000 && end <= 9999) {
                searchReferences(callNumber, searchKeywords, start, end);
            } else {
                searchArea.setText("Years must be between 1000-9999");
                JOptionPane.showMessageDialog(this, "Years must be between 1000-9999!\nSearch Not Performed!!", "Invalid Input!!", JOptionPane.ERROR_MESSAGE);
            }
        }
    }

    /**
     * Check if any reference titles match keywords user input
     *
     * @param searchKeywords
     * @param title
     * @return
     */
    private boolean keywordsValid(String[] searchKeywords, String title) {
        String[] tokenTitle = title.split("[ ,\n]+");
        int counter = 0;

        for (int i = 0; i < searchKeywords.length; i++) {
            for (int j = 0; j < tokenTitle.length; j++) {
                if (searchKeywords[i].equalsIgnoreCase(tokenTitle[j])) {
                    counter++;
                }
            }
        }

        if (counter == searchKeywords.length) {
            return true;
        } else {
            return false;
        }
    }

    /**
     * Search all references that satisfy the search request
     *
     * @param callNumber
     * @param searchKeywords
     * @param year
     */
    public void searchReferences(String callNumber, String[] searchKeywords, int startYear, int endYear) {
        boolean flag = false;
        for (int i = 0; i < referenceList.size(); i++) {
            if ((callNumber.equals("") || referenceList.get(i).getCallNumber().equalsIgnoreCase(callNumber))
                    && (searchKeywords == null || keywordsValid(searchKeywords, referenceList.get(i).getTitle()))
                    && (referenceList.get(i).getYear() >= startYear && referenceList.get(i).getYear() <= endYear)) {
                searchArea.append(referenceList.get(i).toString() + "\n");
                flag = true;
            }
        }

        if (flag == false) {
            searchArea.setText("No References Found");
        }
    }

    /**
     * Search reference list using a hash map
     *
     * @param callNumber
     * @param searchKeywords
     * @param startYear
     * @param endYear
     */
    public void searchHashMap(String callNumber, String[] searchKeywords, int startYear, int endYear) {
        ArrayList<Integer> tempArray = new ArrayList<>();
        ArrayList<Integer> keywordIntersection = new ArrayList<>();
        String keyword = "";
        int counter = 0;
        int counter2 = 0;
        boolean flag = false;

        // Loop through keywords and look for intersection
        while (counter < searchKeywords.length) {
            keyword = searchKeywords[counter];
            if (hashMap.containsKey(keyword)) {
                tempArray.addAll((hashMap.get(keyword)));// Store found key values in temp array
                counter2++;
            }
            if (keywordIntersection.isEmpty()) {
                keywordIntersection.addAll(hashMap.get(keyword));
            }
            keywordIntersection.retainAll(tempArray); // Store common values
            tempArray.removeAll(tempArray); // remove all values from temp array
            counter++;
        }

        if (counter2 == searchKeywords.length) { // if counter2 equals the length of searchkeywords array found all keys
            for (int i = 0; i < keywordIntersection.size(); i++) {
                Integer index = keywordIntersection.get(i);
                int key = index.intValue();
                if ((callNumber.equals("") || referenceList.get(key).getCallNumber().equalsIgnoreCase(callNumber))
                        && (referenceList.get(key).getYear() >= startYear && referenceList.get(key).getYear() <= endYear)) {
                    searchArea.append(referenceList.get(key).toString() + "\n");
                    flag = true;
                }
            }
            if (flag == false) {
                searchArea.setText("No References Found");
            }
        }
    }

    /**
     * Writes to output file to save reference list
     *
     * @param outputStream
     */
    public void saveReferences(PrintWriter outputStream) {
        //Loop to write all references to specified output file
        for (int i = 0; i < referenceList.size(); i++) {
            Reference reference = referenceList.get(i);
            String type = reference.getType();
            if (type.equalsIgnoreCase("book")) {
                Book tempBook = (Book) reference;
                outputStream.println(REFERENCE_TYPE + tempBook.getType());
                outputStream.println(REFERENCE_CALLNUMBER + tempBook.getCallNumber());
                outputStream.println(REFERENCE_AUTHORS + tempBook.getAuthors());
                outputStream.println(REFERENCE_TITLE + tempBook.getTitle());
                outputStream.println(REFERENCE_PUBLISHER + tempBook.getPublisher());
                outputStream.println(REFERENCE_YEAR + tempBook.getYear());
                outputStream.println();
            } else {
                Journal tempJournal = (Journal) reference;
                outputStream.println(REFERENCE_TYPE + tempJournal.getType());
                outputStream.println(REFERENCE_CALLNUMBER + tempJournal.getCallNumber());
                outputStream.println(REFERENCE_TITLE + tempJournal.getTitle());
                outputStream.println(REFERENCE_ORGANIZATION + tempJournal.getOrganization());
                outputStream.println(REFERENCE_YEAR + tempJournal.getYear());
                outputStream.println();
            }
        }
    }

    /**
     * Main method of execution. Loads the references and launches the GUI.
     *
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        if (args.length != 2) {
            System.err.println("Not enough arguments");
            System.exit(0);
        }

        try {
            inputStream = new Scanner(new FileInputStream(args[0]));
        } catch (FileNotFoundException e) {
            System.err.println("Input file not found or could not be opened");
            System.exit(0);
        }

        loadReferences(inputStream); // load references from input file
        inputStream.close(); //close the input file

        LibrarySearch ls = new LibrarySearch(args[1]);
        ls.setVisible(true); // set GUI visible
    }

    /**
     * Window listener to see what the user wants to do
     */
    private class CheckOnExit implements WindowListener {

        @Override
        public void windowOpened(WindowEvent e) {
        }

        @Override
        public void windowClosing(WindowEvent e) {
            ConfirmWindow checker = new ConfirmWindow();
            checker.setVisible(true);
        }

        @Override
        public void windowClosed(WindowEvent e) {
        }

        @Override
        public void windowIconified(WindowEvent e) {
        }

        @Override
        public void windowDeiconified(WindowEvent e) {
        }

        @Override
        public void windowActivated(WindowEvent e) {
        }

        @Override
        public void windowDeactivated(WindowEvent e) {
        }
    }

    /**
     * Creates the pop up window to confirm user wants to exit the program
     */
    private class ConfirmWindow extends JFrame implements ActionListener {

        public ConfirmWindow() {
            setSize(400, 200);
            setLayout(new BorderLayout());
            getContentPane().setBackground(Color.ORANGE);
            JLabel confirmLabel = new JLabel("Are you sure you want to exit? \nYour references will not be saved.");
            add(confirmLabel, BorderLayout.CENTER);
            JPanel buttonPanel = new JPanel();
            buttonPanel.setBackground(Color.ORANGE);
            buttonPanel.setLayout(new FlowLayout());
            JButton exitButton = new JButton("Yes");
            exitButton.setBackground(Color.RED);
            exitButton.addActionListener(this);
            buttonPanel.add(exitButton);
            JButton cancelButton = new JButton("No");
            cancelButton.setBackground(Color.RED);
            cancelButton.addActionListener(this);
            buttonPanel.add(cancelButton);

            add(buttonPanel, BorderLayout.SOUTH);
        }

        @Override
        /**
         * Action listener for the confirmation window
         */
        public void actionPerformed(ActionEvent e) {
            if (e.getActionCommand().equalsIgnoreCase("Yes")) {
                System.exit(0);
            } else if (e.getActionCommand().equalsIgnoreCase("No")) {
                dispose();
            }
        }
    }
}

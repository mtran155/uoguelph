package librarysearch;

/**
 * Book Class
 *
 * @author mtran04
 */
public class Book extends Reference {

    /*
     * INSTANCE VARIABLES
     */
    private String authors;
    private String publisher;

    /*
     * CONSTRUCTORS
     */
    /**
     * Standard constructor that creates the book object with all fields
     * @param callNumber
     * @param authors
     * @param title
     * @param publisher
     * @param year 
     */
    public Book(String callNumber, String authors, String title, String publisher, int year) {
        super("Book", callNumber, title, year);
        this.authors = authors;
        this.publisher = publisher;
    }

    /*
     * MUTATORS
     */

    /**
     * Sets the authors of book
     * @param authors
     * @return 
     */
    public boolean setAuthors(String authors) {
        this.authors = authors;
        return true;
    }

    /**
     * Sets the publisher of book
     * @param publisher
     * @return 
     */
    public boolean setPublisher(String publisher) {
        this.publisher = publisher;
        return true;
    }
    /*
     * ACCESSORS
     */

    /**
     * Retrieves authors of book
     * @return 
     */
    public String getAuthors() {
        return this.authors;
    }   

    /**
     * Retrieves publisher of book
     * @return 
     */
    public String getPublisher() {
        return this.publisher;
    }

    /*
     * STANDARD CLASS METHODS
     */

    /**
     * Formats the output of the bookList in arrayList
     * @return 
     */
    @Override
    public String toString() {
        return super.getType() + ": \nCallNumber: " + super.getCallNumber() + "\nAuthors: " + authors + "\nTitle: " + super.getTitle() + "\nPublisher: " + publisher + "\nYear: " + super.getYear() + "\n";
    }
}

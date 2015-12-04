package librarysearch;

/**
 * Reference Class
 *
 * @author mtran04
 */
public class Reference {

    /*
     * INSTANCE VARIABLES
     */
    private String type;
    private String callNumber;
    private String title;
    private int year;

    /*
     * CONSTRUCTORS
     */
    /**
     * Standard constructor that creates a new reference object
     *
     * @param callNumber
     * @param title
     * @param year
     */
    public Reference(String type, String callNumber, String title, int year) {
        this.type = type;
        this.callNumber = callNumber;
        this.title = title;
        this.year = year;
    }

    /*
     * MUTATORS
     */
    /**
     * Set type of reference
     *
     * @param type
     * @return
     */
    public boolean setType(String type) {
        if (type.isEmpty()) {
            return false;
        } else {
            this.type = type;
            return true;
        }
    }

    /**
     * Set call number of reference
     *
     * @param callNumber
     * @return
     */
    public boolean setCallNumber(String callNumber) {
        if (callNumber.isEmpty()) {
            return false;
        } else {
            this.callNumber = callNumber;
            return true;
        }
    }

    /**
     * Set title of reference
     *
     * @param title
     * @return
     */
    public boolean setTitle(String title) {
        if (title.isEmpty()) {
            return false;
        } else {
            this.title = title;
            return true;
        }
    }

    /**
     * Set year of reference
     *
     * @param year
     */
    public void setYear(int year) {
        if (year < 1000 || year > 9999) {
            System.out.println("Invalid year: " + year);
            System.exit(0);
        } else {
            this.year = year;
        }
    }

    /*
     * ACCESSORS
     */
    /**
     * Retrieves type of reference
     *
     * @return
     */
    public String getType() {
        return this.type;
    }

    /**
     * Retrieves callNumber of reference
     *
     * @return
     */
    public String getCallNumber() {
        return this.callNumber;
    }

    /**
     * Retrieves title of reference
     *
     * @return
     */
    public String getTitle() {
        return this.title;
    }

    /**
     * Retrieves year of reference
     *
     * @return
     */
    public int getYear() {
        return this.year;
    }

    /*
     * STANDARD CLASS METHODS
     */
    /**
     * Compares other reference objects to see if equal
     *
     * @param other
     * @return
     */
    
    @Override
    public boolean equals(Object other) {
        if (other == null) {
            return false;
        } else if (other.getClass() != this.getClass()) {
            return false;
        } else {
            Reference otherReference = (Reference) other;
            return callNumber.equals(otherReference.callNumber) && year == otherReference.year;
        }
    }
}
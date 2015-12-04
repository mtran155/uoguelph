package librarysearch;

/**Journal Class
 *
 * @author mtran04
 */
public class Journal extends Reference {

    /*
     * INSTANCE VARIABLES
     */
    private String organization;

    /*
     * CONSTRUCTORS
     */
    
    /**
     * Standard constructor that creates the journal object with all fields
     * @param callNumber
     * @param title
     * @param organization
     * @param year 
     */
    public Journal(String callNumber, String title, String organization, int year) {
        super("Journal", callNumber, title, year);
        this.organization = organization;
    }

    /*
     * MUTATORS
     */

    /**
     * Sets the organization of journal
     * @param organization
     * @return 
     */
    public boolean setOrganization(String organization) {
        this.organization = organization;
        return true;
    }

    /*
     * ACCESSORS
     */

    /**
     * Retrieves organization of journal
     * @return 
     */
    public String getOrganization() {
        return this.organization;
    }

    /**
     * Format the output the journalList in arrayList
     * @return 
     */
    @Override
    public String toString() {
        return super.getType() + ": \nCallNumber: " + super.getCallNumber() + "\nTitle: " + super.getTitle() + "\nOrganization: " + organization + "\nYear: " + super.getYear() + "\n";
    }
}

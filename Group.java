public class Group {
    String name;
    String eventID;
    String groupID;
    int numMembers;

    public Group(String name, String eventID, String groupID, int numMembers) {
        this.name = name;
        this.eventID = eventID;
        this.groupID = groupID;
        this.numMembers = numMembers;
    }

    @Override
    public String toString() {
        return name + ", " + eventID + ", " + groupID + ", " + numMembers;
    }
}
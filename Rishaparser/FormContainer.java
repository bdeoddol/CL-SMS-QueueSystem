package Rishaparser;
public class FormContainer {
    String fullName;
    String primaryPhoneNumber;
    int projectID;
    int groupSize;
    

    public FormContainer(String var1, String var2, int var3, int var4) {
        this.fullName = var1;
        this.primaryPhoneNumber = var2;
        this.groupSize = var3;
        this.projectID = var4;
    }

    public String toString() {
        return this.fullName + ", " + this.primaryPhoneNumber + ", size: " + 
        this.groupSize + ", project id: " + this.projectID;
   }
}

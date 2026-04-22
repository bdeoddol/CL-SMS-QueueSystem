package Rishaparser;
public class FormContainer {
    String _fullName;
    String _primaryPhoneNumber;
    int _projectID;
    int _groupSize;

    public FormContainer(String var1, String var2, int var3, int var4) {
        this._fullName = var1;
        this._primaryPhoneNumber = var2;
        this._groupSize = var3;
        this._projectID = var4;
    }

    public String toString() {
        return this._fullName + ", " + this._primaryPhoneNumber + ", size: " + 
        this._groupSize + ", project id: " + this._projectID;
   }
}

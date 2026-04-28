// Source code is decompiled from a .class file using FernFlower decompiler (from Intellij IDEA).
package Rishaparser;

public class FormContainer {
   String _fullName;
   String _primaryPhoneNumber;
   int _projectID;
   int _groupSize;
   int _msgID;

   public FormContainer(String var1, String var2, int var3, int var4, int var5) {
      this._fullName = var1;
      this._primaryPhoneNumber = var2;
      this._groupSize = var3;
      this._projectID = var4;
      this._msgID = var5;

   }

   public int getMsgInc() {
      return _msgID;
   }


   public String toString() {
      return this._fullName + ", " + this._primaryPhoneNumber + ", size: " + this._groupSize + ", project id: " + this._projectID + ", msg id: " + this._msgID;
   }
}

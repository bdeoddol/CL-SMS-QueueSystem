package Rishaparser;


public class receiveUserInstruct implements Runnable {
    private static Parser currParser;

    public void receieveUserInstruct(Parser trackParser){
        currParser = trackParser;
    }

    public void run(){
        while(currParser.isPaused() == true){
            
        }
    }
}

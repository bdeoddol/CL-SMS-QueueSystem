package Rishaparser;

import java.io.InputStreamReader;
import java.io.IOException;
import java.net.Socket;
import java.net.URL;
import java.util.ArrayList;

import com.opencsv.CSVReader;
import com.google.gson.Gson;
import java.io.DataInputStream;
import java.io.DataOutput;
import java.io.DataOutputStream;

import java.net.ServerSocket;


public class Parser {
    //state
    private static volatile boolean _paused;
    // private static 


    private final String sheetUrl;
    private final Gson gson;
    private int lastSeen = -1;
    private int lastFetch = -1;
    private int stableCount = 0;
    private static final int REQ_STABLE = 3;
    

    private static boolean _connected;
    private static int _port;
    private static DataInputStream _in;
    private static DataOutputStream _out;
    private static ServerSocket _server;
    private static Socket _socketConnect;
    

    // private static Thread _receiveUserThread;
    // receiveUserInstruct jobWork;
    

    public Parser(String sheetUrl) {
        this.gson = new Gson();

        jobWork = new receiveUserInstruct();
        _receiveUserThread = null;

        this.sheetUrl = sheetUrl;
        _connected = false;
        _paused = false;

    }

    public ArrayList<FormContainer> fetchEntries() throws Exception {
        String noCacheUrlPlease = sheetUrl + "&t=" + System.currentTimeMillis();
        CSVReader csvReader = new CSVReader(new InputStreamReader((new URL(noCacheUrlPlease)).openStream()));
        ArrayList<FormContainer> entries = new ArrayList<>();
        boolean firstLine = true;
        int msgInc = -1;

        String[] fields;
        while((fields = csvReader.readNext()) != null) {
            if(firstLine) {
                firstLine = false;
                continue;
            }
            if(fields.length < 5) continue;
            msgInc++;
            entries.add(new FormContainer(fields[1], fields[2], 
                parseOrDefault(fields[3], 0), 
                parseOrDefault(fields[4], 0), 
                msgInc));
        }

        csvReader.close();
        return entries;
    }

      public void run() throws Exception {
        startInputListener();
        while (true) {
            if (!_paused) {
                ArrayList<FormContainer> entries = fetchEntries();
                int currentCount = entries.size();

                if(currentCount == lastFetch) {
                    stableCount++;
                } else {
                    stableCount = 0;
                }

                if(stableCount >= REQ_STABLE && currentCount > (lastSeen + 1)) {
                    ArrayList<FormContainer> newEntries = new ArrayList<>();
                    for(int i = lastSeen + 1; i < entries.size(); i++) {
                        newEntries.add(entries.get(i));
                    }
                    lastSeen = currentCount - 1;
                    stableCount = 0;
                    System.out.println(gson.toJson(newEntries));
                }
                lastFetch = currentCount;
            }
            Thread.sleep(3000);
        }
    }

    private int parseOrDefault(String s, int defaultVal) {
        try {
            return Integer.parseInt(s.trim());
        } catch (NumberFormatException e) {
            return defaultVal;
        }
}

    public void startInputListener() {
        Thread inputThread = new Thread(() -> {
            try {
                while (true) {
                    char key = (char) System.in.read();
                    if (key == ' ') {
                        _paused = !_paused;
                        System.out.println(_paused ? "\n===paused===" : "\n===unpaused===");
                    }
                }
            } catch (IOException e) {
                e.printStackTrace();
            }
        });
        inputThread.setDaemon(true);
        inputThread.start();
    }


    public void startUpServerSocket(int port){
        _port = port;
        try {
            _server = new ServerSocket(_port);
        } 
        catch (IOException | IllegalArgumentException e) { //check serversocket documentation
            System.out.println("An error has occured while calling startUpServerSocket. returning.....");
        }
    }

    public void awaitClientConnection(){
        System.out.println("Awaiting client connection...");
        try {
            //https://docs.oracle.com/javase/8/docs/api/java/net/ServerSocket.html#accept--
            //.accept() is a blocking function that halts execution until a connection is made
            _socketConnect = _server.accept(); 
            System.out.println("A connection has been made on port: " + _port);
            _in = new DataInputStream(_socketConnect.getInputStream());
            _out = new DataOutputStream(_socketConnect.getOutputStream());
        } catch (IOException e) {
            System.out.println("An error has occured awaiting a connection. Stopping attempt...");
        }

    }

    public boolean isPaused(){
        return _paused;
    }

    // public static void main(String[] args) throws Exception {
    //     String url = "https://docs.google.com/spreadsheets/d/e/2PACX-1vSFDUhAVVoYXpQvqKQ0FrBU_c3c5vPG-ImbMxqeZhKfz0gStUOADiTnmxlbn_q0ar_q8xCiffIr0UVk/pub?output=csv";
    //     new Parser(url);
    //     Parser.startUpServerSocket(800);
    //     Parser.awaitClientConnection();

    //     // new Parser(url).run();





    //     int port = 8000;
    //     int aNumber;
    //     DataInputStream in;
    //     DataOutputStream out;

    //     ServerSocket server;
    //     Socket socketConnect;

    //     server = new ServerSocket(port);
    //     socket = server.accept();

    //     in = new DataInputStream(socket.getInputStream());
    //     out = new DataOutputStream(socket.getOutputStream());

    //     System.out.println(in.readByte());
    //     out.writeDouble(aNumber);
        

    // }
}
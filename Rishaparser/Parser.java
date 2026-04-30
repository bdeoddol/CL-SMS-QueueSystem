package Rishaparser;

import java.io.InputStreamReader;
import java.io.IOException;
import java.net.Socket;
import java.net.URI;
import java.util.ArrayList;

import com.opencsv.CSVReader;
import com.google.gson.Gson;
import java.io.DataInputStream;
// import java.io.DataOutput;
import java.io.DataOutputStream;

import java.net.ServerSocket;


public class Parser {
    //state
    private static volatile boolean _paused;
    // private static 


    private final String[] sheetUrls;
    private final Gson gson;
    private int[] lastSeen = new int[3];
    private int[] lastFetch = new int[3];
    private int[] stableCount = new int[3];
    private static final int REQ_STABLE = 3;
    

    private static boolean _connected;
    private static int _port;
    private static DataInputStream _in;
    private static DataOutputStream _out;
    private static ServerSocket _server;
    private static Socket _socketConnect;
    

    // private static Thread _receiveUserThread;
    // receiveUserInstruct jobWork;
    

    public Parser(String[] sheetUrls) {
        this.gson = new Gson();
        this.sheetUrls = sheetUrls;
        
        for(int i = 0; i < 3; i++) {
            lastSeen[i] = -1;
            lastFetch[i] = -1;
            stableCount[i] = 0;
        }
        

        // jobWork = new receiveUserInstruct();
        // _receiveUserThread = null;

        _connected = false;
        _paused = false;

    }

    public ArrayList<FormContainer> fetchEntries(String url) throws Exception {
        String noCacheUrlPlease = url + "&t=" + System.currentTimeMillis();
        CSVReader csvReader = new CSVReader(new InputStreamReader(URI.create(noCacheUrlPlease).toURL().openStream()));
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
        startReceiveListener();
        while (true) {
            if (!_paused) {
                ArrayList<FormContainer> allNewEntries = new ArrayList<>();
                
                for(int i = 0; i < 3; i++) {
                    if(sheetUrls[i].isEmpty()) continue;

                    ArrayList<FormContainer> entries = fetchEntries(sheetUrls[i]);
                    int currentCount = entries.size();

                    if(currentCount == lastFetch[i]) {
                        stableCount[i]++;
                    } else {
                        stableCount[i] = 0;
                    }

                    if(stableCount[i] >= REQ_STABLE && currentCount > (lastSeen[i] + 1)) {
                        for(int j = lastSeen[i] + 1; j < entries.size(); j++) {
                            allNewEntries.add(entries.get(j));
                        }
                        lastSeen[i] = currentCount - 1;
                        stableCount[i] = 0;
                    }
                    lastFetch[i] = currentCount;
                }
                for(FormContainer entry : allNewEntries) {
                    String json = gson.toJson(entry);
                    System.out.println(json);
                    sendToClient(json);
                }
            }
            Thread.sleep(500);
        }
    }

    private int parseOrDefault(String s, int defaultVal) {
        try {
            return Integer.parseInt(s.trim());
        } catch (NumberFormatException e) {
            return defaultVal;
        }
    }

    public void sendToClient(String json) {
        if(_out == null) {
            System.out.println("!!! out is null; wrong run order");
            return;
        }
        
        try {
            _out.writeBytes(json + "\n");
            _out.flush();
            System.out.println("sent");
        } catch (IOException e) {
            System.out.println("! Error sending to client");
        }
    }

    public void startReceiveListener() {
        Thread receiveThread = new Thread(() ->  {
            try {
                StringBuilder buffer = new StringBuilder();
                int b;
                while((b = _in.read()) != -1) {
                    char c = (char) b;
                    if(c == '\n') {
                        String msg = buffer.toString().trim();
                        buffer.setLength(0);

                        if(msg.startsWith("c-")) {
                            try {
                                int confirmedID = Integer.parseInt(msg.substring(2));
                                System.out.println("Confirmed msgID: " + confirmedID);
                            } catch(NumberFormatException e) {
                                System.out.println("! Bad confirmation key");
                            }
                        } else if(msg.equals("p")) {
                            _paused = true;
                            System.out.println("===paused===");
                        } else if(msg.equals("s")) {
                            _paused = false;
                            System.out.println("===unpaused===");
                        }
                    } else {
                        buffer.append(c);
                    }
                }
            } catch(IOException e) {
                System.out.println("! Receiver listener error: " + e.getMessage());
            }
        });
        receiveThread.setDaemon(true);
        receiveThread.start();
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
            _connected = true;
        } catch (IOException e) {
            System.out.println("An error has occured awaiting a connection. Stopping attempt...");
        }

    }

    public boolean isPaused(){
        return _paused;
    }


}
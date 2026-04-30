package Rishaparser;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.net.ServerSocket;
import java.net.Socket;

public class Main {
        public static void main(String[] args) throws Exception {
        String frUrl = "https://docs.google.com/spreadsheets/d/e/2PACX-1vSXeOhlScR5caXUwFzHc0nqhQdjbzDZvouMhqR7-lE-0DgI_E1T3xHAedY_QAqSkxTlioNPrHS5dyMr/pub?gid=1347883480&single=true&output=csv";
        String esUrl = "https://docs.google.com/spreadsheets/d/e/2PACX-1vSXeOhlScR5caXUwFzHc0nqhQdjbzDZvouMhqR7-lE-0DgI_E1T3xHAedY_QAqSkxTlioNPrHS5dyMr/pub?gid=195098169&single=true&output=csv";
        String ddUrl = "https://docs.google.com/spreadsheets/d/e/2PACX-1vSXeOhlScR5caXUwFzHc0nqhQdjbzDZvouMhqR7-lE-0DgI_E1T3xHAedY_QAqSkxTlioNPrHS5dyMr/pub?gid=1861108058&single=true&output=csv";

        String[] urls = {frUrl, esUrl, ddUrl};
        Parser mainParser = new Parser(urls);

        mainParser.startUpServerSocket(800);
        mainParser.awaitClientConnection();
        mainParser.run();




        // int port = 8000;
        // int aNumber;
        // DataInputStream in;
        // DataOutputStream out;

        // ServerSocket server;
        // Socket socketConnect;

        // server = new ServerSocket(port);
        // //socket = server.accept();

        // in = new DataInputStream(socket.getInputStream());
        // out = new DataOutputStream(socket.getOutputStream());

        // System.out.println(in.readByte());
        // out.writeDouble(aNumber);
        

    }
}

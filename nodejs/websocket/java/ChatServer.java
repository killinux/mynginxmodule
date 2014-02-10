import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.InetAddress;
import java.net.InetSocketAddress;
import java.net.UnknownHostException;
import java.util.Set;

import org.java_websocket.WebSocket;
import org.java_websocket.WebSocketServer;
import org.java_websocket.handshake.ClientHandshake;

public class ChatServer extends WebSocketServer {

	public ChatServer( int port ) throws UnknownHostException {
		//				super( new InetSocketAddress( "10.221.12.197", port ) );
				//		super( new InetSocketAddress( "203.195.183.79", port ) );
		//		super( new InetSocketAddress( "localhost/127.0.0.1", port ) );
				super( new InetSocketAddress( InetAddress.getByName( "localhost" ), port ) );
		
	}

	public ChatServer( InetSocketAddress address ) {
		super( address );
	}

	@Override
	public void onOpen( WebSocket conn, ClientHandshake handshake ) {
		try {
			this.sendToAll( "new" );
		} catch ( InterruptedException ex ) {
			ex.printStackTrace();
		}
		System.out.println( conn + " entered the room!" );
	}

	@Override
	public void onClose( WebSocket conn, int code, String reason, boolean remote ) {
		try {
			this.sendToAll( conn + " has left the room!" );
		} catch ( InterruptedException ex ) {
			ex.printStackTrace();
		}
		System.out.println( conn + " has left the room!" );
	}

	@Override
	public void onMessage( WebSocket conn, String message ) {
		try {
			this.sendToAll( message );
		} catch ( InterruptedException ex ) {
			ex.printStackTrace();
		}
		System.out.println( conn + ": " + message );
	}


	@Override
	public void onError( WebSocket conn, Exception ex ) {
		ex.printStackTrace();
	}

	public void sendToAll( String text ) throws InterruptedException {
		Set<WebSocket> con = connections();
		synchronized ( con ) {
			for( WebSocket c : con ) {
				c.send( text );
			}
		}
	}
	
	///////////////////////////////////////////////////////////////////////////////////////
	public static void main( String[] args ) throws InterruptedException , IOException {
		//connection
		WebSocket.DEBUG = true;
		int port = 8887;
		try {
			port = Integer.parseInt( args[ 0 ] );
		} catch ( Exception ex ) { }
		ChatServer s = new ChatServer( port );
		s.start();
		System.out.println( "ChatServer started on port: " + s.getPort() );

		//server message 
		BufferedReader sysin = new BufferedReader( new InputStreamReader( System.in ) );
		while ( true ) {
			String in = sysin.readLine();
			s.sendToAll( in );
		}
	}

}

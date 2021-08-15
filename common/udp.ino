// ---------------------------------------------------------------
/*
	udp.ino

					Aug/07/2021
*/
// ---------------------------------------------------------------
int udp_open_proc(){
//	SerialUSB.println("### Open.");
	int connectId;
	connectId = Wio.SocketOpen("harvest.soracom.io", 8514, WIOLTE_UDP);
	if (connectId < 0) {
		SerialUSB.println("### ERROR! SocketOpen ###");
	}

	return connectId;
}

// ---------------------------------------------------------------
void udp_close_proc(int connectId){
//	SerialUSB.println("### Close.");
	if (!Wio.SocketClose(connectId)) {
		SerialUSB.println("### ERROR! SocketClose ###");
	}

}

// ---------------------------------------------------------------
boolean udp_send_proc(int connectId,char data_json[]){
//	SerialUSB.println("### Send.");
	SerialUSB.print("Send:");
	SerialUSB.print(data_json);
	SerialUSB.println("");
	boolean result = Wio.SocketSend(connectId, data_json);
	if (!result){
		SerialUSB.println("### ERROR! SocketSend ###");
	}
	return result;
}

// ---------------------------------------------------------------
boolean udp_receive_proc(int connectId){
		char data_rec[128];

	boolean result = true;
	
//	SerialUSB.println("### Receive.");
	int length;
	length = Wio.SocketReceive(connectId, data_rec, sizeof (data_rec), RECEIVE_TIMEOUT);
	if (length < 0) {
		SerialUSB.println("### ERROR! SocketReceive ###");
		result = false;
	}
	else if (length == 0) {
		SerialUSB.println("### RECEIVE TIMEOUT! ###");
		result = false;
	}
	else {
	SerialUSB.print("Receive:");
	SerialUSB.print(data_rec);
	SerialUSB.println("");

	return result;
	}
}

// ---------------------------------------------------------------

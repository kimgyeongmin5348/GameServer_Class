// ---------------------------------------------------------------------------
// 03_25 4주차 1일 (화요일)
// ---------------------------------------------------------------------------
// 
// n:1 echo server
//	서버에서 여러개의 접속을 유지해야함.
//		소켓에 대한 정보를 세셩(SESSION)이라고 많이 부름.
//		unordered_map<int,SESSION>이 필요.
//		SESSION은 Recv할 때마다 new/delete 하는 것 보다 효율적이다.
// 
//	다중 접속 Accept
//		모든 컨텐츠는 callback에서 실행되며 메인 루틴은 accept를 계속 받음.
//		우리는 accept만 하면 된다. callback도 알아서 해준다.
//			while (true) {
//				SOCKET s_client = WSAAccept(server, reinterpret_cast<sockaddr*>(&cl_addr), &addr_size, NULL, NULL);						
//				add_session(s_client);
//				do_recv(s_client);
//			}
//	
//// ---------------------------------------------------------------------------
// 03_27 4주차 2일 (목요일)
// ---------------------------------------------------------------------------
// 
//	채팅서버 ( echo server에서의 진화 )
//		진정한 멀티플레이의 시작
//		클라이언트에 다른 클라이언트의 메시지도 전달해 주어야 함.
//		send 와 recv가 차례로 호출되지 않고 동시 다발적으로 발생.
//		Packet 단위로 Send/Recv 가 되어야 한다.
//		Send/Recv가 더이상 OVERLAPPED, WSABUF, BUF를 공유할 수 없다.
//			- send가 독립적으로 (비동기적으로) 실행되기 때문.
//			- 모든 send는 overlapped/wsabuf/buf 를 별도의 객체를 사용해서 수행해야 한다.
//			- overlapped 포인터로 WSABUF와 BUF의 주소를 찾아야 한다.
//		클라이언트 수정 필요
//			- 분리가 필요함.
// 
// 
// 
//
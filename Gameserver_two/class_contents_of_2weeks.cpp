// ---------------------------------------------------------------------------
// 03_11 2주차 1일 (화요일) <- 노트북으로 작성하였음.
// ---------------------------------------------------------------------------
// 
// 
// ---------------------------------------------------------------------------
// 03_13 2주차 2일 (목요일)
// ---------------------------------------------------------------------------
// 
// Socket 만들기
//	SOCKET WSASocket(int af, int type, int protocol, LPWSAPROTOCOL_INFO lpProtocolInfo, GROUP g, DWORDdwFlags);
//		af : 인터넷 주소
//		type : 이번 수업에는 SOCK_STREAM만 사용할 것이다.
//		protocol : IPPROTO_TCP 만 사용할 것이다.
//		IpProtocolInfo : 우리는 이런거 안쓸거다.
//		g : 우리는 이런거 안쓸거다.
//	
// 
// Socket 연결
//	int WSAConnect(SOCKET s, const struct sockaddr* name, int namelen, LPWSABUF lpCallerData, LPWSABUF lpCalleeData, LPQOS lpSQOS, LPQOS lpGQOS);
//		s : 소켓
//		name, namelen : 상대 소켓 주소, 주소 길이
//		나머지 : 쓸일 없으니 다 NULL로 해주면 된다.
// 
// 
// sockaddr 주소 수조체
//	네트워크 주소를 저장. ( IP주소와 PORT번호 )
//	SEVER_PORT는 short, SERVER_IP는 문자열
// 
// 
// Socket에서 데이터 받기
//	int WSARecv(SOCKET s, LPWSABUF lpBuffers, DWORD dwBufferCount, LPDWORD lpNumberofBytesRecvd, LPDWORD lpFlags, LPWSAOVERLAPPED lpOverlapped, LPWSAOVERLAPPED_COMPLETION_ROUTINElpCompletionRoutine);
//		lpBuffers : 받은 데이터를 저장할 버퍼
//		dwBufferCount : 버퍼의 개수
//		lpFlags : 동작 옵션(MSG_PEEK, MSG_OOB)
//		lpNumberofBytesRecvd : 받은 데이터의 크기
//		lpOverlapped, lpCompletionRoutine : 뒤에 설명
// 
// 
// Socket에서 데이터 보내기
//	int WSASend(SOCKET s, LPWSABUF lpBuffers, DWORD dwBufferCount, LPDWORD lpNumberofBytesSent, DWORD dwFlags, LPWSAOVERLAPPED lpOverlapped, LPWSAOVERLAPPED_COMPLETION_ROUTINElpCompletionRoutine);
//		s : 소켓
//		lpBuffers : 보내는 데이터가 저장된 버퍼
//		dwBufferCount : 버퍼의 개수
//		lpFlags : 동작 옵션(MSG_OOB)
//		lpNumberofBytesSent : 보낸 데이터의 크기
//		lpOverlapped, lpCompletionRoutine : 뒤에 설명
// 
// 
// 
//
// --------------------------- < 추가 설명 들> --------------------------------
// 
// 
// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
// 03_11 2���� 1�� (ȭ����) <- ��Ʈ������ �ۼ��Ͽ���.
// ---------------------------------------------------------------------------
// 
// 
// ---------------------------------------------------------------------------
// 03_13 2���� 2�� (�����)
// ---------------------------------------------------------------------------
// 
// Socket �����
//	SOCKET WSASocket(int af, int type, int protocol, LPWSAPROTOCOL_INFO lpProtocolInfo, GROUP g, DWORDdwFlags);
//		af : ���ͳ� �ּ�
//		type : �̹� �������� SOCK_STREAM�� ����� ���̴�.
//		protocol : IPPROTO_TCP �� ����� ���̴�.
//		IpProtocolInfo : �츮�� �̷��� �Ⱦ��Ŵ�.
//		g : �츮�� �̷��� �Ⱦ��Ŵ�.
//	
// 
// Socket ����
//	int WSAConnect(SOCKET s, const struct sockaddr* name, int namelen, LPWSABUF lpCallerData, LPWSABUF lpCalleeData, LPQOS lpSQOS, LPQOS lpGQOS);
//		s : ����
//		name, namelen : ��� ���� �ּ�, �ּ� ����
//		������ : ���� ������ �� NULL�� ���ָ� �ȴ�.
// 
// 
// sockaddr �ּ� ����ü
//	��Ʈ��ũ �ּҸ� ����. ( IP�ּҿ� PORT��ȣ )
//	SEVER_PORT�� short, SERVER_IP�� ���ڿ�
// 
// 
// Socket���� ������ �ޱ�
//	int WSARecv(SOCKET s, LPWSABUF lpBuffers, DWORD dwBufferCount, LPDWORD lpNumberofBytesRecvd, LPDWORD lpFlags, LPWSAOVERLAPPED lpOverlapped, LPWSAOVERLAPPED_COMPLETION_ROUTINElpCompletionRoutine);
//		lpBuffers : ���� �����͸� ������ ����
//		dwBufferCount : ������ ����
//		lpFlags : ���� �ɼ�(MSG_PEEK, MSG_OOB)
//		lpNumberofBytesRecvd : ���� �������� ũ��
//		lpOverlapped, lpCompletionRoutine : �ڿ� ����
// 
// 
// Socket���� ������ ������
//	int WSASend(SOCKET s, LPWSABUF lpBuffers, DWORD dwBufferCount, LPDWORD lpNumberofBytesSent, DWORD dwFlags, LPWSAOVERLAPPED lpOverlapped, LPWSAOVERLAPPED_COMPLETION_ROUTINElpCompletionRoutine);
//		s : ����
//		lpBuffers : ������ �����Ͱ� ����� ����
//		dwBufferCount : ������ ����
//		lpFlags : ���� �ɼ�(MSG_OOB)
//		lpNumberofBytesSent : ���� �������� ũ��
//		lpOverlapped, lpCompletionRoutine : �ڿ� ����
// 
// 
// 
//
// --------------------------- < �߰� ���� ��> --------------------------------
// 
// 
// ---------------------------------------------------------------------------
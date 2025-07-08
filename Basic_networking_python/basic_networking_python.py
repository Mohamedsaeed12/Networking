# Import socket module
from socket import *
import sys  # In order to terminate the program

# Prepare a server socket
serverSocket = socket(AF_INET, SOCK_STREAM)

# Fill in start
serverPort = 6789  # port given by you
serverSocket.bind(('', serverPort))  # Bind the socket to the server's IP and port
serverSocket.listen(1)
# Fill in end

while True:
    # Establish the connection
    print("Ready to serve...")
    connectionSocket, addr = serverSocket.accept()
    
    try:
        message = connectionSocket.recv(1024).decode()
        filename = message.split()[1]
        f = open(filename[1:], 'r')
        outputdata = f.read()

        # Fill in start
        connectionSocket.send("HTTP/1.1 200 OK\r\n\r\n".encode())

        for i in range(0, len(outputdata)):
            connectionSocket.send(outputdata[i].encode())

        connectionSocket.send("\r\n".encode())
        connectionSocket.close()
        
    except IOError:
        # Send response message for file not found
        # Fill in start
        connectionSocket.send("HTTP/1.1 404 Not Found\r\n\r\n".encode())  # 404 Error response
        connectionSocket.send("<html><body><h1>404 Not Found</h1></body></html>\r\n".encode())  # Send 404 HTML
        connectionSocket.close()

    serverSocket.close()
    sys.exit()  # Terminate the program after sending the corresponding data
    

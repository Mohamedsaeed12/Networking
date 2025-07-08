from socket import *

# Server configuration
serverPort = 12000
serverSocket = socket(AF_INET, SOCK_STREAM)
serverSocket.bind(('', serverPort))
serverSocket.listen(1)

print("The server is ready to receive")

# Accept client connection
connectionSocket, addr = serverSocket.accept()
print(f"Connection established with: {addr}")

# Main server loop
while True:
    sentence = connectionSocket.recv(1024).decode()
    
    if not sentence:
        print("Client disconnected")
        break
    
    print(f"Received from client: {sentence.strip()}")
    capitalizedSentence = sentence.upper()
    connectionSocket.send(capitalizedSentence.encode())

# Clean up
connectionSocket.close()

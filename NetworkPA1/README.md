# Python Networking Examples

This folder contains simple Python networking projects for educational purposes:
- A basic HTTP file server
- A TCP echo server

## Contents

- `simple_http_server.py` — Serves HTML files over HTTP (formerly `networkPA1.py`)
- `tcp_echo_server.py` — Responds to TCP clients by echoing messages (formerly `Problem12.py`)
- `helloworld.html` — Example HTML file to serve
- `notfound.html` — Custom 404 error page
- `Screenshot ...png` — Example output screenshots

## Requirements
- Python 3.x (no external libraries required)

## Usage

### 1. HTTP File Server
Serves files over HTTP on port 6789. You can access it from your browser.

```bash
python simple_http_server.py
# Then visit: http://localhost:6789/helloworld.html
```

- If the file exists, it will be served.
- If not, a 404 error page (`notfound.html`) is shown.

### 2. TCP Echo Server
Listens for TCP connections on port 12000 and echoes back any received messages.

```bash
python tcp_echo_server.py
# In another terminal:
telnet localhost 12000
# Or use netcat:
nc localhost 12000
```

Type messages and see them echoed back in uppercase.

## HTML Files
- `helloworld.html`: A simple HTML page for testing the HTTP server.
- `notfound.html`: Displayed when a requested file is not found.

## Screenshots
- PNG files show example server output and browser/client interaction.

## Notes
- These scripts are for learning and demonstration. Do not use in production.
- Make sure the required ports are free before running the servers.

## References
- [Python socket documentation](https://docs.python.org/3/library/socket.html) 
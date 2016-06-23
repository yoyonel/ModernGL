import http.server
import socketserver

httpd = socketserver.TCPServer(('127.0.0.1', 80), http.server.SimpleHTTPRequestHandler)
httpd.serve_forever()

from http.server import BaseHTTPRequestHandler, HTTPServer
import os

import time

# Path to the named pipe
pipe_path = "/tmp/mousepipe"

# Function to send commands to the named pipe
def send_command(command):
    try:
        with open(pipe_path, "w") as pipe:
            pipe.write(command)
        print(f"Sent command: {command}")
    except Exception as e:
        print(f"Error sending command: {e}")



class RequestHandler(BaseHTTPRequestHandler):
    # Define the response to GET requests
    def do_GET(self):
        # Serve the HTML file when the root URL is requested
        if self.path == '/' or self.path == '/index.html':
            self.send_response(200)
            self.send_header('Content-type', 'text/html')
            self.end_headers()
            with open('index.html', 'rb') as f:
                self.wfile.write(f.read())
        elif self.path.startswith('/keypress'):
            # Handle button click events
            key = self.path.split('?')[1].split('=')[1]
            print('Key pressed:', key)
            self.send_response(200)
            self.send_header('Content-type', 'text/plain')
            self.end_headers()
            # self.wfile.write(('Key pressed: ' + key).encode())
            send_command(key)




        else:
            # Handle 404 Not Found
            self.send_error(404, 'File not found')

def run_server(port=8000):
    # Create the HTTP server
    server_address = ('', port)
    httpd = HTTPServer(server_address, RequestHandler)
    print('Server is running on port', port)
    httpd.serve_forever()

if __name__ == '__main__':
    run_server()
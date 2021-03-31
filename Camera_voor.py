import io
import picamera
import logging
import socketserver
from threading import Condition
from http import server

PAGE="""\
<html>
<head>
<style type="text/css"> html { 
  background: url(
https://www.pixelstalk.net/wp-content/uploads/2015/05/Blue-sea-landscape-wallpaper.jpg) 
    no-repeat center center fixed; 
  -webkit-background-size: cover;
  -moz-background-size: cover;
  background-size: cover;
}

#wrapper {width: 500px;
margin: 0 auto;}

div.camera_voor{
	position: fixed;
	top: 150px;
	left: 200px;
}

div.camera_achter{
	position: fixed;
	top: 150px;
	right:200px;
	
}
</style>

<title>Raspberry Pi - Surveillance Camera</title>
</head>

<body>
	
<div id="wrapper">
	
<h1 style="color:white">Raspberry Pi - RC_Boat Front View</h1></center>

<div class= "camera_voor">	<img src="stream.mjpg" width="480" height="640">
	</div>		
	
<div class= "camera_achter">	<img src="stream_achter.mjpg" width="480" height="640">
	</div>

<button onclick="window.location.href='http://192.168.0.122:8000';">
      Click Here
    </button>

</div>
</body>
</html>


"""



class StreamingOutput(object):
    def __init__(self):
        self.frame = None
        self.buffer = io.BytesIO()
        self.condition = Condition()

    def write(self, buf):
        if buf.startswith(b'\xff\xd8'):
            # New frame, copy the existing buffer's content and notify all
            # clients it's available
            self.buffer.truncate()
            with self.condition:
                self.frame = self.buffer.getvalue()
                self.condition.notify_all()
            self.buffer.seek(0)
        return self.buffer.write(buf)

class StreamingHandler(server.BaseHTTPRequestHandler):
    def do_GET(self):
        if self.path == '/':
            self.send_response(301)
            self.send_header('Location', '/index.html')
            self.end_headers()
        elif self.path == '/index.html':
            content = PAGE.encode('utf-8')
            self.send_response(200)
            self.send_header('Content-Type', 'text/html')
            self.send_header('Content-Length', len(content))
            self.end_headers()
            self.wfile.write(content)
        elif self.path == '/stream.mjpg':
            self.send_response(200)
            self.send_header('Age', 0)
            self.send_header('Cache-Control', 'no-cache, private')
            self.send_header('Pragma', 'no-cache')
            self.send_header('Content-Type', 'multipart/x-mixed-replace; boundary=FRAME')
            self.end_headers()
            try:
                while True:
                    with output.condition:
                        output.condition.wait()
                        frame = output.frame
                    self.wfile.write(b'--FRAME\r\n')
                    self.send_header('Content-Type', 'image/jpeg')
                    self.send_header('Content-Length', len(frame))
                    self.end_headers()
                    self.wfile.write(frame)
                    self.wfile.write(b'\r\n')
            except Exception as e:
                logging.warning(
                    'Removed streaming client %s: %s',
                    self.client_address, str(e))
        else:
            self.send_error(404)
            self.end_headers()

class StreamingServer(socketserver.ThreadingMixIn, server.HTTPServer):
    allow_reuse_address = True
    daemon_threads = True

with picamera.PiCamera(resolution='640x480', framerate=50) as camera:
    output = StreamingOutput()
    #Uncomment the next line to change your Pi's Camera rotation (in degrees)
    #camera.rotation = 90
    camera.start_recording(output, format='mjpeg')
    try:
        address = ('', 8000)
        server = StreamingServer(address, StreamingHandler)
        server.serve_forever()
    finally:
        camera.stop_recording()
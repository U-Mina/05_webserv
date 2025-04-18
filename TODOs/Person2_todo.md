Week 14/04/2025
- handle GET request
- send chunks to client
- properly settle getMediaType and ContentType

17/04/2025
- directory listing

18/04/2025
- handle DELETE, POST, etc request
- Install NGINX and telnet to check (directory listing in special)

19-20/04/2025
- Have a working program with default config
- Error pages

Week 21/04/2025
- CGI

Week
- caching

Check:
- Presence of message body just in the cases when needed https://datatracker.ietf.org/doc/html/rfc9112#name-message-body-length
- Read related RFC more carefully


Person 2: Request Processing and Response Generation

HTTP response generation
File handling and MIME type detection
Implementation of HTTP methods (GET, POST, etc.)
CGI script execution
Directory listing generation

Person 2: Request Processing and Response Generation
1. HTTP Response Generation

Response Structure Creation:

<!-- Generate status line (HTTP version, status code, reason phrase)
Construct response headers
Prepare response body -->
* Read RFC for situations in which display body, length, etc.!?


Status Code Handling:

<!-- Implement all required HTTP status codes (200, 404, 500, etc.) -->
* Generate appropriate error pages


Header Management:

* Set Content-Type, Content-Length headers
Handle conditional headers (If-Modified-Since, etc.)
* Implement caching headers


Response Compression:

Support gzip/deflate encoding
Determine when to compress responses



2. File Handling and MIME Type Detection

File Access:

Open and read files securely
Handle file permissions
Implement partial content (Range requests)


MIME Type Detection:

Create a MIME type mapping system
Auto-detect content types
Handle binary vs text files correctly


Static File Serving:

Optimize file delivery
Support directory indexes
Handle symbolic links safely



3. Implementation of HTTP Methods

GET Method:

Retrieve resources
Handle conditional GETs
Support query parameters


POST Method:

Process form submissions
Handle file uploads
Parse multipart/form-data


DELETE Method:

Remove resources if permitted
Generate proper responses


Other Methods (PUT, HEAD, OPTIONS):

Implement as required by project specifications



4. CGI Script Execution

CGI Environment Setup:

Set environment variables (PATH_INFO, QUERY_STRING, etc.)
Pass request data
Handle HTTP headers conversion


Process Management:

Fork and execute CGI scripts
Manage process timeouts
Capture script output


Response Integration:

Parse CGI output
Generate appropriate HTTP responses
Handle errors in CGI execution



5. Directory Listing Generation

Directory Reading:

Get directory contents safely
Filter listings based on configuration
Sort entries logically


HTML Generation:

Create formatted directory listing pages
Include file sizes, modification times
Add navigation elements


Access Control:

Respect directory access permissions
Implement directory-specific configurations




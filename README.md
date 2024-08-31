# Own Dynamic Web Server

A simple, configurable, and dynamic web server built with C++. This server is capable of serving static HTML files, executing PHP scripts, and can be easily configured via a `server.conf` file.

## Features

- **Static File Serving:** Serve HTML files directly from a specified directory.
- **PHP Script Execution:** Execute PHP files and return the generated output.
- **Configurable Settings:** Easily change server settings like port, IP address, file preferences, and more via `server.conf`.
- **Logging:** Logs server activity to a `.log` file for easy monitoring.
- **Automatic Index File Loading:** Automatically load index files (e.g., `index.html` or `index.php`) based on the configuration.
- **Custom 404 Error Page:** Serve a custom 404 page if the requested resource is not found.


# What Next

 Here are the features and services I will implement next to make my server more powerful and closer to production-level quality.

## 1. HTTPS Support (SSL/TLS)
**Description:** I will secure the server by adding support for SSL/TLS to handle HTTPS requests.
- **Benefit:** This will protect data in transit between the server and clients.
- **How:** I will implement SSL/TLS using libraries like OpenSSL.

## 2. Multi-threading/Concurrency
**Description:** I will allow the server to handle multiple requests simultaneously by introducing concurrency.
- **Benefit:** This will improve performance and scalability.
- **How:** I will use a thread pool to manage multiple connections.

## 3. Virtual Hosts
**Description:** I will enable the server to host multiple domains on the same IP address.
- **Benefit:** This will be essential for shared hosting environments.
- **How:** I will support multiple virtual hosts, each with its own configuration.

## 4. Routing System
**Description:** I will introduce a dynamic URL routing system to handle RESTful APIs and custom URL patterns.
- **Benefit:** This will support dynamic content and API development.
- **How:** I will map URLs to specific handler functions or files.

## 5. Logging and Monitoring
**Description:** I will enhance server diagnostics by logging requests, errors, and performance metrics.
- **Benefit:** This will improve troubleshooting and monitoring.
- **How:** I will implement access logs, error logs, and integrate with monitoring tools like Prometheus.

## 6. Database Integration
**Description:** I will add support for connecting to and interacting with databases like MySQL or SQLite.
- **Benefit:** This will enable dynamic content management and persistent data storage.
- **How:** I will provide basic CRUD operations with database connectivity.

## 7. Support for Other Scripting Languages
**Description:** I will extend the server's capabilities by supporting additional scripting languages.
- **Benefit:** This will offer flexibility by allowing the execution of scripts written in languages like Python or Ruby.
- **How:** I will expand the CGI handler to support multiple scripting languages.

## 8. Session Management
**Description:** I will implement session handling and cookie management.
- **Benefit:** This will support user sessions, logins, and personalized content.
- **How:** I will store session data on the server or use cookies for session management.

## 9. Security Features
**Description:** I will protect the server and clients from common web vulnerabilities.
- **Benefit:** This will enhance server security and user safety.
- **How:** I will add features like rate limiting, IP blocking, input sanitization, and CSRF/XSS protection.

## 10. Configuration Reload Without Restart
**Description:** I will allow configuration changes to take effect without restarting the server.
- **Benefit:** This will improve uptime and flexibility in server management.
- **How:** I will implement a signal handler to reload configurations on receiving a specific signal (e.g., SIGHUP).

## 11. Custom Error Pages
**Description:** I will provide custom error pages for HTTP errors like 404 and 500.
- **Benefit:** This will improve user experience with informative error messages.
- **How:** I will allow the configuration to specify custom HTML files for various error codes.

## 12. Content Compression (Gzip)
**Description:** I will compress content before sending it to clients to reduce response size.
- **Benefit:** This will speed up load times and reduce bandwidth usage.
- **How:** I will implement Gzip compression for text-based content like HTML, CSS, and JavaScript.

## 13. Load Balancing
**Description:** I will distribute incoming traffic across multiple server instances.
- **Benefit:** This will improve performance and reliability under heavy load.
- **How:** I will implement a basic load balancer to distribute traffic.

## 14. Caching Mechanism
**Description:** I will cache frequently requested files or results to improve performance.
- **Benefit:** This will reduce server load and speed up response times.
- **How:** I will implement an in-memory cache or use a caching proxy.

## 15. Support for WebSockets
**Description:** I will enable real-time communication between the server and clients.
- **Benefit:** This will be useful for applications requiring real-time updates like chat systems.
- **How:** I will implement WebSocket protocol handling for maintaining real-time connections.

---

By adding these features, I will significantly enhance the capabilities of my C++ web server, making it more robust, secure, and versatile.

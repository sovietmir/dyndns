# dyndns
The project utilizes the support of dynamic updates in named-bind and is written in PHP. It consists of two parts: one part used through Apache and the other used as a CLI script.

- The first part is installed on an external server with a static IP address. The external server runs a named-bind system configured to allow updates from localhost for configured zones (domains). The external server also runs an Apache web server with PHP that serves URIs ip.php and dns.php. The ip.php script returns the IP of the request, while dns.php accepts a parameter named "ip" in the request and executes an appropriate nsupdate command to update named-bind.

- The second part is installed on a home server. On the home server, the client.php script is executed as a CLI script. The client.php script runs a permanent loop that periodically (every 5 minutes) makes an HTTP GET request to the external server's ip.php to obtain knowledge of the current home server IP. It keeps a record of the previously obtained IP knowledge. If the IP changes, it makes an HTTP GET request to the external server's dns.php with the new IP as a parameter.


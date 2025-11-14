const http = require('http');

const PORT = process.env.PORT || 3001;

// PUBLIC_INTERFACE
/**
 * Simple HTTP server for entservices-infra-712.
 * Listens on the configured PORT and returns status for root route.
 */
const server = http.createServer((req, res) => {
  if (req.url === '/' && req.method === 'GET') {
    res.writeHead(200, {'Content-Type': 'application/json'});
    res.end(JSON.stringify({ status: 'entservices-infra-712 running', port: PORT }));
  } else {
    res.writeHead(404, {'Content-Type': 'application/json'});
    res.end(JSON.stringify({ error: 'Not found' }));
  }
});

server.listen(PORT, () => {
  console.log(`entservices-infra-712 server started on port ${PORT}`);
});

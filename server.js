'use strict';

/**
 * Minimal HTTP server for entservices-infra-712.
 * - Binds to 0.0.0.0 so it is reachable from container networking.
 * - PORT is configurable via process.env.PORT (default 3001).
 * - Provides simple health and readiness endpoints.
 *
 * Note: This server is a lightweight bootstrap to ensure the container has
 * a deterministic start command. It does not attempt to build or run the
 * C++ components found in this repository.
 */

const http = require('http');

const HOST = process.env.HOST || '0.0.0.0';
const PORT = Number.parseInt(process.env.PORT, 10) || 3001;

/**
 * Safely write a JSON response.
 * @param {http.ServerResponse} res - response object
 * @param {number} status - HTTP status code
 * @param {object} body - payload to send as JSON
 * @param {object} [extraHeaders] - optional headers
 */
function sendJson(res, status, body, extraHeaders = {}) {
  const payload = JSON.stringify(body);
  res.writeHead(status, {
    'Content-Type': 'application/json; charset=utf-8',
    'Cache-Control': 'no-store',
    'Content-Length': Buffer.byteLength(payload),
    ...extraHeaders,
  });
  res.end(payload);
}

/**
 * PUBLIC_INTERFACE
 * Handle incoming HTTP requests (health, readiness, and basic root info).
 * This is intentionally small and dependency-free.
 *
 * - GET / or /status  -> basic service info with timestamp
 * - GET /healthz      -> liveness
 * - GET /readyz       -> readiness
 */
function handleRequest(req, res) {
  // Normalize method and path to handle trailing slashes consistently
  const method = (req.method || 'GET').toUpperCase();
  const url = new URL(req.url, `http://${req.headers.host || 'localhost'}`);

  if (method !== 'GET') {
    return sendJson(res, 405, { status: 'error', message: 'Method Not Allowed' }, { Allow: 'GET' });
  }

  switch (url.pathname) {
    case '/':
    case '/status':
      return sendJson(res, 200, {
        status: 'ok',
        service: 'entservices-infra-712',
        description: 'Infrastructure minimal HTTP bootstrap',
        time: new Date().toISOString(),
      });
    case '/healthz':
      return sendJson(res, 200, { status: 'ok' });
    case '/readyz':
      return sendJson(res, 200, { status: 'ready' });
    default:
      return sendJson(res, 404, { status: 'not_found', path: url.pathname });
  }
}

/**
 * PUBLIC_INTERFACE
 * Start the HTTP server and attach basic process-level error handlers.
 */
function start() {
  const server = http.createServer(handleRequest);

  server.listen(PORT, HOST, () => {
    // eslint-disable-next-line no-console
    console.log(`[entservices-infra-712] Listening on http://${HOST}:${PORT}`);
  });

  server.on('error', (err) => {
    // eslint-disable-next-line no-console
    console.error('[entservices-infra-712] Server error:', err);
    process.exitCode = 1;
  });

  // Graceful shutdown hooks
  const shutdown = (signal) => {
    // eslint-disable-next-line no-console
    console.log(`[entservices-infra-712] Received ${signal}, shutting down...`);
    server.close(() => {
      // eslint-disable-next-line no-console
      console.log('[entservices-infra-712] Server closed.');
      process.exit(0);
    });
    // Force exit if close takes too long
    setTimeout(() => process.exit(0), 5000).unref();
  };

  process.on('SIGINT', () => shutdown('SIGINT'));
  process.on('SIGTERM', () => shutdown('SIGTERM'));

  process.on('uncaughtException', (err) => {
    // eslint-disable-next-line no-console
    console.error('[entservices-infra-712] Uncaught exception:', err);
    process.exit(1);
  });

  process.on('unhandledRejection', (reason) => {
    // eslint-disable-next-line no-console
    console.error('[entservices-infra-712] Unhandled rejection:', reason);
    process.exit(1);
  });

  return server;
}

// Start the server when executed directly
if (require.main === module) {
  start();
}

// Export for potential testing or advanced usage.
module.exports = { start, handleRequest };

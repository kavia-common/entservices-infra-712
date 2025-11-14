const express = require('express');
const app = express();

const PORT = process.env.PORT || 3001;

// Health endpoint for monitoring
// PUBLIC_INTERFACE
app.get('/health', (req, res) => {
  /** Health check endpoint. Returns {status: 'ok'} if server is running. */
  res.json({ status: 'ok' });
});

// Basic static response at root
// PUBLIC_INTERFACE
app.get('/', (req, res) => {
  /** Root endpoint. Returns a simple static response string. */
  res.send('entservices-infra-712 backend service is running.');
});

// Bind server to the specified port
app.listen(PORT, () => {
  console.log(`entservices-infra-712 backend service listening on port ${PORT}`);
});

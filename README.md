# entservices-infra-712 Backend Service

This is a minimal Node.js Express backend service with a health check endpoint.

## Getting Started

### Install dependencies

```
npm install
```
from within the `entservices-infra-712` directory.

### Running the server

```
npm start
```
The server will start on the port specified by the `PORT` environment variable (default: 3001).

### Health Endpoint

- `GET /health` returns `{ "status": "ok" }` to verify the service is running.

### Example Environment Setup

Copy `.env.example` to `.env` and edit as needed:
```
cp .env.example .env
```

## Endpoints

- `GET /` – Returns static confirmation string
- `GET /health` – Returns JSON `{ "status": "ok" }`

## Requirements

- Node.js v14 or higher

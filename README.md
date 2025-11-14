# entservices-infra-712

This project provides infrastructure and supporting services for enterprise applications, such as deployment, monitoring, or orchestration utilities.

## Getting Started

### Requirements

- Node.js (v14 or later)
- npm

### Setup

1. Install dependencies:
    ```sh
    npm install
    ```

2. Configure environment variables:
    - Copy `.env.example` to `.env` and (optionally) set `PORT`:
      ```sh
      cp .env.example .env
      ```

3. Start the server:
    ```sh
    npm start
    ```

The server will listen on the port set in your `.env` file's `PORT` variable (defaults to 3001 if not set).

## Entrypoint

The service entrypoint is [`server.js`](server.js). It uses [Express](https://expressjs.com/) and listens on `process.env.PORT || 3001`.

### Health Endpoint

- `GET /` — Returns a plain message confirming the service is running.

## Example Environment Setup

Copy the example:
```sh
cp .env.example .env
```

Change `PORT` if you want to use a non-default port.

## License

See the [LICENSE](LICENSE) file for details.

# template
Template repository with common workflows for future clone

---

## Quick start (container bootstrap)

This repository primarily contains C++ modules and build scripts. To provide a deterministic start command for the container runtime, a minimal Node.js HTTP server has been added.

- Start the service:
  - npm start

- Behavior:
  - Binds to 0.0.0.0
  - Uses PORT environment variable if set, otherwise defaults to 3000

- Example:
  - PORT=3000 npm start

- Fallback:
  - A Procfile is also included with: `web: npm start`

### Endpoints

- GET / or /status
  - Returns a simple JSON status payload with current timestamp
- GET /healthz
  - Liveness probe
- GET /readyz
  - Readiness probe

### Notes

- This minimal server does not build or run the C++ components. It exists to ensure the container has an unambiguous start command.
- If you want to build the native components, use the CMake files in the repository per your toolchain/environment.

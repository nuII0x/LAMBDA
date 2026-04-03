# API Layer

This folder is reserved for the future HTTP service.

The core rule is that the API should reuse the domain and application contracts
already defined in:

- `include/wexacts/core`
- `include/wexacts/education`
- `include/wexacts/platform/contracts.h`

Recommended next step:

1. Map an HTTP request body into `wrs::solve_request`.
2. Call `wrs::solveRequest`.
3. Serialize `wrs::solve_response` back to JSON.

This keeps CLI, API and future GUI applications aligned around the same math
engine.

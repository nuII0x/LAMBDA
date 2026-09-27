Warm: This project is not ready at the momento, it's only a skeleton of the intended purpose.
# WExacts

WExacts is a C++ mathematics engine designed to grow from a reusable library
into a complete educational product. The project now starts with a layered
structure:

- `include/wexacts/core`: pure mathematical algorithms
- `include/wexacts/education`: skill catalog, teaching metadata, explanations
- `include/wexacts/platform`: request/response contracts for CLI or API layers
- `apps/cli`: first command-line entry point
- `services/api`: future HTTP service boundary
- `tests`: smoke tests for the public surface
- `docs`: roadmap and curriculum planning

The existing root files remain available as compatibility entry points:

- `arithmetic.h`
- `arithmetic`
- `matrix`

## File naming

This repository uses `.h` for headers and no extension for source-style entry
files, following the project convention.

## Current focus

The current architecture is aimed at turning high-school mathematics into a
simple, portable engine. Each skill should have:

- a stable `skill_id`
- validated inputs
- formulas and outputs
- an executable solver
- step-by-step explanation data

The long-term target is:

1. reliable C++ math core
2. practical CLI for local use and validation
3. later export to WebAssembly for a public site

## Suggested next phases

1. Add more school skills on top of the same solver contract.
2. Keep the CLI as the main local validation tool.
3. Add a thin WebAssembly export layer later without changing the math core.
4. Add unit tests for every skill and edge case.

## Quick build checks

Smoke test:

```bash
g++ -std=c++17 -I. -x c++ tests/smoke -o /tmp/wexacts_smoke
/tmp/wexacts_smoke
```

CLI seed:

```bash
g++ -std=c++17 -I. -x c++ apps/cli/main -o /tmp/wexacts_cli
/tmp/wexacts_cli
/tmp/wexacts_cli catalog
/tmp/wexacts_cli show algebra.quadratic.roots
/tmp/wexacts_cli solve algebra.quadratic.roots a=1 b=-5 c=6
/tmp/wexacts_cli solve algebra.linear_system_2x2 a1=1 b1=1 c1=5 a2=2 b2=-1 c2=4
/tmp/wexacts_cli solve statistics.central_tendency data=2,3,3,5,8
```

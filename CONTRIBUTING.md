# Contributing to pmake

Thanks for your interest in improving pmake. This document describes how the project is organized, the coding conventions it follows, and how to submit changes.

## Getting started

1. Fork the repository and clone your fork.
2. Build the project to make sure your toolchain works:

   ```
   make
   ./pmake --help
   ```

3. Create a branch for your change:

   ```
   git checkout -b fix/short-description
   ```

## Project layout

```
pmake/
├── src/            one .c file per command/module
├── include/         matching .h file for each .c file
├── Makefile
├── README.md
└── CONTRIBUTING.md
```

Each command (`init`, `activate`/`deactivate`, `add`, `delete`) lives in its own source file with a matching header. `platform.c` holds all OS-specific path/command logic, `util.c` holds small shared helpers (file checks, running shell commands). `main.c` only parses `argv` and dispatches to the right function — it should not contain command logic itself.

## Coding conventions

pmake is deliberately small and readable. Please follow the existing style:

- **C11**, compiled with `-Wall -Wextra`. New code must build without warnings.
- **Naming**: use plain names, not prefixed ones. A new command called `foo` goes in `src/foo.c` / `include/foo.h`, with a function `foo(int argc, char **argv)` — not `pmake_foo.c` or `pmake_foo()`. Avoid naming collisions with C keywords/reserved identifiers (see `delete_venv` instead of `delete`).
- **One command, one file.** If you add a new command, give it its own `.c`/`.h` pair and wire it into `main.c`, rather than folding it into an existing file.
- **Minimal comments.** Code should be clear enough from naming and structure that comments aren't needed. Add a comment only when something is genuinely non-obvious (e.g. a platform quirk), not to restate what the code already says.
- **No new dependencies.** pmake intentionally only uses the C standard library and shells out to `python`/`pip`. Don't introduce third-party libraries.
- **Cross-platform by construction.** Any path, executable name, or command string that differs between Linux, macOS, and Windows belongs in `platform.c`, behind `current_os()` — not scattered `#ifdef`s in command files.
- **Errors go to stderr**, normal output to stdout, and every command returns `0` on success / non-zero on failure.

## Testing your change

There's no formal test suite; test manually against a real Python installation:

```
make
./pmake init test-env
./pmake add six
./pmake activate test-env
./pmake deactivate
./pmake delete test-env
make clean
```

Please test on at least one platform, and mention in your pull request which platform(s) you tested on. If your change touches `platform.c`, try to verify the generated paths/commands are correct for Linux, macOS, and Windows even if you can only run one of them — read the equivalent branches carefully for the others.

## Commit messages

Keep commits focused and the message short and descriptive, e.g.:

```
Added support installing from a requirements file
Fixed activate path on macOS
```

## Submitting a pull request

- Keep pull requests focused on a single change; unrelated fixes should be separate PRs.
- Describe what the change does and why, and note any behavior changes to existing commands.
- Update `README.md` if you add, remove, or change the behavior of a command.
- Make sure `make` builds cleanly before submitting.

## License

pmake is licensed under the GNU General Public License v3.0 (GPL-3.0). By submitting a contribution, you agree that it will be licensed under the same terms.

## Reporting bugs / suggesting features

Open an issue describing:

- What you expected to happen.
- What actually happened (include the exact command and output).
- Your OS and Python version.

For feature requests, a short description of the use case is more useful than a full implementation proposal.

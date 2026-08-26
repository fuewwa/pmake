# pmake

pmake is a small command line utility, written in C, for creating and managing Python virtual environments. Think of it as a thin, opinionated wrapper around the standard `venv` and `pip` tools: instead of remembering the exact invocation for your platform, you run one short command and pmake works out the rest.

pmake runs on Linux, macOS and Windows. The same source code is used on every platform; at compile time pmake detects the operating system it was built for and adjusts paths and commands accordingly (`bin` vs `Scripts`, forward slashes vs backslashes, `python3` vs `python`, and so on).

## How it works

pmake does not reimplement `venv` or `pip`. It shells out to whatever Python interpreter is on your `PATH` (`python3` on Linux/macOS, `python` on Windows) and to the `pip` binary that Python installs inside the virtual environment. This keeps pmake tiny and means it always behaves exactly like the underlying tools, just with a shorter and more consistent interface.

By default pmake looks for (and creates) a virtual environment in a directory named `venv` in the current working directory. Most commands accept an optional name argument if you want to use a different directory.

### A note on `activate` / `deactivate`

Activating a virtual environment means changing environment variables (`PATH`, `VIRTUAL_ENV`, your shell prompt, and so on) inside your *current shell*. A separate process — like the `pmake` binary — cannot reach into the shell that launched it and modify its environment; this is a hard limitation of how processes work on every operating system, not something specific to pmake.

Because of this, `pmake activate` and `pmake deactivate` do not activate anything by themselves. Instead they print the exact command your shell needs to run:

```
$ pmake activate
source venv/bin/activate
```

You then either copy that command, or — much more conveniently — wrap pmake in a one-line shell function so activation happens automatically. See "Shell integration" below.

## Building

You need a C compiler (`gcc` or `clang`) and `make`.

### Linux / macOS

```
git clone <your-repository-url>
cd pmake
make
```

This produces a `pmake` binary in the project root. To install it system-wide:

```
sudo make install
```

This copies the binary to `/usr/local/bin/pmake`, so you can run `pmake` from any directory.

### Windows

Install a toolchain that provides `gcc` and `make`, for example [MSYS2](https://www.msys2.org/) or [MinGW-w64](https://www.mingw-w64.org/). From an MSYS2/MinGW shell:

```
git clone https://github.com/KURWAss/pmake.git
cd pmake
make
```

This produces `pmake.exe`. `make install` copies it into your Windows directory so it is available on `PATH`; alternatively, copy `pmake.exe` yourself into any directory already on `PATH`.

If you prefer not to use MinGW/MSYS2, you can compile manually with any C11 compiler, for example:

```
cl /I include src\*.c /Fe:pmake.exe
```

### Cleaning up build artifacts

```
make clean
```

## Usage

```
pmake <command> [arguments]
```

| Command                   | Description                                                        |
|----------------------------|---------------------------------------------------------------------|
| `pmake init [name]`        | Create a virtual environment (default directory name: `venv`)       |
| `pmake remove [--venv <name>] <pkg> [pkg...]` | Uninstall one or more packages from the virtual environment with pip |
| `pmake activate [name]`    | Print the command to activate the virtual environment                |
| `pmake deactivate`         | Print the command to deactivate the current virtual environment      |
| `pmake add [--venv <name>] <pkg> [pkg...]` | Install one or more packages into the virtual environment with pip   |
| `pmake delete [name]`      | Remove the virtual environment directory                             |
| `pmake --help` / `-h`      | Show usage information                                               |

### Examples

Create a virtual environment named `venv` in the current directory:

```
$ pmake init
pmake: creating virtual environment 'venv'
pmake: virtual environment 'venv' created
```

Remove a package from it:

```
$ pmake remove flask
pmake: removing packages
Found existing installation: Flask ...
pmake: packages removed
```

Create one with a custom name:

```
$ pmake init myproject-env
```

Install packages into it:

```
$ pmake add requests flask
pmake: installing packages
Collecting requests
...
pmake: packages installed
```

Remove it once you're done:

```
$ pmake delete
pmake: deleting 'venv'
pmake: 'venv' deleted
```

### Shell integration

To make `pmake activate` and `pmake deactivate` actually affect your current shell, add a small function to your shell configuration file. It runs `pmake` normally for every command, but for `activate`/`deactivate` it evaluates the printed command in the current shell instead of just printing it.

**bash / zsh** (`~/.bashrc`, `~/.zshrc`):

```sh
pmake() {
    if [ "$1" = "activate" ] || [ "$1" = "deactivate" ]; then
        eval "$(command pmake "$@")"
    else
        command pmake "$@"
    fi
}
```

**PowerShell** (`$PROFILE`):

```powershell
function pmake {
    param([Parameter(ValueFromRemainingArguments = $true)]$Args)
    if ($Args[0] -eq "activate") {
        $venv = if ($Args.Count -gt 1) { $Args[1] } else { "venv" }
        & "$venv\Scripts\Activate.ps1"
    } elseif ($Args[0] -eq "deactivate") {
        deactivate
    } else {
        pmake.exe @Args
    }
}
```

After adding this, `pmake activate` and `pmake deactivate` will behave exactly like running the underlying venv scripts by hand, while every other command (`init`, `add`, `delete`) is passed straight through to the real `pmake` binary.

## Project layout

```
pmake/
├── src/            C source files
├── include/        C header files
├── Makefile        Build, install and clean targets
├── .gitignore
├── .gitattributes
└── README.md
```

## Requirements

- A working Python 3 installation with the `venv` module (included in the standard library).
- `pip`, installed automatically by `venv` inside each virtual environment.

## License

pmake is licensed under the GNU General Public License v3.0 (GPL-3.0)

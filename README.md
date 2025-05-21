# Mint
A simple & powerful package manager for _Candycane GNU/Linux_.

## Installation
> [!WARNING]
> Mint is recommended to be installed on _Candycane GNU/Linux_.

Mint can be installed in one command:
```shell
curl -fs https://raw.githubusercontent.com/realbxnnie/Mint/refs/heads/main/install.sh | bash
```
## Usage
```
COMMANDS
    install <category>/<pkgName>     Install a package
    purge   <category>/<pkgName>     Remove a package
    update  <category>/<pkgName>     Update a package or update the repositories
    list                             List packages installed on your system
    help                             Display this message
    info                             Display program info
ARGUMENTS
    --yes     -y                     Don't ask Y/n
```
## Repositories
### Adding a repository
The repositories are placed in `/etc/mint/repos.conf`.\
Open the file via a text editor. You'll see something like that:
```bash
mint="https://github.com/realbxnnie/mint-repo"
```
Add a variable with any category name (e.g myRepo) and assign a repository link to it.

Now, the repositories file should look like that:
```bash
mint="https://github.com/realbxnnie/mint-repo"
myRepo="https://link.to/repo"
```

Kaboom! You have now added a repository. You can now install a package from that repository:
```shell
mint install myRepo/packageLOL
```
### Removing a repository
Simply remove a category from the `/etc/mint/repos.conf` file.

## Making a package
`Not documented yet.`

$${\color{gray}Made\space with \space love}$$
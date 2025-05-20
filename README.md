# Mint
A simple & powerful package manager for _Candycane GNU/Linux_.

## Installation
> [!WARNING]
> Mint is recommended to be installed on _Candycane GNU/Linux_.

Mint can be installed in one command:
```shell
curl -f https://raw.githubusercontent.com/realbxnnie/Mint/refs/heads/main/install.sh | bash
```
## Usage
```
COMMANDS
    install <category>::<pkgName>     Install a package
    purge   <category>::<pkgName>     Remove a package
    update  <category>::<pkgName>     Update a package or update the repositories
ARGUMENTS
    --quiet   -q     Build quietly
    --verbose -v     Build with output [DEFAULT]
    --yes     -y     Don't ask Y/n
```
## Repositories
### Adding a repository
The repositories are placed in `/etc/mint/repos.conf`.\
Open the file via a text editor. You'll see something like that:
```bash
main_repo="https://github.com/realbxnnie/mint-repo"
```
Add a variable with any category name (e.g myRepo) and assign a repository link to it.

Now, the repositories file should look like that:
```bash
main_repo="https://github.com/realbxnnie/mint-repo"
myRepo="https://link.to/repo"
```
After editing the repositories file, run:
```shell
mint update
```
Kaboom! You have now added a repository. You can now install a package from that repository:
```shell
mint install myRepo::packageLOL
```
### Removing a repository
Simply remove a category from the `/etc/mint/repos.conf` file, then run:
```shell
mint update
```

## Making a package
1. Create a folder & name it as you want.
2. Create a file in the folder named `make.mint`.
3. Write the template to the file:
```bash
export NAME="My Package"
export PACKAGE_URL="https://link.to/package.git"

build() {
    git clone $PACKAGE_URL
    pushd $(basename "$PACKAGE_URL" .git)
    make
}
```
4. Edit the template as you want.
5. Save changes.
6. Upload the folder to a repository.\
**Done!**

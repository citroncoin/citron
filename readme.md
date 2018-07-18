
![CitronCoin](https://citroncoin.net/logos/logo-fit.png)

Citron is a decentralized PoW/PoS cryptocurrency with support for private transactions and high-reward masternodes.
## License
Citron follows the guidelines of the [MIT License](https://opensource.org/licenses/MIT). 

## Coin Specificatons 
| Specification | Value |
| ------ | ------ |
| Max Coins | 45,000,000 CTRN |
| Block Time | 120 seconds |
| Main Port | 42012 |
| RPC Port | 42011 |
| Masternode Collateral | 4500 CTRN |
| Algorithm | Scrypt |
| PoS Maturity | 24 hours |

# Installation
## Ubuntu Linux
### Automatic Install
To automatically download, compile and setup the Citron daemon on Linux, run the below command. Please note that the automatic install does not yet support the graphical frontend of Citron. This will come in a later release.
```sh
wget -q https://citroncoin.net/scripts/autoinstall.sh && sudo bash autoinstall.sh
```
This script will download the Citron sources from GitHub (https://github.com/citroncoin/citron) and compile the source. It will automatically install dependencies and tools needed for compilation. Once compiled, it will also set up `citrond` as a systemd service, and configure to automatically start at boot.

Please note running scripts as root from the internet is not advised. However, this is the easiest way to install `citrond`.

### Manual Installation
Add the following dependencies and repositories using APT:
```sh
sudo apt-get install build-essential libssl-dev libboost-all-dev libqrencode-dev pkg-config libminiupnpc-dev qt5-default qttools5-dev-tools libgmp3-dev autoconf automake libtool

sudo add-apt-repository ppa:bitcoin/bitcoin
sudo apt-get update
sudo apt-get install libdb4.8-dev libdb4.8++-dev
```
Clone this github repository and change directory:
```sh
git clone https://github.com/citroncoin/citron
cd citron
```
For compiling the headless `citrond` daemon, enter the following commands:
```sh
cd src
make -f makefile.unix
strip citrond 
```
For compiling the graphical QT wallet, enter the following commands:
```sh
qmake
make
strip Citron-qt
```
To install the daemon and QT wallet globally, copy the files to ```/usr/local/bin``` or whatever path your distro uses.
```sh
sudo cp citrond /usr/local/bin
sudo cp Citron-qt /usr/local/bin
```

## Windows
Compiliation steps are currently unavailable for Windows operating systems. Compiled wallet downloads are available at [https://citroncoin.net](httsp://citroncoin.net).

# Important
>THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

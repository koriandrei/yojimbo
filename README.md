[![Build status](https://github.com/networkprotocol/yojimbo/workflows/CI/badge.svg)](https://github.com/networkprotocol/yojimbo/actions?query=workflow%3ACI)

# yojimbo

**yojimbo** is a network library for client/server games written in C++.

It's designed around the networking requirements of competitive multiplayer games like first person shooters. 

It has the following features:

* Cryptographically secure authentication via [connect tokens](https://github.com/networkprotocol/netcode/blob/master/STANDARD.md)
* Client/server connection management and timeouts
* Encrypted and signed packets sent over UDP
* Packet fragmentation and reassembly
* Bitpacker and serialization system
* Reliable-ordered messages and data blocks
* Estimates of packet loss, latency and bandwidth usage

yojimbo is stable and production ready.

## Source Code

You can get the latest source code by cloning it from github:

      git clone https://github.com/mas-bandwidth/yojimbo.git

Alternatively, you can download the latest [releases](https://github.com/mas-bandwidth/yojimbo/releases)

## Author

The author of this library is Glenn Fiedler.

Open source libraries by the same author include: [netcode](https://github.com/mas-bandwidth/netcode), [reliable](https://github.com/mas-bandwidth/reliable),  and [serialize](https://github.com/mas-bandwidth/serialize)

If you find this software useful, please consider [sponsoring it](https://github.com/sponsors/mas-bandwidth). Thanks!

## License

[BSD 3-Clause license](https://opensource.org/licenses/BSD-3-Clause).

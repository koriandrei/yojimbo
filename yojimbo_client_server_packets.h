/*
    Yojimbo Client/Server Network Protocol Library.
    
    Copyright © 2016, The Network Protocol Company, Inc.

    Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

        1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.

        2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer 
           in the documentation and/or other materials provided with the distribution.

        3. Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote products derived 
           from this software without specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, 
    INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE 
    DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
    SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR 
    SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
    WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE
    USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef YOJIMBO_CLIENT_SERVER_PACKETS_H
#define YOJIMBO_CLIENT_SERVER_PACKETS_H

#include "yojimbo_config.h"
#include "yojimbo_packet.h"
#include "yojimbo_tokens.h"

namespace yojimbo
{
    struct ConnectionRequestPacket : public Packet
    {
        uint64_t connectTokenExpireTimestamp;
        uint8_t connectTokenData[ConnectTokenBytes];                        // encrypted connect token data generated by matchmaker
        uint8_t connectTokenNonce[NonceBytes];                              // nonce required to decrypt the connect token on the server

        ConnectionRequestPacket()
        {
            connectTokenExpireTimestamp = 0;
            memset( connectTokenData, 0, sizeof( connectTokenData ) );
            memset( connectTokenNonce, 0, sizeof( connectTokenNonce ) );
        }

        template <typename Stream> bool Serialize( Stream & stream )
        {
            serialize_uint64( stream, connectTokenExpireTimestamp );
            serialize_bytes( stream, connectTokenData, sizeof( connectTokenData ) );
            serialize_bytes( stream, connectTokenNonce, sizeof( connectTokenNonce ) );
            return true;
        }

        YOJIMBO_ADD_VIRTUAL_SERIALIZE_FUNCTIONS();
    };

    struct ConnectionDeniedPacket : public Packet
    {
        template <typename Stream> bool Serialize( Stream & /*stream*/ ) { return true; }

        YOJIMBO_ADD_VIRTUAL_SERIALIZE_FUNCTIONS();
    };

    struct ChallengePacket : public Packet
    {
        uint8_t challengeTokenData[ChallengeTokenBytes];                      // encrypted challenge token data generated by matchmaker
        uint8_t challengeTokenNonce[NonceBytes];                              // nonce required to decrypt the challenge token on the server

        ChallengePacket()
        {
            memset( challengeTokenData, 0, sizeof( challengeTokenData ) );
            memset( challengeTokenNonce, 0, sizeof( challengeTokenNonce ) );
        }

        template <typename Stream> bool Serialize( Stream & stream )
        {
            serialize_bytes( stream, challengeTokenData, sizeof( challengeTokenData ) );
            serialize_bytes( stream, challengeTokenNonce, sizeof( challengeTokenNonce ) );
            return true;
        }

        YOJIMBO_ADD_VIRTUAL_SERIALIZE_FUNCTIONS();
    };

    struct ChallengeResponsePacket : public Packet
    {
        uint8_t challengeTokenData[ChallengeTokenBytes];                      // encrypted challenge token data generated by matchmaker
        uint8_t challengeTokenNonce[NonceBytes];                              // nonce required to decrypt the challenge token on the server

        ChallengeResponsePacket()
        {
            memset( challengeTokenData, 0, sizeof( challengeTokenData ) );
            memset( challengeTokenNonce, 0, sizeof( challengeTokenNonce ) );
        }

        template <typename Stream> bool Serialize( Stream & stream )
        {
            serialize_bytes( stream, challengeTokenData, sizeof( challengeTokenData ) );
            serialize_bytes( stream, challengeTokenNonce, sizeof( challengeTokenNonce ) );
            return true;
        }

        YOJIMBO_ADD_VIRTUAL_SERIALIZE_FUNCTIONS();
    };

    struct KeepAlivePacket : public Packet
    {
        int clientIndex;

        KeepAlivePacket()
        {
            clientIndex = 0;
        }

        template <typename Stream> bool Serialize( Stream & stream )
        { 
            serialize_int( stream, clientIndex, 0, MaxClients - 1 );
            return true; 
        }

        YOJIMBO_ADD_VIRTUAL_SERIALIZE_FUNCTIONS();
    };

    struct DisconnectPacket : public Packet
    {
        template <typename Stream> bool Serialize( Stream & /*stream*/ ) { return true; }

        YOJIMBO_ADD_VIRTUAL_SERIALIZE_FUNCTIONS();
    };

#if YOJIMBO_INSECURE_CONNECT

    struct InsecureConnectPacket : public Packet
    {
        uint64_t clientSalt;

        InsecureConnectPacket()
        {
            clientSalt = 0;
        }

        template <typename Stream> bool Serialize( Stream & stream )
        {
            serialize_uint64( stream, clientSalt );
            return true;
        }

        YOJIMBO_ADD_VIRTUAL_SERIALIZE_FUNCTIONS();
    };

#endif // #if YOJIMBO_INSECURE_CONNECT

    enum ClientServerPacketTypes
    {
        CLIENT_SERVER_PACKET_CONNECTION_REQUEST,                    // client requests a connection.
        CLIENT_SERVER_PACKET_CONNECTION_DENIED,                     // server denies client connection request.
        CLIENT_SERVER_PACKET_CHALLENGE,                             // server response to client connection request.
        CLIENT_SERVER_PACKET_CHALLENGE_RESPONSE,                    // client response to server connection challenge.
        CLIENT_SERVER_PACKET_KEEPALIVE,                             // keepalive packet sent at some low rate (once per-second) to keep the connection alive.
        CLIENT_SERVER_PACKET_DISCONNECT,                            // courtesy packet to indicate that the other side has disconnected. better than a timeout.
#if YOJIMBO_INSECURE_CONNECT
        CLIENT_SERVER_PACKET_INSECURE_CONNECT,                      // client requests an insecure connection (dev only!)
#endif // #if YOJIMBO_INSECURE_CONNECT
        CLIENT_SERVER_PACKET_CONNECTION,                            // connection packet carries messages and other data once connection is established.
        CLIENT_SERVER_NUM_PACKETS
    };

    YOJIMBO_PACKET_FACTORY_START( ClientServerPacketFactory, PacketFactory, CLIENT_SERVER_NUM_PACKETS );

        YOJIMBO_DECLARE_PACKET_TYPE( CLIENT_SERVER_PACKET_CONNECTION_REQUEST,       ConnectionRequestPacket );
        YOJIMBO_DECLARE_PACKET_TYPE( CLIENT_SERVER_PACKET_CONNECTION_DENIED,        ConnectionDeniedPacket );
        YOJIMBO_DECLARE_PACKET_TYPE( CLIENT_SERVER_PACKET_CHALLENGE,                ChallengePacket );
        YOJIMBO_DECLARE_PACKET_TYPE( CLIENT_SERVER_PACKET_CHALLENGE_RESPONSE,       ChallengeResponsePacket );
        YOJIMBO_DECLARE_PACKET_TYPE( CLIENT_SERVER_PACKET_KEEPALIVE,                KeepAlivePacket );
        YOJIMBO_DECLARE_PACKET_TYPE( CLIENT_SERVER_PACKET_DISCONNECT,               DisconnectPacket );
#if YOJIMBO_INSECURE_CONNECT
        YOJIMBO_DECLARE_PACKET_TYPE( CLIENT_SERVER_PACKET_INSECURE_CONNECT,         InsecureConnectPacket );
#endif // #if YOJIMBO_INSECURE_CONNECT
        YOJIMBO_DECLARE_PACKET_TYPE( CLIENT_SERVER_PACKET_CONNECTION,               ConnectionPacket );

    YOJIMBO_PACKET_FACTORY_FINISH()
}

#endif // #ifndef YOJIMBO_CLIENT_SERVER_PACKETS_H

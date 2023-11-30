//
// Created by YuHuanTin on 2023/11/28.
//



#include "PackageMaker.h"

#include <memory>
#include "brotli/decode.h"
#include <WinSock2.h>

#include "../Buf/Buffer.hpp"


/**
 * copy from https://gist.github.com/thomastrapp/0c71d68a0a60e5df8a76c09c65e719c0 and modified
 * 
 * @param Input 
 * @return 
 */
std::expected<std::vector<uint8_t>, std::string>
brotli_decode(const std::vector<uint8_t> &Input) {
    std::unique_ptr<
            BrotliDecoderState,
            decltype(&BrotliDecoderDestroyInstance)> state(
            BrotliDecoderCreateInstance(nullptr, nullptr, nullptr),
            BrotliDecoderDestroyInstance);

    BrotliDecoderResult result = BROTLI_DECODER_RESULT_ERROR;

    std::vector<uint8_t> out;
    const size_t chunk_size = 1 << 16;
    std::vector<std::uint8_t> buffer(chunk_size, 0);

    size_t available_in = Input.size();
    const auto *next_in = Input.data();
    size_t available_out = buffer.size();
    std::uint8_t *next_out = buffer.data();

    while (true) {
        result = BrotliDecoderDecompressStream(state.get(), &available_in, &next_in, &available_out, &next_out, 0);

        if (result == BROTLI_DECODER_RESULT_NEEDS_MORE_OUTPUT ||
            result == BROTLI_DECODER_RESULT_SUCCESS) {
            out.insert(out.end(), buffer.data(), buffer.data() + std::distance(buffer.data(), next_out));

            if (result == BROTLI_DECODER_RESULT_SUCCESS)
                return out;

            available_out = buffer.size();
            next_out = buffer.data();
        } else if (result == BROTLI_DECODER_RESULT_NEEDS_MORE_INPUT) {
            return std::unexpected("not enough input");
        } else {
            if (result == BROTLI_DECODER_RESULT_ERROR) {
                std::string detail = BrotliDecoderErrorString(BrotliDecoderGetErrorCode(state.get()));
                return std::unexpected("decoding failed (" + detail + ")");
            }
            return std::unexpected("decoding failed");
        }
    }
}

/**
 * js src
 * 
    t.prototype.convertToArrayBuffer = function(t, e) {
        this.encoder || (this.encoder = r.a.getEncoder());
        var n = new ArrayBuffer(o.a.WS_PACKAGE_HEADER_TOTAL_LENGTH)
          , i = new DataView(n,o.a.WS_PACKAGE_OFFSET)
          , s = this.encoder.encode(t);
        return i.setInt32(o.a.WS_PACKAGE_OFFSET, o.a.WS_PACKAGE_HEADER_TOTAL_LENGTH + s.byteLength),
        this.wsBinaryHeaderList[2].value = e,
        this.wsBinaryHeaderList.forEach(function(t) {
            4 === t.bytes ? i.setInt32(t.offset, t.value) : 2 === t.bytes && i.setInt16(t.offset, t.value)
        }),
        r.a.mergeArrayBuffer(n, s)
    }
    ,
    t.prototype.convertToObject = function(t) {
        var e = new DataView(t)
          , n = {
            body: []
        };
        if (n.packetLen = e.getInt32(o.a.WS_PACKAGE_OFFSET),
        this.wsBinaryHeaderList.forEach(function(t) {
            4 === t.bytes ? n[t.key] = e.getInt32(t.offset) : 2 === t.bytes && (n[t.key] = e.getInt16(t.offset))
        }),
        n.packetLen < t.byteLength && this.convertToObject(t.slice(0, n.packetLen)),
        this.decoder || (this.decoder = r.a.getDecoder()),
        !n.op || o.a.WS_OP_MESSAGE !== n.op && n.op !== o.a.WS_OP_CONNECT_SUCCESS)
            n.op && o.a.WS_OP_HEARTBEAT_REPLY === n.op && (n.body = {
                count: e.getInt32(o.a.WS_PACKAGE_HEADER_TOTAL_LENGTH)
            });
        else
            for (var i = o.a.WS_PACKAGE_OFFSET, s = n.packetLen, a = "", u = ""; i < t.byteLength; i += s) {
                s = e.getInt32(i),
                a = e.getInt16(i + o.a.WS_HEADER_OFFSET);
                try {
                    if (n.ver === o.a.WS_BODY_PROTOCOL_VERSION_NORMAL) {
                        var c = this.decoder.decode(t.slice(i + a, i + s));
                        u = 0 !== c.length ? JSON.parse(c) : null
                    } else if (n.ver === o.a.WS_BODY_PROTOCOL_VERSION_BROTLI) {
                        var l = t.slice(i + a, i + s)
                          , h = window.BrotliDecode(new Uint8Array(l));
                        u = this.convertToObject(h.buffer).body
                    }
                    u && n.body.push(u)
                } catch (e) {
                    this.options.onLogger("decode body error:", new Uint8Array(t), n, e)
                }
            }
        return n
    }
 */

namespace PackageMaker {
    std::expected<std::vector<uint8_t>, std::string> make(const std::string &DataToMake, OperatorType Operator) {
        size_t dataLength = DataToMake.length();
        size_t totalLength = dataLength + OperatorType::WS_PACKAGE_HEADER_TOTAL_LENGTH;


        /// alloc memory
        std::vector<uint8_t> data(totalLength, 0);


        /// make header
        PackageHeader header{};
        header.totalLength = htonl(totalLength);
        header.headerLength = htons(OperatorType::WS_PACKAGE_HEADER_TOTAL_LENGTH);
        header.protocalVersion = htons(OperatorType::WS_HEADER_DEFAULT_VERSION);
        header.operation = htonl(Operator);
        header.sequeceId = htonl(OperatorType::WS_HEADER_DEFAULT_SEQUENCE);


        /// make buffer
        /// note: big endian need htonxx function
        Buffer<uint8_t> buf{data.data(), totalLength};
        try {
            // +0 [WS_PACKAGE_OFFSET] total length
            buf.write(header.totalLength);
            // +4 [WS_HEADER_OFFSET] header length
            buf.write(header.headerLength);
            // +6 [WS_VERSION_OFFSET] protocol version
            buf.write(header.protocalVersion);
            // +8 [WS_OPERATION_OFFSET] operator
            buf.write(header.operation);
            // +12 [WS_SEQUENCE_OFFSET] Sequence Id
            buf.write(header.sequeceId);
            // +16 data
            buf.write(DataToMake.data(), dataLength);
        } catch (std::exception &Exception) {
            return std::unexpected<std::string>(Exception.what());
        }

        return data;
    }

    std::expected<std::vector<std::string>, std::string> parse(std::vector<uint8_t> &DataToParse) {
        /// make buffer
        Buffer<uint8_t> buf{DataToParse.data(), DataToParse.size()};


        /// parse package header
        PackageHeader header{};
        header.totalLength = ntohl(buf.read<uint32_t>());
        header.headerLength = ntohs(buf.read<uint16_t>());
        header.protocalVersion = ntohs(buf.read<uint16_t>());
        header.operation = ntohl(buf.read<uint32_t>());
        header.sequeceId = ntohl(buf.read<uint32_t>());
        buf.reset();


        /// skip heartbeat reply
        if (header.operation == OperatorType::WS_OP_HEARTBEAT_REPLY) {
            return {};
        }


        /// parse data
        std::vector<std::string> result;
        for (std::size_t i = OperatorType::WS_PACKAGE_OFFSET,
                     packageSize = 0,
                     headerSize = 0; i < DataToParse.size(); i += packageSize) {
            packageSize = ntohl(buf.read<uint32_t>());
            headerSize = ntohs(buf.read<uint16_t>());
            buf.moveTo(i + headerSize);


            if (header.protocalVersion == OperatorType::WS_BODY_PROTOCOL_VERSION_NORMAL) {
                /// get body
                std::vector<uint8_t> body(packageSize - headerSize, '\0');
                buf.read(body.data(), packageSize - headerSize);


                /// insert to result
                result.emplace_back(body.begin(), body.end());
            } else if (header.protocalVersion == OperatorType::WS_BODY_PROTOCOL_VERSION_BROTLI) {
                /// get body
                std::vector<uint8_t> body(packageSize - headerSize, '\0');
                buf.read(body.data(), packageSize - headerSize);


                /// decode
                auto decodeResult = brotli_decode(body);
                if (!decodeResult) {
                    return std::unexpected("brotli decode failed");
                }


                /// parse again
                auto parseResult = parse(decodeResult.value());
                if (!parseResult) {
                    return std::unexpected("parse failed");
                }


                /// append to result
                result.insert(result.end(), parseResult.value().begin(), parseResult.value().end());
            }
        }
        return result;
    }
}

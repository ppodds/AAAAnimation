#pragma once
extern "C" {
#include <libavformat/avformat.h>
}

class StreamWrapper
{
public:
	StreamWrapper();
	~StreamWrapper();
	StreamWrapper(AVStream* stream, AVCodecParameters* codec_par);
	void load_codec_context();
	AVCodecContext* get_codec_context();
	AVStream* get_stream();
private:
	AVStream* stream;
	AVCodecParameters* codec_par;
	AVCodec* codec;
	AVCodecContext* codec_context;
};

#include "stream_wrapper.h"
#include <exception>

StreamWrapper::StreamWrapper() {

}
StreamWrapper::StreamWrapper(AVStream* stream, AVCodecParameters* codec_par) {
	this->stream = stream;
	this->codec_par = codec_par;
	codec = avcodec_find_decoder(codec_par->codec_id);
	if (!codec)
		throw std::exception("Unsupported video codec!");
	codec_context = nullptr;
}
void StreamWrapper::load_codec_context() {
	codec_context = avcodec_alloc_context3(codec);
	if (!codec_context)
		throw std::exception("Failed to allocated memory for AVCodecContext.");
	if (avcodec_parameters_to_context(codec_context, codec_par) < 0)
		throw std::exception("Failed to copy codec params to codec context.");
	if (avcodec_open2(codec_context, codec, nullptr) < 0)
		throw std::exception("Encounter error while trying open context.");
}

AVCodecContext* StreamWrapper::get_codec_context()
{
	return codec_context;
}

AVStream* StreamWrapper::get_stream()
{
	return stream;
}

#ifndef ILLA_TYPES_H
#define ILLA_TYPES_H

#include "orz/exception.h"
#include <cstdint>

namespace Err {
	struct CodecError:public std::runtime_error {
		CodecError(const std::string& msg):std::runtime_error("Codec error: " + msg) {}
	};

	struct InvalidHeader:public CodecError {
		InvalidHeader(const std::string& msg):CodecError("InvalidHeader: " + msg) {}
	};
}

namespace Img {
	enum class Format {
		Undefined,
		ARGB8888,
		XRGB8888,
		ARGB1555,
		XRGB1555,
		RGB565,
		Index8,
		Num
	};

	uint8_t EstimatePixelSize(Format sf);
	bool HasAlpha(Format sf);
}

std::string ToAString(const Img::Format& imgFormat);
namespace Img
{
	std::basic_ostream<char>& operator<<(std::basic_ostream<char>& in, const Img::Format& fmt);
}

#include "color.h"
#include "color_conv.h"
#include "filter_buffer.h"
#include "orz/geom.h"
#include "palette.h"


namespace Filter {
	enum class Mode {
		Undefined = 255,
		DirectCopy = 0,
		NearestNeighbor,
		Bilinear,
		Lanczos3,
		Num
	};

	enum class RotationAngle {
		RotateDefault,
		FlipX,
		FlipY,
		Rotate90,
		Rotate90FlipY,
		Rotate180,
		Rotate270,
		Rotate270FlipY,
		RotateUndefined
	};

	Geom::SizeInt CalculateUnzoomedSize(Geom::SizeInt defaultDims, Filter::RotationAngle angle);
	std::basic_ostream<char>& operator<<(std::basic_ostream<char>& in, const Filter::Mode& m);
}

std::string ToAString(const Filter::RotationAngle& angle);
std::basic_ostream<char>& operator<<(std::basic_ostream<char>& in, const Filter::RotationAngle& c);

namespace Img {
	Filter::RotationAngle RotateLeft(Filter::RotationAngle in);
	Filter::RotationAngle RotateRight(Filter::RotationAngle in);

	struct Properties {
		int						Brightness;
		int						Contrast;
		int						Gamma;
		Filter::Mode			ResampleFilter;
		bool					RetainAlpha;
		Img::Color				BackgroundColor;
		float					Zoom;
		Filter::RotationAngle	RequestedAngle;
		Filter::RotationAngle	MetaAngle;

		Filter::RotationAngle FinalAngle() const;

		Properties();
	};
}

#endif
